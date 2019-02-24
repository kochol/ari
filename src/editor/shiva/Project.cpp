#include "Project.hpp"
#include <JsonCast.h>
#include "sx/os.h"
#include "core/Error.hpp"
#include "sx/io.h"
#include "sx/lin-alloc.h"

namespace ari
{
	namespace sh
	{
		Project::Project()
		{
		}

		Project::~Project()
		{
		}

		Project * Project::New(core::FilePath projectPath, std::string name, core::Error* err)
		{
			projectPath.Join(name.c_str());

			// check the folder is empty
			if (sx_os_path_exists(projectPath.Path.AsCStr()))
			{
				err->SetError("The directory is already exist.");
				return nullptr;
			}

			// 1st Create the folders
			if (!core::MakeAll(projectPath, err))
			{
				return nullptr;
			}
			core::FilePath tmp = projectPath;
			tmp.Join("src");
			core::Make(tmp, err);
			tmp = projectPath;
			tmp.Join("scripts");
			core::Make(tmp, err);
			tmp = projectPath;
			tmp.Join("assets");
			core::Make(tmp, err);
			tmp = projectPath;
			tmp.Join(".import");
			core::Make(tmp, err);

			Project* p = new Project();
			p->m_ProjectName = name;
			p->m_Tree.Path = projectPath;
			p->m_Tree.IsRoot = true;
			projectPath.Join(name.append(".shiva").c_str());
			p->m_ProjectPath = projectPath;
			p->Save();
			p->UpdateProjectTree();

			return p;
		}

		void Project::Save()
		{
			json root;
			to_json(root, *this);

			sx_file_writer writer;
			if (sx_file_open_writer(&writer, m_ProjectPath.Path.AsCStr()))
			{
				auto s = root.dump();
				sx_file_write(&writer, s.c_str(), (int)s.length());
				sx_file_close_writer(&writer);
			}
			else
				Oryol::Log::Error("Can't write to %s file.", m_ProjectPath.Path.AsCStr());
		}

		Project * Project::Load(core::FilePath path, core::Error* err)
		{
			auto mem = sx_file_load_text(sx_alloc_malloc, path.Path.AsCStr());
			if (mem == nullptr)
			{
				err->SetError("Can't load project file.");
				return nullptr;
			}

			Project* p = Oryol::Memory::New<Project>();
			json root = json::parse((char*)mem->data);
			from_json(root, *p);

			sx_mem_destroy_block(mem);

			p->m_ProjectPath = path;
			p->m_Tree.Path.SetPath(path.Folder);
			p->m_Tree.IsRoot = true;
			p->UpdateProjectTree();

			return p;
		}

		void Project::UpdateProjectTree()
		{
			m_Tree.Update();
		}

	} // sh

} // ari
