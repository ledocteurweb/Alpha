#include "gauss.h"

/*les préconditions a remplir il faudrait que le système d'équation à résoudre compte n équations à n variables 
distincts ce qui ne veut dire d'autre qu'une matrice de taille nxn avec toutes les  lignes et colonnes differentes du
vecteur nul de plus aucune ligne ne doit etre multiple d'une autre */

/*Une première idee qui me vienne serait de trouver une ligne qui me servira de i-ème pivot dont l'élément 
à la i-eme colonne est non nul et ce i-ème pivot j'échangerais sa place avec la i-ème ligne afin de 
pouvoir  la retrancher de toutes les lignes suivantes en suposant bi le coefficient se trouvant a la i-ème colonne 
des lignes précédentes et ai celui du i-eme pivot je devrais donc realiser l'opération  
i-ème ligne = i-ème ligne - (bi/ai) *i-ème pivot  */

int verif_ligne_null(mat *M, int ligne){
    int colonne,somme;
    colonne=row_of_matrice(M);
    somme=0;
    for (int indice_colonne = 0; indice_colonne < colonne; indice_colonne++)
    { 
        somme+=(M->tab[colonne*ligne + indice_colonne]==0);
    }
    return somme;
}

int verif_colonne_null(mat *M, int colonne){
    int ligne, somme;
    somme=0;
    ligne=line_of_matrice(M);
    for (int indice_ligne = 0; indice_ligne < ligne; indice_ligne++)
    {
        somme+=(M->tab[colonne*indice_ligne + colonne]==0);
    }
    return somme;
}

int verif_egalite_ligne(mat *M){
    
}