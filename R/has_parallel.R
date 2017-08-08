#' Does thie package have paralell capability via OMP?
#'
#' @return a logical `TRUE` or `FALSE`
#' @export
#'
#' @examples
#' has_parallel()
has_parallel <- function(){
  as.logical(.Call("omp_test", PACKAGE = "regolith"))
}
