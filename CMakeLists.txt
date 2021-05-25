cmake_minimum_required(VERSION 3.16)
project(ifcgeom)

set(OpenGL_GL_PREFERENCE "GLVND")
include(cmake/pkg.cmake)

file(GLOB_RECURSE ifcgeom-files src/*.cc)
add_library(ifcgeom ${ifcgeom-files})
target_include_directories(ifcgeom PUBLIC include)
target_link_libraries(ifcgeom cinder)
target_compile_features(ifcgeom PUBLIC cxx_std_20)

file(GLOB_RECURSE ifcgeom-render-files exe/main.cc)
add_executable(render ${ifcgeom-render-files})
target_link_libraries(render ifcgeom boost-system cinder)
target_compile_features(ifcgeom PUBLIC cxx_std_20)

file(GLOB_RECURSE ifcgeom-test-files test/*.cc)
add_executable(ifcgeom-test ${ifcgeom-test-files})
target_compile_features(ifcgeom PUBLIC cxx_std_20)
target_link_libraries(ifcgeom-test ifcgeom doctest)
