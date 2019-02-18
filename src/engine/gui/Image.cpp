#include "Image.hpp"
#include "IMUI/IMUI.h"

namespace ari
{
	namespace gui
	{
		Image::Image()
		{
			ImageUi = Oryol::IMUI::AllocImage();
		}

		Image::~Image()
		{
			Oryol::IMUI::FreeImage(ImageUi);
		}

		bool Image::BeginRender()
		{
			ImGui::Image(ImageUi, Size);

			if (OnHovered.IsBound() && ImGui::IsItemHovered())
				OnHovered.Execute();

			return false;
		}

	} // gui

} // ari
