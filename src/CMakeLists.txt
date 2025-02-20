if(NOT (${USE_F2C} OR ${USE_FORTRAN_SUBDIRECTORY}))
  enable_language(Fortran)
elseif(${USE_F2C})
  enable_language(C)
endif()

set(SOURCES QuadProg.cpp)
set(HEADERS eigen_quadprog_api.h QuadProg.h)

set(QUAD_FORT QuadProg/f/solve.QP.f QuadProg/f/solve.QP.compact.f QuadProg/f/util.f)
set(QUAD_C QuadProg/c/solve.QP.c QuadProg/c/solve.QP.compact.c QuadProg/c/util.c)

set(BLAS_FORT BLAS/f/blas.f)
set(BLAS_C BLAS/c/blas.c)

if(${USE_F2C})
  list(APPEND SOURCES ${QUAD_C} ${BLAS_C})
elseif(NOT ${USE_FORTRAN_SUBDIRECTORY})
  list(APPEND SOURCES ${QUAD_FORT} ${BLAS_FORT})
endif()

add_library(${PROJECT_NAME} SHARED ${SOURCES} ${HEADERS})
target_include_directories(
  ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                         $<INSTALL_INTERFACE:include>
)
set_target_properties(
  ${PROJECT_NAME} PROPERTIES SOVERSION ${PROJECT_VERSION_MAJOR} VERSION
                                                                ${PROJECT_VERSION}
)
set_target_properties(
  ${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-DEIGEN_QUADPROG_EXPORT"
)
if(TARGET Eigen3::Eigen)
  target_link_libraries(${PROJECT_NAME} PUBLIC Eigen3::Eigen)
else()
  target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${EIGEN3_INCLUDE_DIR}")
endif()

if(${USE_FORTRAN_SUBDIRECTORY})
  include(CMakeAddFortranSubdirectory)
  cmake_add_fortran_subdirectory(
    quadprog_fortran
    PROJECT quadprog_fortran # project name in toplevel CMakeLists.txt in lapack
    ARCHIVE_DIR quadprog_fortran # .lib location relative to root binary tree
    RUNTIME_DIR quadprog_fortran # .dll location relative to root binary tree
    LIBRARIES quadprog_fortran # target libraries created
    LINK_LIBRARIES # link interface libraries
    NO_EXTERNAL_INSTALL
  )
  set(quadprog_fortran_SHARED_LIBRARY
      ${CMAKE_CURRENT_BINARY_DIR}/quadprog_fortran/libquadprog_fortran${CMAKE_SHARED_LIBRARY_SUFFIX}
  )
  set(quadprog_fortran_STATIC_LIBRARY
      ${CMAKE_CURRENT_BINARY_DIR}/quadprog_fortran/libquadprog_fortran${CMAKE_STATIC_LIBRARY_SUFFIX}
  )
  # Required here because qld_fortran is external to this project and install does not
  # run
  if(WIN32)
    install(FILES ${quadprog_fortran_SHARED_LIBRARY}
            DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    install(FILES ${quadprog_fortran_STATIC_LIBRARY}
            DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
    set(PACKAGE_EXTRA_MACROS
        "
get_filename_component(PACKAGE_PREFIX_DIR \"\${CMAKE_CURRENT_LIST_DIR}/../../../\" ABSOLUTE)
if(NOT TARGET quadprog_fortran)
  add_library(quadprog_fortran STATIC IMPORTED)
  set_target_properties(quadprog_fortran PROPERTIES
    IMPORTED_LOCATION \"\${PACKAGE_PREFIX_DIR}/lib/libquadprog_fortran${CMAKE_STATIC_LIBRARY_SUFFIX}\"
  )
endif()
"
        PARENT_SCOPE
    )
  endif()
  target_link_libraries(${PROJECT_NAME} PUBLIC quadprog_fortran)
endif()

if(${USE_F2C})
  include(find_eigen_quadprog_f2c.cmake)
  find_eigen_quadprog_f2c()
  target_link_libraries(${PROJECT_NAME} PUBLIC eigen-quadprog::f2c)
  set(PACKAGE_EXTRA_MACROS
      "${PACKAGE_EXTRA_MACROS}
  include(\"\${CMAKE_CURRENT_LIST_DIR}/find_eigen_quadprog_f2c.cmake\")
  find_eigen_quadprog_f2c()
  "
      PARENT_SCOPE
  )
  install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/find_eigen_quadprog_f2c.cmake"
          DESTINATION "${CONFIG_INSTALL_DIR}"
  )
endif()

install(
  TARGETS ${PROJECT_NAME}
  EXPORT "${TARGETS_EXPORT_NAME}"
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
install(FILES ${HEADERS} DESTINATION ${INCLUDE_INSTALL_DESTINATION})
