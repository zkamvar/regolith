#include <Rinternals.h>
#include <R.h>
#include <Rdefines.h>
#include <stdlib.h>
#define CAN_RUN 1

int compare_function (const void * first, const void * second);
SEXP omp_test();
SEXP larr_c(SEXP arr);
SEXP add_one_c(SEXP x);
// Simple function to check for openMP support
// Returns 1 if openMP is supported, 0 if it is not.
#ifdef CAN_RUN
SEXP expand_binomial_c(SEXP arr);
#endif



int compare_function(const void *first, const void *second)
{
  const int first_ = *(const int *)first;
  const int second_  = *(const int *)second;
  return (first_ > second_) - (first_ < second_);
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
  int* ARR = INTEGER(arr);
	R_qsort_int(ARR, 1, length(arr));
	for (int i = 0; i < length(arr); i++)
	{
		INTEGER(res)[i] = ARR[i];
	}
	UNPROTECT(1);
	return(res);
}

SEXP nosort_c(SEXP arr, SEXP print)
{
	SEXP res = PROTECT(allocVector(INTSXP, length(arr)));
	int* ARR = INTEGER(arr);
	int* PARR;
	int i;
	int n = length(arr);
	int p = asInteger(print);
	PARR = R_Calloc(n, int);
	for (i = 0; i < n; i++)
	{
		PARR[i] = ARR[i];
	}
	// R_qsort_int_I(ARR, PARR, 1, length(arr));
	qsort(PARR, n, sizeof(int), compare_function);
	for (i = 0; i < n; i++)
	{
		INTEGER(res)[i] = PARR[i];
		if (p)
			Rprintf("PARR: %d\tARR: %d\n", PARR[i], ARR[i]);
	}
	UNPROTECT(1);
	R_Free(PARR);
	return(res);
}

#ifdef CAN_RUN
SEXP expand_binomial_c(SEXP arr) {
	SEXP res = PROTECT(allocVector(INTSXP, 1));
	int* RES = INTEGER(res);
	int* ARR = INTEGER(arr);
	int i;
	int n = length(arr);
	int count = 1;
	int* facts;
	int* TEMP;
	facts = R_Calloc(n, int);
	TEMP  = R_Calloc(n, int);
	for (i = 1; i <= n; i++)
	{
		facts[i - 1] = (i == 1) ? i : facts[i - 2] * i;
		TEMP[i - 1] = ARR[i - 1];
	}
	R_qsort_int(TEMP, 1, n); // Note: this takes the arguments of what indices to sort, 1-indexed
	// qsort(TEMP, n, sizeof(int), compare_function);
	int previous_value = TEMP[0];
	RES[0] = count;
	for (i = 1; i < n; i++)
	{
		if (TEMP[i] != previous_value)
		{
			RES[0] *= facts[count - 1];
			Rprintf("%d count: %d (%d)\n", TEMP[i - 1], count, RES[0]);
			count = 1;
		}
		else
		{
			count++;
		}
		previous_value = TEMP[i];

	}
	RES[0] *= facts[count - 1];
	Rprintf("%d count: %d (%d)\n", TEMP[n - 1], count, RES[0]);
	RES[0] = facts[n - 1]/RES[0]; // n!/a!b!c!
	R_Free(facts);
	R_Free(TEMP);
	UNPROTECT(1);
	return(res);
}
#endif
