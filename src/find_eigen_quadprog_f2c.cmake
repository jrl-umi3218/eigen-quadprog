function(find_eigen_quadprog_f2c)
  if(TARGET eigen-quadprog::f2c)
    return()
  endif()
  if(NOT DEFINED F2C_PREFIX)
    set(F2C_PREFIX "${CMAKE_INSTALL_PREFIX}")
  endif()

  find_path(
    F2C_INCLUDE_DIR
    NAMES f2c.h
    HINTS ${F2C_PREFIX})

  find_library(
    F2C_LIBRARY
    NAMES f2c
    PATHS ${F2C_PREFIX})

  include(FindPackageHandleStandardArgs)
  find_package_handle_standard_args(F2C DEFAULT_MSG F2C_LIBRARY F2C_INCLUDE_DIR)
  mark_as_advanced(F2C_INCLUDE_DIR F2C_LIBRARY)
  if(F2C_FOUND)
    add_library(eigen-quadprog::f2c INTERFACE IMPORTED GLOBAL)
    set_target_properties(
      eigen-quadprog::f2c
      PROPERTIES INTERFACE_INCLUDE_DIRECTORIES ${F2C_INCLUDE_DIR}
                 INTERFACE_LINK_LIBRARIES ${F2C_LIBRARY})
  endif()
endfunction()
