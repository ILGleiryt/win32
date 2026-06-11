#include "Window.h"
#include <gl/GL.h> // use directx instead for easy development
#include <iostream>
#pragma comment(lib, "opengl32.lib")

int main()
{
	try {
		Window wnd(L"MyWindow", 800, 600);

		int exitCode = wnd.GameLoop();

		std::cout << "Window closed. Exit code: " << exitCode << std::endl;
		return exitCode;

	}
	catch (const std::exception& e) {
		// Если окно не создалось (исключение в конструкторе)
		MessageBoxA(nullptr, e.what(), "Fatal Error", MB_ICONERROR);
		return 1;
	}
}