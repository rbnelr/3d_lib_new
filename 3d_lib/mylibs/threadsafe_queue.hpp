#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

// with help from https://stackoverflow.com/questions/15278343/c11-thread-safe-queue

template <typename T>
class threadsafe_queue {
public:
	// push one element onto the queue
	// can be called from multiple threads (multiple producer)
	inline void push (T elem) {
		std::lock_guard<std::mutex> lock(m);
		q.emplace( std::move(elem) );
		c.notify_one();
	}

	// push n elements onto the queue
	// can be called from multiple threads (multiple producer)
	inline void push_n (std::vector<T> elems) {
		std::lock_guard<std::mutex> lock(m);
		for (auto& elem : elems)
			q.emplace( std::move(elem) );
		c.notify_one();
	}

	// deque one element from the queue or wait if there are none
	// can be called from multiple threads (multiple consumer)
	inline T pop () {
		std::unique_lock<std::mutex> lock(m);
		
		while(q.empty()) {
			c.wait(lock); // release lock as long as the wait and reaquire it afterwards.
		}
		
		T val = std::move(q.front());
		q.pop();
		return val;
	}

	// deque one or multiple elements from the queue or wait if there are none
	// can be called from multiple threads (multiple consumer)
	inline void pop_n (std::vector<T>* elems) {
		std::unique_lock<std::mutex> lock(m);

		while(q.empty()) {
			c.wait(lock); // release lock as long as the wait and reaquire it afterwards.
		}

		while (!q.empty()) {
			elems->emplace_back( std::move(q.front()) );
			q.pop();
		}
	}

	// deque one element from the queue if there is one
	// can be called from multiple threads (multiple consumer)
	inline bool try_pop (T* elem) {
		std::lock_guard<std::mutex> lock(m);
		
		if (q.empty())
			return false;

		*elem = std::move(q.front());
		q.pop();

		return true;
	}

	// deque n elements from the queue if there is one
	// can be called from multiple threads (multiple consumer)
	inline bool try_pop_n (std::vector<T>* elems) {
		std::lock_guard<std::mutex> lock(m);

		if (q.empty())
			return false;

		while (!q.empty()) {
			elems->emplace_back( std::move(q.front()) );
			q.pop();
		}

		return true;
	}

private:
	std::queue<T> q;
	mutable std::mutex m;
	std::condition_variable c;
};
