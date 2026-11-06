#include <stdio.h>

#define TAILLE 10

// Fonction pour initialiser la grille vide (0)
void initialiserGrille(int g[TAILLE][TAILLE]) {
    int i, j;
    for (i = 0; i < TAILLE; i++) {
        for (j = 0; j < TAILLE; j++) {
            g[i][j] = 0;
        }
    }
}

// Fonction pour afficher l'espace aérien dans la console
void afficherGrille(int g[TAILLE][TAILLE]) {
    int i, j;
    printf("\n   ");
    for (j = 0; j < TAILLE; j++) {
        printf("%d ", j);
    }
    printf("\n  ---------------------\n");
    for (i = 0; i < TAILLE; i++) {
        printf("%d |", i);
        for (j = 0; j < TAILLE; j++) {
            if (g[i][j] == 0) {
                printf(". "); // Ciel vide
            } else {
                printf("A "); // Avion
            }
        }
        printf("|\n");
    }
    printf("  ---------------------\n");
}

// Fonction pour compter les avions voisins autour d'une case
int compterVoisins(int g[TAILLE][TAILLE], int x, int y) {
    int count = 0;
    int i, j;
    for (i = -1; i <= 1; i++) {
        for (j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue; // Ne pas compter la cellule elle-même
            }
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < TAILLE && ny >= 0 && ny < TAILLE) {
                if (g[nx][ny] != 0) {
                    count++;
                }
            }
        }
    }
    return count;
}

// Fonction qui applique les règles de Conway (turbulences) à la fin du tour
void appliquerConway(int g[TAILLE][TAILLE]) {
    int temp[TAILLE][TAILLE];
    int i, j;
    
    // Copie de l'état actuel dans un tableau temporaire
    for (i = 0; i < TAILLE; i++) {
        for (j = 0; j < TAILLE; j++) {
            temp[i][j] = g[i][j];
        }
    }

    // Application des règles du Jeu de la vie
    for (i = 0; i < TAILLE; i++) {
        for (j = 0; j < TAILLE; j++) {
            int voisins = compterVoisins(temp, i, j);
            if (temp[i][j] != 0) {
                // Règle de mort : isolement (< 2) ou surpopulation (> 3)[cite: 1]
                if (voisins < 2 || voisins > 3) {
                    g[i][j] = 0; 
                }
            } else {
                // Règle de naissance : exactement 3 voisins[cite: 1]
                if (voisins == 3) {
                    g[i][j] = 1; 
                }
            }
        }
    }
}

int main() {
    int grille[TAILLE][TAILLE];
    int tour = 1;
    int choix, x, y;

    initialiserGrille(grille);

    // Configuration initiale (quelques avions de départ)
    grille[2][2] = 1;
    grille[2][3] = 1;
    grille[2][4] = 1;

    printf("=== BIENVENUE DANS SKY CONWAY ===\n");

    // Boucle principale du jeu sur 5 tours (extensible)
    while (tour <= 5) {
        printf("\n--- TOUR %d ---\n", tour);
        afficherGrille(grille);

        printf("Actions :\n");
        printf("1. Placer un nouvel avion\n");
        printf("2. Passer son tour\n");
        printf("Votre choix : ");
        scanf("%d", &choix);

        if (choix == 1) {
            printf("Entrez les coordonnees (ligne et colonne, de 0 a 9) : ");
            scanf("%d %d", &x, &y);
            if (x >= 0 && x < TAILLE && y >= 0 && y < TAILLE && grille[x][y] == 0) {
                grille[x][y] = 1;
                printf("Avion place avec succes !\n");
            } else {
                printf("Coordonnees invalides ou case deja occupee !\n");
            }
        }

        // Application automatique des règles de Conway à la fin de chaque tour[cite: 2]
        printf("\n-> Fin du tour : Application des turbulences (regles de Conway)...\n");
        appliquerConway(grille);

        tour++;
    }

    printf("\nFin de partie ! Merci d'avoir joue a Sky Conway.\n");
    return 0;
}