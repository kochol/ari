#include "DirectoryTree.hpp"
#include "dirent.h"
#include "Core/String/StringBuilder.h"

namespace ari
{
	namespace sh
	{
		void DirectoryTree::Update()
		{
			if (Name.Length() == 0)
			{
				Oryol::StringBuilder p(Path.Folder);
				const int i = p.FindLastOf(0, p.Length(), "/");
				Name = p.GetSubString(i + 1, p.Length());
			}

			// clear the children.
			Directories.Clear();
			FileList.Clear();

			// get file list.
			DIR* dir = opendir(Path.Path.AsCStr());
			dirent* next;
			do
			{
				next = readdir(dir);
				if (next)
				{
					if (next->d_name[0] == '.')
						continue;

					if (next->d_type == DT_DIR)
					{
						DirectoryTree child;
						child.Path = Path;
						child.Path.Join(next->d_name);
						Directories.Add(child);
						Directories[Directories.Size() - 1].Update();
					}
					else if (next->d_type == DT_REG)
					{
						FileList.Add({ next->d_name });
					}
					else
					{
						Oryol::Log::Error("Unknown file type.");
					}
				}
			} while (next);
		}

	} // shiva

} // ari
