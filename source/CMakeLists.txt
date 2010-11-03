add_library( vtkPoissonReconstruction
  ${SHARED_LIBS}
  vtkPoissonReconstruction.cxx
  Factor.cpp
  Geometry.cpp
  MarchingCubes.cpp
  MultiGridOctest.cpp
  MultiGridOctreeData.cpp
)

target_link_libraries( vtkPoissonReconstruction
  vtkHybrid
)

