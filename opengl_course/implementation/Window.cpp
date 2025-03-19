#include "Window.h"


Window::Window(uint32_t s_width, uint32_t s_height, const char* s_title, uint8_t major , uint8_t minor) : width(s_width), height(s_height), title(s_title), window(nullptr)
{
	
	//init the glfw
	if (!glfwInit())
	{
		printf("[GLFW]:Glfw can't init");
		return;
	}
	

	//set the opengl major , minor and core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,major);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//making the window
	window = glfwCreateWindow(s_width, s_height, s_title, NULL, NULL);
	if (!window) {
		printf("[WINDOW]:can't create window");
		glfwTerminate();
		return;
	}
	
	//make the window thw current in the opengl
	glfwMakeContextCurrent(window);

	//init glew 
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("[GLEW]:glew  can't init");
		glfwTerminate();
		glfwDestroyWindow(window);
		return;
	}

	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	


}

GLFWwindow* Window::mxGetWindow()
{
	return window;
}

void Window::mxSwapBuffer()
{
	glfwSwapBuffers(window);
}

void Window::mxPollEvents()
{
	glfwPollEvents();
}

bool Window::mxShouldClose()
{
	return glfwWindowShouldClose(window);
}

Window::~Window()
{
	glfwDestroyWindow(window);
	glfwTerminate();
}