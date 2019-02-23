#pragma once

#include <Core/String/String.h>

namespace ari
{
	namespace core
	{
		struct FilePath
		{
			void SetPath(Oryol::String _path);

			void Join(Oryol::String _path);

			Oryol::String	Path;
			Oryol::String	Folder;
			Oryol::String	FileName;
			Oryol::String	FileExt;

		}; // FilePath
		
	} // core
	
} // ari
