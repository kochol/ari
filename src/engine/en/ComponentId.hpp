#pragma once

namespace ari
{
	namespace en
	{
		struct ComponentId
		{
			enum Enum
			{
				Entity,

				// 3D
				Transform3D,

				// 2D
				Transform2D,

				// GUI
				Window,

				Count,
				UserComponent = 1000
			};
		};

		struct ComponentTag
		{
			enum Enum
			{
				General,
				_3D,
				_2D,
				GUI
			};
		};
		
		
	} // en
	
} // ari
