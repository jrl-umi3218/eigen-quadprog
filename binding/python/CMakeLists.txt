# Copyright 2012-2017 CNRS-UM LIRMM, CNRS-AIST JRL
#
# This file is part of eigen-quadprog.
#
# eigen-quadprog is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# eigen-quadprog is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with eigen-quadprog.  If not, see <http://www.gnu.org/licenses/>.

macro(GET_EQUADPROG_PROPERTY PROPERTY)
  get_target_property(EQUADPROG_${PROPERTY} eigen-quadprog ${PROPERTY})
  if(NOT EQUADPROG_${PROPERTY})
    set(EQUADPROG_${PROPERTY} "")
  endif()
endmacro()
GET_EQUADPROG_PROPERTY(COMPILE_FLAGS)
GET_EQUADPROG_PROPERTY(INCLUDE_DIRECTORIES)
LIST(APPEND EQUADPROG_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/../../src)
GET_EQUADPROG_PROPERTY(LINK_FLAGS)
GET_EQUADPROG_PROPERTY(LINK_LIBRARIES)
GET_EQUADPROG_PROPERTY(LOCATION)
configure_file(setup.in.py ${CMAKE_CURRENT_SOURCE_DIR}/setup.py)

# Build the bindings locally at build time for test purposes
add_custom_target(eigen-quadprog-python-bindings ALL
  COMMAND python setup.py build_ext --inplace
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "Generating local eigen-quadprog Python bindings"
  DEPENDS eigen_quadprog/c_eigen_quadprog.pxd eigen_quadprog/eigen_quadprog.pxd eigen_quadprog/eigen_quadprog.pyx
)

if(NOT ${DISABLE_TESTS})
  add_custom_target(test-eigen-quadprog-python-bindings
    COMMAND nosetests
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Test eigen-quadprog Python bindings"
    DEPENDS tests/test_eigen-quadprog_pickle.py
  )
  add_test(NAME PythonBindingsTest
    COMMAND nosetests
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )
endif()

set(PIP_EXTRA_OPTIONS "")
if(${PYTHON_BINDING_USER_INSTALL})
  set(PIP_EXTRA_OPTIONS "--user")
endif()
# Install the bindings
add_custom_target(install-eigen-quadprog-python-bindings
  COMMAND pip install . ${PIP_EXTRA_OPTIONS}
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "Install eigen-quadprog Python bindings"
)
install(CODE "execute_process(COMMAND ${CMAKE_MAKE_PROGRAM} install-eigen-quadprog-python-bindings)")
