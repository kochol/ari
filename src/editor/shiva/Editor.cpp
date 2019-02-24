#include "Editor.hpp"
#include "EditorSettings.hpp"
#include "Project.hpp"
#include "Core/Time/Clock.h"

namespace ari
{
	namespace sh
	{
		Editor* g_pEditor = nullptr;

		Editor::Editor()
		{
			g_pEditor = this;
		}

		Editor::~Editor()
		{
			g_pEditor = nullptr;
		}

		void Editor::Init()
		{
			m_LastTimePoint = Oryol::Clock::Now();

			// Load editor settings
			EditorSettings::Load();

			// Add Systems
			m_EditorWorld.AddSystem(&m_GuiSystem);
			//m_EditorWorld.AddSystem(&m_RenderSystem);
			//m_EditorWorld.AddSystem(&m_SceneSystem);
			//m_EditorWorld.SetUpdateType(ari::World::UpdateType::Sync);

			// Init project browser
			m_ProjectBrowser.Init(&m_EditorWorld);
		}

		void Editor::Update()
		{			
			m_EditorWorld.Update((float)Oryol::Clock::LapTime(m_LastTimePoint).AsSeconds());
		}

		void Editor::LoadProject(Project* project)
		{
			delete m_pCurrentProject;
			m_pCurrentProject = project;

			EditorSettings::Get().LastProjectPath = project->GetPath().Path.AsCStr();
			EditorSettings::Save();

			m_EditorWindow.Init(&m_EditorWorld);
		}

	} // sh
	
} // ari
