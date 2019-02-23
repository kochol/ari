#include "FilePath.hpp"
#include "Core/String/StringBuilder.h"

namespace ari
{
	namespace core
	{
		void FilePath::SetPath(Oryol::String _path)
		{
			Path = _path;
			Oryol::StringBuilder s(Path);
			int i = s.FindLastOf(0, Path.Length(), "/");
			o_assert(i != Oryol::InvalidIndex);
			Folder = s.GetSubString(0, i);
			FileName = s.GetSubString(i, Path.Length() - 1);
			i = s.FindLastOf(i, Path.Length(), ".");
			FileExt = s.GetSubString(i, Path.Length() - 1);
		}

		void FilePath::Join(Oryol::String _path)
		{
			Oryol::StringBuilder s(Path);
			s.Append(_path);
			SetPath(s.GetString());
		}

	} // core
	
} // ari
