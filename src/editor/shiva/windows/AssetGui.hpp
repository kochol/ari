#pragma once
#include "gui/Gui.hpp"
#include "core/Delegate.hpp"
#include <string>

namespace ari
{
	namespace sh
	{
		class AssetGui : public gui::Gui
		{
		public:
			AssetGui();
			~AssetGui() override;
			bool BeginRender() override;

			std::shared_ptr<ari::Texture>	Image;
			std::string						FileName,
				Path;
			bool							IsDirectory;
			ari::DelegateOneParam<void, AssetGui*>
				OnDblClick,
				OnRightClick;
		};

	} // sh

} // ari

