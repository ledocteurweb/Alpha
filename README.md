================================================================================
                    RÉSOLUTION DE SYSTÈMES LINÉAIRES PAR LA MÉTHODE DE GAUSS
================================================================================

DESCRIPTION
-----------
Ce projet implémente la résolution de systèmes linéaires de la forme AX = B
en utilisant la méthode d'élimination de Gauss avec pivot partiel.
Il repose sur une bibliothèque de manipulation de matrices (matrice.c/.h)
et un module de résolution (gauss.c/.h).


FICHIERS DU PROJET
------------------
  matrice.h / matrice.c   : Bibliothèque de manipulation de matrices
                             (allocation, affichage, opérations arithmétiques)
  gauss.h / gauss.c       : Module de résolution par élimination de Gauss
  test_gauss.c            : Programme principal (saisie interactive et affichage)
  Makefile                : Fichier de compilation


COMPILATION
-----------
Prérequis : gcc, make

Pour compiler le projet :

    make

Un exécutable sera généré (voir le Makefile pour le nom exact).

Pour nettoyer les fichiers compilés :

    make clean


UTILISATION
-----------
Lancer l'exécutable généré :

    ./nom_executable

Le programme vous guidera interactivement :
  1. Saisir les dimensions et les coefficients de la matrice A (carrée n×n)
  2. Saisir les dimensions et les valeurs du vecteur colonne B (n×1)
  3. Le programme affiche le système avant résolution, puis la solution X


EXEMPLE
-------
Pour le système :
    2x + y  = 5
    x  + 3y = 10

Saisir A (2 lignes, 2 colonnes) :
    2  1
    1  3

Saisir B (2 lignes, 1 colonne) :
    5
    10

Résultat attendu :
    x[0] =  1.00
    x[1] =  3.00


FONCTIONS PRINCIPALES
---------------------
  initialise_matrice(mat *M, int ligne, int colonne)
      Alloue et initialise une matrice de dimensions données.

  liberer_matrice(mat *M)
      Libère la mémoire allouée pour une matrice.

  affecter_valeurs(mat *M, int i, int j, double val)
      Affecte une valeur à la case (i, j) de la matrice.

  afficher_matrice(mat *M)
      Affiche le contenu d'une matrice dans le terminal.

  echange_ligne(mat *M, int i, int j)
      Échange deux lignes d'une matrice (utilisé pour le pivot).

  solve_by_gauss(mat *A, mat *X)
      Résout le système AX = B par élimination de Gauss avec pivot partiel.
      Modifie A et X en place. X contient la solution après appel.


CODES D'ERREUR (matrice_error)
-------------------------------
  MATRICE_CORRECT        : Opération réussie
  MATRICE_ALLOC_ERROR    : Échec d'allocation mémoire
  MATRICE_DIM_ERROR      : Dimensions incompatibles
  MATRICE_INDICE_ERROR   : Indice hors bornes
  MATRICE_VALEUR_ERROR   : Pivot quasi-nul (système singulier ou mal conditionné)
  MATRICE_NULL_ERROR     : Pointeur nul inattendu


LIMITATIONS
-----------
  - La matrice A doit être carrée (n×n).
  - Le vecteur B doit avoir le même nombre de lignes que A.
  - Le système doit avoir une solution unique (matrice non singulière).
    Si le pivot est inférieur à 1e-12, la résolution est abandonnée.
  - La résolution modifie A et B en place : faire une copie si besoin
    de conserver les valeurs originales (voir copimatrice()).


================================================================================
