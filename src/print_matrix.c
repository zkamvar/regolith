#include <Rinternals.h>
#include <R.h>
#include <Rdefines.h>
#include <stdlib.h>

SEXP print_matrix(SEXP mat, SEXP nrow, SEXP ncol);
SEXP matlen(SEXP mat);

SEXP print_matrix(SEXP mat, SEXP nrow, SEXP ncol)
{
  int len;
  int NROW;
  int NCOL;
  int i;
  int j;
  SEXP res = PROTECT(allocVector(INTSXP, 1));
  len = length(mat);
  NROW = INTEGER(nrow)[0];
  NCOL = INTEGER(ncol)[0];
  Rprintf("The matrix is of length %d\n", len);
  for (i = 0; i < NROW; i++)
  {
    for (j = 0; j < NCOL; j++)
    {
      Rprintf("%d ", INTEGER(mat)[i + j * NROW]);
    }
    Rprintf("\n");
  }
  INTEGER(res)[0] = len;
  UNPROTECT(1);
  return(res);
}

SEXP matlen(SEXP mat)
{
  int len;
  SEXP NROW;
  SEXP NCOL;
  SEXP Rdim;
  Rdim = getAttrib(mat, R_DimSymbol);
  NROW = PROTECT(ScalarInteger(INTEGER(Rdim)[0]));
  NCOL = PROTECT(ScalarInteger(INTEGER(Rdim)[1]));
  SEXP res = PROTECT(allocVector(INTSXP, 1));
  res = print_matrix(mat, NROW, NCOL);
  UNPROTECT(3);
  return(res);
}
