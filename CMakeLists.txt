cmake_minimum_required(VERSION 2.6)

PROJECT(PoissonReconstruction)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

ADD_EXECUTABLE(PoissonReconstruction Example.cxx vtkPoissonReconstruction.cxx Factor.cpp Geometry.cpp MarchingCubes.cpp Time.cpp MultiGridOctest.cpp MultiGridOctreeData.cpp)
TARGET_LINK_LIBRARIES(PoissonReconstruction vtkHybrid)

ADD_TEST( PoissonReconstructionTest 
  ${PoissonReconstruction_BINARY_DIR}/PoissonReconstruction 
  ${PoissonReconstruction_SOURCE_DIR}/data/horsePoints.vtp
  5 
  temp.vtp 
)

INCLUDE( CTest )
