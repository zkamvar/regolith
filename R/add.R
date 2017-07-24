#' add
#'
#' @param a a number
#' @param b another number
#'
#' @return the sum of the two
#' @export
#' @md
#'
#' @note this is from [Hadely's guide on C](http://adv-r.had.co.nz/C-interface.html)
#'
#' @examples
#' regolith::add(1, 4)
add <- function(a, b){
  .Call("add_c", a, b, package = "regolith")
}
