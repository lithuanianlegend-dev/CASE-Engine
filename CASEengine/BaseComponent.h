#pragma once

#include "Types.h"

namespace ECS {
	struct BaseComponent {
		BaseComponent() { entityId = 0; }
		virtual ~BaseComponent() {}
		inline const EntityID GetID() const { return entityId; }

	private:
		friend class EntityManager;
		EntityID entityId;
	};


}