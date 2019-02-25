#pragma once

#include "../DirectoryTree.hpp"
#include "DockWindow.hpp"
#include <string>

namespace ari {

	namespace gui
	{
		class Button;
	}

	namespace sh
	{
		class AssetGui;

		class  AssetBrowser : public DockWindow
		{
		public:

			~AssetBrowser();

			void Init(en::World* p_world) override;

		private:

			void UpdateAssets(const DirectoryTree& _tree);
			static DirectoryTree* FindPathTree(DirectoryTree* _tree, const Oryol::String& _path);
			void OnDblClick(AssetGui* _sender);
			void OnRightClick(AssetGui* _sender);

			Oryol::Array<en::ComponentHandle<AssetGui>>	m_vAssets;

		}; // AssetBrowser

	} // sh

} // ari
