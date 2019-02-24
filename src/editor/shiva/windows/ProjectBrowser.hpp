#pragma once

#include "gui/Gui.hpp"
#include "DockWindow.hpp"

namespace ari
{
	namespace en
	{
		struct World;
	}

	namespace gui
	{
		class Button;
		class Label;
		class TextBox;
		class Popup;
	}

	namespace sh
	{
		class Project;

		/*!
		 * Custom GUI component to show a project in the list.
		 */
		class ProjectGui : public gui::Gui
		{
		public:
			bool BeginRender() override;
			void EndRender() override;

		}; // ProjectGui

		class ProjectBrowser : DockWindow
		{
		public:
			ProjectBrowser();

			~ProjectBrowser();

			void Init(en::World* p_world) override;

			void Shutdown() override;

		protected:

			en::ComponentHandle<gui::TextBox>	m_NewProjectName;
			en::ComponentHandle<gui::TextBox>	m_NewProjectPath;
			en::ComponentHandle<gui::Button>	m_NewProjectBtn;
			en::ComponentHandle<gui::TextBox>	m_OpenProjectPath;
			en::ComponentHandle<gui::Button>	m_OpenProjectBtn;
			en::ComponentHandle<gui::Popup>		m_MessageBox;
			en::ComponentHandle<gui::Label>		m_MbLabel;
			en::ComponentHandle<gui::Button>	m_MbOkBtn;

			void OnNewProjectClick();
			void OnOpenProjectClick();

			void OnClickMbOk();

			void ProjectOpened(Project* project);

		}; // ProjectBrowser

	} // sh

} // ari
