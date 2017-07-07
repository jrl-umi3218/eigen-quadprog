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

#pragma once

// includes
// Eigen
#include <Eigen/Core>
#include <Eigen/Sparse>

// eigen-quadprog
#include "eigen_quadprog_api.h"

namespace Eigen
{

extern "C" int qpgen1_(double* dmat, double* dvec, const int* fddmat,
	const int* n, double* sol, double* crval, double* amat, const int* iamat,
	double* bvec, const int* fdamat, const int* q, const int* meq, int* iact,
	int* nact, int* iter, double* work, const int* ierr);

extern "C" int qpgen2_(double* dmat, double* dvec, const int* fddmat,
	const int* n, double* sol, double* crval, double* amat, double* bvec,
	const int* fdamat, const int* q, const int* meq, int* iact, int* nact,
	int* iter, double* work, const int* ierr);


class QuadProgCommon
{
public:
	EIGEN_QUADPROG_API QuadProgCommon();

	EIGEN_QUADPROG_API const VectorXi& iter() const;
	EIGEN_QUADPROG_API int fail() const;

	EIGEN_QUADPROG_API const VectorXd& result() const;

	EIGEN_QUADPROG_API void problem(int nrvar, int nreq, int nrineq);

        EIGEN_QUADPROG_API double cost() const;

protected:
	void fillQCBf(int nreq, int nrineq,
		const MatrixXd& Q, const VectorXd& C,
		const VectorXd& Beq, const VectorXd& Bineq,
		bool isDecomp);

protected:
	MatrixXd Q_;
	VectorXd C_, B_, X_;
	int fail_;
	VectorXi iact_;
	VectorXi iter_;
	VectorXd work_;
        double cost_;
};


class QuadProgDense : public QuadProgCommon
{
public:
	EIGEN_QUADPROG_API QuadProgDense();
	EIGEN_QUADPROG_API QuadProgDense(int nrvar, int nreq, int nrineq);

	EIGEN_QUADPROG_API void problem(int nrvar, int nreq, int nrineq);

	EIGEN_QUADPROG_API bool solve(const MatrixXd& Q, const VectorXd& C,
		const MatrixXd& Aeq, const VectorXd& Beq,
		const MatrixXd& Aineq, const VectorXd& Bineq,
		bool isDecomp=false);

private:
	MatrixXd A_;
};


class QuadProgSparse : public QuadProgCommon
{
public:
	EIGEN_QUADPROG_API QuadProgSparse();
	EIGEN_QUADPROG_API QuadProgSparse(int nrvar, int nreq, int nrineq);

	EIGEN_QUADPROG_API void problem(int nrvar, int nreq, int nrineq);

	EIGEN_QUADPROG_API bool solve(const MatrixXd& Q, const VectorXd& C,
		const SparseMatrix<double>& Aeq, const VectorXd& Beq,
		const SparseMatrix<double>& Aineq, const VectorXd& Bineq,
		bool isDecomp=false);

private:
	MatrixXd A_;
	MatrixXi iA_;
};

} // namespace Eigen
