/* f/blas.f -- translated by f2c (version 20100827).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Table of constant values */

static integer c__1 = 1;

/* Subroutine */ int daxpy_(integer *n, doublereal *da, doublereal *dx, 
	integer *incx, doublereal *dy, integer *incy)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, m, ix, iy, mp1;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*     DAXPY constant times a vector plus a vector. */
/*     uses unrolled loops for increments equal to one. */

/*  Further Details */
/*  =============== */

/*     jack dongarra, linpack, 3/11/78. */
/*     modified 12/3/93, array(1) declarations changed to array(*) */

/*  ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
    /* Parameter adjustments */
    --dy;
    --dx;

    /* Function Body */
    if (*n <= 0) {
	return 0;
    }
    if (*da == 0.) {
	return 0;
    }
    if (*incx == 1 && *incy == 1) {

/*        code for both increments equal to 1 */


/*        clean-up loop */

	m = *n % 4;
	if (m != 0) {
	    i__1 = m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		dy[i__] += *da * dx[i__];
	    }
	}
	if (*n < 4) {
	    return 0;
	}
	mp1 = m + 1;
	i__1 = *n;
	for (i__ = mp1; i__ <= i__1; i__ += 4) {
	    dy[i__] += *da * dx[i__];
	    dy[i__ + 1] += *da * dx[i__ + 1];
	    dy[i__ + 2] += *da * dx[i__ + 2];
	    dy[i__ + 3] += *da * dx[i__ + 3];
	}
    } else {

/*        code for unequal increments or equal increments */
/*          not equal to 1 */

	ix = 1;
	iy = 1;
	if (*incx < 0) {
	    ix = (-(*n) + 1) * *incx + 1;
	}
	if (*incy < 0) {
	    iy = (-(*n) + 1) * *incy + 1;
	}
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    dy[iy] += *da * dx[ix];
	    ix += *incx;
	    iy += *incy;
	}
    }
    return 0;
} /* daxpy_ */

doublereal ddot_(integer *n, doublereal *dx, integer *incx, doublereal *dy, 
	integer *incy)
{
    /* System generated locals */
    integer i__1;
    doublereal ret_val;

    /* Local variables */
    static integer i__, m, ix, iy, mp1;
    static doublereal dtemp;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*     DDOT forms the dot product of two vectors. */
/*     uses unrolled loops for increments equal to one. */

/*  Further Details */
/*  =============== */

/*     jack dongarra, linpack, 3/11/78. */
/*     modified 12/3/93, array(1) declarations changed to array(*) */

/*  ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
    /* Parameter adjustments */
    --dy;
    --dx;

    /* Function Body */
    ret_val = 0.;
    dtemp = 0.;
    if (*n <= 0) {
	return ret_val;
    }
    if (*incx == 1 && *incy == 1) {

/*        code for both increments equal to 1 */


/*        clean-up loop */

	m = *n % 5;
	if (m != 0) {
	    i__1 = m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		dtemp += dx[i__] * dy[i__];
	    }
	    if (*n < 5) {
		ret_val = dtemp;
		return ret_val;
	    }
	}
	mp1 = m + 1;
	i__1 = *n;
	for (i__ = mp1; i__ <= i__1; i__ += 5) {
	    dtemp = dtemp + dx[i__] * dy[i__] + dx[i__ + 1] * dy[i__ + 1] + 
		    dx[i__ + 2] * dy[i__ + 2] + dx[i__ + 3] * dy[i__ + 3] + 
		    dx[i__ + 4] * dy[i__ + 4];
	}
    } else {

/*        code for unequal increments or equal increments */
/*          not equal to 1 */

	ix = 1;
	iy = 1;
	if (*incx < 0) {
	    ix = (-(*n) + 1) * *incx + 1;
	}
	if (*incy < 0) {
	    iy = (-(*n) + 1) * *incy + 1;
	}
	i__1 = *n;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    dtemp += dx[ix] * dy[iy];
	    ix += *incx;
	    iy += *incy;
	}
    }
    ret_val = dtemp;
    return ret_val;
} /* ddot_ */

/* Subroutine */ int dpofa_(doublereal *a, integer *lda, integer *n, integer *
	info)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer j, k;
    static doublereal s, t;
    static integer jm1;
    extern doublereal ddot_(integer *, doublereal *, integer *, doublereal *, 
	    integer *);


/*     dpofa factors a double precision symmetric positive definite */
/*     matrix. */

/*     dpofa is usually called by dpoco, but it can be called */
/*     directly with a saving in time if  rcond  is not needed. */
/*     (time for dpoco) = (1 + 18/n)*(time for dpofa) . */

/*     on entry */

/*        a       double precision(lda, n) */
/*                the symmetric matrix to be factored.  only the */
/*                diagonal and upper triangle are used. */

/*        lda     integer */
/*                the leading dimension of the array  a . */

/*        n       integer */
/*                the order of the matrix  a . */

/*     on return */

/*        a       an upper triangular matrix  r  so that  a = trans(r)*r */
/*                where  trans(r)  is the transpose. */
/*                the strict lower triangle is unaltered. */
/*                if  info .ne. 0 , the factorization is not complete. */

/*        info    integer */
/*                = 0  for normal return. */
/*                = k  signals an error condition.  the leading minor */
/*                     of order  k  is not positive definite. */

/*     linpack.  this version dated 08/14/78 . */
/*     cleve moler, university of new mexico, argonne national lab. */

/*     subroutines and functions */

/*     blas ddot */
/*     fortran dsqrt */

/*     internal variables */

/*     begin block with ...exits to 40 */


    /* Parameter adjustments */
    a_dim1 = *lda;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	*info = j;
	s = 0.;
	jm1 = j - 1;
	if (jm1 < 1) {
	    goto L20;
	}
	i__2 = jm1;
	for (k = 1; k <= i__2; ++k) {
	    i__3 = k - 1;
	    t = a[k + j * a_dim1] - ddot_(&i__3, &a[k * a_dim1 + 1], &c__1, &
		    a[j * a_dim1 + 1], &c__1);
	    t /= a[k + k * a_dim1];
	    a[k + j * a_dim1] = t;
	    s += t * t;
/* L10: */
	}
L20:
	s = a[j + j * a_dim1] - s;
/*     ......exit */
	if (s <= 0.) {
	    goto L40;
	}
	a[j + j * a_dim1] = sqrt(s);
/* L30: */
    }
    *info = 0;
L40:
    return 0;
} /* dpofa_ */

/* Subroutine */ int dscal_(integer *n, doublereal *da, doublereal *dx, 
	integer *incx)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    static integer i__, m, mp1, nincx;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */

/*  Purpose */
/*  ======= */

/*     DSCAL scales a vector by a constant. */
/*     uses unrolled loops for increment equal to one. */

/*  Further Details */
/*  =============== */

/*     jack dongarra, linpack, 3/11/78. */
/*     modified 3/93 to return if incx .le. 0. */
/*     modified 12/3/93, array(1) declarations changed to array(*) */

/*  ===================================================================== */

/*     .. Local Scalars .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
    /* Parameter adjustments */
    --dx;

    /* Function Body */
    if (*n <= 0 || *incx <= 0) {
	return 0;
    }
    if (*incx == 1) {

/*        code for increment equal to 1 */


/*        clean-up loop */

	m = *n % 5;
	if (m != 0) {
	    i__1 = m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		dx[i__] = *da * dx[i__];
	    }
	    if (*n < 5) {
		return 0;
	    }
	}
	mp1 = m + 1;
	i__1 = *n;
	for (i__ = mp1; i__ <= i__1; i__ += 5) {
	    dx[i__] = *da * dx[i__];
	    dx[i__ + 1] = *da * dx[i__ + 1];
	    dx[i__ + 2] = *da * dx[i__ + 2];
	    dx[i__ + 3] = *da * dx[i__ + 3];
	    dx[i__ + 4] = *da * dx[i__ + 4];
	}
    } else {

/*        code for increment not equal to 1 */

	nincx = *n * *incx;
	i__1 = nincx;
	i__2 = *incx;
	for (i__ = 1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
	    dx[i__] = *da * dx[i__];
	}
    }
    return 0;
} /* dscal_ */
