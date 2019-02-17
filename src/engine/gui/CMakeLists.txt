fips_begin_module(ari_gui)
	fips_vs_warning_level(3)
	fips_deps(ari_en IMUI)
    fips_files(
		Gui.hpp
		GuiSystem.cpp	GuiSystem.hpp
		Window.cpp		Window.hpp
    )
fips_end_module()
