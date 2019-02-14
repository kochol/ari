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
			int					Handle;
			
			T*					Component;

			ComponentId::Enum	Id;

			T* operator->() const
			{
				return Component;
			}

		}; // ComponentHandle
		
	} // en
	
} // ari
