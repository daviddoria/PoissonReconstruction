cmake_minimum_required(VERSION 2.6)

PROJECT(PoissonReconstruction)

FIND_PACKAGE(VTK REQUIRED)
INCLUDE(${VTK_USE_FILE})

ADD_EXECUTABLE(PoissonReconstruction CmdLineParser.cpp Factor.cpp Geometry.cpp MarchingCubes.cpp ply.cpp plyfile.cpp Time.cpp MultiGridOctest.cpp)
TARGET_LINK_LIBRARIES(PoissonReconstruction vtkHybrid)