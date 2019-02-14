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
			Oryol::Array<EntityComponent>& arr = m_mEntityComponents[_id];
			for(int i = 0; i < arr.Size(); i++)
			{
				if (arr[i].entity == _entity)
				{
					arr.EraseSwap(i);
					return;
				}
			}
		}

	} // en
	
} // ari
