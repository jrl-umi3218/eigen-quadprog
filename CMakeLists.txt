cmake_minimum_required(VERSION 2.8)

include(cmake/base.cmake)
include(cmake/boost.cmake)
include(cmake/eigen.cmake)

set(PROJECT_NAME eigen-quadprog)
set(PROJECT_DESCRIPTION "QuadProg QP solver through Eigen3 library.")
set(PROJECT_URL "https://github.com/jorisv/RBDyn/eigen-quadprog")

project(${PROJECT_NAME} CXX)

# Disable -Werror on Unix for now.
set(CXX_DISABLE_WERROR True)
set(DOXYGEN_USE_MATHJAX "YES")

option(USE_F2C "Use f2c converted code (usually slower)." OFF)
option(USE_FORTRAN_SUBDIRECTORY "Use cmake to generate sub project for fortran parts" OFF)

if(WIN32)
  set(USE_F2C OFF)
  set(USE_FORTRAN_SUBDIRECTORY ON)
endif()

setup_project()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

#########################
# External dependencies
if(PKG_CONFIG_FOUND)
  search_for_eigen()
else()
  find_path(Eigen_INCLUDE_DIR NAMES signature_of_eigen3_matrix_library
    PATHS
    ${CMAKE_INSTALL_PREFIX}/include
    PATH_SUFFIXES eigen3 eigen
  )
  include_directories(SYSTEM ${Eigen_INCLUDE_DIR})
endif()

#########################

add_definitions("-DEIGEN_QUADPROG_EXPORT")

add_subdirectory(src)
add_subdirectory(tests)

# Add dependency towards the library in the pkg-config file.
pkg_config_append_libs(${PROJECT_NAME})

setup_project_finalize()
