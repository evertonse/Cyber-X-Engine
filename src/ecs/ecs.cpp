#include "ecs.hpp"

namespace cyx {

	Entity::Entity()
		:id(-1) {}

	Entity::Entity(u32 id)
		:id(id) {}

	// @note If loop throught this: DO NOT remove items from this, even indirectly, 
	template<typename C>
	auto Registry::components() ->  const std::vector<C>& {
		return Component<C>::components;
	}
	
	template<typename C>
	auto Registry::component(EntityId e) {
		auto& comp_type_id = Component<C>::id;
		
		assert(comp_type_id && "This compoents Type was never seen before");
		assert(entities[e].componenets_mask[comp_type_id] == true && "This entity does not have this component");
		
		auto& index = entities[e].typeid2index[comp_type_id];
		return Component<C>::components[index];
	}	
	
	// returns true if this entity owns this type
	template<typename C>
	auto Registry::owns(EntityId e) {
		auto& comp_type_id = Component<C>::id;
		
		if (comp_type_id == -1)
			return false;

		auto& comps		   = Component<C>::components;
		auto& entity	   = entities[e];
		if (entity.componenets_mask[comp_type_id] == true)
		{
			assert(
				comps[entities[e].typeid2index[comp_type_id]].owner == e &&
				"[BUG] If you actually own this piece of data, you should be the owner"
			);
			return true;
		}
		return false;
	}
	
	template<typename C> inline
	auto Registry::owner(C comp) -> EntityId{
		return comp.owner;
	}

	inline EntityId Registry::next_component_id() { return components_type_count++;}
	inline EntityId Registry::next_entity_id() { return (EntityId)entities.size();}
	
	auto Registry::valid(EntityId e) const -> bool {
		return entities[e].id != -1;
	}


	template<typename C>
	auto Registry::add(EntityId e, C comp) {
		static_assert(std::derived_from<C, Component<C>> == true);
		assert(!owns<C>(e) && "An Entity can only hold one type of component at a time");

		auto& comp_type_id = Component<C>::id;
		if (comp_type_id == -1)
			Component<C>::id = next_component_id();

		entities[e].componenets_mask[comp_type_id] = true;
		comp.owner = e;
		Component<C>::components.push_back(std::move(comp));

		// set the offset to easily find the component for this entity;
		entities[e].typeid2index[comp_type_id] = Component<C>::components.size() - 1;
	}

	template<typename C, typename... Args>
	auto Registry::emplace(const EntityId  e, Args &&...args) {
		assert(valid(e) && "Invalid entity");
		assert(!owns<C>(e) && "An Entity can only hold one type of component at a time");

		auto& comp_type_id = Component<C>::id;
		if (comp_type_id == -1)
			Component<C>::id = next_component_id();

		entities[e].componenets_mask[comp_type_id] = true;
		auto& comp = Component<C>::components.emplace(e, std::forward<Args>(args)...);
		comp.owner = e;

		// set the offset to easily find the component for this entity;
		entities[e].typeid2index[comp_type_id] = Component<C>::components.size() - 1;
	}
	/**
	 * @brief remove a component from an entity.
	 *
	 *
	 * @sa remove
	 * @tparam C, is a data-only component
	 * @param entity A valid identifier.
	 * @return true always, just like me =P
	 */
	template<typename C>
	auto Registry::remove(EntityId e) -> bool {
		static_assert(std::derived_from<C, Component<C>> == true);

		auto& comp_type_id = Component<C>::id;

		auto& comps  = Component<C>::components;
	
		auto& curr_entity		= entities[e];
		auto  curr_comp_index	= curr_entity.typeid2index[comp_type_id];
		auto& curr_comp			= comps[curr_comp_index];

		auto& last_entity		= entities[comps.back().owner];
		auto  last_comp_index	= comps.size()-1;
		auto& last_comp			= comps.back();

		assert(valid(e) && "Cant remove component from invalid entity");
		assert(curr_entity.componenets_mask[comp_type_id] == true && "Entity doenst have this componente");
		assert(comps.size() != 1 && "");
	
		// copies last component into the currnent component slot (essentially current gets erased)
		curr_comp = last_comp;
		comps.pop_back();
	
		// Set flag to indicate that this entity doesnt have doesnt own this type of componente anymore
		curr_entity.componenets_mask[comp_type_id] = false;
		// invalidate index to any component of this type
		curr_entity.typeid2index[comp_type_id] = -1;

		// adjust the index position of the previously last component owner to be this new index;
		last_entity.typeid2index[comp_type_id] = curr_comp_index;
		assert(last_entity.componenets_mask[comp_type_id] == true);
		return true;
	}

		template<typename Function>
		auto Registry::each(Function fn) const -> void {
			// if no entites is on the freelist, then we can iterate freely
			if (freelist.empty()) {
				for (auto& e : entities) {
					fn(EntityId{ e.id });
				}
			}
			else {
				for (auto& e : entities) {
					if (valid(e.id))
						fn(EntityId{ e.id });
				}
			}
		}


		auto Registry::create() -> EntityId {
			u32 nextid;
			// if no id is free, create another one, this block should be continuous
			if (freelist.empty()) {
				nextid = entities.size();
				entities.emplace_back();
			}
			// there's is available indexes (aka. EntityId) to use
			else {
				// get next index
				nextid = freelist.back();
				// remove from freelist
				freelist.pop_back();
			}

			// ative [e] = true;
			entities[nextid].id = nextid;
			return nextid;
		};

		auto Registry::destroy(EntityId entity) -> bool {
			auto& id = entity;

			assert(valid(entity) && "This Entity must be a valid entity");
	
			// add removed entity to the freelist in order to be utilizied later
			freelist.push_back(EntityId{id});

			// TODO(Everton): invalidade all components for this entity
			entities[id].id = -1;
			assert(valid(entity) == false && "This Entity should have been  invalidated right now");

			return true;
		}
};