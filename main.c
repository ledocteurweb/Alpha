#include <stdio.h>
#include "matrice.h"
#include "gauss.h" // Assure-toi que ce header contient le prototype de solve_by_gauss

int main() {
    mat A, X;
    matrice_error err;

    // 1. Initialisation de la matrice A (3x3)
    initialise_matrice(&A, 3, 3);
    affecter_valeurs(&A, 0, 0, 2.0);  affecter_valeurs(&A, 0, 1, 1.0);  affecter_valeurs(&A, 0, 2, -1.0);
    affecter_valeurs(&A, 1, 0, -3.0); affecter_valeurs(&A, 1, 1, -1.0); affecter_valeurs(&A, 1, 2, 2.0);
    affecter_valeurs(&A, 2, 0, -2.0); affecter_valeurs(&A, 2, 1, 1.0);  affecter_valeurs(&A, 2, 2, 2.0);

    // 2. Initialisation du vecteur X (3x1) avec les valeurs du second membre (b)
    initialise_matrice(&X, 3, 1);
    affecter_valeurs(&X, 0, 0, 8.0);
    affecter_valeurs(&X, 1, 0, -11.0);
    affecter_valeurs(&X, 2, 0, -3.0);

    printf("--- Systeme avant resolution ---\n");
    printf("Matrice A :\n"); afficher_matrice(&A);
    printf("Vecteur b (stocke dans X) :\n"); afficher_matrice(&X);

    // 3. Appel de ta fonction corrigee
    err = solve_by_gauss(&A, &X);

    if (err == MATRICE_CORRECT) {
        printf("\n--- Resolution reussie ---\n");
        printf("Le vecteur solution x est :\n");
        // On affiche X qui contient maintenant les resultats x, y, z
        for(int i=0; i < X.ligne; i++) {
            printf("x[% d] = % .2f\n", i, X.tab[i]);
        }
    } else {
        printf("\nErreur lors de la resolution : code %d\n", err);
    }

    // 4. Nettoyage
    liberer_matrice(&A);
    liberer_matrice(&X);

    return 0;
}