#include "gauss.h"




/*fonction d'échange de 2 lignes*/

matrice_error echange_ligne(mat *M, int i, int j){
    int colonne, ligne, tmp;
    colonne=row_of_matrice(M);
    ligne=line_of_matrice(M);
    if (i>=ligne || i<0 || j >= ligne || j < 0)
    {
        return MATRICE_INDICE_ERROR;
    }
    for(int indice_colonne = 0; indice_colonne < colonne; indice_colonne++){
        tmp=M->tab[i*colonne + indice_colonne];
        M->tab[i*colonne + indice_colonne]=M->tab[j*colonne+indice_colonne];
        M->tab[j*colonne + indice_colonne]=tmp;
    }
    return MATRICE_CORRECT;
}

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
/* IL EST A NOTER QUE JE CONSIDERE Q'UAUCUNE LIGNE NE PEUT ETRE NULLE CETTE FONCTION VIENT COMPLETER LES 2 PREMIERES 
FONCTIONS  */
matrice_error verif_egalite_ligne(mat *M){
    int ligne, colonne, temoin, cpt;
    double quotient, quotient2,a,b;
    ligne=line_of_matrice(M);
    colonne=row_of_matrice(M);
    for (int indice_ligne = 0; indice_ligne < (ligne -1) ; indice_ligne++)
    {
        for (int d = indice_ligne+1; d < ligne ; d++)
        {
            /*s'il est egal à 0 à la fin c'est qu'on à deux vecteurs lignes colineaires dès qu'il sera égal à 1
            la seconde boucle s'arrête*/
            temoin=0 ;
            cpt=0;
            /*cpt me permet juste de ne pas comparer quotient2 a quotient sachant que quotient2 n'est pas initialisé*/
            for (int indice_colonne = 0; (temoin==0 )&& ( indice_colonne < colonne )  ; indice_colonne++)
            {
                a=M->tab[colonne*indice_ligne + indice_colonne];
                b=M->tab[colonne*d + indice_colonne];
                if ((fabs(b) > 1e-9 && fabs(a) < 1e-9) || (fabs(a) > 1e-9 && fabs(b) < 1e-9))
                {
                    temoin=1;
                }
                else if (fabs(b) < 1e-9 && fabs(a) <  1e-9)
                {
                    temoin=0;
                }
                else{
                    quotient2=a/b;
                    if (cpt==0)
                    {
                        temoin=0;
                        cpt++;
                    }
                    else{
                        if(fabs(quotient-quotient2) > 1e-9){
                            temoin=1;
                        }
                    }
                    quotient=quotient2;   
                }
            }
            if (temoin == 0 )
            {
                return MATRICE_LIGNE_DOUBLE;
            }
        }
    }
    return MATRICE_CORRECT;
}


matrice_error solve_by_gauss(mat *A, mat *X, mat *B){
    int lignea,lignex,colonnea;
    lignea=line_of_matrice(A);
    lignex=line_of_matrice(X);
    colonnea=row_of_matrice(X);
    // verifier les préconditions
    if(lignea!=lignex)
        return MATRICE_DIM_ERROR;
    for (int indice_ligne = 0; indice_ligne < lignea; indice_ligne++)
    {
        if (verif_ligne_null(A,indice_ligne)!=MATRICE_CORRECT)
            return MATRICE_LIGNE_NULL;
    }
    for (int indice_colonne = 0; indice_colonne < colonnea; indice_colonne++)
    {
        if(verif_colonne_null(A,indice_colonne)!=MATRICE_CORRECT)
            return MATRICE_COLONNE_NULL;
    }
    if(verif_egalite_ligne(A)!=MATRICE_CORRECT)
        return MATRICE_LIGNE_DOUBLE;
    // debut de la résolution de l'equation  

    int indice_pivot=0;
    if(initialise_matrice(B,lignea,colonnea)!=MATRICE_CORRECT)
        return MATRICE_ALLOC_ERROR;
    
    for (int indice_ligne = 0; indice_ligne < lignea; indice_ligne++)
    {
        // trouver la ligne pivot
        int val_pivot=A->tab[indice_pivot*colonnea];
        int val=A->tab[indice_ligne*colonnea];
        if (val!=0 && val<val_pivot)
        {
            indice_pivot=indice_ligne;
        }
    }
    if(indice_pivot!=0){
        if(echange_ligne(A,0,indice_pivot)!=MATRICE_CORRECT)
            return MATRICE_INDICE_ERROR;
    }
    

}