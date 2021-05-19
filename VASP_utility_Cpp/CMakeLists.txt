# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("VASP_utility_Cpp")
enable_testing()

# Include sub-projects.
add_subdirectory ("VASP_utility_Cpp")
