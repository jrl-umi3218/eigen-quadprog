cmake_minimum_required(VERSION 3.1.3)

include(cmake/base.cmake)
include(cmake/boost.cmake)
include(cmake/msvc-specific.cmake)

set(PROJECT_NAME eigen-quadprog)
set(PROJECT_DESCRIPTION "QuadProg QP solver through Eigen3 library.")
set(PROJECT_URL "https://github.com/jorisv/RBDyn/eigen-quadprog")
set(PROJECT_DEBUG_POSTFIX "_d")

set(CMAKE_CXX_STANDARD 11)
set(CXX_DISABLE_WERROR True) # disable -Werror on Unix for now.
set(DOXYGEN_USE_MATHJAX "YES")

option(USE_F2C "Use f2c converted code (usually slower)." OFF)
if(WIN32)
  set(USE_FORTRAN_SUBDIRECTORY_DEFAULT ON)
else()
  set(USE_FORTRAN_SUBDIRECTORY_DEFAULT OFF)
endif()
option(USE_FORTRAN_SUBDIRECTORY "Use cmake to generate sub project for fortran parts" ${USE_FORTRAN_SUBDIRECTORY_DEFAULT})
option(DISABLE_TESTS "Disable unit tests." OFF)

setup_project()
set(PROJECT_VERSION 1.0.0)

add_project_dependency(Eigen3 REQUIRED)

if(MSVC)
  if(USE_FORTRAN_SUBDIRECTORY)
    set(CMAKE_MSVCIDE_RUN_PATH "\$(SolutionDir)/src/\$(Configuration);\$(SolutionDir)/src/quadprog_fortran")
  else()
    set(CMAKE_MSVCIDE_RUN_PATH "\$(SolutionDir)/src/\$(Configuration)")
  endif()
endif(MSVC)

#########################

add_subdirectory(src)

if(NOT ${DISABLE_TESTS})
  add_subdirectory(tests)
endif()

setup_project_finalize()
setup_project_package_finalize()
