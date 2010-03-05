cmake_minimum_required(VERSION 2.6)

PROJECT(PoissonReconstruction)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})


SET(BUILD_PARAVIEW_PLUGIN OFF CACHE BOOL "Build Paraview plugin?")

if(BUILD_PARAVIEW_PLUGIN)
SUBDIRS(plugin)
endif(BUILD_PARAVIEW_PLUGIN)

ADD_EXECUTABLE(PoissonReconstruction Example.cxx vtkPoissonReconstruction.cxx Factor.cpp Geometry.cpp MarchingCubes.cpp Time.cpp MultiGridOctest.cpp MultiGridOctreeData.cpp 
#MemoryUsage.h 
)
TARGET_LINK_LIBRARIES(PoissonReconstruction vtkHybrid)

ADD_TEST( PoissonReconstructionTest 
  ${PoissonReconstruction_BINARY_DIR}/PoissonReconstruction 
  ${PoissonReconstruction_SOURCE_DIR}/data/horsePoints.vtp
  5 
  temp.vtp 
)

INCLUDE( CTest )
