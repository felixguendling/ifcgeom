cmake_minimum_required(VERSION 3.16)
project(ifcgeom)

set(WITH_SDL2APPLICATION ON CACHE BOOL "" FORCE)

include(cmake/pkg.cmake)

file(GLOB_RECURSE ifcgeom-render-files exe/main.cc)
add_executable(render ${ifcgeom-render-files})
target_link_libraries(render PRIVATE
  Corrade::Main
  MagnumSdl2Application
  MagnumGL
  MagnumMeshTools
  MagnumPrimitives
  MagnumShaders
  MagnumSceneGraph)
target_compile_features(render PUBLIC cxx_std_20)


if (false)

express2cpp(IFC4.exp ifc4)
express2cpp(IFC2X3.exp ifc2x3)

file(GLOB_RECURSE ifcgeom-files src/*.cc)
add_library(ifcgeom ${ifcgeom-files})
target_include_directories(ifcgeom PUBLIC include)
target_link_libraries(ifcgeom cinder)
target_compile_features(ifcgeom PUBLIC cxx_std_20)

file(GLOB_RECURSE ifcgeom-render-files exe/main.cc)
add_executable(render ${ifcgeom-render-files})
target_link_libraries(render ifcgeom boost-system cinder ifc)
target_compile_features(ifcgeom PUBLIC cxx_std_20)

file(GLOB_RECURSE ifcgeom-test-files test/*.cc)
add_executable(ifcgeom-test ${ifcgeom-test-files})
target_compile_features(ifcgeom PUBLIC cxx_std_20)
target_link_libraries(ifcgeom-test ifcgeom doctest)

endif()