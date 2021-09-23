#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>

const char* dgemv_desc = "OpenMP dgemv.";

/*
 * This routine performs a dgemv operation
 * Y :=  A * X + Y
 * where A is n-by-n matrix stored in row-major format, and X and Y are n by 1 vectors.
 * On exit, A and X maintain their input values.
 */

void my_dgemv(int n, double* A, double* x, double* y) {

#if defined(EXPLICIT)
	
	#pragma omp parallel
	{
		int nthreads = omp_get_num_threads();
		int thread_id = omp_get_thread_num();
		int total = n/nthreads;
		int end = total*(thread_id + 1);
		for (int i = total*thread_id; i < end; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				y[i] += A[i*n + j]*x[j];
			}
		}
	}
	
#elif defined(NESTED)
	
	#pragma omp parallel
	{
		int nthreads = omp_get_num_threads();
		int thread_id = omp_get_thread_num();
		int total = n/nthreads;
		int end = total*(thread_id + 1);
		for (int i = total*thread_id; i < end; ++i)
		{
			#pragma omp parallel for
			for (int j = 0; j < n; ++j)
			{
				y[i] += A[i*n + j]*x[j];
			}
		}
	}
	
#elif defined(COLLAPSE)
	
	#pragma omp parallel for collapse(2)
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			y[i] += A[i*n + j]*x[j];
		}
	}
	
#else
	
	#pragma omp parallel for
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			y[i] += A[i*n + j]*x[j];
		}
	}
	
#endif
}

