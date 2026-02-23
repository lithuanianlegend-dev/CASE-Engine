#include "pch.h"
#include "Engine.h"

namespace CASE {
	
	Engine::Engine() : run(true), window(NULL), video_width(SCREEN_WIDTH), video_height(SCREEN_HEIGHT) {
		
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		auto& monitor = *glfwGetVideoMode(glfwGetPrimaryMonitor());

		glfwWindowHint(GLFW_RED_BITS, monitor.redBits);
		glfwWindowHint(GLFW_BLUE_BITS, monitor.blueBits);
		glfwWindowHint(GLFW_GREEN_BITS, monitor.greenBits);
	
		window = glfwCreateWindow(video_width, video_height, "CASE", NULL, NULL);
		assert(window && "ERROR: Failed to create window!");
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "ERROR: Failed to initialize glad!" << std::endl;
		}
	}

	Engine::~Engine() {
		glfwTerminate();
	}

	void Engine::Update() {
		
	}

	void Engine::Initialize() {
		
	}

	void Engine::Quit() {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		run = false;
	}


}