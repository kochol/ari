#pragma once

#include "UpdateState.hpp"

namespace ari
{
	namespace en
	{
		struct World;

		typedef void(system_update_cb)(World* _world, float _elasped,
			UpdateState::Enum _state, void* _userData);
		
		typedef bool(system_need_update_cb)(UpdateState::Enum _state, void* _userData);

		struct System
		{
			//! User data
			void					* 	UserData;

			//! Update callback
			system_update_cb		*	UpdateCallback;

			//! Need update on the particular state callback
			system_need_update_cb	*	NeedUpdateCallback;

		};
		
	} // en
	
} // ari
