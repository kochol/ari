fips_begin_module(ari_en)
	fips_vs_warning_level(3)
	fips_deps(ari_core sx)
    fips_files(
		ComponentId.hpp
		Entity.hpp
		System.hpp
		UpdateState.hpp
        WorldManager.cpp WorldManager.hpp
        World.cpp World.hpp
    )
fips_end_module()
