#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP add_c(SEXP, SEXP);
extern SEXP expand_binomial_c(SEXP);
extern SEXP larr_c(SEXP);
extern SEXP omp_test();

static const R_CallMethodDef CallEntries[] = {
    {"add_c",             (DL_FUNC) &add_c,             2},
    {"expand_binomial_c", (DL_FUNC) &expand_binomial_c, 1},
    {"larr_c",            (DL_FUNC) &larr_c,            1},
    {"omp_test",          (DL_FUNC) &omp_test,          0},
    {NULL, NULL, 0}
};

void R_init_regolith(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
