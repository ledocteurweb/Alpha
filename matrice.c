#include "matrice.h"
#include <stdio.h>

// La fonction ci dessous verifie  que les lignes et les colonnes donne en paramètre sont bien positifs 

matrice_error initialise_matrice(mat *M, int ligne, int colonne){
    if(ligne <=0 || colonne <= 0){
        return MATRICE_DIM_ERROR;
    }
    M->ligne = ligne;
    M->colonne = colonne;
    M->tab = malloc( ligne*colonne*sizeof(double)); 

    if (M->tab == NULL)
    {
        return MATRICE_ALLOC_ERROR;
    }
    return MATRICE_CORRECT;
}



int line_of_matrice(mat *M){
    return M->ligne;
}

int row_of_matrice(mat *M){
    return M->colonne;
}

// cette fonction verifiera que la position ou l'on veut affecter notre valeur est bien accesible 

matrice_error affecter_valeurs(mat *M, int indice_ligne, int indice_colonne, double val){
    if((0<=indice_ligne<line_of_matrice(M)) && (0<=indice_colonne<row_of_matrice(M))){
        M->tab[indice_colonne + indice_ligne ] = val ;
        return MATRICE_CORRECT;
    }
    return MATRICE_INDICE_ERROR;
}

//  addition de 2 matrices .La matrice destination contiendra la somme des  matrices M et N

matrice_error additioner_matrice(mat *M, mat *N, mat *destination){
    if (line_of_matrice(M)!=line_of_matrice(N) || row_of_matrice(M)!=row_of_matrice(N))
    {
        return MATRICE_INDICE_ERROR;
    }
    
    int ligne,colonne;
    ligne=line_of_matrice(M);
    colonne=row_of_matrice(M);
    initialise_matrice(destination,ligne,colonne);
    for (int indice_ligne = 0; indice_ligne < ligne; indice_ligne++)
    {
        for (int indice_colonne = 0; indice_colonne < colonne ; indice_colonne++)
        {
            destination->tab[indice_colonne + indice_ligne] = M->tab[indice_colonne + indice_ligne] +N->tab[indice_colonne + indice_ligne];
        } 
    }
    return MATRICE_CORRECT;
}

// multiplication d'une matrice par un reel 

matrice_error reelXmatrice(mat *M, double val, mat *destination){
    int ligne,colonne;
    ligne=line_of_matrice(M);
    colonne=row_of_matrice(M);
    initialise_matrice(destination,ligne,colonne);
    for (int indice_ligne = 0; indice_ligne < ligne; indice_ligne++)
    {
        for (int indice_colonne = 0; indice_colonne < colonne ; indice_colonne++)
        {
            destination->tab[indice_colonne + indice_ligne] = val*M->tab[indice_colonne + indice_ligne];
        } 
    }
    return MATRICE_CORRECT;
}


// produit d'une matrice ligne par une colonne 
matrice_error ligneXcolonne(mat *M, mat*N, int *resultat){
    int ligne=line_of_matrice(M);
    if ((M->ligne + M->colonne != N->ligne + N->colonne))
    {
        return MATRICE_DIM_ERROR;
    }
    for (int i = 0; i < ligne; i++)
    {
        *resultat+=M->tab[i]*N->tab[i];
    }
    return MATRICE_CORRECT;
}


matrice_error extraire_line_of_matrice(mat *M, mat *line, int indice){
    int ligne,colonne;
    ligne=line_of_matrice(M);
    colonne=row_of_matrice(M);
    initialise_matrice(line,colonne,1);
    if (indice > ligne*colonne)
    {
        return MATRICE_INDICE_ERROR;
    }
    
    for (int i = indice; i <= indice+colonne  ; i++)
    {
        line->tab[i-indice]=M->tab[indice];
    }
    return MATRICE_CORRECT;
}

matrice_error extraire_row_of_matrice(mat *M, mat *row, int indice){
    int ligne,colonne,j;
    ligne=line_of_matrice(M);
    colonne=row_of_matrice(M);
    j=0;
    initialise_matrice(row,ligne,1);
    if (indice > ligne*colonne)
    {
        return MATRICE_INDICE_ERROR;
    }
    for (int i = indice; i < ligne*(colonne-1) + indice; i+=colonne)
    {
        row->tab[j]=M->tab[indice];
    }
    return MATRICE_CORRECT;
}
// produit de 2 matrices 

matrice_error matriceXmatrice(mat *M, mat *N, mat *destination){
    int ligne_m, ligne_n, colonne_m, colonne_n, indice, *valeur;
    ligne_m=line_of_matrice(M);
    ligne_n=line_of_matrice(N);
    colonne_m=row_of_matrice(M);
    colonne_n=row_of_matrice(N);
    indice=0;
    valeur=0;
    if (colonne_m!=ligne_n)
    {
        return MATRICE_DIM_ERROR;
    }
    mat *matrice_ligne, *matrice_colonne;
    for(int i = 0; i < ligne_m*(colonne_m-1) ; i+=colonne_m)
    {
        extraire_line_of_matrice(M,matrice_ligne,i);
        for (int j = 0; j < colonne_n ; j++)
        {
            extraire_row_of_matrice(N,matrice_colonne,j);
            ligneXcolonne(matrice_ligne, matrice_colonne,valeur);
        }
        
    }
    
    
}