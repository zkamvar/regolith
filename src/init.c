#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME: 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP add_c(SEXP, SEXP, SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"add_c", (DL_FUNC) &add_c, 3},
    {NULL, NULL, 0}
};

void R_init_regolith(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
