find_package( Doxygen )

if( DOXYGEN_FOUND )

  configure_file(
    ${PoissonReconstruction_SOURCE_DIR}/documentation/Doxyfile.txt.in
    ${PoissonReconstruction_BINARY_DIR}/Doxyfile.txt
  )

  add_custom_target(doc ALL
    ${DOXYGEN_EXECUTABLE} ${PoissonReconstruction_BINARY_DIR}/Doxyfile.txt
    DEPENDS ${PoissonReconstruction_BINARY_DIR}/Doxyfile.txt
  )

endif( DOXYGEN_FOUND )
