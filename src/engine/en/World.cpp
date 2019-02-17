#include "World.hpp"
#include "System.hpp"
#include "sx/allocator.h"

static void thread_init(sx_job_context* ctx, int thread_index, uint32_t thread_id, void* user) 
{
    Oryol::Log::Dbg("init thread id=0x%x index=%d\n", thread_id, thread_index);
}

static void thread_shutdown(sx_job_context* ctx, int thread_index, uint32_t thread_id, void* user) 
{
    Oryol::Log::Dbg("shutdown thread id=0x%x index=%d\n", thread_id, thread_index);
}

struct UpdateJobData
{
	ari::en::System			*	System;
	ari::en::World			*	World;
	ari::en::UpdateState::Enum	UpdateState;
	float						ElaspedTime;
};

static void system_update_job_cb(int _index, void* _userData)
{
	UpdateJobData* data = reinterpret_cast<UpdateJobData*>(_userData);
	data->System->Update(data->World, data->ElaspedTime, data->UpdateState);
}

namespace ari
{
	namespace en
	{
		World::World()
		{
			// Create Job context
			const sx_alloc* alloc = sx_alloc_malloc;
			static sx_job_context_desc cd;
			cd.thread_init_cb = thread_init;
			cd.thread_shutdown_cb = thread_shutdown;
			JobContext = sx_job_create_context(alloc, &cd);
		}

		Entity World::CreateEntity()
		{
			return m_eNextEntityId++;
		}	

		void World::SetComponentTag(ComponentId::Enum _id, ComponentTag::Enum _tag)
		{
			m_mComponentTags.Add(_id, _tag);

			if (!m_mTags.Contains(_tag))
				m_mTags.Add(_tag, Oryol::Array<ComponentId::Enum>());

			auto& v = m_mTags[_tag];
			for(auto& id: v)
				if (id == _id)
					return;

			m_mTags[_tag].Add(_id);
		}

		ComponentTag::Enum World::GetComponentTag(ComponentId::Enum _id)
		{
			int i = m_mComponentTags.FindIndex(_id);
			if (i == Oryol::InvalidIndex)
				return ComponentTag::General;

			return m_mComponentTags.ValueAtIndex(i);
		}

		const Oryol::Array<ComponentId::Enum>& World::GetComponentIdsByTag(ComponentTag::Enum _tag)
		{
			return m_mTags[_tag];
		}

		// Removes a component from an entity
		void World::RemoveComponent(Entity _entity, ComponentId::Enum _id)
		{
			m_mEntityComponents[_id].Erase(_entity);
		}

		//! Add a system to the world
		void World::AddSystem(System* _system)
		{
			m_aSystems.Add(_system);
			_system->Configure(this);
		}

		//! Removes a system from world
		void World::RemoveSystem(System* _system)
		{
			for (int i = 0; i < m_aSystems.Size(); i++)
			{
				if (m_aSystems[i] == _system)
				{
					m_aSystems.EraseSwap(i);
					_system->UnConfigure(this);
					return;
				}
			}
		}

		void World::Update(float _elapsedTime)
		{
			// 1st, Run the main thread update state.
			for (int i = 0; i < m_aSystems.Size(); i++)
			{
				if (m_aSystems[i]->NeedUpdateOn(UpdateState::MainThreadState))
					m_aSystems[i]->Update(this, _elapsedTime, UpdateState::MainThreadState);
			}

			if (UpdateType == UpdateType::Sync)
			{
				// 2nd, Run gameplay update state
				for (int i = 0; i < m_aSystems.Size(); i++)
				{
					if (m_aSystems[i]->NeedUpdateOn(UpdateState::GamePlayState))
						m_aSystems[i]->Update(this, _elapsedTime, UpdateState::GamePlayState);
				}

				// 3rd, Run scene update state
				for (int i = 0; i < m_aSystems.Size(); i++)
				{
					if (m_aSystems[i]->NeedUpdateOn(UpdateState::SceneState))
						m_aSystems[i]->Update(this, _elapsedTime, UpdateState::SceneState);
				}

				// 4th, Run frame update state
				for (int i = 0; i < m_aSystems.Size(); i++)
				{
					if (m_aSystems[i]->NeedUpdateOn(UpdateState::FrameState))
						m_aSystems[i]->Update(this, _elapsedTime, UpdateState::FrameState);
				}				
			}
			else
			{
				// Dispatch jobs
				static Oryol::Array<sx_job_desc> 	gameplayJobs,
													sceneJobs,
													frameJobs;
				static Oryol::Array<UpdateJobData>	jobDatas;
				sx_job_t							frameJobHandle;

				gameplayJobs.Clear();
				sceneJobs.Clear();
				frameJobs.Clear();
				jobDatas.Clear();
				int c = 0;

				// 2nd Run frame update state
				for (int i = 0; i < m_aSystems.Size(); i++)
				{
					if (m_aSystems[i]->NeedUpdateOn(UpdateState::FrameState))
					{
						jobDatas.Add({m_aSystems[i], this, UpdateState::FrameState, _elapsedTime });
						frameJobs.Add({system_update_job_cb, &jobDatas[c], SX_JOB_PRIORITY_HIGH});
						c++;
					}
				}				
				if (!frameJobs.Empty())
				{
					frameJobHandle = sx_job_dispatch(JobContext, &frameJobs[0], frameJobs.Size());
				}

				// 3rd, Run gameplay update state
				for (int i = 0; i < m_aSystems.Size(); i++)
				{
					if (m_aSystems[i]->NeedUpdateOn(UpdateState::GamePlayState))
					{
						jobDatas.Add({m_aSystems[i], this, UpdateState::GamePlayState, _elapsedTime });
						gameplayJobs.Add({system_update_job_cb, &jobDatas[c], SX_JOB_PRIORITY_HIGH});
						c++;
					}
				}				
				if (!gameplayJobs.Empty())
				{
					auto h = sx_job_dispatch(JobContext, &gameplayJobs[0], gameplayJobs.Size());
					sx_job_wait_and_del(JobContext, h);
				}

				// 4th, Run scene update state
				for (int i = 0; i < m_aSystems.Size(); i++)
				{
					if (m_aSystems[i]->NeedUpdateOn(UpdateState::SceneState))
					{
						jobDatas.Add({m_aSystems[i], this, UpdateState::SceneState, _elapsedTime });
						sceneJobs.Add({system_update_job_cb, &jobDatas[c], SX_JOB_PRIORITY_HIGH});
						c++;
					}
				}
				if (!sceneJobs.Empty())
				{
					auto h = sx_job_dispatch(JobContext, &sceneJobs[0], sceneJobs.Size());
					sx_job_wait_and_del(JobContext, h);
				}

				// Wait on frame rendering updates
				sx_job_wait_and_del(JobContext, frameJobHandle);
			}		
		}

	} // en
	
} // ari
