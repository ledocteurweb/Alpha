#include "matrice.h"

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

void liberer_matrice(mat *M){
    free(M->tab);
    M->tab = NULL;
}

int line_of_matrice(mat *M){
    return M->ligne;
}

int column_of_matice(mat *M){
    return M->colonne;
}

// cette fonction verifiera que la position ou l'on veut affecter notre valeur est bien accesible 

matrice_error affecter_valeurs(mat *M, int indice_ligne, int indice_colonne, double val){
    if(((0<=indice_ligne)&& (indice_ligne<line_of_matrice(M))) && ((0<=indice_colonne) && (indice_colonne<column_of_matice(M)))){
        int colonne = column_of_matice(M) ;
        M->tab[indice_colonne + colonne*indice_ligne ] = val ;
        return MATRICE_CORRECT;
    }
    return MATRICE_INDICE_ERROR;
}


void afficher_matrice(mat *M){
    for (int indice_ligne = 0; indice_ligne < M->ligne; indice_ligne++) {
        for (int indice_colonne = 0; indice_colonne < M->colonne; indice_colonne++) {
            printf("% .2f ", M->tab[indice_ligne * M->colonne + indice_colonne]);
        }
        printf("\n");
    }
}

matrice_error copimatrice(mat *M, mat *destination){
    int ligne,colonne;
    ligne=line_of_matrice(M);
    colonne=column_of_matice(M);

    if (initialise_matrice(destination,ligne,colonne)!=MATRICE_CORRECT)
        return MATRICE_NULL_ERROR;
    
    for (int indice_ligne = 0; indice_ligne < ligne; indice_ligne++)
    {
        for (int indice_colonne = 0; indice_colonne < colonne; indice_colonne++)
        {
            destination->tab[indice_ligne*colonne + indice_colonne]=M->tab[indice_ligne*colonne + indice_colonne];
        }
        
    }
    return MATRICE_CORRECT;    
}
//  addition de 2 matrices .La matrice destination contiendra la somme des  matrices M et N

matrice_error additioner_matrice(mat *M, mat *N, mat *destination){
    if (line_of_matrice(M)!=line_of_matrice(N) || column_of_matice(M)!=column_of_matice(N))
    {
        return MATRICE_INDICE_ERROR;
    }
    
    int ligne,colonne;
    ligne=line_of_matrice(M);
    colonne=column_of_matice(M);
    if (initialise_matrice(destination,ligne,colonne) != MATRICE_CORRECT)
        return MATRICE_ALLOC_ERROR;
    for (int indice_ligne = 0; indice_ligne < ligne; indice_ligne++)
    {
        for (int indice_colonne = 0; indice_colonne < colonne ; indice_colonne++)
        {
            destination->tab[indice_colonne + colonne*indice_ligne] = M->tab[indice_colonne + colonne*indice_ligne] +N->tab[indice_colonne + colonne*indice_ligne];
        } 
    }
    return MATRICE_CORRECT;
}

// multiplication d'une matrice par un reel 

matrice_error reelXmatrice(mat *M, double val, mat *destination){
    int ligne,colonne;
    ligne=line_of_matrice(M);
    colonne=column_of_matice(M);
    if(initialise_matrice(destination,ligne,colonne)!= MATRICE_CORRECT)
        return MATRICE_ALLOC_ERROR;
    for (int indice_ligne = 0; indice_ligne < ligne; indice_ligne++)
    {
        for (int indice_colonne = 0; indice_colonne < colonne ; indice_colonne++)
        {
            destination->tab[indice_colonne + colonne*indice_ligne] = val*M->tab[indice_colonne + colonne*indice_ligne];
        } 
    }
    return MATRICE_CORRECT;
}


// produit d'une matrice ligne par une colonne 

matrice_error matriceXmatrice(mat *M, mat *N, mat *destination){
    int lignem, colonnem, colonnen;
    double valeur;
    lignem=line_of_matrice(M);
    colonnem=column_of_matice(M);
    colonnen=column_of_matice(N);
    if (M->colonne != N->ligne)
        return MATRICE_DIM_ERROR;

    if (initialise_matrice(destination, lignem, colonnen) != MATRICE_CORRECT)
        return MATRICE_ALLOC_ERROR;

    for (int indice_ligne = 0; indice_ligne < lignem; indice_ligne++) {
        for (int indice_colonne = 0; indice_colonne < colonnen; indice_colonne++) {
            valeur = 0;
            for (int tmp = 0; tmp < colonnem; tmp++) {
                valeur += M->tab[indice_ligne*colonnem + tmp] *
                         N->tab[tmp*colonnen + indice_colonne];
            }
            destination->tab[indice_ligne*colonnen + indice_colonne] = valeur;
        }
    }
    return MATRICE_CORRECT;
}

void lirematrice(mat *M){

    int ligne,colonne;
    do
    {
        printf("Entrer le nombre de ligne de votre matrice (entier strictement positif) ");
        scanf("%d",&ligne);
        printf("\n");
    } while (ligne <= 0);

    do
    {
        printf("Entrer le nombre de colonne de votre matrice (entier stirctement positif) ");
        scanf("%d",&colonne);
        printf("\n");
    } while (colonne <= 0);


    initialise_matrice(M,ligne,colonne);

    for (int indice_ligne = 0; indice_ligne < ligne; indice_ligne++)
    {
        for (int indice_colonne = 0; indice_colonne < colonne; indice_colonne++)
        {
            printf("Entrer la valeur du coefficient de la matrice à l'indice (%d,%d) ", indice_ligne, indice_colonne);
            scanf("%lf",  &M->tab[indice_ligne*colonne +indice_colonne]);
        }
    }

}
