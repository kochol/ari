#pragma once
#include <string>
#include "bx/file.h"
#include <vector>

namespace ari
{
	namespace sh
	{
		struct FileInfo
		{
			std::string Name;
		};

		class DirectoryTree
		{
		public:

			std::string Name;
			bx::FilePath Path;
			std::vector<FileInfo> FileList;
			std::vector<DirectoryTree> Directories;
			bool IsRoot = false;

			void Update();

		};

	} // sh

} // ari
