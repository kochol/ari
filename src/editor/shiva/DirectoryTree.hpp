#pragma once
#include <Core/String/String.h>
#include <Core/Containers/Array.h>
#include "core/FilePath.hpp"

namespace ari
{
	namespace sh
	{
		struct FileInfo
		{
			Oryol::String Name;
		};

		struct DirectoryTree
		{
			Oryol::String				Name;
			ari::core::FilePath			Path;
			Oryol::Array<FileInfo>		FileList;
			Oryol::Array<DirectoryTree> Directories;
			bool						IsRoot = false;

			void Update();

		};

	} // sh

} // ari
