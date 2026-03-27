#include <stdio.h>
#include "matrice.h"
#include "gauss.h" // Assure-toi que ce header contient le prototype de solve_by_gauss

int main() {
    mat A, X;
    matrice_error err;

    printf("Ce programme permet de résoudre une équation matricielle du type AX=B\n");
    printf("Vous aller entrer les informations de la matrice A\n");
    lirematrice(&A);

    printf("\n Entrer maintenant les informations de la matrice colonne B \n");
    lirematrice(&X);

    printf("\n\n\n--- Systeme avant resolution ---\n\n\n");
    printf("Matrice A :\n"); 
    afficher_matrice(&A);
    printf("\n");
    printf("Vecteur B :\n"); 
    afficher_matrice(&X);
    printf("\n");

    // 3. Appel de ta fonction corrigee
    err = solve_by_gauss(&A, &X);

    if (err == MATRICE_CORRECT) {
        printf("\n--- Resolution reussie ---\n");
        printf("Le vecteur solution x est :\n");
        // On affiche X qui est le vecteur solution
        for(int i=0; i < X.ligne; i++) {
            printf("x[%d] = % .2f\n", i, X.tab[i]);
        }
    } else {
        printf("\nErreur lors de la resolution : code %d\n", err);
    }

    // 4. Nettoyage
    liberer_matrice(&A);
    liberer_matrice(&X);

    return 0;
}