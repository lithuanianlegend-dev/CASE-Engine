#include "pch.h"
#include "Engine.h"

namespace CASE {
	
	Engine::Engine() : run(true), window(NULL), video_width(SCREEN_WIDTH), video_height(SCREEN_HEIGHT) {
		
		// initialize everything with our versions
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// making sure we follow the monitor's color scheme and stuff
		auto& monitor = *glfwGetVideoMode(glfwGetPrimaryMonitor());

		glfwWindowHint(GLFW_RED_BITS, monitor.redBits);
		glfwWindowHint(GLFW_BLUE_BITS, monitor.blueBits);
		glfwWindowHint(GLFW_GREEN_BITS, monitor.greenBits);
	
		// create the actual window
		window = glfwCreateWindow(video_width, video_height, "CASE Engine", NULL, NULL);
		assert(window && "ERROR: Failed to create window!");
		glfwMakeContextCurrent(window);

		// check if GLAD has loaded in
		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
			std::cout << "ERROR: Failed to initialize glad!" << std::endl;
		}

		// make the icon
		GLFWimage icon[1];
		icon[0].pixels = stbi_load("res/icons/icon.png", &icon[0].width, &icon[0].height, 0, 4);
		glfwSetWindowIcon(window, 1, icon);
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