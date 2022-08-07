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

#include <string>
#include <fstream>
#include "FileHandler.h"

int CreateShaderObjectFromFile(std::string const& pathToFile, GLenum typeOfShader) {
	unsigned int shaderObject;

	// Creating shader object.
	shaderObject = glCreateShader(typeOfShader);

	// Attach shader source code to the shader object.
	std::string data = ReadTextFromFile(pathToFile);
	const char* fData = data.c_str();
	glShaderSource(shaderObject, 1, &fData, NULL);

	std::cout << "SRC::SHADER::" << typeOfShader << "::COMPILATION_SOURCE\n" << data << "\n";

	// Compiling shader object.
	glCompileShader(shaderObject);

	// Checking if compiling of shader object is successful.
	int success; // Integer to indicate success.
	char infoLog[512]; // Storage container for the error messages.
	glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::" << typeOfShader << "::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	else {
		std::cout << "SUCCESS::SHADER::" << typeOfShader << "::COMPILATION_SUCCESS\n" << std::endl;
		return shaderObject;
	}
}

int main(void) {

	Window* pWindow;
	pWindow = new Window();

	pWindow->Initialize();

	std::cout << CreateShaderObjectFromFile("Shaders\\shader.vert", GL_VERTEX_SHADER);

	// ########## RENDER LOOOP ########
	while (!pWindow->isWindowClosed()) {
		
		// Checking if any event happend.
		pWindow->PollEvents();

		// Clearing previous scene.
		pWindow->ClearColorBuffer();


		float vertices[] = {
			-0.5f, -0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f
		};

		unsigned int VBO;

		// Generating the buffer.
		glGenBuffers(1, &VBO);

		// Binding newly created buffer to the GL_ARRAY_BUFFER.
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		// Copying the previously defined vertex data into the buffer's memory.
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		
		/*
			glBufferData(target, size, data, usage);
			Is a function specifically targeted to copy user-defined data into currently bound buffer.
			Its first argument is the type of the buffer we want to copy data into: the vertex buffer object is currently bound to GL_ARRAY_BUFFER.
			The second argument specifieds the size of the data (in bytes) we want to pass to the buffer; a simple sizeof of the vertex data suffices.
			The third parameter is the actual data we want to send.
			The fourth parameter specifies how we want the graphics card to manage the given data. This can take 3 forms:
				- GL_STREAM_DRAW: The data is set only once and used by the GPU at most a few times.
				- GL_STATIC_DRAW: The data is set only once and used many times.
				- GL_DYNAMIC_DRAW: The data is changed a lot and used many times.
		*/



		// Swapping color buffer.
		pWindow->SwapBuffers();

		if (pWindow->isKeyPressed(GLFW_KEY_ESCAPE))
			pWindow->Close();
	}
	
	// Free resources taken by GLFW.
	pWindow->Deinitialize();

	return 0;
}