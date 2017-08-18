#' @useDynLib rNodal.oilwells, .registration = TRUE
#'
#' @import Rcpp
# #' @import RcppArmadillo
# importing RcppArmadillo here would cause the following note:
# Package in Depends/Imports which should probably only be in LinkingTo: 'RcppArmadillo'
NULL

#                                         <- enabling this causes error
# .onLoad <- function (libpath, pkgname) {
#     dyn.load(pkgname, libpath)
# }

.onUnload <- function (libpath) {
    library.dynam.unload("rNodal.oilwells", libpath)
}
