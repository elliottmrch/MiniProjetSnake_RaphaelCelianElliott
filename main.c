#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
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

void initialiser_grille(char grille[20][20]) {
    for (int i = 0; i < 20; i++) {
        for (int j = 0; j < 20; j++) {
            grille[i][j] = ' ';
        }
    }
}

void position_serpent(char grille[20][20], int taille_serpent, int direction, int *x, int *y) {
    if (direction == 1) {  // Haut
        for (int i = 0; i < taille_serpent; i++) {
            grille[*x - i][*y] = 'O';
        }
        (*x)--; 
    }
    else if (direction == 2) {  // Droite
        for (int i = 0; i < taille_serpent; i++) {
            grille[*x][*y + i] = 'O';
        }
        (*y)++; 
    }
    else if (direction == 3) {  // Bas
        for (int i = 0; i < taille_serpent; i++) {
            grille[*x + i][*y] = 'O';
        }
        (*x)++;
    }
    else if (direction == 4) {  // Gauche
        for (int i = 0; i < taille_serpent; i++) {
            grille[*x][*y - i] = 'O';
        }
        (*y)--; 
    }
}

int direction_serpent(int direction) {
    if (_kbhit()) {
        char touche = _getch();

        switch (touche) {
            case 'z': case 72:
                if (direction != 3) {
                    direction = 1;
                }
                break;
            case 'd': case 77:
                if (direction != 4) {
                    direction = 2;
                }
                break;
            case 's': case 80:
                if (direction != 1) {
                    direction = 3;
                }
                break;
            case 'q': case 75:
                if (direction != 2) {
                    direction = 4;
                }
                break;
        }
    }
    return direction;
}

int main() {
    char grille[20][20];
    int taille_serpent = 3;
    int direction = 2;
    int x = 0;
    int y = 0;
    initialiser_grille(grille);
    position_serpent(grille, taille_serpent, direction, &x, &y);
    afficher_grille(grille);
    
    while (1) {
        direction = direction_serpent(direction);
        initialiser_grille(grille);
        position_serpent(grille, taille_serpent, direction, &x, &y);
        afficher_grille(grille);
        Sleep(700);
        system("cls");
    }

    return 0;
}
