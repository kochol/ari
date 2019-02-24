fips_begin_module(ari_core)
	fips_vs_warning_level(3)
	fips_deps(Core)
    fips_files(
			Delegate.hpp
			Error.hpp
			FilePath.hpp		FilePath.cpp
			ObjectPool.hpp		
    )
fips_end_module()
