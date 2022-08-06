#include "Window.h"

// Create window with specified params.
Window::Window(int width, int height, const std::string& title)
{
	this->width = width;
	this->height = height;
	this->title = title;
}

// Default constructor.
Window::Window()
{
	this->width = 800;
	this->height = 600;
	this->title = std::string("OpenGL Application");
}

// Destructor.
Window::~Window()
{
	// Free all resources.
	this->Deinitialize();
}

// Check if window is initialized.
int Window::isInitialized()
{
	return this->initialized;
}

// Get width of window/ viewport.
int Window::getWitdh()
{
	return this->width;
}

// Get height of window/ viewport.
int Window::getHeight()
{
	return this->height;
}

// Check if window is closed.
int Window::isWindowClosed()
{
	return glfwWindowShouldClose(this->pWindow);
}

// Get title of window.
const std::string& Window::getTitle()
{
	return this->title;
}

// Swap buffers (front with back) - double buffering.
void Window::SwapBuffers()
{
	// Checking if object is initialized -> GLEW, GLFW and GLFWWindow is correctly initialized.
	if (this->initialized)
	{
		// Swap front with back.
		glfwSwapBuffers(this->pWindow);
	}
}

// Check events if any happened.
void Window::PollEvents()
{
	// Checking if object is initialized -> GLEW, GLFW and GLFWWindow is correctly initialized.
	if (this->initialized)
	{
		// Check events if any happened.
		glfwPollEvents();
	}
}

// Free resources that are were by used by GLFW.
void Window::Deinitialize()
{
	if (this->initialized) {
		glfwTerminate();
		this->initialized = 0;
	}
}

// Callback for framebuffer resize operation.
void framebuffer_size_callback(GLFWwindow* pWindow, int widthOfWindow, int heightOfWindow)
{
	// Setting up the new configuration of viewport.
	glViewport(0, 0, widthOfWindow, heightOfWindow);
}

// Initialize GLFW (Window and its associated context) and GLEW.
void Window::Initialize()
{
	// Initlizing GLFW library.
	if (glfwInit() == GLFW_FALSE) {
		std::cout << "Failed to intialize GLFW library" << std::endl;
		this->initialized = 0;
		return;
	}

	// Setting the up the configuration for window.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creating window and its associated context.
	this->pWindow = glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr);

	// Checking if window is correctly created.
	if (this->pWindow == nullptr)
	{
		// Printing the message about failing.
		std::cout << "Failed to created GFLW window and its associated context!" << std::endl;

		// Frees allocated resources by GLFW, terminates the GLFW library.
		glfwTerminate();

		// Exiting the program with error.
		this->initialized = 0;
		return;
	}

	// Setting up the current context for the current thread.
	glfwMakeContextCurrent(this->pWindow);

	// Ensuring that GLEW will use modern techniques for managaing OpenGL functionality.
	glewExperimental = GL_TRUE;

	// Initilizng GLEW library.
	if (glewInit() != GLEW_OK) {
		// Printing message about failing.
		std::cout << "Failed to initilize GLEW library!" << std::endl;

		// Exiting the program with error.
		this->initialized = 0;
		return;
	}

	// Setting up the dimensions of viewport.
	glViewport(0, 0, this->width, this->height);

	// Setting up the framebuffer callback for viewport.
	glfwSetFramebufferSizeCallback(this->pWindow, framebuffer_size_callback);

	this->initialized = 1;
}