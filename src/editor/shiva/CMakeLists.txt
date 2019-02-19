fips_begin_module(shiva)
	fips_vs_warning_level(3)
	fips_deps(ari_gui)
    fips_files(
			Editor.hpp					Editor.cpp
			EditorSettings.hpp	EditorSettings.cpp
	)
	fips_dir(windows)
	fips_files(
		EditorWindowManager.hpp			EditorWindowManager.cpp
	)
fips_end_module()
