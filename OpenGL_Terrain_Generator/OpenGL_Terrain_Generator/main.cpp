#include <iostream>
#define GLEW_STATIC

#ifndef GLEW_HEADER_INCLUDED
#define GLEW_HEADER_INCLUDED
#include "glew.h"
#endif // !GLEW_HEADER_INCLUDED

#ifndef GLFW_HEADER_INCLUDED
#define GLFW_HEADER_INCLUDED
#include "glfw3.h"
#endif // !GLFW_HEADER_INCLUDED
#include "Window.h"


int main(void) {

	Window* pWindow;
	pWindow = new Window();
	
	pWindow->Initialize();

	// ########## RENDER LOOOP ########
	while (!pWindow->isWindowClosed()) {
		
		// Checking if any event happend.
		pWindow->PollEvents();

		// Swapping color buffer.
		pWindow->SwapBuffers();
	}
	
	// Free resources taken by GLFW.
	pWindow->Deinitialize();

	return 0;
}