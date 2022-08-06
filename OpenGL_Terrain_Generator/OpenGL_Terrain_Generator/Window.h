#pragma once
#include <string>

#ifndef GLEW_HEADER_INCLUDED
#define GLEW_HEADER_INCLUDED
#define GLEW_STATIC
#include "glew.h"
#endif // !GLEW_HEADER_INCLUDED

#ifndef GLFW_HEADER_INCLUDED
#define GLFW_HEADER_INCLUDED
#include "glfw3.h"
#endif // !GLFW_HEADER_INCLUDED

#ifndef IOSTREAM_INCLUDED
#define IOSTREAM_INCLUDED
#include <iostream>
#endif // !IOSTREAM_INCLUDED

class Window
{
private:
	int width; // Width of GLFW window and viewport.
	int height; // Height of GLFW window and viewport.
	int initialized; // Flag about initializion: 1 - initialized, 0 - not initialized.
	std::string title; // Title of window.
	GLFWwindow* pWindow; // Pointer to the GLFW window.

public:
	// Constructors:
	Window(int width, int height, const std::string& title);
	Window();

	// Desturctors:
	~Window();

	// Proporties:
	int getWitdh();
	int getHeight();
	int isInitialized();
	int isWindowClosed();
	const std::string& getTitle();
	
	// Methods:
	void SwapBuffers(); // Swap buffers (front with back - double buffering).
	void PollEvents();  // Check if any events happened.
	void Initialize();  // Initialize GLFW Window and other things.
	void Deinitialize(); // Free resources.
};

