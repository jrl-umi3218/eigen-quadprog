# -*- coding: utf-8 -*-
#
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

# Port of the C++ test

import unittest

import eigen
import eigen_quadprog

class QP1(object):
  def __init__(self):
    self.nrvar = 6
    self.nreq = 3
    self.nrineq = 2

    self.Q = eigen.MatrixXd.Identity(self.nrvar, self.nrvar)

    self.Aeq = eigen.MatrixXd([ [1., -1., 1., 0., 3., 1.],
                                [-1., 0., -3., -4., 5., 6.],
                                [2., 5., 3., 0., 1., 0.] ])
    self.Beq = eigen.VectorXd([1., 2., 3.])

    self.Aineq = eigen.MatrixXd([ [0., 1., 0., 1., 2., -1.],
                                  [-1., 0., 2., 1., 1., 0.] ])
    self.Bineq = eigen.VectorXd([-1., 2.5])

    self.XL = eigen.VectorXd([ -1000., -10000., 0., -1000., -1000.,-1000. ])
    self.XU = eigen.VectorXd([ 10000., 100., 1.5, 100., 100., 1000. ])

    self.C = eigen.VectorXd([ 1., 2., 3., 4., 5., 6. ])

    self.X = eigen.VectorXd([ 1.7975426, -0.3381487, 0.1633880, -4.9884023, 0.6054943, -3.1155623 ])

def ineqWithXBounds(Aineq, Bineq, XL, XU):
  inf = float('inf')

  lbounds = [ (i, XL[i]) for i in range(XL.rows()) if XL[i] != -inf ]
  ubounds = [ (i, XU[i]) for i in range(XU.rows()) if XU[i] != inf ]

  nrconstr = Bineq.rows() + len(lbounds) + len(ubounds)

  A = eigen.MatrixXd.Zero(nrconstr, Aineq.cols())
  B = eigen.VectorXd.Zero(nrconstr)

  # "block" copy
  for i in range(Aineq.rows()):
    for j in range(Aineq.cols()):
      A[i,j] = Aineq[i,j]
  for i in range(Bineq.rows()):
    B[i] = Bineq[i]

  start = Aineq.rows()
  for i in range(len(lbounds)):
    A[start, lbounds[i][0]] = -1
    B[start] = -lbounds[i][1]
    start += 1
  for i in range(len(ubounds)):
    A[start, ubounds[i][0]] = 1
    B[start] = ubounds[i][1]
    start += 1

  return A, B

class TestIneqWithXBounds(unittest.TestCase):
  def test(self):
    qp1 = QP1()

    Aineq, Bineq = ineqWithXBounds(qp1.Aineq, qp1.Bineq, qp1.XL, qp1.XU)

    nrineq = Aineq.rows()
    quadprog = eigen_quadprog.QuadProgDense(qp1.nrvar, qp1.nreq, nrineq)

    self.assertTrue(quadprog.solve(qp1.Q, qp1.C, qp1.Aeq, qp1.Beq, Aineq, Bineq))

    self.assertAlmostEqual((quadprog.result() - qp1.X).norm(), 0, 6)
