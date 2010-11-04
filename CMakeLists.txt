cmake_minimum_required(VERSION 2.6)

project(PoissonReconstruction)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

if( ${VTK_BUILD_SHARED_LIBS} MATCHES ON )
  set( SHARED_LIBS "SHARED" )
  add_definitions( "-DvtkPoissonReconstruction_EXPORTS" )
  add_definitions( "-DBUILD_SHARED_LIBS" )
else(${VTK_BUILD_SHARED_LIBS} MATCHES ON )
  set( SHARED_LIBS "STATIC" )
endif(${VTK_BUILD_SHARED_LIBS} MATCHES ON )

set( CMAKE_RUNTIME_OUTPUT_DIRECTORY
  ${PoissonReconstruction_BINARY_DIR}/bin
)

set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY
  ${PoissonReconstruction_BINARY_DIR}/lib
)

SET( CMAKE_LIBRARY_OUTPUT_DIRECTORY
  ${PoissonReconstruction_BINARY_DIR}/lib
)

include_directories(
  ${PoissonReconstruction_SOURCE_DIR}/source
  ${PoissonReconstruction_BINARY_DIR}
)

add_subdirectory(source)

include( CTest )
add_subdirectory(example)

set(BUILD_PARAVIEW_PLUGIN OFF CACHE BOOL "Build Paraview plugin?")

if(BUILD_PARAVIEW_PLUGIN)
  add_subdirectory(plugin)
endif(BUILD_PARAVIEW_PLUGIN)

option( BUILD_DOCUMENTATION "Build Doxygen Documentation" OFF )

if( BUILD_DOCUMENTATION )
  add_subdirectory( documentation )
endif( BUILD_DOCUMENTATION )

