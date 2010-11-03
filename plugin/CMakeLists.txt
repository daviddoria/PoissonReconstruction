find_package(ParaView REQUIRED)
include(${PARAVIEW_USE_FILE})

include_directories(
  ${INCLUDE_DIRECTORIES}
  ${PoissonReconstruction_SOURCE_DIR}/source
)

add_paraview_plugin(PoissonReconstructionPlugin "1.0"
  SERVER_MANAGER_XML vtkPoissonReconstruction.xml
  SERVER_MANAGER_SOURCES ../source/vtkPoissonReconstruction.cxx
  SERVER_SOURCES  ../source/Factor.cpp ../source/Geometry.cpp
                  ../source/MarchingCubes.cpp ../source/MultiGridOctest.cpp
                  ../source/MultiGridOctreeData.cpp
)

