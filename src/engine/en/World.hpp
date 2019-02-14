#pragma once

#include "Entity.hpp"
#include "ComponentId.hpp"
#include "ComponentHandle.hpp"
#include "core/ObjectPool.hpp"
#include "Core/Containers/Array.h"
#include "Core/Containers/Map.h"

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
			ComponentHandle<T> CreateComponent(ComponentId::Enum _id);

			template<class T>
			void DestroyComponent(ComponentHandle<T> _cmp);

			//! Add a component to an entity
			template<class T>
			void AddComponent(Entity _entity, ComponentHandle<T> _cmp);

			//! Removes a component from an entity
			void RemoveComponent(Entity _entity, ComponentId::Enum _id);

		private:

			template<class T>
			core::ObjectPool<T, 1000>* GetComponentPool(ComponentId::Enum _id);

			Entity		m_eNextEntityId = 0;	
			Oryol::StaticArray<void*, ComponentId::Count>
						m_aComponentPools;

			struct EntityComponent
			{
				Entity 	entity;
				int		Handle;
			};
			
			Oryol::Map<ComponentId::Enum, Oryol::Array<EntityComponent>>
						m_mEntityComponents;
		};

		template <class T>
		ComponentHandle<T> World::CreateComponent(ComponentId::Enum _id)
		{
			auto pool = GetComponentPool<T>(_id);
			int i = pool->GetFreeIndex();

			return {i, &pool->Pool[i], _id};
		}

		template<class T>
		void World::DestroyComponent(ComponentHandle<T> _cmp)
		{
			auto pool = GetComponentPool<T>(_cmp.Id);
			pool->Remove(_cmp.Handle);
		}

		// Add a component to an entity
		template <class T>
		void World::AddComponent(Entity _entity, ComponentHandle<T> _cmp)
		{
			if (!m_mEntityComponents.Contains(_cmp.Id))
				m_mEntityComponents.Add(_cmp.Id, Oryol::Array());
			
			m_mEntityComponents[_cmp.Id].Add({ _entity, _cmp.Handle });
		}

		template<class T>
		core::ObjectPool<T, 1000>* World::GetComponentPool(ComponentId::Enum _id)
		{
			if (m_aComponentPools[_id] == nullptr)
				m_aComponentPools[_id] = Oryol::Memory::New<core::ObjectPool<T, 1000>>();
			return static_cast<core::ObjectPool<T, 1000>*>(m_aComponentPools[_id]);
		}
		
	} // en
	
} // ari
