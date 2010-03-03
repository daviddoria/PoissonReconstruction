cmake_minimum_required(VERSION 2.6)

PROJECT(PoissonReconstruction)

ADD_EXECUTABLE(PoissonReconstruction CmdLineParser.cpp Factor.cpp Geometry.cpp MarchingCubes.cpp ply.cpp plyfile.cpp Time.cpp MultiGridOctest.cpp)
