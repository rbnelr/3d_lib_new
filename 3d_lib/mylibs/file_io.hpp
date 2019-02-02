#pragma once

#include <string>

#include "stdio.h"

#include "preprocessor_stuff.hpp"
#include "basic_typedefs.hpp"
#include "defer.hpp"

namespace file_io {
	using namespace basic_typedefs;

	bool load_text_file (cstr filepath, std::string* text);

	class Blob {
		MOVE_ONLY_CLASS(Blob)

	public:
		void*	data = nullptr;
		uptr	size = 0;

		//
		static inline Blob alloc (uptr size) {
			Blob b;
			b.data = malloc(size);
			b.size = size;
			return b;
		}

		inline ~Blob () {
			if (data)
				free(data);
		}
	};
	inline void swap (Blob& l, Blob& r) {
		std::swap(l.data, r.data);
		std::swap(l.size, r.size);
	}

	bool load_binary_file (cstr filepath, Blob* blob);

	bool load_fixed_size_binary_file (cstr filepath, void* data, uptr sz);

	bool write_fixed_size_binary_file (cstr filepath, void const* data, uptr sz);

	bool write_text_file (cstr filepath, std::string const& text);
}
