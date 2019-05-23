#pragma once

#include <string>
#include <Meta.h>
#include "DirectoryTree.hpp"
#include "core/FilePath.hpp"

namespace ari
{
	namespace core 
	{
		struct Error;
	}

	namespace sh
	{
		class Project
		{
			friend auto meta::registerMembers<Project>();
		public:
			Project();

			~Project();

			static Project* New(core::FilePath projectPath, std::string name, core::Error* err);

			void Save();

			static Project* Load(core::FilePath path, core::Error* err);

			void UpdateProjectTree();

			const DirectoryTree& GetTree() const { return m_Tree; }

			const core::FilePath& GetPath() const { return m_ProjectPath; }

		private:

			core::FilePath	m_ProjectPath;
			std::string		m_ProjectName;
			DirectoryTree	m_Tree;

		}; // Project

	} // sh

} // ari

namespace meta {

	template <>
	inline auto registerMembers<ari::sh::Project>()
	{
		return members(
			member("name", &ari::sh::Project::m_ProjectName)
		);
	}

} // end of namespace meta
