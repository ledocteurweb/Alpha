#include <stdio.h>
#include "matrice.h"

int main(void){
    mat A, B, C;

    /* Initialisation des matrices */
    initialise_matrice(&A, 2, 3);
    initialise_matrice(&B, 3, 2);

    /* Remplissage de A */
    affecter_valeurs(&A, 0, 0, 1);
    affecter_valeurs(&A, 0, 1, 2);
    affecter_valeurs(&A, 0, 2, 3);
    affecter_valeurs(&A, 1, 0, 4);
    affecter_valeurs(&A, 1, 1, 5);
    affecter_valeurs(&A, 1, 2, 6);

    /* Remplissage de B */
    affecter_valeurs(&B, 0, 0, 7);
    affecter_valeurs(&B, 0, 1, 8);
    affecter_valeurs(&B, 1, 0, 9);
    affecter_valeurs(&B, 1, 1, 10);
    affecter_valeurs(&B, 2, 0, 11);
    affecter_valeurs(&B, 2, 1, 12);

    printf("Matrice A :\n");
    afficher_matrice(&A);

    printf("\nMatrice B :\n");
    afficher_matrice(&B);

    /* Multiplication A x B */
    if (matriceXmatrice(&A, &B, &C) == MATRICE_CORRECT) {
        printf("\nMatrice C = A x B :\n");
        afficher_matrice(&C);
    } else {
        printf("Erreur lors de la multiplication\n");
    }

    /* Libération mémoire */
    liberer_matrice(&A);
    liberer_matrice(&B);
    liberer_matrice(&C);

    return 0;
}
