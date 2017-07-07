# Copyright 2012-2017 CNRS-UM LIRMM, CNRS-AIST JRL
#
# This file is part of eigen-quadprog.
#
# eigen-lssol is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# eigen-lssol is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with eigen-lssol.  If not, see <http://www.gnu.org/licenses/>.

cimport c_eigen_quadprog

cdef class QuadProgDense(object):
  cdef c_eigen_quadprog.QuadProgDense * impl
