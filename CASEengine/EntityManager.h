#pragma once

#include "Types.h"
#include "BaseSystem.h"
#include "ComponentList.h"
#include "BaseComponent.h"

namespace ECS {
	class EntityManager {
		
	public:
		EntityManager() : entityCount(0) {
			for (EntityID entity = 0u; entity < MAX_ENTITIES; entity++) {
				availableEntities.push(entity);
			}
		}

		~EntityManager() {
		
		}
		
		void Update() {
			for (auto& system : registeredSystems) {
				system.second->Update();
			}
		}

		void Render() {
			for (auto& system : registeredSystems) {
				system.second->Render();
			}
		}

		const EntityID AddNewEntity() {
			const EntityID entityID = availableEntities.front();
			AddEntitySignature(entityID);
			availableEntities.pop();
			entityCount++;
			return entityID;
		}

		void DestroyEntity(const EntityID entity) {
			assert(entity < MAX_ENTITIES && "ERROR: Entity count out of range!");
			entitySignatures.erase(entity);

			for (auto& array : componentArrays) {
				array.second->Erase(entity);
			}

			for (auto& system : registeredSystems) {
				system.second->RemoveEntity(entity);
			}

			entityCount--;
			availableEntities.push(entity);
		}

		template<typename T, typename... Args>
		void AddComponent(const EntityID entity, Args&&... args) {
			assert(entity < MAX_ENTITIES && "ERROR: EntityID out of range!");
			assert(entitySignatures[entity].size() < MAX_COMPONENT_COUNT && "ERROR: Component limit reached!");

			T component(std::forward<Args>(args)...);
			component.entityID = entity;
			GetEntitySignature(entity).insert(ComponentType<T>());
			GetCompList<T>()->Insert(component);
			UpdateEntityTargetSystems(entity);
		}

		template<typename T>
		void RemoveComponent(const EntityID entity) {
			assert(entity < MAX_ENTITIES && "ERROR: EntityID out of range!");
			const ComponentTypeID compType = ComponentType<T>();
			entitySignatures.at(entity).erase(compType);
			GetCompList<T>()->Erase(entity);
			UpdateEntityTargetSystems(entity);
		}

		template<typename T, typename>
		T& GetComponent(const EntityID entity) {
			assert(entity < MAX_ENTITIES && "ERROR: EntityID out of range!");
			return GetCompList<T>()->Get(entity);
		}

		template<typename T>
		const bool HasComponent(const EntityID entity) {
			assert(entity < MAX_ENTITIES && "ERROR: EntityID out of range!");
			const EntitySignature signature = entitySignatures.at(entity);
			const ComponentTypeID compType = ComponentType<T>();
			return (signature.count(compType) > 0);
		}

		// ----------------------------------------------------------------

		template<typename T>
		void RegisterSystem() {
			const SystemTypeID systemType = SystemType<T>();
			assert(registeredSystems.count(systemType) == 0 && "ERROR: System already registered!");
			auto system = std::make_unique<T>();

			// add the entity to the new system!!!1 :D
			T* systemPtr = system.get();
			for (EntityID entity = 0; entity < entityCount; entity++) {
				AddEntityToSystem(entity, systemPtr);
			}

			system->Start();
			registeredSystems[systemType] = std::move(system);
		}

		template<typename T>
		void UnRegisterSystem() {
			const SystemTypeID systemType = SystemType<T>();
			assert(registeredSystems.count(systemType) != 0 && "ERROR: System not registered!");
			registeredSystems.erase(systemType);
		}
			

	private:
		template<typename T>
		void AddCompList() {
			const ComponentTypeID compType = ComponentType<T>();
			assert(componentArrays.find(compType) == componentArrays.end() && "ERROR: Component list already registered!");
			componentArrays[compType] = std::move(std::make_shared<CompList<T>>());
		}

		template<typename T>
		std::shared_ptr<CompList<T>> GetCompList() {
			const ComponentTypeID compType = ComponentType<T>();
			if (componentArrays.count(compType) == 0) { AddCompList<T>(); }
			return std::static_pointer_cast<CompList<T>>(componentArrays.at(compType));
		}

		void AddEntitySignature(const EntityID entity) {
			assert(entitySignatures.find(entity) == entitySignatures.end() && "ERROR: Signature already exists!");
			entitySignatures[entity] = EntitySignature();
		}

		EntitySignature& GetEntitySignature(const EntityID entity) {
			assert(entitySignatures.find(entity) != entitySignatures.end() && "ERROR: Signature not found!");
			return entitySignatures.at(entity);
		}

		void UpdateEntityTargetSystems(const EntityID entity) {
			for (auto& system : registeredSystems) {
				AddEntityToSystem(entity, system.second.get());
			}
		}

		void AddEntityToSystem(const EntityID entity, BaseSystem* system) {
			if (BelongToSystem(entity, system->signature)) {
				system->entities.insert(entity);
			}
			else
			{
				system->entities.erase(entity);
			}
		}

		bool BelongToSystem(const EntityID entity, const EntitySignature& system_signature) {
			for (const auto compType : system_signature) {
				if (GetEntitySignature(entity).count(compType) == 0) {
					return false;
				}
			}
			return true;
		}

		EntityID entityCount;
		std::queue<EntityID> availableEntities;
		std::map<EntityID, EntitySignature> entitySignatures;
		std::map <SystemTypeID, std::unique_ptr<BaseSystem>> registeredSystems;
		std::map<ComponentTypeID, std::shared_ptr<ICompList>> componentArrays;
	};
}