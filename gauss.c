#include "gauss.h"




/*fonction d'échange de 2 lignes*/

matrice_error echange_ligne(mat *M, int i, int j){
    int colonne, ligne;
    double tmp;
    colonne=column_of_matice(M);
    ligne=line_of_matrice(M);

    if (i>=ligne || i<0 || j >= ligne || j < 0)
        return MATRICE_INDICE_ERROR;

    if (i==j)
        return MATRICE_CORRECT;
    
    for(int indice_colonne = 0; indice_colonne < colonne; indice_colonne++){
        tmp=M->tab[i*colonne + indice_colonne];
        M->tab[i*colonne + indice_colonne]=M->tab[j*colonne+indice_colonne];
        M->tab[j*colonne + indice_colonne]=tmp;
    }
    return MATRICE_CORRECT;
}

matrice_error solve_by_gauss(mat *A, mat *X){
    int lignea,linex,colonnea;
    lignea=line_of_matrice(A);
    linex=line_of_matrice(X);
    colonnea=column_of_matice(A);

    // verifier les préconditions
    if(lignea!=linex || lignea != colonnea )
        return MATRICE_DIM_ERROR;

    // transformation en matrice triangulaire 
    for (int etape = 0; etape < lignea; etape++)
    {
        // trouver la ligne pivot
        int indice_pivot=etape;
        double val_pivot=fabs(A->tab[etape*colonnea + etape]);
        for (int indice_ligne = etape+1; indice_ligne < lignea; indice_ligne++)
        {
            
            double val=fabs(A->tab[indice_ligne*colonnea + etape]);
            if (val_pivot<val)
            {
                indice_pivot=indice_ligne;
                val_pivot=val;
            }
        }

        // ON  arrete le calcul vu que cette variable admettra une infité de solution.
        if (val_pivot<1e-12)
            return MATRICE_VALEUR_ERROR;

        // echange des lignes si on en a besoin 
        if (indice_pivot != etape) 
            if (echange_ligne(A, etape, indice_pivot) != MATRICE_CORRECT  || echange_ligne(X,etape,indice_pivot) != MATRICE_CORRECT)
                return MATRICE_INDICE_ERROR;

        // retrancher la ligne pivaut aux lignes suivantes 
        for (int indice_ligne = etape+1; indice_ligne < lignea; indice_ligne++)
        {   
            double coef=A->tab[indice_ligne*colonnea + etape]/A->tab[etape*colonnea + etape];
            X->tab[indice_ligne]-= coef*X->tab[etape];
            for (int indice_colonne = etape; indice_colonne < colonnea ; indice_colonne++)
            {
                A->tab[indice_ligne*colonnea + indice_colonne] -= coef*A->tab[etape*colonnea+indice_colonne];
            }   
        }   
    }
    // deduction des valeurs des solutions que l'on mettra dans le vecteur 
    for (int indice_ligne = lignea - 1; indice_ligne >= 0; indice_ligne--)
    {
        double somme=0.00;
        for (int indice_colonne = indice_ligne + 1; indice_colonne < lignea; indice_colonne++)
        {
            somme+=A->tab[indice_ligne*colonnea + indice_colonne]*X->tab[indice_colonne];
        }
        X->tab[indice_ligne]=(X->tab[indice_ligne]-somme)/A->tab[indice_ligne*colonnea + indice_ligne];
    }
    
    return MATRICE_CORRECT;
}