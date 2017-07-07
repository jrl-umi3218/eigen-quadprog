#pragma once

#ifdef WIN32
    #define EIGEN_QUADPROG_DLLIMPORT __declspec(dllimport)
    #define EIGEN_QUADPROG_DLLEXPORT __declspec(dllexport)
#else
    #define EIGEN_QUADPROG_DLLIMPORT
    #define EIGEN_QUADPROG_DLLEXPORT
#endif

#ifdef EIGEN_QUADPROG_EXPORT
    #define EIGEN_QUADPROG_API EIGEN_QUADPROG_DLLEXPORT
#else
    #define EIGEN_QUADPROG_API EIGEN_QUADPROG_DLLIMPORT
#endif
