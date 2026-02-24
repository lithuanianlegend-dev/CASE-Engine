#pragma once

#include "Types.h"

namespace ECS {
	struct BaseComponent {
		BaseComponent() { entityID = 0; }
		virtual ~BaseComponent() {}
		inline const EntityID GetID() const { return entityID; }

	private:
		friend class EntityManager;
		EntityID entityID;
	};


}