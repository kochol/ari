fips_begin_app(ShivaEditor cmdline)
    fips_vs_warning_level(3)
    fips_files(
		ShivaApp.hpp		ShivaApp.cpp
	)
    fips_deps(Gfx)
fips_end_app()