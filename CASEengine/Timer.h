#pragma once

namespace CASE {

	class T_Timer {

	public:
		~T_Timer();
		T_Timer(const T_Timer&) = delete;
		T_Timer();

		static T_Timer& Ref()
		{
			static T_Timer reference;
			return reference;
		}

		void Tick();
		void Initialize();
		inline float DeltaTime() { return deltaTime; }

	private:
		float deltaTime, lastFrame;
	};

	static T_Timer& Timer = T_Timer::Ref();
}