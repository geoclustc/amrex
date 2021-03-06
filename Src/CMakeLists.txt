#
# Define a macro to accumulate all headers
#
set (AMREX_ALLHEADERS "" )
macro (accumulate_headers headers)
   list (APPEND AMREX_ALLHEADERS ${${headers}} )
endmacro ()

#
# Define a macro to accumulate include paths
#
set (INCLUDE_PATHS "")
macro (accumulate_include_dirs path)
   list (APPEND INCLUDE_PATHS ${path})
endmacro ()


#
# Fist, define the library we want to add
#
add_library ( amrex "")


#
# Now, one by one, let's add all the source files in the subdirectories
#
include (Base/CMakeLists.txt)
include (Boundary/CMakeLists.txt)
include (AmrCore/CMakeLists.txt)
include (Amr/CMakeLists.txt)

#
# Optional components
#
if (ENABLE_EB)
   include (EB/CMakeLists.txt)
   include (GeometryShop/CMakeLists.txt)
endif ()

if (ENABLE_FBASELIB)
   include (F_BaseLib/CMakeLists.txt)
endif ()

if (ENABLE_PROFPARSER OR ENABLE_AMRDATA)
   include (Extern/CMakeLists.txt)
endif ()

if (ENABLE_LINEAR_SOLVERS)
   include (LinearSolvers/CMakeLists.txt)
endif ()

if (ENABLE_FORTRAN_INTERFACES) 
   include (F_Interfaces/CMakeLists.txt)
endif ()

if ( ENABLE_PARTICLES )
   include (Particle/CMakeLists.txt)
endif ()


#
# Add all the include paths collected so far
# 
include_directories ( ${CMAKE_Fortran_MODULE_DIRECTORY} ${INCLUDE_PATHS}
   ${AMREX_EXTRA_Fortran_INCLUDE_PATH} ${AMREX_EXTRA_CXX_INCLUDE_PATH} )


#
# Define install  
#
set_target_properties ( amrex PROPERTIES PUBLIC_HEADER "${AMREX_ALLHEADERS}" )

install ( TARGETS amrex EXPORT amrex ARCHIVE DESTINATION ${AMREX_LIBRARY_DIR}
   PUBLIC_HEADER DESTINATION ${AMREX_INCLUDE_DIR} )
install ( DIRECTORY ${CMAKE_Fortran_MODULE_DIRECTORY}/ DESTINATION ${AMREX_INCLUDE_DIR})


#
# This header in a weird path has to be copied to install includes
# 
install ( FILES ${PROJECT_SOURCE_DIR}/Tools/C_scripts/AMReX_buildInfo.H
   DESTINATION ${AMREX_INCLUDE_DIR} )

#
# Write and install configure file 
# 
configure_file ( ${AMREX_CONFIG_INSTALL_INFILE} ${AMREX_CONFIG_INSTALL_OUTFILE} @ONLY)
install ( FILES ${AMREX_CONFIG_INSTALL_OUTFILE} DESTINATION ${AMREX_CMAKE_DIR})

#
# Install Tools directory
#
install (DIRECTORY ${PROJECT_SOURCE_DIR}/Tools
   DESTINATION ${CMAKE_INSTALL_PREFIX}
   USE_SOURCE_PERMISSIONS )

