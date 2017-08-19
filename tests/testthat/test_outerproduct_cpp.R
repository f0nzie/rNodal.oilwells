library(testthat)

context("test outer_product")

test_that("outerproduct_cpp yields expected result", {
    expected <-  rbind(
        c(1,    2,    3,    4,    5),
        c(2,    4,    6,    8,   10),
        c(3,    6,    9,   12,   15),
        c(4,    8,   12,   16,   20),
        c(5,   10,   15,   20,   25)
    )

    res <- outerproduct_cpp(c(1,2,3,4,5))
    expect_equal(res, expected)
})
