#pragma once

#include "Entity.hpp"

namespace ari
{
	namespace en
	{
		struct World
		{
			//! Creates a new entity
			Entity CreateEntity();

			//=========================================================================
			// Members
			//=========================================================================
			Entity	m_eNextEntityId = 0;

		};
		
	} // en
	
} // ari
