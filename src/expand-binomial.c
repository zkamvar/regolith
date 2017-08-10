#include <Rinternals.h>
#include <R.h>
#include <Rdefines.h>
#define CAN_RUN 1

int intcmp (const void * a, const void * b);
SEXP omp_test();
SEXP larr_c(SEXP arr);
SEXP add_one_c(SEXP x);
// Simple function to check for openMP support
// Returns 1 if openMP is supported, 0 if it is not.
#ifdef CAN_RUN
SEXP expand_binomial_c(SEXP arr);
#endif



int intcmp (const void * a, const void * b)
{
	   return ( *(int*)a - *(int*)b );
}

SEXP omp_test()
{
  SEXP Rout;
  PROTECT(Rout = allocVector(INTSXP,1));
  #ifdef _OPENMP
  INTEGER(Rout)[0] = 1;
  #else
  INTEGER(Rout)[0] = 0;
  #endif
  UNPROTECT(1);
  return(Rout);
}

SEXP larr_c(SEXP arr)
{
	SEXP res = PROTECT(allocVector(INTSXP, 1));
	INTEGER(res)[0] = length(arr);
	UNPROTECT(1);
	return(res);
}

SEXP add_one_c(SEXP x)
{
	int n = length(x);
	SEXP out = PROTECT(allocVector(REALSXP, n));

	for (int i = 0; i < n; i++) {
		REAL(out)[i] = REAL(x)[i] + 1;
	}
	UNPROTECT(1);

	return out;
}

SEXP facts_c(SEXP n)
{
	int i;
	int N = asInteger(n);
	int* OUT;
	SEXP out = PROTECT(allocVector(INTSXP, N));
	OUT = INTEGER(out);
	for (i = 1; i <= N; i++) // 2017-08-10: fencepost error with i < N
	{
		OUT[i - 1] = (i == 1) ? i : OUT[i - 2] * i;
	}
	UNPROTECT(1);
	return(out);
}

SEXP sort_c(SEXP arr)
{
	SEXP res = PROTECT(allocVector(INTSXP, length(arr)));
	R_qsort_int(INTEGER(arr), 0, length(arr));
	for (int i = 0; i < length(arr); i++)
	{
		INTEGER(res)[i] = INTEGER(arr)[i];
	}
	UNPROTECT(1);
	return(res);
}

#ifdef CAN_RUN
SEXP expand_binomial_c(SEXP arr) {
 	SEXP res = PROTECT(allocVector(INTSXP, 1));
 	int* RES = INTEGER(res);
 	int i;
 	int n = length(arr);
 	int count = 1;
 	int* facts;
 	facts = R_Calloc(n, int);
 	for (i = 1; i <= n; i++)
 	{
 		facts[i - 1] = (i == 1) ? i : facts[i - 2] * i;
 	}
 	R_qsort_int(INTEGER(arr), 0, n);
 	int previous_value = INTEGER(arr)[0];
 	RES[0] = count;
 	for (i = 1; i < n; i++)
  	{
		if (INTEGER(arr)[i] != previous_value)
		{
			RES[0] *= facts[count - 1];
			Rprintf("%d count: %d (%d)\n", INTEGER(arr)[i - 1], count, RES[0]);
			count = 1;
		}
		else
		{
			count++;
		}
		previous_value = INTEGER(arr)[i];

 	}
 	RES[0] *= facts[count - 1];
 	Rprintf("%d count: %d (%d)\n", INTEGER(arr)[n - 1], count, RES[0]);
 	RES[0] = facts[n - 1]/RES[0]; // n!/a!b!c!
 	R_Free(facts);
 	UNPROTECT(1);
 	return(res);
}
#endif
