#pragma once

#include "Entity.hpp"
#include "ComponentId.hpp"
#include "ComponentHandle.hpp"
#include "core/ObjectPool.hpp"

namespace ari
{
	namespace en
	{
		struct World
		{
			//! Constructor
			World();

			//! Creates a new entity
			Entity CreateEntity();

			//! Creates a component from pool
			template<class T>
			ComponentHandle<T> CreateComponent(ComponentId::Enum _id)
			{
				auto pool = GetComponentPool<T>(_id);
				int i = pool->GetFreeIndex();

				return { i, &pool->Pool[i] };
			}

			template<class T>
			core::ObjectPool<T, 1000>* GetComponentPool(ComponentId::Enum _id)
			{
				if (m_aComponentPools[_id] == nullptr)
					m_aComponentPools[_id] = Oryol::Memory::New<core::ObjectPool<T, 1000>>();
				return static_cast<core::ObjectPool<T, 1000>*>(m_aComponentPools[_id]);
			}
			
			//=========================================================================
			// Members
			//=========================================================================
		private:

			Entity	m_eNextEntityId = 0;	
			Oryol::StaticArray<void*, ComponentId::Count>
					m_aComponentPools;

		};
		
	} // en
	
} // ari
