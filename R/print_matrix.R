#' print matrix
#'
#' @return the length of a matrix (60)
#' @export
#'
#' @examples
#' pm()
pm <- function(){
  mat <- matrix(seq(40*20), nrow = 40, ncol = 20)
  .Call("matlen", mat, PACKAGE = "regolith")
}
