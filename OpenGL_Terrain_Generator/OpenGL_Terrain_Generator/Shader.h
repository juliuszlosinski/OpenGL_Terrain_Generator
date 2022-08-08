#pragma once
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

class Shader
{
private:
	int shaderProgram; // Id program.
public:

	// Default constructor;
	Shader();

	// Getting the id of shader program.
	int getShaderProgramId();

	// Start using shader program.
	void UseProgram();

	// Stop using program.
	void StopUsingProgram();

	// Create shader program from shader objects.
	void CreateFromShaderObjects(int vertexShaderObject, int fragmentShaderObject);

	// Create shader program from files.
	void CreateFromFiles(std::string const& pathToVertexShader, std::string const& pathToFragmentShader);

	// Create shader program from strings.
	void CreateFromStrings(std::string const& vertexShaderCode, std::string const& fragmentShaderCode);

	// Creating vertex shader object based on file.
	static int CreateVertexShaderObjectFromFile(std::string const& pathToFile);

	// Creating fragment shader object based on file.
	static int CreateFragmentShaderObjectFromFile(std::string const& pathToFile);

	// Creating vertex shader object based on string.
	static int CreateVertexShaderObjectFromString(std::string const& data);

	// Creating fragment shader object based on string.
	static int CreateFragmentShaderObjectFromString(std::string const& data);

	// Creating shader object based on file.
	static int CreateShaderObjectFromFile(std::string const& pathToFile, GLenum typeOfShader);

	// Creating shader object based on string.
	static int CreateShaderObjectFromString(std::string const& data, GLenum typeOfShader);
};