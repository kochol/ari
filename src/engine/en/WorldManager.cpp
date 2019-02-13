#include "WorldManager.hpp"
#include "World.hpp"
#include <Core/Memory/Memory.h>

namespace ari
{
	namespace en
	{
		//! Create a new World
		World* WorldManager::CreateWorld()
		{
			return Oryol::Memory::New<World>();
		}

		//! Destroy a world
		void WorldManager::DestroyWorld(World* _world)
		{
			Oryol::Memory::Delete<World>(_world);
		}

	} // en
	
} // ari
