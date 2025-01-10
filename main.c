#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

void afficher_grille(char grille[][20], int taille) {
    printf("+");
    for (int i = 0; i < taille * 2; i++) {
        printf("-");
    }
    printf("+\n");

    for (int i = 0; i < taille; i++) {
        printf("|");
        for (int j = 0; j < taille; j++) {
            printf("%c ", grille[i][j]);
        }
        printf("|\n");
    }

    printf("+");
    for (int i = 0; i < taille * 2; i++) {
        printf("-");
    }
    printf("+\n");
}

void initialiser_grille(char grille[][20], int taille) {
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille; j++) {
            grille[i][j] = ' ';
        }
    }
}

int case_occupee_par_serpent(int serpent[][2], int taille_serpent, int x, int y) {
    for (int i = 0; i < taille_serpent; i++) {
        if (serpent[i][0] == x && serpent[i][1] == y) {
            return 1;
        }
    }
    return 0;
}

void ajout_nourriture(char grille[][20], int serpent[][2], int taille_serpent, int *pomme_x, int *pomme_y, int taille) {
    int x, y;
    do {
        x = rand() % taille;
        y = rand() % taille;
    } while (case_occupee_par_serpent(serpent, taille_serpent, x, y));

    *pomme_x = x;
    *pomme_y = y;
    grille[x][y] = '@';
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

void mise_a_jour_serpent(int serpent[][2], int taille_serpent, int direction, int *derniere_queue_x, int *derniere_queue_y) {
    *derniere_queue_x = serpent[taille_serpent-1][0];
    *derniere_queue_y = serpent[taille_serpent-1][1];
    
    for (int i = taille_serpent - 1; i > 0; i--) {
        serpent[i][0] = serpent[i - 1][0];
        serpent[i][1] = serpent[i - 1][1];
    }

    switch (direction) {
        case 1: 
            serpent[0][0]--;
            break;
        case 2: 
            serpent[0][1]++;
            break;
        case 3: 
            serpent[0][0]++;
            break;
        case 4: 
            serpent[0][1]--;
            break;
    }
}

void initialiser_serpent(int serpent[][2], int taille) {
    serpent[0][0] = taille / 2;
    serpent[0][1] = taille / 2;
    serpent[1][0] = taille / 2;
    serpent[1][1] = taille / 2 - 1;
    serpent[2][0] = taille / 2;
    serpent[2][1] = taille / 2 - 2;
}

int main() {
    int taille = 20;
    char grille[20][20];
    int serpent[400][2];
    int taille_serpent = 3;
    int direction = 2;
    int pomme_x, pomme_y;
    int score = 0;
    int derniere_queue_x, derniere_queue_y;

    srand(time(NULL));

    initialiser_serpent(serpent, taille);
    initialiser_grille(grille, taille);
    ajout_nourriture(grille, serpent, taille_serpent, &pomme_x, &pomme_y, taille);

    while (1) {
        direction = direction_serpent(direction);
        mise_a_jour_serpent(serpent, taille_serpent, direction, &derniere_queue_x, &derniere_queue_y);

        if (serpent[0][0] < 0 || serpent[0][0] >= taille || serpent[0][1] < 0 || serpent[0][1] >= taille) {
            printf("Game Over! Collision avec le mur.\nScore final: %d\n", score);
            break;
        }

        for (int i = 1; i < taille_serpent; i++) {
            if (serpent[0][0] == serpent[i][0] && serpent[0][1] == serpent[i][1]) {
                printf("Game Over! Collision avec le corps.\nScore final: %d\n", score);
                return 0;
            }
        }

        if (serpent[0][0] == pomme_x && serpent[0][1] == pomme_y) {
            serpent[taille_serpent][0] = derniere_queue_x;
            serpent[taille_serpent][1] = derniere_queue_y;
            taille_serpent++;
            score += 1;
            ajout_nourriture(grille, serpent, taille_serpent, &pomme_x, &pomme_y, taille);
        }

        initialiser_grille(grille, taille);
        grille[pomme_x][pomme_y] = '@';
        
        for (int i = 0; i < taille_serpent; i++) {
            grille[serpent[i][0]][serpent[i][1]] = 'O';
        }

        printf("Score: %d\n", score);
        afficher_grille(grille, taille);

        Sleep(300);
        system("cls");
    }

    return 0;
}