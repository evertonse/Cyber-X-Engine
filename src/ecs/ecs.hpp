#pragma once
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <bitset>
#include <bitset>
#include <unordered_map>
#include <concepts>
#include <cassert>
#include "..\utils\common.h"


#define persistent static
// Max Comoments of a given component type
#define MAX_COMPONENTS 32

#pragma once

namespace cyx {
	using EntityId = i32;
	using ComponentTypeId = i32;

	struct Entity {
		Entity();
		Entity(u32 id);


		//if id == -1 means that the Entity is invalid
		EntityId id;
		// ex: if component[10] == 1 therefore the this Entity has component of wich has ComponenTypeId equals 10
		// : ComponentTypeId -> false
		std::bitset<MAX_COMPONENTS> componenets_mask;
		// : ComponentTypeId -> index: u32
		std::unordered_map<ComponentTypeId, u32> typeid2index;
	};

	//class System {
	//	virtual void on_update(Registry& reg) = 0;
	//};

	template<typename C>
	struct Component {
		friend class Registry;

	private:
		EntityId owner = -1;

		static ComponentTypeId id;
		static std::vector<C> components;
	};

	template<typename C>
	std::vector<C> Component<C>::components{};

	template<typename C>
	ComponentTypeId Component<C>::id = -1;

	// if more than one regestry per application -> BOOM crash everything, templated args can only be generated once
	class Registry {
	public:
		// constructs a naked entity with no components and returns its identifier
		auto create()->EntityId;

		// destroys an entity and all its components
		auto destroy(EntityId e) -> bool;

		// returns true if the entity is still valid, false otherwise
		auto valid(EntityId e) const -> bool;

		template<typename C>
		auto add(EntityId e, C comp);


		template<typename C, typename... Args>
		auto emplace(const EntityId  e, Args &&...args);

		template<typename C>
		auto remove(EntityId e) -> bool;

		// @note If loop throught this: DO NOT remove items from this, even indirectly, 
		template<typename C>
		auto components() ->  const std::vector<C>&;

		template<typename C>
		auto component(EntityId e);

		// returns true if this entity owns this type
		template<typename C>
		auto owns(EntityId e);

		template<typename C> inline
			auto owner(C comp)->EntityId;

		// Iterate through entites
		template<typename Function>
		auto each(Function fn) const -> void;

	private:
		int components_type_count = 0;

	private:
		std::vector<Entity> entities;
		// id is also index
		// TODO:  make the free list a queue
		std::vector<EntityId> freelist;

		// TODO: make a IComponentVector to have access to specific component at runtine

		inline EntityId next_component_id();
		inline EntityId next_entity_id();

	};

}
