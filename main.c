#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

void afficher_grille(char grille[20][20]) {
    printf("+----------------------------------------+\n");
    for (int i = 0; i < 20; i++) {
        printf("|");
        for (int j = 0; j < 20; j++) {
            printf(" %c", grille[i][j]);
        }
        printf("|\n");
    }
    printf("+----------------------------------------+\n");
}

char initialiser_grille(char grille[20][20]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            grille[i][j] = ' ';
        }
    }
    return grille;
}

char position_serpent(char grille[20][20], int taille_serpent, int direction, int x, int y) {
    // 1 = haut, 2 = droite, 3 = bas, 4 = gauche
    if (direction == 1) {
        for (int i = 0; i < taille_serpent; i++) {
            grille[x - i][y] = 'O';
        }
    }
    else if (direction == 2) {
        for (int i = 0; i < taille_serpent; i++) {
            grille[x][y + i] = 'O';
        }
    }
    else if (direction == 3) {
        for (int i = 0; i < taille_serpent; i++) {
            grille[x + i][y] = 'O';
        }
    }
    else if (direction == 4) {
        for (int i = 0; i < taille_serpent; i++) {
            grille[x][y - i] = 'O';
        }
    }
    return grille;
}

int direction_serpent(int direction) {
    char touche = _getch();

    switch (touche) {
        case ('z'):
            direction = 1;
        break;
        case 'd':
            direction = 2;
        break;
        case 's':
            direction = 3;
        break;
        case 'q':
            direction = 4;
        break;
    }

    return direction;
}

int main() {
    char grille[20][20];
    int taille_serpent = 3;
    int direction = 2;
    initialiser_grille(grille);

    while (1) {
        position_serpent(grille, taille_serpent, direction, 0, 0);
        afficher_grille(grille);
    }
    return 0;
}