#pragma once

#include <GLFW/glfw3.h>

namespace CASE {

	// screen width and height
	const int SCREEN_WIDTH(1280);
	const int SCREEN_HEIGHT(780);

	class Engine {
	public:
		Engine(const Engine&) = delete; // make sure we dont create duplicates
		Engine& operator = (const Engine&) = delete; // make sure we dont create duplicates (i wont be referencing this anymore as this is a very common theme for my header files and classes.)
		~Engine();

		// create a reference so we dont have to crowd our App.cpp file with stupid stuff
		static Engine& Ref()
		{
			static Engine reference;
			return reference;
		}

		void Quit();
		void Update();
		void Initialize();

		// pretty cool stuff here
		inline const bool Run() const { return run; }
		inline GLFWwindow& Window() { return *window; }
		inline const float VideoWidth() const { return video_width; }
		inline const float VideoHeight() const { return video_height; }

	private:
		// dont really need this in public so shove it in here.
		Engine();

	private:
		// variabling variables!
		bool run;
		GLFWwindow* window;
		float video_width, video_height;
	};

	// make a reference
	static Engine& Core = Engine::Ref();
}