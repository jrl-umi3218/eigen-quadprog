cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)
set(CXX_DISABLE_WERROR True) # disable -Werror on Unix for now.

set(PROJECT_NAME eigen-quadprog)
set(PROJECT_DESCRIPTION "QuadProg QP solver through Eigen3 library.")
set(PROJECT_URL "https://github.com/jrl-umi3218/eigen-quadprog")
set(PROJECT_DEBUG_POSTFIX "_d")
set(PROJECT_VERSION 1.1.4)
set(PROJECT_USE_CMAKE_EXPORT TRUE)

set(DOXYGEN_USE_MATHJAX "YES")

# Check if the submodule cmake have been initialized
set(JRL_CMAKE_MODULES "${CMAKE_CURRENT_LIST_DIR}/cmake")
if(EXISTS "${JRL_CMAKE_MODULES}/base.cmake")
  message(STATUS "JRL cmakemodules found in 'cmake/' git submodule")
else()
  find_package(jrl-cmakemodules QUIET CONFIG)
  if(jrl-cmakemodules_FOUND)
    get_property(
      JRL_CMAKE_MODULES
      TARGET jrl-cmakemodules::jrl-cmakemodules
      PROPERTY INTERFACE_INCLUDE_DIRECTORIES)
    message(STATUS "JRL cmakemodules found on system at ${JRL_CMAKE_MODULES}")
  else()
    message(STATUS "JRL cmakemodules not found. Let's fetch it.")
    include(FetchContent)
    FetchContent_Declare(
      "jrl-cmakemodules"
      GIT_REPOSITORY "https://github.com/jrl-umi3218/jrl-cmakemodules.git")
    FetchContent_MakeAvailable("jrl-cmakemodules")
    FetchContent_GetProperties("jrl-cmakemodules" SOURCE_DIR JRL_CMAKE_MODULES)
  endif()
endif()
include(${JRL_CMAKE_MODULES}/base.cmake)
include(${JRL_CMAKE_MODULES}/msvc-specific.cmake)

project(eigen-quadprog C CXX)

option(USE_F2C "Use f2c converted code (usually slower)." OFF)
if(WIN32)
  set(USE_FORTRAN_SUBDIRECTORY_DEFAULT ON)
else()
  set(USE_FORTRAN_SUBDIRECTORY_DEFAULT OFF)
endif()
option(USE_FORTRAN_SUBDIRECTORY
       "Use cmake to generate sub project for fortran parts"
       ${USE_FORTRAN_SUBDIRECTORY_DEFAULT})
option(DISABLE_TESTS "Disable unit tests." OFF)

find_package(Eigen3 QUIET NO_CMAKE_PACKAGE_REGISTRY)
if(Eigen3_FOUND)
  add_project_dependency(Eigen3 REQUIRED NO_CMAKE_PACKAGE_REGISTRY)
else()
  add_project_dependency(Eigen3 MODULE REQUIRED)
endif()

if(MSVC)
  if(USE_FORTRAN_SUBDIRECTORY)
    set(CMAKE_MSVCIDE_RUN_PATH
        "\$(SolutionDir)/src/\$(Configuration);\$(SolutionDir)/src/quadprog_fortran"
    )
  else()
    set(CMAKE_MSVCIDE_RUN_PATH "\$(SolutionDir)/src/\$(Configuration)")
  endif()
endif(MSVC)

# ##############################################################################

add_subdirectory(src)

if(${BUILD_TESTING})
  add_subdirectory(tests)
endif()
