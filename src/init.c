#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* FIXME:
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
extern SEXP _rNodal_oilwells_bothproducts(SEXP);
extern SEXP _rNodal_oilwells_hello_world();
extern SEXP _rNodal_oilwells_outerproduct_cpp(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"_rNodal_oilwells_bothproducts",     (DL_FUNC) &_rNodal_oilwells_bothproducts,     1},
    {"_rNodal_oilwells_hello_world",      (DL_FUNC) &_rNodal_oilwells_hello_world,      0},
    {"_rNodal_oilwells_outerproduct_cpp", (DL_FUNC) &_rNodal_oilwells_outerproduct_cpp, 1},
    {NULL, NULL, 0}
};

void R_init_rNodal_oilwells(DllInfo *dll)
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
