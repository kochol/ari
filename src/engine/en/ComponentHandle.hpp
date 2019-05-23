#pragma once

#include "ComponentId.hpp"

namespace ari
{
	namespace en
	{
		template<class T>
		class ComponentHandle
		{
		public:
			int					Handle = Oryol::InvalidIndex;
			
			T*					Component = nullptr;

			ComponentId::Enum	Id;

			T* operator->() const
			{
				return Component;
			}

		}; // ComponentHandle
		
	} // en
	
} // ari
