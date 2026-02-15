#include "gauss.h"

/*les préconditions a remplir il faudrait que le système d'équation à résoudre compte n équations à n variables 
distincts ce qui ne veut dire d'autre qu'une matrice de taille nxn avec toutes les  lignes et colonnes differentes du
vecteur nul de plus aucune ligne ne doit etre multiple d'une autre */

/*Une première idee qui me vienne serait de trouver une ligne qui me servira de i-ème pivot dont l'élément 
à la i-eme colonne est non nul et ce i-ème pivot j'échangerais sa place avec la i-ème ligne afin de 
pouvoir  la retrancher de toutes les lignes suivantes en suposant bi le coefficient se trouvant a la i-ème colonne 
des lignes précédentes et ai celui du i-eme pivot je devrais donc realiser l'opération  
i-ème ligne = i-ème ligne - (bi/ai) *i-ème pivot  */

matrice_error verif_ligne_null(mat *M, int ligne){
    int colonne,somme;
    colonne=row_of_matrice(M);
    somme=0;
    for (int indice_colonne = 0; indice_colonne < colonne; indice_colonne++)
    { 
        somme+=(fabs(M->tab[colonne*ligne + indice_colonne]) < 1e-9);
    }
    if (somme==colonne)
    {
        return MATRICE_LIGNE_NULL;
    }
    return MATRICE_CORRECT;
}

matrice_error verif_colonne_null(mat *M, int colonne){
    int ligne,colonne2 ,somme;
    somme=0;
    ligne=line_of_matrice(M);
    colonne2=row_of_matrice(M);
    for (int indice_ligne = 0; indice_ligne < ligne; indice_ligne++)
    {
        somme+=(fabs(M->tab[colonne2*indice_ligne + colonne]) < 1e-9);
    }
    if (somme==ligne)
    {
        return MATRICE_COLONNE_NULL;
    }
    return MATRICE_CORRECT;
    
}
/*afin de vérifier si une ligne est egal a k fois une autre il me faudrait prendre un ligne i et verifier si 
les k lignes qui la suivent sont multiples de cette dernière. La meilleur procedure possible en soit serait
de considerer les éléments sur la même colonne, tout d'abord on prendrait les 2 éléments qui se trouvent sur la
première colonne puis realiser le quotient que l'on stockera dans une variable ensuite faire ssuccesivement le 
quotients succecifs des autres elements sur la ligne. à ce niveau on a 2 possibilités soit 
on se retrouve avec les quotients successifs qui sont tous égaux donc à ce niveau on arrête la verification 
parceque le nombre d'équtions  devient inférieru au nombre de variable. Sinon on tombe 
sur un quotient different du premier quotient et donc on arrete directement et on reprends la verification sur
la ligne suivante. */
matrice_error verif_egalite_ligne(mat *M){
    int ligne, colonne, temoin;
    double quotient, quotient2;
    ligne=line_of_matrice(M);
    colonne=row_of_matrice(M);
    for (int indice_ligne = 0; indice_ligne < (ligne -1) ; indice_ligne++)
    {
        temoin=0 ;
        /*s'il est egal à 0 à la fin c'est qu'on à deux vecteurs lignes colineaires dès qu'il sera égal à 1
        la seconde boucle s'arrête*/
        if (M->tab[colonne*(indice_ligne+1)]!=0)
        {
            quotient=M->tab[colonne*indice_ligne]/M->tab[colonne*(indice_ligne+1)];
        }
        else{
            temoin=1;
        }
        for (int indice_colonne = 1; (temoin==0 )&& ( indice_colonne < colonne )  ; indice_colonne++)
        {
            if (fabs(M->tab[colonne*(indice_ligne+1) + indice_colonne]) > 1e-9)
            {
                quotient2=M->tab[colonne*indice_ligne + indice_colonne]/M->tab[colonne*(indice_ligne+1) + indice_colonne];
            }
            else{
                temoin=1;
            }
            if (fabs(quotient - quotient2) > 1e-9)
            {
                temoin=1;
            } 
        }
        if (temoin == 0 )
        {
            return MATRICE_LIGNE_DOUBLE;
        }
    }
    return MATRICE_CORRECT;
}