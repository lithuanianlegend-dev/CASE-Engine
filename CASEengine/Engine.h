#pragma once

#include <GLFW/glfw3.h>

namespace CASE {

	const int SCREEN_WIDTH(1280);
	const int SCREEN_HEIGHT(780);

	class Engine {
	public:
		Engine(const Engine&) = delete;
		Engine& operator = (const Engine&) = delete;
		~Engine();

		static Engine& Ref()
		{
			static Engine reference;
			return reference;
		}

		void Quit();
		void Update();
		void Initialize();

		inline const bool Run() const { return run; }
		inline GLFWwindow& Window() { return *window; }
		inline const float VideoWidth() const { return video_width; }
		inline const float VideoHeight() const { return video_height; }

	private:
		Engine();

	private:
		bool run;
		GLFWwindow* window;
		float video_width, video_height;
	};

	static Engine& Core = Engine::Ref();
}