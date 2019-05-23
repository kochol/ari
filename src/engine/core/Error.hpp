#pragma once

#include "Core/String/String.h"

namespace ari
{
	namespace core
	{
		struct Error
		{
			bool			Ok = true;
			Oryol::String	Message;

			void SetError(Oryol::String	_msg)
			{
				Ok = false;
				Message = _msg;
			}

		}; // Error
		
	} // core
	
} // ari
