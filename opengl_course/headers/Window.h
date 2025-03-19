#pragma once
#include <iostream>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
private:
	GLFWwindow* window = nullptr;
	int width, height;
	const char* title = nullptr;
public:
	Window(uint32_t s_width , uint32_t s_height , const char* title, uint8_t major, uint8_t minor);
	GLFWwindow* mxGetWindow();
	void mxSwapBuffer();
	void mxPollEvents();
	bool mxShouldClose();
	~Window();

};

