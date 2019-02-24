#include "DockWindow.hpp"
#include "en/World.hpp"
#include "gui/Window.hpp"

namespace ari
{
	namespace sh
	{
		void DockWindow::Init(en::World* p_world)
		{
			m_pWorld = p_world;
			m_Entity = p_world->CreateEntity();
			m_Window = p_world->CreateComponent<gui::Window>(en::ComponentId::Window);
			p_world->AddComponent(m_Entity, m_Window);
		}

		void DockWindow::Shutdown()
		{
			if (m_Entity != NULL_ENTITY)
			{
				m_pWorld->DestroyEntity(m_Entity);
				m_pWorld->DestroyComponent(m_Window);
			}
		}

	} // sh

} // ari
