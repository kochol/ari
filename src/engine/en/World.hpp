#pragma once

#include "Entity.hpp"
#include "ComponentId.hpp"
#include "ComponentHandle.hpp"
#include "core/ObjectPool.hpp"
#include "Core/Containers/Array.h"
#include "Core/Containers/Map.h"
#include "UpdateState.hpp"
#include "sx/jobs.h"

namespace ari
{
	namespace en
	{
		class System;

		struct World
		{
			enum class UpdateType
			{
				Sync,
				Async
			};

			UpdateType UpdateType = UpdateType::Async;

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

			//! Add a system to the world
			void AddSystem(System* _system);

			//! Removes a system from world
			void RemoveSystem(System* _system);

			void Update(float _elaspedTime);

			sx_job_context	*	JobContext = nullptr;

		private:

			template<class T>
			core::ObjectPool<T, 1000>* GetComponentPool(ComponentId::Enum _id);

			Entity					m_eNextEntityId = 0;	
			Oryol::Array<void*>		m_aComponentPools;
			
			Oryol::Map<ComponentId::Enum, Oryol::Map<Entity, int>>
									m_mEntityComponents;

			Oryol::Array<System*>	m_aSystems;			
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
				m_mEntityComponents.Add(_cmp.Id, Oryol::Map<Entity, int>());
			
			m_mEntityComponents[_cmp.Id].Add(_entity, _cmp.Handle);
		}

		template<class T>
		core::ObjectPool<T, 1000>* World::GetComponentPool(ComponentId::Enum _id)
		{
			while (m_aComponentPools.Size() <= _id)
				m_aComponentPools.Add(nullptr);

			if (m_aComponentPools[_id] == nullptr)
				m_aComponentPools[_id] = Oryol::Memory::New<core::ObjectPool<T, 1000>>();

			return static_cast<core::ObjectPool<T, 1000>*>(m_aComponentPools[_id]);
		}
		
	} // en
	
} // ari
