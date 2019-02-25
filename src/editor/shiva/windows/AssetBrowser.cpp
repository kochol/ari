#include "AssetBrowser.hpp"
#include "gui/Button.hpp"
#include "en/World.hpp"
#include "AssetGui.hpp"
#include "../Project.hpp"
#include "../Editor.hpp"
#include "gui/Window.hpp"
#include "Core/String/StringBuilder.h"

namespace ari
{
	namespace sh
	{
		AssetBrowser::~AssetBrowser()
		{
			Shutdown();
		}

		void AssetBrowser::Init(en::World* p_world)
		{
			DockWindow::Init(p_world);

			m_Window->Name = "Asset browser";
			UpdateAssets(g_pEditor->GetCurrentProject()->GetTree());
		}

		void AssetBrowser::UpdateAssets(const DirectoryTree & _tree)
		{
			int c = 0;
			static Oryol::String strFile("sh:icons/filetypes/DEFAULT.png");
			static Oryol::String strFolder("sh:icons/filetypes/folder.png");
			static Oryol::String strUp("sh:icons/filetypes/folder_up.png");

			if (!_tree.IsRoot)
			{
				m_vAssets[0]->Image = ari::g_pEngine->texture_manager.Load(strUp, nullptr);
				Oryol::StringBuilder sb(_tree.Path.Path);				
				m_vAssets[0]->Path = sb.GetSubString(0, sb.FindLastOf(0, sb.Length(), "/"));
				m_vAssets[0]->FileName = "..";
				m_vAssets[0]->IsDirectory = true;
				c++;
			}
			for (int i = 0; i < _tree.Directories.Size(); ++i)
			{
				if (m_vAssets.Size() <= c)
				{
					auto p_gui = m_pWorld->CreateComponent<AssetGui>(ComponentId::AssetGui);
					p_gui->Image = ari::g_pEngine->texture_manager.Load(strFolder, nullptr);
					p_gui->FileName = _tree.Directories[i].Name;
					p_gui->Path = _tree.Directories[i].Path.Path;
					p_gui->IsDirectory = true;
					p_gui->OnDblClick.Bind(this, &AssetBrowser::OnDblClick);
					p_gui->OnRightClick.Bind(this, &AssetBrowser::OnRightClick);
					if (c % 2 == 1)
						p_gui->SameLine = true;
					m_Window->AddChild(p_gui);
					m_vAssets.Add(p_gui);
				}
				else
				{
					m_vAssets[c]->Image = ari::g_pEngine->texture_manager.Load(strFolder, nullptr);
					m_vAssets[c]->FileName = _tree.Directories[i].Name;
					m_vAssets[c]->Visible = true;
					m_vAssets[c]->Path = _tree.Directories[i].Path.Path;
					m_vAssets[c]->IsDirectory = true;
				}
				c++;
			}
			for (int i = 0; i < _tree.FileList.Size(); ++i)
			{
				if (m_vAssets.Size() <= c)
				{
					auto p_gui = m_pWorld->CreateComponent<AssetGui>(ComponentId::AssetGui);
					p_gui->Image = ari::g_pEngine->texture_manager.Load(strFile, nullptr);
					p_gui->FileName = _tree.FileList[i].Name;
					p_gui->Path = _tree.Path.Path;
					p_gui->IsDirectory = false;
					p_gui->OnDblClick.Bind(this, &AssetBrowser::OnDblClick);
					p_gui->OnRightClick.Bind(this, &AssetBrowser::OnRightClick);
					if (c % 2 == 1)
						p_gui->SameLine = true;
					m_Window->AddChild(p_gui);
					m_vAssets.Add(p_gui);
				}
				else
				{
					m_vAssets[c]->Image = ari::g_pEngine->texture_manager.Load(strFile, nullptr);
					m_vAssets[c]->FileName = _tree.FileList[i].Name;
					m_vAssets[c]->Visible = true;
					m_vAssets[c]->Path = _tree.Path.Path;
					m_vAssets[c]->IsDirectory = false;
				}
				c++;
			}
			for (int i = c; i < m_vAssets.Size(); i++)
			{
				m_vAssets[i]->Visible = false;
			}
		}

		DirectoryTree* AssetBrowser::FindPathTree(DirectoryTree* _tree, const Oryol::String& _path)
		{
			if (_tree->Path.Path == _path)
				return _tree;

			for (int i = 0; i < _tree->Directories.Size(); i++)
			{
				const auto r = FindPathTree(&_tree->Directories[i], _path);
				if (r)
					return r;
			}
			return nullptr;
		}

		void AssetBrowser::OnDblClick(AssetGui* _sender)
		{
			if (_sender->IsDirectory)
			{
				DirectoryTree tree = g_pEditor->GetCurrentProject()->GetTree();
				auto r = FindPathTree(&tree, _sender->Path);
				if (r)
					UpdateAssets(*r);
				else
					Oryol::Log::Error("Can't find the directory %s.", _sender->Path.AsCStr());
			}
		}

		void AssetBrowser::OnRightClick(AssetGui* _sender)
		{
		}

	} // sh

} // ari

