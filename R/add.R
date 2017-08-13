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


#' Number of possible rearrangements
#'
#' @param x an integer vector
#'
#' @return a number indicating the number of possible rearrangements for a given
#'   vector using binomial expansion: `n!/(a!b!c!)`
#'
#' @export
#'
#' @examples
#' x <- c(10L, 9L, 9L, 8L, 10L)
#' eb(x)
#' eb(c(1, 2))
#' eb(c(1, 1))
#' eb(c(1, 2, 3, 3))
eb <- function(x){
  .Call("expand_binomial_c", as.integer(x), PACKAGE = "regolith")
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

#' Facts
#'
#' @param x
#'
#' @return a number
#' @export
#'
#' @examples
#' facts(5)
facts <- function(x){
  .Call("facts_c", x, PACKAGE = "regolith")
}

#' sorts
#'
#' @param x
#' @param R if sort should be done by `R_qsort()` or `qsort()`
#' @param print if `R = FALSE`, should the comparison be printed?
#'
#' @return a number
#' @export
#'
#' @examples
#' (x <- sample(10, replace = TRUE))
#' sorts(x)
#' x # has side-effect
#' (x <- sample(10, replace = TRUE))
#' sorts(x, R = FALSE)
#' sorts(x, R = FALSE, print = TRUE)
sorts <- function(x, R = TRUE, print = FALSE){
  if (R){
    .Call("sort_c", x, PACKAGE = "regolith")
  } else {
    .Call("nosort_c", x, print, PACKAGE = "regolith")
  }
}
