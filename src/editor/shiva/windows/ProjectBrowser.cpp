#include "ProjectBrowser.hpp"
#include "gui/Window.hpp"
#include "en/World.hpp"
#include "gui/TextBox.hpp"
#include "gui/Button.hpp"
#include "gui/Label.hpp"
#include "gui/Popup.hpp"
#include "../EditorSettings.hpp"
#include "../Editor.hpp"

namespace ari
{
	namespace sh
	{
		ProjectBrowser::ProjectBrowser()
		{
		}

		ProjectBrowser::~ProjectBrowser()
		{
			Shutdown();
		}

		void ProjectBrowser::Init(en::World* p_world)
		{
			DockWindow::Init(p_world);

			// Init Project browser window.
			m_Window->Name = "Project Browser";
			m_NewProjectName = p_world->CreateComponent<gui::TextBox>(en::ComponentId::TextBox);
			m_NewProjectName->Label = "Project name";
			m_NewProjectName->SetText("New project");
			m_Window->AddChild(m_NewProjectName);
			m_NewProjectPath = p_world->CreateComponent<gui::TextBox>(en::ComponentId::TextBox);
			m_NewProjectPath->Label = "Project path";
			//m_NewProjectPath->SetText(bx::FilePath(bx::Dir::Home).get());
			m_Window->AddChild(m_NewProjectPath);
			m_NewProjectBtn = p_world->CreateComponent<gui::Button>(en::ComponentId::Button);
			m_NewProjectBtn->Label = "New project";
			m_NewProjectBtn->OnClick.Bind(this, &ProjectBrowser::OnNewProjectClick);
			m_Window->AddChild(m_NewProjectBtn);

			// Init open project textbox
			m_OpenProjectPath = p_world->CreateComponent<gui::TextBox>(en::ComponentId::TextBox);
			m_OpenProjectPath->Label = "Project path to open";
			m_OpenProjectPath->Separator = true;
			m_OpenProjectPath->SetText(EditorSettings::Get().LastProjectPath.c_str());
			m_Window->AddChild(m_OpenProjectPath);
			m_OpenProjectBtn = p_world->CreateComponent<gui::Button>(en::ComponentId::Button);
			m_OpenProjectBtn->Label = "Open project";
			m_OpenProjectBtn->OnClick.Bind(this, &ProjectBrowser::OnOpenProjectClick);
			m_Window->AddChild(m_OpenProjectBtn);

			// Init message window
			m_MessageBox = p_world->CreateComponent<gui::Popup>(en::ComponentId::Popup);
			m_MessageBox->Name = "MessageBox";
			m_MbLabel = p_world->CreateComponent<gui::Label>(en::ComponentId::Label);
			m_MessageBox->AddChild(m_MbLabel);
			m_MbOkBtn = p_world->CreateComponent<gui::Button>(en::ComponentId::Button);
			m_MbOkBtn->Label = "OK";
			m_MbOkBtn->OnClick.Bind(this, &ProjectBrowser::OnClickMbOk);
			m_MessageBox->AddChild(m_MbOkBtn);
		}

		void ProjectBrowser::Shutdown()
		{
			if (m_Entity != NULL_ENTITY)
			{
				m_pWorld->DestroyComponent(m_NewProjectName);
				m_pWorld->DestroyComponent(m_NewProjectPath);
				m_pWorld->DestroyComponent(m_NewProjectBtn);
				m_pWorld->DestroyComponent(m_OpenProjectPath);
				m_pWorld->DestroyComponent(m_OpenProjectBtn);
				m_pWorld->DestroyComponent(m_MessageBox);
				m_pWorld->DestroyComponent(m_MbLabel);
				m_pWorld->DestroyComponent(m_MbOkBtn);
				DockWindow::Shutdown();
			}
		}

		void ProjectBrowser::OnNewProjectClick()
		{
			bx::Error err;
			Project* p = Project::New(bx::FilePath(m_pNewProjectPath->Text), m_pNewProjectName->Text, &err);
			if (p)
			{
				ProjectOpened(p);
			}
			else
			{
				m_pMbLabel->Text = err.getMessage().getPtr();
				m_pMessageBox->Show();
			}
		}

		void ProjectBrowser::OnOpenProjectClick()
		{
			bx::Error err;
			Project* p = Project::Load(bx::FilePath(m_pOpenProjectPath->Text), &err);
			if (p)
			{
				ProjectOpened(p);
			}
			else
			{
				m_pMbLabel->Text = err.getMessage().getPtr();
				m_pMessageBox->Show();
			}
		}

		void ProjectBrowser::OnClickMbOk()
		{
			m_MessageBox->Hide();
		}

		void ProjectBrowser::ProjectOpened(Project* project)
		{
			g_pEditor->LoadProject(project);
			Shutdown();
		}

		bool ProjectGui::BeginRender()
		{
			ImGui::BeginGroup();
			{
				ImGui::BeginGroup();
				ImGui::Button("AAA");
				ImGui::SameLine();
				ImGui::Button("BBB");
				ImGui::SameLine();
				ImGui::BeginGroup();
				ImGui::Button("CCC");
				ImGui::Button("DDD");
				ImGui::EndGroup();
				ImGui::SameLine();
				ImGui::Button("EEE");
				ImGui::EndGroup();
				if (ImGui::IsItemHovered())
					ImGui::SetTooltip("First group hovered");
			}
			// Capture the group size and create widgets using the same size
			ImVec2 size = ImGui::GetItemRectSize();
			const float values[5] = { 0.5f, 0.20f, 0.80f, 0.60f, 0.25f };
			ImGui::PlotHistogram("##values", values, IM_ARRAYSIZE(values), 0, NULL, 0.0f, 1.0f, size);

			ImGui::Button("ACTION", ImVec2((size.x - ImGui::GetStyle().ItemSpacing.x)*0.5f, size.y));
			ImGui::SameLine();
			ImGui::Button("REACTION", ImVec2((size.x - ImGui::GetStyle().ItemSpacing.x)*0.5f, size.y));
			ImGui::EndGroup();

			return false;
		}

		void ProjectGui::EndRender()
		{
		}

	} // sh

} // ari
