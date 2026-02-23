/******************
	CASE ENGINE
******************/

#include "pch.h"
#include "CASE.h"

int main()
{
	CASE::Core.Initialize();
	CASE::Event.Initialize();
	CASE::Timer.Initialize();

	while (CASE::Core.Run()) {
		CASE::Event.Poll();
		CASE::Timer.Tick();
		CASE::Core.Update();
	}

	return EXIT_SUCCESS;
}