#ifndef MATRICE_H
#define MATRICE_H

typedef struct matrice
{
    int ligne;
    int colonne;
    double *tab;
}mat;

typedef enum{
    MATRICE_CORRECT =0,
    MATRICE_ALLOC_ERROR,
    MATRICE_DIM_ERROR,
    MATRICE_INDICE_ERROR,
    MATRICE_VALEUR_ERROR,
    MATRICE_NULL_ERROR,
}matrice_error;

// initialisation d'une matrice 

matrice_error initialise_matrice(mat *M, int ligne, int colonne);

// recuperation des lignes et des colonnes

int line_of_matrice(mat *M);

int row_of_matrice(mat *M);

// ajout des valeurs à une matrice (ici ligne et colonne désigne la position d'affectation de la valeur )

matrice_error affecter_valeurs(mat *M, int indice_ligne, int indice_colonne, double val);

//  addition de 2 matrices .La matrice destination contiendra la somme des  matrices M et N

matrice_error additioner_matrice(mat *M, mat *N, mat *destination);

// multiplication d'une matrice par un reel 

matrice_error reelXmatrice(mat *M, double val, mat *destination);

matrice_error ligneXcolonne(mat *M, mat*N, int *resultat);

matrice_error extraire_line_of_matrice(mat *M, mat *line, int indice);

matrice_error extraire_row_of_matrice(mat *M, mat *row, int indice);

// produit de 2 matrices 

matrice_error matriceXmatrice(mat *M, mat *N, mat *destination);


#endif 