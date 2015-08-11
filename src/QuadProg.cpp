// This file is part of EigenQP.
//
// EigenQP is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// EigenQP is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with EigenQP.  If not, see <http://www.gnu.org/licenses/>.

// associated header
#include "QuadProg.h"

namespace Eigen
{


/**
	*												QuadProgCommon
	*/


QuadProgCommon::QuadProgCommon():
	Q_(),
	C_(),
	B_(),
	X_(),
	fail_(0),
	iact_(),
	iter_(2)
{
}


const VectorXi& QuadProgCommon::iter() const
{
	return iter_;
}


int QuadProgCommon::fail() const
{
	return fail_;
}


const VectorXd& QuadProgCommon::result() const
{
	return X_;
}


void QuadProgCommon::problem(int nrvar, int nreq, int nrineq)
{
	int nrconstr = nreq + nrineq;

	Q_.resize(nrvar, nrvar);

	C_.resize(nrvar);
	B_.resize(nrconstr);
	X_.resize(nrvar);

	iact_.resize(nrconstr);

	// compute work size, see fortran file to understand
	int r = std::min(nrvar, nrconstr);
	int lwork = static_cast<int>(
		std::ceil(2.*nrvar + r*(r + 5.)/2. + 2.*nrconstr + 1.));
	work_.resize(lwork);
}


void QuadProgCommon::fillQCBf(int nreq, int nrineq,
	const MatrixXd& Q, const VectorXd& C,
	const VectorXd& Beq, const VectorXd& Bineq,
	bool isDecomp)
{
	Q_ = Q;
	C_ = -C;

	B_.segment(0, nreq) = Beq;
	B_.segment(nreq, nrineq) = -Bineq;

	fail_ = isDecomp ? 1 : 0;
}


/**
	*												QuadProgDense
	*/


QuadProgDense::QuadProgDense():
	A_()
{ }


QuadProgDense::QuadProgDense(int nrvar, int nreq, int nrineq):
	A_()
{
	problem(nrvar, nreq, nrineq);
}


void QuadProgDense::problem(int nrvar, int nreq, int nrineq)
{
	QuadProgCommon::problem(nrvar, nreq, nrineq);
	int nrconstr = nreq + nrineq;

	A_.resize(nrvar, nrconstr);
}


bool QuadProgDense::solve(const MatrixXd& Q, const VectorXd& C,
	const MatrixXd& Aeq, const VectorXd& Beq,
	const MatrixXd& Aineq, const VectorXd& Bineq,
	bool isDecomp)
{
	int nrvar = static_cast<int>(C.rows());
	int nreq = static_cast<int>(Beq.rows());
	int nrineq = static_cast<int>(Bineq.rows());

	int fddmat = static_cast<int>(Q_.rows());
	int n = nrvar;
	double crval;
	int fdamat = static_cast<int>(A_.rows());
	int q = nreq + nrineq;
	int meq = nreq;
	int nact;

	fillQCBf(nreq, nrineq, Q, C, Beq, Bineq, isDecomp);

	A_.block(0, 0, nrvar, nreq) = Aeq.transpose();
	A_.block(0, nreq, nrvar, nrineq) = -Aineq.transpose();

	qpgen2_(Q_.data(), C_.data(), &fddmat, &n, X_.data(), &crval,
		A_.data(), B_.data(), &fdamat, &q, &meq, iact_.data(), &nact,
		iter_.data(), work_.data(), &fail_);

	return fail_ == 0;
}


/**
	*												QuadProgSparse
	*/


QuadProgSparse::QuadProgSparse():
  A_(),
  iA_()
{ }


QuadProgSparse::QuadProgSparse(int nrvar, int nreq, int nrineq):
  A_(),
  iA_()
{
  problem(nrvar, nreq, nrineq);
}


void QuadProgSparse::problem(int nrvar, int nreq, int nrineq)
{
	QuadProgCommon::problem(nrvar, nreq, nrineq);
	int nrconstr = nreq + nrineq;

	A_.resize(nrvar, nrconstr);
	iA_.resize(nrvar + 1, nrconstr);
}


bool QuadProgSparse::solve(const MatrixXd& Q, const VectorXd& C,
	const SparseMatrix<double>& Aeq, const VectorXd& Beq,
	const SparseMatrix<double>& Aineq, const VectorXd& Bineq,
	bool isDecomp)
{
	int nrvar = static_cast<int>(C.rows());
	int nreq = static_cast<int>(Beq.rows());
	int nrineq = static_cast<int>(Bineq.rows());

	int fddmat = static_cast<int>(Q_.rows());
	int n = nrvar;
	double crval;
	int fdamat = static_cast<int>(A_.rows());
	int q = nreq + nrineq;
	int meq = nreq;
	int nact;

	fillQCBf(nreq, nrineq, Q, C, Beq, Bineq, isDecomp);

	iA_.row(0).setZero();

	// in A{eq,ineq} row is the constraint index, col is the variable index
	// so row its A_ col and col is A_ row.
	for(int k = 0; k < Aeq.outerSize(); ++k)
	{
		for(SparseMatrix<double>::InnerIterator it(Aeq, k); it; ++it)
		{
			int nrValCi = iA_(0, it.row()) += 1;
			iA_(nrValCi, it.row()) = it.col() + 1;
			A_(nrValCi - 1, it.row()) = it.value();
		}
	}

	for(int k = 0; k < Aineq.outerSize(); ++k)
	{
		for(SparseMatrix<double>::InnerIterator it(Aineq, k); it; ++it)
		{
			int nrValCi = iA_(0, it.row() + nreq) += 1;
			iA_(nrValCi, it.row() + nreq) = it.col() + 1;
			A_(nrValCi - 1, it.row() + nreq) = -it.value();
		}
	}

	qpgen1_(Q_.data(), C_.data(), &fddmat, &n, X_.data(), &crval,
		A_.data(), iA_.data(), B_.data(), &fdamat, &q, &meq, iact_.data(), &nact,
		iter_.data(), work_.data(), &fail_);

	return fail_ == 0;
}


} // namespace Eigen
