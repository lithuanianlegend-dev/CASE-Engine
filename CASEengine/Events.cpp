#include "pch.h"
#include "Events.h"
#include "Engine.h"

namespace CASE {

	void WindowCloseCallBack(GLFWwindow* window);

	Events::Events()
	{
	
	}

	Events::~Events()
	{
	
	}

	void Events::Poll()
	{
		// poll stuff like input.
		glfwPollEvents();
	}

	void Events::Initialize()
	{
		// make window and and set our window close callback
		GLFWwindow& window = Core.Window();
		glfwSetWindowCloseCallback(&window, WindowCloseCallBack);
	}

	void WindowCloseCallBack(GLFWwindow* window)
	{
		// quit if we close the window (quit if we quit!)
		Core.Quit();
	}
}