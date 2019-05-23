#pragma once
#include "gui/Gui.hpp"
#include "core/Delegate.hpp"
#include <string>
#include "gui/Image.hpp"
#include "Core/String/String.h"

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

			ImTextureID						Image;
			Oryol::String					FileName,
											Path;
			bool							IsDirectory;
			ari::DelegateOneParam<void, AssetGui*>
											OnDblClick,
											OnRightClick;
		};

	} // sh

} // ari

