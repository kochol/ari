#include "EditorWindowManager.hpp"
#include "en/World.hpp"
#include "gui/Window.hpp"
#include "AssetBrowser.hpp"
#include "Viewport.hpp"
#include "PropertyEditor.hpp"

namespace ari
{
	namespace sh
	{
		EditorWindowManager::EditorWindowManager() = default;

		EditorWindowManager::~EditorWindowManager()
		{
			Shutdown();
			delete m_pAssetBrowser;
		}

		void EditorWindowManager::Init(en::World* _world)
		{
			m_Entity = _world->CreateEntity();

			// Init Viewport
			if (!m_pViewport)
				m_pViewport = new Viewport;
			m_pViewport->Init(pWorld);

			// Init Asset Browser
			if (!m_pAssetBrowser)
				m_pAssetBrowser = new AssetBrowser;
			m_pAssetBrowser->Init(pWorld);

			// Init Property Editor
			if (!m_pPropertyEditor)
				m_pPropertyEditor = new PropertyEditor;
			m_pPropertyEditor->Init(pWorld);

		} // Init

		void EditorWindowManager::Shutdown()
		{
			if (m_pEntity)
				m_pEntity->Destroy();
			m_pEntity = nullptr;
			m_pAssetBrowser->Shutdown();
			m_pViewport->Shutdown();
			m_pPropertyEditor->Shutdown();

		} // ShutDown

	} // sh

} // ari
