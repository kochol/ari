#pragma once

namespace ari
{
	namespace en
	{
		template<class T>
		class ComponentHandle
		{
		public:
			int	Index;
			
			T*	Component;

			T* operator->() const
			{
				return Component;
			}

		}; // ComponentHandle
		
	} // en
	
} // ari
