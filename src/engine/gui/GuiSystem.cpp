#include "en/World.hpp"
#include "GuiSystem.hpp"
#include "IMUI/IMUI.h"
#include "Input/Input.h"

using namespace Oryol;

namespace ari
{
	namespace gui
	{
		GuiSystem::GuiSystem()
		{
			en::World::SetComponentTag(en::ComponentId::Button, en::ComponentTag::GUI);
			en::World::SetComponentTag(en::ComponentId::CheckBox, en::ComponentTag::GUI);
			en::World::SetComponentTag(en::ComponentId::Image, en::ComponentTag::GUI);
			en::World::SetComponentTag(en::ComponentId::Label, en::ComponentTag::GUI);
			en::World::SetComponentTag(en::ComponentId::Popup, en::ComponentTag::GUI);
			en::World::SetComponentTag(en::ComponentId::TextBox, en::ComponentTag::GUI);
			en::World::SetComponentTag(en::ComponentId::Window, en::ComponentTag::GUI);
		}

		GuiSystem::~GuiSystem()
		{
		}

		void GuiSystem::Configure(World* _world)
		{
			if (!Input::IsValid())
				Input::Setup();

			IMUI::Setup();
		}

		void GuiSystem::UnConfigure(World* _world)
		{
			IMUI::Discard();
			Input::Discard();
		}

		void GuiSystem::Update(World* _world, float _elapsed,
			UpdateState::Enum _state)
		{
			IMUI::NewFrame(); // TODO: Pass elapsed param

			auto& ids = World::GetComponentIdsByTag(ComponentTag::GUI);
			for (const auto& id: ids)
			{
				_world->GetComponents<Gui>(id, [this](Entity _entity, ComponentHandle<Gui> gui)
				{
					this->RenderGui(gui.Component);
				});
			}

			ImGui::Render();
		}

		bool GuiSystem::NeedUpdateOn(UpdateState::Enum _state)
		{
			return _state == UpdateState::MainThreadState;
		}

		void GuiSystem::RenderGui(Gui * _gui)
		{
			if (!_gui->Visible)
				return;

			if (_gui->SameLine)
				ImGui::SameLine();

			if (_gui->Separator)
				ImGui::Separator();

			if (_gui->BeginRender())
			{
				auto& ids = World::GetComponentIdsByTag(ComponentTag::GUI);
				for (const auto& id : ids)
				{
					for (auto child: _gui->GetChildren(id))
						this->RenderGui(static_cast<Gui*>(child));
				}
			}
			_gui->EndRender();
		}

	} // gui
	
} // ari
