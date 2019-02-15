#include "World.hpp"

namespace ari
{
	namespace en
	{
		World::World()
		{
			m_aComponentPools.Fill(nullptr);
		}

		Entity World::CreateEntity()
		{
			return m_eNextEntityId++;
		}	

		// Removes a component from an entity
		void World::RemoveComponent(Entity _entity, ComponentId::Enum _id)
		{
			auto m = m_mEntityComponents[_id];
			m.EraseIndex(m.FindIndex(_entity));
		}

	} // en
	
} // ari
