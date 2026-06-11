#include "Window.h"
// use directx instead for easy development
#include <iostream>

int main()
{
	try 
	{
		Window wnd(L"MyWindow", 800, 600);

		int exitCode = wnd.GameLoop();

 // work on doesnt work resize function

		std::cout << "Window closed. Exit code: " << exitCode << std::endl << "Window parameters: Height>> " << wnd.GetHeight() << "Width>> " << wnd.GetWidth() << std::endl;
		return exitCode;
	}
	catch (const std::exception& e) 
	{
		MessageBoxA(nullptr, e.what(), "Fatal Error", MB_ICONERROR);
		return 1;
	}
}