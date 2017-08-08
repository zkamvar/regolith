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
  .Call("add_c", a, b, PACKAGE = "regolith")
}


#' Title
#'
#' @param x
#'
#' @return a number
#' @export
#'
#' @examples
#' x <- c(10L, 9L, 9L, 8L, 10L)
#' eb(x)
eb <- function(x){
  .Call("expand_binomial_c", x, PACKAGE = "regolith")
}

#' Title 2
#'
#' @param x
#'
#' @return a number
#' @export
#'
#' @examples
#' x <- c(10L, 9L, 9L, 8L, 10L)
#' larr(x)
larr <- function(x){
  .Call("larr_c", x, PACKAGE = "regolith")
}
