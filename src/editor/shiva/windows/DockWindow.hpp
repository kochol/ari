#pragma once

#include "en/Entity.hpp"
#include "en/ComponentHandle.hpp"

namespace ari {
	namespace en
	{
		struct World;
	}
	namespace gui
	{
		class Window;
	}
}

namespace ari
{
	namespace sh
	{
		/*!
		 * DockWindow is the base class for other windows in editor.
		 */
		class DockWindow
		{
		public:

			virtual ~DockWindow() = default;

			gui::Window* GetDock() const { return m_Window.Component; }

			virtual void Init(en::World* p_world);

			virtual void Shutdown();

		protected:

			en::Entity								m_Entity = NULL_ENTITY;
			en::ComponentHandle<gui::Window>		m_Window;
			en::World							*	m_pWorld = nullptr;

		};

	} // sh

} // ari
