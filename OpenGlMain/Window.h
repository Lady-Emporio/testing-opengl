#pragma once
//#include <iostream>
//#define GLEW_STATIC
//#include <GL/glew.h>
//#include <GLFW/glfw3.h>
#include "ALL.h"
class Window
{
public:
	static Window *get();
	static GLFWwindow *w();
	bool isExit();
	void swapBuffers();
	void lookingEvent();
private:
	GLFWwindow* window;
	void initGL_F_W();
	void createWindow();
	void initGL_E_W();
	Window();
	~Window();
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouse_callback(GLFWwindow *window, int button, int action, int mods);

};

