#
# project: oryol-samples
#
cmake_minimum_required(VERSION 2.8)

# include the fips main cmake file
get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
include("${FIPS_ROOT_DIR}/cmake/fips.cmake")

fips_setup(PROJECT ari)
set(CMAKE_CXX_STANDARD 17)
include_directories(src/engine)
fips_add_subdirectory(src)
fips_finish()
