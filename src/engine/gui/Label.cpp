#include "Label.hpp"
#include "imgui.h"

namespace ari
{
	namespace gui
	{
		Label::Label() : Text(nullptr)
		{
		}

		bool Label::BeginRender()
		{
			ImGui::Text(Text);
			return true;
		}

	} // gui

} // ari
