#pragma once
#include <string>
#include <Meta.h>
#include "DirectoryTree.hpp"

namespace ari
{
	namespace sh
	{
		class Project
		{
			friend auto meta::registerMembers<Project>();
		public:
			Project();

			~Project();

			static Project* New(bx::FilePath projectPath, std::string name, bx::Error* err);

			void Save();
			static Project* Load(bx::FilePath path, bx::Error* err);

			void UpdateProjectTree();

			const DirectoryTree& GetTree() const { return m_Tree; }

			const bx::FilePath& GetPath() const { return m_ProjectPath; }

		private:

			bx::FilePath	m_ProjectPath;
			std::string		m_ProjectName;
			DirectoryTree	m_Tree;

		}; // Project

	} // sh

} // ari

namespace meta {

	template <>
	inline auto registerMembers<shiva::Project>()
	{
		return members(
			member("name", &shiva::Project::m_ProjectName)
		);
	}

} // end of namespace meta
