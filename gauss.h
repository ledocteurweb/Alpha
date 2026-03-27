#ifndef GAUSS_H
#define GAUSS_H
#include "matrice.h"
#include <math.h>


matrice_error echange_ligne(mat *M, int i, int j);

matrice_error solve_by_gauss(mat *A, mat *X);

#endif