cmake_minimum_required(VERSION 3.12)

# Change the project name here!
project(DateTime LANGUAGES CXX)

# Set this option to ON to be able to use folders / filters in your project when using Visual Studio.
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Set the C++ standard to 20 (C++20).
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

# Add RED4ext.SDK as a dependency.
add_subdirectory(deps/RED4ext.SDK)
set_target_properties(RED4ext.SDK PROPERTIES FOLDER "Dependencies")

# Add RedLib as a dependency.
add_compile_definitions(NOMINMAX)
add_subdirectory(deps/RedLib)
set_target_properties(RedLib PROPERTIES FOLDER "Dependencies")

# This will mark the following RED4ext variables as advanced. They won't be displayed in CMake's GUI.
mark_as_advanced(
  RED4EXT_BUILD_EXAMPLES
  RED4EXT_HEADER_ONLY
)

# Include the main project.
add_subdirectory(src)
