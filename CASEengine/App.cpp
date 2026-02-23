/******************
	CASE ENGINE
******************/

#include "pch.h"
#include "CASE.h"

class TestComp1 : public ECS::BaseComponent {


};

int main() {

	ECS::EntityManager mgr;
	auto id = mgr.AddNewEntity();
	auto id1 = mgr.AddNewEntity();

	std::cout << id << " " << id1 << std::endl;
	mgr.DestroyEntity(id1);

	auto id2 = mgr.AddNewEntity();

	auto typeID1 = ECS::ComponentType<TestComp1>();
	std::cout << id << " " << id1 << " " << id2 << std::endl;


	// INITIALIZE
	CASE::Core.Initialize();
	CASE::Event.Initialize();
	CASE::Timer.Initialize();

	while (CASE::Core.Run()) {
		// MAIN FUNCTIONS
		CASE::Event.Poll();
		CASE::Timer.Tick();
		CASE::Core.Update();
	}

	return EXIT_SUCCESS;
}