project(quadprog_fortran Fortran)

set(QUAD_FORT ../QuadProg/f/solve.QP.f ../QuadProg/f/solve.QP.compact.f
              ../QuadProg/f/util.f)

set(BLAS_FORT ../BLAS/f/blas.f)

add_library(quadprog_fortran ${QUAD_FORT} ${BLAS_FORT})
set_target_properties(quadprog_fortran PROPERTIES IMPORT_SUFFIX ".lib")
