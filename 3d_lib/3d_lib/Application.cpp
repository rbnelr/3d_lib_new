#include "Application.hpp"

#define GLFW_EXPOSE_NATIVE_WIN32 1
#include "deps/glfw/include/GLFW/glfw3native.h"

#include "windows.h"

namespace n_3d_lib {
	struct RectI {
		iv2	low;
		iv2	high;

		inline iv2 get_size () {
			return high -low;
		}
	};

	RectI to_rect (RECT win32_rect) {
		return {	iv2(win32_rect.left,	win32_rect.top),
			iv2(win32_rect.right,	win32_rect.bottom) };
	}
	
	void glfw_error_proc (int err, cstr msg) {
		logerr("GLFW Error! 0x%x '%s'\n", err, msg);
	}

	class Window {
	public:

		GLFWwindow* glfw_wnd; // read from both threads

		threadsafe_queue<Input_Message>		input_queue;
		threadsafe_queue<Window_Command>	cmd_queue;

		void send_command (Window_Command::type_e cmd) {
			cmd_queue.push({ cmd });
			PostMessageA(glfwGetWin32Window(glfw_wnd), WM_USER, 0,0); // wake up window thread (glfwWaitMessage can oly be woken up by a window message, since it does not wait on our queue)
		}

		~Window () { // at this point the renderer thread is stopped
			save_window_positioning();
			
			if (glfw_wnd)
				glfwDestroyWindow(glfw_wnd);

			glfwTerminate();
		}

	private:
		friend unique_ptr<Window, WindowDeleter> open_window (cstr title, iv2 def_size, e_vsync_mode def_vsync_mode);
		friend void run_window_loop (Renderer* renderer);

		WINDOWPLACEMENT		win32_windowplacement = {}; // Zeroed

		void get_win32_windowplacement () {
			GetWindowPlacement(glfwGetWin32Window(glfw_wnd), &win32_windowplacement);
		}
		void set_win32_windowplacement () {
			SetWindowPlacement(glfwGetWin32Window(glfw_wnd), &win32_windowplacement);
		}

		static constexpr cstr window_placement_file = TO_STRING(APP_NAME) "_window_placement.bin";

		void save_window_positioning () {

			//if (is_fullscreen) {
			//	// keep window positioning that we got when we switched to fullscreen
			//} else {
				get_win32_windowplacement();
			//}

			if (!write_fixed_size_binary_file(window_placement_file, &win32_windowplacement, sizeof(win32_windowplacement))) {
				logerr("Could not save window_placement to %s, window position and size won't be restored on the next launch of this app.", window_placement_file);
			}
		}
		bool load_window_positioning () {
			return load_fixed_size_binary_file(window_placement_file, &win32_windowplacement, sizeof(win32_windowplacement));
		}

		static unique_ptr<Window, WindowDeleter> open (cstr title, iv2 def_size, e_vsync_mode def_vsync_mode) {

			glfwSetErrorCallback(glfw_error_proc);

			if (glfwInit() == 0) // do not support multiple windows at the moment, so just init glfw together with window
				return nullptr; // GLFW error

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_SRGB_CAPABLE, GLFW_TRUE);

			#if !defined(NDEBUG)
			glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
			#endif

			auto wnd = unique_ptr<Window, WindowDeleter>(new Window());
			bool placement_loaded = wnd->load_window_positioning();

			iv2 size = placement_loaded ? to_rect(wnd->win32_windowplacement.rcNormalPosition).get_size() : def_size;

			auto* glfw_wnd = glfwCreateWindow(size.x, size.y, title, NULL, NULL);

			wnd->glfw_wnd = glfw_wnd;
			if (!wnd->glfw_wnd)
				return nullptr; // GLFW error

			if (placement_loaded) {
				wnd->set_win32_windowplacement();
			}

			glfwSetWindowUserPointer(wnd->glfw_wnd, wnd.get());

			return wnd;
		}

		void loop () {
			
			bool wnd_is_open = true;

			while (wnd_is_open) {

				glfwWaitEvents();

				if (glfwWindowShouldClose(glfw_wnd)) {
					input_queue.push({ Input_Message::WANT_CLOSE_WINDOW });

					glfwSetWindowShouldClose(glfw_wnd, false); // let input thread decide, do this to stop seding WANT_CLOSE_WINDOW messages
				}

				std::vector<Window_Command> cmds;

				if (cmd_queue.try_pop_n(&cmds)) {
					for (auto& cmd : cmds) {
						
						switch (cmd.type) {
							case Window_Command::CLOSE_WINDOW: {
								wnd_is_open = false;
							} break;
						}
					}
				}
			}

		}
	};

	unique_ptr<Window, WindowDeleter> open_window (cstr title, iv2 def_size, e_vsync_mode def_vsync_mode) { // wrapper, so i don't need to put the definition of Window in to the header
		return Window::open(title, def_size, def_vsync_mode);
	}
	void run_window_loop (Renderer* renderer) {
		renderer->window->loop();
	}

	void WindowDeleter::operator() (Window* p) {
		delete p;
	}

	void Renderer::poll_input () {
		std::vector<Input_Message> msgs;

		if (window->input_queue.try_pop_n(&msgs)) {
			for (auto& msg : msgs) {

				switch (msg.type) {
					case Input_Message::WANT_CLOSE_WINDOW: {
						input.want_close_window = true;
					} break;
				}
			}
		}

		if (input.want_close_window)
			input.do_close_window = true; // user can override this, if user ignores this close window
	}
	void Renderer::loop () {

		glfwMakeContextCurrent(window->glfw_wnd);
		
		for (uptr frame_i=0; frame_i<500; ++frame_i) {
			
			poll_input();
			
			frame();

			glfwSwapBuffers(window->glfw_wnd);

			if (input.do_close_window)
				break;
		}
		
		window->send_command(Window_Command::CLOSE_WINDOW);
	}
}
