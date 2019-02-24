fips_begin_module(shiva)
	fips_vs_warning_level(3)
	fips_deps(ari_gui)
    fips_files(
		DirectoryTree.hpp		DirectoryTree.cpp
		Editor.hpp				Editor.cpp
		EditorSettings.hpp		EditorSettings.cpp
		Project.hpp				Project.cpp
	)
	fips_dir(windows)
	fips_files(
		AssetBrowser.hpp				AssetBrowser.cpp
		AssetGui.hpp						AssetGui.cpp
		DockWindow.hpp					DockWindow.cpp
		EditorWindowManager.hpp	EditorWindowManager.cpp
		ProjectBrowser.hpp			ProjectBrowser.cpp
	)
fips_end_module()
