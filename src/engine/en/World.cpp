#include "World.hpp"

namespace ari
{
	namespace en
	{
		Entity World::CreateEntity()
		{
			return m_eNextEntityId++;
		}	

	} // en
	
} // ari
