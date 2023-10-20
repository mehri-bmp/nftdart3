//Creating an R package that includes C functions.
//Include several header files, such as <R.h>, <Rinternals.h>, <stdlib.h>, and <R_ext/Rdynload.h>. These headers provide access to essential R functions and data structures for working with R from C code.
#include <R.h>
#include <Rinternals.h>
#include <stdlib.h> // for NULL
#include <R_ext/Rdynload.h>

/* 
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
//Function declarations for several C functions. Functions like cpsambrt_predict2, cprnft2, and cnft2 are declared. These functions are intended to be called from R using the .Call interface.
//extern SEXP cpsambrt_predict(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP cpsambrt_predict2(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
//extern SEXP cprnft(SEXP, SEXP, SEXP, SEXP);
extern SEXP cprnft2(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
//extern SEXP cnft(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP);
extern SEXP cnft2(SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP,SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP, SEXP); //Mehri B.M.P., 9 SEXP's added for dart

static const R_CallMethodDef CallEntries[] = { //The R_CallMethodDef structure is defined, which is necessary for registering functions to be called from R. It includes the function names and the number of arguments for each function. These correspond to the previously declared functions.
//    {"cpsambrt_predict", (DL_FUNC) &cpsambrt_predict,  7},
    {"cpsambrt_predict2",(DL_FUNC) &cpsambrt_predict2, 9},
//    {"cprnft",           (DL_FUNC) &cprnft,            4},
    {"cprnft2",          (DL_FUNC) &cprnft2,           6},
//    {"cnft",             (DL_FUNC) &cnft,             32},
    {"cnft2",            (DL_FUNC) &cnft2,            33},
    {NULL, NULL, 0}
};

void R_init_nftbart(DllInfo *dll) //The code defines the R_init_nftbart function, which is used for initializing the package. It registers the functions specified in CallEntries with R, allowing them to be called from R code.
{
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
