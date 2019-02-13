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

	} // en
	
} // ari
