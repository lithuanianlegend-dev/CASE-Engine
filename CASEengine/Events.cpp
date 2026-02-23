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
		glfwPollEvents();
	}

	void Events::Initialize()
	{
		GLFWwindow& window = Core.Window();
		glfwSetWindowCloseCallback(&window, WindowCloseCallBack);
	}

	void WindowCloseCallBack(GLFWwindow* window)
	{
		Core.Quit();
	}
}