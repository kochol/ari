fips_begin_module(ari_en)
	fips_vs_warning_level(3)
	fips_deps(ari_core sx)
    fips_files(
		ComponentId.hpp
		Entity.hpp
		Node.hpp			Node.cpp
		System.hpp
		UpdateState.hpp
        WorldManager.hpp 	WorldManager.cpp
        World.hpp 			World.cpp
    )
fips_end_module()
