
#include "Window.h"

	// Constructor: Initializes GLFW and creates a window
	Window::Window(uint32_t s_width, uint32_t s_height, const char* s_title, uint8_t major, uint8_t minor)
		: width(s_width), height(s_height), title(s_title), window(nullptr)
	{
		// Initialize GLFW
		if (!glfwInit()) {
			std::cerr << "[ERROR] GLFW initialization failed!" << std::endl;
			return;
		}

		// Set OpenGL version and core profile
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, major);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minor);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create the window
		window = glfwCreateWindow(s_width, s_height, s_title, nullptr, nullptr);
		if (!window) {
			std::cerr << "[ERROR] Failed to create GLFW window!" << std::endl;
			glfwTerminate();
			return;
		}

		// Make the window's OpenGL context current
		glfwMakeContextCurrent(window);

		// Initialize GLEW
		glewExperimental = GL_TRUE;  // Enable modern OpenGL features
		if (glewInit() != GLEW_OK) {
			std::cerr << "[ERROR] GLEW initialization failed!" << std::endl;
			glfwDestroyWindow(window);
			glfwTerminate();
			return;
		}

		// Print OpenGL and GLSL versions
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
	}

	// Returns the GLFW window pointer
	GLFWwindow* Window::mxGetWindow() {
		return window;
	}

	// Swaps the front and back buffers
	void Window::mxSwapBuffer() {
		glfwSwapBuffers(window);
	}

	// Polls for window events
	void Window::mxPollEvents() {
		glfwPollEvents();
	}

	// Checks if the window should close
	bool Window::mxShouldClose() {
		return glfwWindowShouldClose(window);
	}

	// Destructor: Destroys window and properly terminates GLFW
	Window::~Window() {
		if (window) {
			glfwDestroyWindow(window);
		}
		glfwTerminate();
	}



