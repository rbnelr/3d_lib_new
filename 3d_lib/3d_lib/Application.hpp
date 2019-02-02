#pragma once

#include "mylibs/preprocessor_stuff.hpp"
#include "mylibs/vector_math.hpp"
#include "mylibs/float_precision.hpp"
#include "mylibs/threadsafe_queue.hpp"
#include "mylibs/file_io.hpp"

#include "assert.h"
#include <thread>

#pragma push_macro("APIENTRY")
#include "deps/glfw/include/GLFW/glfw3.h"
#pragma pop_macro("APIENTRY")

namespace n_3d_lib {
	using namespace vector_math;
	using namespace float_precision;
	using namespace file_io;
	
	#define logerr(...) fprintf(stderr, __VA_ARGS__)

	enum e_vsync_mode {
		VSYNC_ON,
		VSYNC_OFF,
	};

	struct Time {
		flt max_dt = 1.0f / 20; // slow down time when framerate gets low enough
		flt scale = 1; // to slow down or speed up time

		flt	dt; // delta time of frame (clamped and scaled)
		f64 t; // absolute time since first frame (clamped and scaled)

		flt	unscaled_dt; // delta time of frame (clamped)
		f64 unscaled_t; // absolute time since first frame (clamped)

		flt	real_dt; // delta time of frame (real time)
		f64 real_t; // absolute time since first frame (real time)
	};

	struct Input_Message {
		enum type_e {
			WANT_CLOSE_WINDOW,

		};

		type_e type;
	};
	struct Window_Command {
		enum type_e {
			CLOSE_WINDOW,

		};

		type_e type;

		union {
			
		};
	};

	class Window;
	struct WindowDeleter { // can't have unique_ptr to incomplete type
		void operator() (Window* p);
	};

	struct Input {
		bool want_close_window = false;
		bool do_close_window; // if (want_close_window) ask user if he really wants to close, set do_close_window = false; until user decies, then set do_close_window to desired value and set want_close_window = false;
	};

	class Renderer {
	public:
		
		Input	input;
		Time	time;

		void poll_input ();

		virtual void frame () = 0;

	private:
		template <typename APP_RENDERER> friend bool run_window (cstr title, iv2 def_size, e_vsync_mode def_vsync_mode);
		friend void run_window_loop (Renderer* renderer);

		void loop ();

		unique_ptr<Window, WindowDeleter>	window;
	};

	unique_ptr<Window, WindowDeleter> open_window (cstr title, iv2 def_size, e_vsync_mode def_vsync_mode);

	template <typename APP_RENDERER> // use a template function here so we can construct the user App object after having a opengl context, else any opengl call the user wants to do in the constructor would fail
	bool run_window (cstr title=TO_STRING(APP_NAME), iv2 def_size=iv2(1280,720), e_vsync_mode def_vsync_mode=VSYNC_ON) {
		auto wnd = open_window(title, def_size, def_vsync_mode); // open window and set up opengl context for it

		if (!wnd)
			return false;

		auto renderer = make_unique<APP_RENDERER>();
		renderer->window = std::move(wnd);

		std::thread thr(&Renderer::loop, renderer.get()); // run renderer in different thread

		run_window_loop(renderer.get());

		thr.join();
		
		return true;
	}
}
