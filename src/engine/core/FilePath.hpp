#pragma once

#include <Core/String/String.h>
#include "Error.hpp"

namespace ari
{
	namespace core
	{
		struct FilePath
		{
			FilePath() = default;

			FilePath(Oryol::String _path);

			void SetPath(Oryol::String _path);

			void Join(Oryol::String _path);

			Oryol::String	Path;
			Oryol::String	Folder;
			Oryol::String	FileName;
			Oryol::String	FileExt;

		}; // FilePath

		/// Creates a directory named `_filePath`.
		///
		bool Make(const FilePath& _filePath, Error* _err = NULL);

		/// Creates a directory named `_filePath` along with all necessary parents.
		///
		bool MakeAll(const FilePath& _filePath, Error* _err = NULL);
	
	} // core
	
} // ari
