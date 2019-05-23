#include "FilePath.hpp"
#include "Core/String/StringBuilder.h"
#include <sx/platform.h>
#include "sx/os.h"

#if SX_CRT_MSVC
#	include <direct.h>   // _getcwd
#else
#	include <sys/stat.h> // mkdir
#	include <unistd.h>   // getcwd
#endif // BX_CRT_MSVC

namespace ari
{
	namespace core
	{
		FilePath::FilePath(Oryol::String _path)
		{
			SetPath(_path);
		}

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

		bool Make(const FilePath & _filePath, Error * _err)
		{
			if (!_err->Ok)
			{
				return false;
			}


#if SX_CRT_MSVC
			int32_t result = ::_mkdir(_filePath.Path.AsCStr());
#elif SX_CRT_MINGW
			int32_t result = ::mkdir(_filePath.Path.AsCStr());
#elif SX_CRT_NONE
			SX_UNUSED(_filePath);
			int32_t result = -1;
#else
			int32_t result = ::mkdir(_filePath.Path.AsCStr(), 0700);
#endif // BX_CRT_MSVC

			if (0 != result)
			{
				_err->SetError("The parent directory does not allow write permission to the process.");
				return false;
			}

			return true;

		} // Make

		bool MakeAll(const FilePath & _filePath, Error * _err)
		{
			if (!_err->Ok)
			{
				return false;
			}

			sx_file_info fi = sx_os_stat(_filePath.Path.AsCStr());
			
			if (SX_FILE_TYPE_DIRECTORY == fi.type)
			{
				return true;
			}

			if (SX_FILE_TYPE_REGULAR == fi.type)
			{
				_err->SetError("File already exist, and is not directory.");
				return false;
			}

			Oryol::StringBuilder sb(_filePath.Path);
			const Oryol::String dir = sb.GetSubString(0, sb.FindLastOf(0, sb.Length(), "/"));
			Oryol::StringBuilder sbDir(dir);
			const Oryol::String slash = sbDir.GetSubString(sbDir.FindLastOf(0, sbDir.Length(), "/"), 
				sbDir.Length());

			if (!slash.Empty()
				&& slash.AsCStr() - dir.AsCStr() > 1)
			{
				FilePath fp;
				fp.SetPath(dir);
				if (!MakeAll(fp, _err))
				{
					return false;
				}
			}

			FilePath path;
			path.SetPath(dir);
			return Make(path, _err);

		} // MakeAll

	} // core
	
} // ari
