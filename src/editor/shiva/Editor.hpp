#pragma once
#include "en/World.hpp"
#include "gui/GuiSystem.hpp"
#include "windows/EditorWindowManager.hpp"
#include "Core/Time/TimePoint.h"
#include "windows/ProjectBrowser.hpp"

namespace ari
{
	namespace sh
	{
		class Project;

		class Editor
		{
		public:

			Editor();

			~Editor();

			void Init();

			void Update();

			void LoadProject(Project* project);

			Project* GetCurrentProject() const { return m_pCurrentProject; }

			gui::GuiSystem* GetGuiSystem() { return &m_GuiSystem; }

		protected:

			en::World			m_EditorWorld;
			gui::GuiSystem		m_GuiSystem;
			//ari::RenderSystem	m_RenderSystem;
			//ari::SceneSystem	m_SceneSystem;
			ProjectBrowser		m_ProjectBrowser;
			EditorWindowManager	m_EditorWindow;
			Project			*	m_pCurrentProject = nullptr;
			Oryol::TimePoint	m_LastTimePoint;


		}; // Editor

		extern Editor* g_pEditor;

	} // sh
	
} // ari
