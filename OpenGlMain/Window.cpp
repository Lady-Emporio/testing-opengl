#include "Window.h"


Window * Window::get()
{
	static Window  * window = new Window();
	if (window == nullptr) {
		Twilight::Error("Somebody delete window.");
	}
	return window;
}

GLFWwindow * Window::w()
{
	Window *window = Window::get();
	return window->window;
}

void Window::initGL_F_W()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
}

void Window::createWindow()
{
	window = glfwCreateWindow(800, 600, "Main Open Gl", nullptr, nullptr);
	if (window == nullptr)
	{
		Twilight::Error("Failed to create GLFW window");
	}
	glfwMakeContextCurrent(window);
}

void Window::initGL_E_W()
{
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		Twilight::Error("Failed to initialize GLEW.");
	}
}

Window::Window()
{
	initGL_F_W();
	createWindow();
	initGL_E_W();
	glfwSetKeyCallback(this->window, Window::key_callback);
	glfwSetMouseButtonCallback(this->window, Window::mouse_callback);
}

Window::~Window()
{
}


void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
}

void Window::mouse_callback(GLFWwindow * window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_1 && action== GLFW_PRESS){
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		Twilight::log(std::to_string(xpos).c_str());
		Twilight::log(std::to_string(ypos).c_str());
	}


	
}

bool Window::isExit()
{
	return glfwWindowShouldClose(this->window);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(this->window);
}

void Window::lookingEvent()
{
	glfwPollEvents();
}
