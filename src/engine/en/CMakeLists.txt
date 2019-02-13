fips_begin_module(ari_en)
	fips_vs_warning_level(3)
	fips_deps(ari_core)
    fips_files(
		ComponentId.hpp
		Entity.hpp
        WorldManager.cpp WorldManager.hpp
        World.cpp World.hpp
    )
fips_end_module()
