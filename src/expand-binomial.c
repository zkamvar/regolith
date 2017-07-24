#include <R.h>
#include <Rinternals.h>
// #define CAN_RUN 1

int intcmp (const void * a, const void * b);

#ifdef CAN_RUN
SEXP expand_binomial_c(SEXP numlist);
#endif

int intcmp (const void * a, const void * b)
{
       return ( *(int*)a - *(int*)b );
}
#ifdef CAN_RUN
SEXP expand_binomial_c(SEXP numlist) {
  int i;
  int res = 1;
  int count = 1;
  int* facts;
  for (i = 0; i < 10; i++)
  {
  	facts[i] = fact(i+1);
  }
  R_  qsort(arr, 10, sizeof(int), intcmp);
  int previous_value = arr[0];
  for (i = 1; i < 10; i++)
  {
      if (arr[i] != previous_value)
      {
          res *= facts[count - 1];
          printf("%d count: %d (%d)\n", arr[i-1], count, res);
          count = 1;
      }
      else
      {
          count++;
      }
      previous_value = arr[i];

  }

  res *= facts[count - 1];
}
#endif
