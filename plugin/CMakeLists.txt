FIND_PACKAGE(ParaView REQUIRED)
INCLUDE(${PARAVIEW_USE_FILE})

INCLUDE_DIRECTORIES(${INCLUDE_DIRECTORIES} ../)

ADD_PARAVIEW_PLUGIN(PoissonReconstructionPlugin "1.0"
  SERVER_MANAGER_XML ../vtkPoissonReconstruction.xml
SERVER_MANAGER_SOURCES ../vtkPoissonReconstruction.cxx  
SERVER_SOURCES ../Factor.cpp ../Geometry.cpp ../MarchingCubes.cpp ../MultiGridOctest.cpp ../MultiGridOctreeData.cpp 
)

