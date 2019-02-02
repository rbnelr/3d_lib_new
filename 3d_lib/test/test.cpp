#include "3d_lib/Application.hpp"
using namespace n_3d_lib;

class MyApplication : public Renderer {
	
	void frame () {
		
	}

};

//int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow) {
int main (int argc, char *argv[]) {
	return run_window<MyApplication>() ? 0 : 1;
}
