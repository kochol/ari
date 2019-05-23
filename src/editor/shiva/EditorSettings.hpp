#pragma once
#include <Meta.h>

namespace ari
{
	namespace sh
	{
		class EditorSettings
		{
		public:

			std::string			LastProjectPath;

			static EditorSettings& Get();
			static void Save();
			static void Load();
		};

	} // sh
	
} // ari

namespace meta {

	template <>
	inline auto registerMembers<ari::sh::EditorSettings>()
	{
		return members(
			member("last_project_path", &ari::sh::EditorSettings::LastProjectPath)
		);
	}

} // end of namespace meta