# Copyright 2012-2017 CNRS-UM LIRMM, CNRS-AIST JRL
#
# This file is part of eigen-lssol.
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

cimport eigen.c_eigen as c_eigen
from libcpp cimport bool

cdef extern from "<eigen-quadprog/QuadProg.h>" namespace "Eigen":
  cdef cppclass QuadProgDense:
    QuadProgDense()
    QuadProgDense(int, int, int)

    void problem(int, int, int)

    const c_eigen.VectorXd& result()

    bool solve(const c_eigen.MatrixXd&, const c_eigen.VectorXd&,
        const c_eigen.MatrixXd&,
        const c_eigen.VectorXd&, const c_eigen.MatrixXd&,
        const c_eigen.VectorXd&, bool)
