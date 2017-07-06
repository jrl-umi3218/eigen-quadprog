# distutils: language = c++

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

cdef extern from "private_typedefs.h":
  pass

cimport c_eigen_quadprog

cimport eigen.eigen as eigen

cdef class QuadProgDense(object):
  def __dealloc__(self):
    if type(self) is QuadProgDense:
      del self.impl
  def __cinit__(self, *args):
    if type(self) is not QuadProgDense:
      return
    if len(args) == 0:
      self.impl = new c_eigen_quadprog.QuadProgDense()
    elif len(args) == 3:
      self.impl = new c_eigen_quadprog.QuadProgDense(args[0], args[1], args[2])
    else:
      raise TypeError("Wrong arguments passed to LSSOL ctor")
  def problem(self, nrvar, nreq, nrineq):
    self.impl.problem(nrvar, nreq, nrineq)
  def result(self):
    return eigen.VectorXdFromC(self.impl.result())
  def solve(self, eigen.MatrixXd Q, eigen.VectorXd C,
                  eigen.MatrixXd Aeq, eigen.VectorXd Beq,
                  eigen.MatrixXd Aineq, eigen.VectorXd Bineq,
                  isDecomp = False):
    return self.impl.solve(Q.impl, C.impl, Aeq.impl, Beq.impl, Aineq.impl, Bineq.impl,isDecomp)
