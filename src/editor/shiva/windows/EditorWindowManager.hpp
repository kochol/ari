#pragma once

#include "en/Entity.hpp"

namespace ari
{
	namespace en
	{
		struct World;
	}
	namespace gui
	{
		class Window;
	}

	namespace sh
	{
		class AssetBrowser;
		class Viewport;
		class Project;
		class PropertyEditor;

		class EditorWindowManager
		{
		public:

			EditorWindowManager();

			~EditorWindowManager();

			void Init(en::World* _world);

			void Shutdown();

		protected:

			en::Entity				m_Entity = NULL_ENTITY;
			AssetBrowser		*	m_pAssetBrowser = nullptr;
			Viewport			*	m_pViewport = nullptr;
			PropertyEditor		*	m_pPropertyEditor = nullptr;

		}; // EditorWindowManager

	} // sh

} // ari
