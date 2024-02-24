#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> // Pour abs()

struct Partie {
    char grille[5][5];
    short nb_tour;
    bool mini;
    char coord;
};

/**
 * @param p_jeu : c'est un pointer
 */
void Init(struct Partie *p_jeu){
    p_jeu->nb_tour = 0;
    p_jeu->mini = false;
    for(int i = 4; i>=0; i--){
        for(int j = 0; j<5; j++){
            p_jeu->grille[i][j] = 0;
        }
    }
}

/**
 * @brief Afficher la partie
 *
 * @param p_jeu : c'est un pointer
 */
void Affiche(struct Partie *p_jeu){
    for(int i = 4; i>=0; i--){
        for(int j = 0; j<5; j++){
            printf("%2d", p_jeu->grille[j][i]);
        }
        printf("\n");
    }
    printf("\n");
}

bool Check_draw(struct Partie *p_partie){
    for (int i = 0; i<5; i++) {
        for (int j = 0; j<5; j++) {
            if (p_partie->grille[i][j] == 0) {
                return false;
            }
        }
    }
    return true;
}

int Grille_update(struct Partie *p_partie, short x, short y) {
    p_partie->nb_tour ++;

    if (p_partie->grille[x][y] != 0) {
        return -1;
    }
    p_partie->grille[x][y] = p_partie->nb_tour%2+1;

    // on supprime les cases inutiles
    if (!p_partie->mini) {
        for (int i = 0; i<5; i++) {
            for (int j = 0; j<5; j++) {
                if (!(abs(i-x) < 3 && abs(j-y) < 3)) {
                    p_partie->grille[i][j] = 3;
                }
            }
        }
        // mini ?
        int count = 0;
        for (int i = 0; i<5; i++) {
            for (int j = 0; j<5; j++) {
                if (p_partie->grille[i][j] == 3) {
                    count ++;
                }
            }
        }
        if (count == 16) {
            p_partie->mini = true;
        }
    } else {
        // grille de pointers
        for (int i = 0; i<5; i++) {
            for (int j = 0; j<5; j++) {
                if (p_partie->grille[i][j] != 3) {
                    p_partie->coord = i*10+j;
                    return 0;
                }
            }
        }
    }
    return 0;
}

int Input_joueur(short *x, short *y) {
    // x et y sont des pointeurs
    int input;
    printf(">>>");
    scanf("%d", &input);

    if (input>=100) {
        return -1;
    }

    *x = input/10;
    *y = input%10;

    return 0;
}

/**
 * @brief Jouer un tour
 *
 * @param partie : pointer vers la partie
 * @param x,y : coord de l'endroit ou l'on doit jouer
 * @return int 1 ou 2 selon qui gagne (1 = les impaires), -1 si le coup n'est pas possible, 0 si la partie continue et 3 si c'est match nul
 */
int Jouer(struct Partie *p_partie, short x, short y) {
    // TODO : modifier la grille (et ajouter 1 au nb tour + suppr les cases en trop)
    int r = Grille_update(p_partie,x,y);
    if (!(r == 0)) {return r;}


    if (p_partie->mini) {
        // TODO : check win
        

        // check draw
        if (Check_draw(p_partie)) {
            return 3;
        }
    }

    return 0;
}

int main(){
    printf("Hello World\n");
    struct Partie partie;
    Init(&partie);
    Affiche(&partie);
    Jouer(&partie, 2, 2);
    Affiche(&partie);
    Jouer(&partie, 4, 4);
    Affiche(&partie);
    Jouer(&partie, 3,4);
    Affiche(&partie);
    Jouer(&partie, 2,4);
    Affiche(&partie);

    printf("%d|%d\n", partie.coord/10, partie.coord%10);


    short x,y;
    Input_joueur(&x,&y);
    while (true){
        int r = Jouer(&partie,x,y);
        Affiche(&partie);
        if(r == -1){
            printf("T CON FREWW\n");
        } else if (r == 0) {} else {break;}
        Input_joueur(&x,&y);
    }

    return 0;
}

