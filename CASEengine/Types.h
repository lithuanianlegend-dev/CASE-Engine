#pragma once

#include "pch.h"

namespace ECS {
	
	class BaseSystem;
	class BaseComponent;

	// constantations things
	const size_t MAX_ENTITIES = 50000;
	const size_t MAX_COMPONENT_COUNT = 32;

	// custom types
	using EntityID = size_t; // just creates an entity (weird look)
	using SystemTypeID = size_t;
	using ComponentTypeID = size_t;
	using EntitySignature = std::set<ComponentTypeID>; // std::set because we dont really want to include two components now do we?

	// returns component runtime id
	inline static const ComponentTypeID GetRuntimeComponentTypeID() {
		static ComponentTypeID typeID = 0u;
		return typeID++;
	}

	// returns system runtime id
	inline static const ComponentTypeID GetRuntimeSystemTypeID() {
		static SystemTypeID typeID = 0u;
		return typeID++;
	}

	template<typename T>
	inline static const ComponentTypeID ComponentType() noexcept {
		// check at compile time if the components thing your getting isnt a parent of Component.
		static_assert(
			std::is_base_of<BaseComponent, T>::value &&
			!std::is_same<BaseComponent, T>::value,
			"ERROR: Invalid template type!"
		);
		static const ComponentTypeID typeID = GetRuntimeComponentTypeID();
		return typeID;
	} 

	// does the exact same except its for systems.
	template<typename T>
	inline static const SystemTypeID SystemType() noexcept {
		static_assert(
			std::is_base_of<BaseSystem, T>::value &&
			!std::is_same<BaseSystem, T>::value,
			"ERROR: Invalid template type!"
		);
		static const SystemTypeID typeID = GetRuntimeSystemTypeID();
		return typeID;
	}

}