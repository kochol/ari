fips_begin_module(ari_en)
	fips_vs_warning_level(3)
	fips_deps(Core)
    fips_files(
        WorldManager.cpp WorldManager.hpp
        World.cpp World.hpp
    )
fips_end_module()
