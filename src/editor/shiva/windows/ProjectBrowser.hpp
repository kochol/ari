#pragma once
#include "en/Entity.hpp"
#include "gui/Gui.hpp"
#include "gui/Button.hpp"
#include "gui/Label.hpp"

namespace ari
{
	class World;
	class TextBox;
	class Popup;

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

			void Init(ari::World* p_world) override;

			void Shutdown() override;

		protected:

			ari::TextBox		*	m_pNewProjectName;
			ari::TextBox		*	m_pNewProjectPath;
			ari::Button			*	m_pNewProjectBtn;
			ari::TextBox		*	m_pOpenProjectPath;
			ari::Button			*	m_pOpenProjectBtn;
			ari::Popup			*	m_pMessageBox;
			ari::Label			*	m_pMbLabel;
			ari::Button			*	m_pMbOkBtn;

			void OnNewProjectClick();
			void OnOpenProjectClick();

			void OnClickMbOk();

			void ProjectOpened(Project* project);

		}; // ProjectBrowser

	} // sh

} // ari
