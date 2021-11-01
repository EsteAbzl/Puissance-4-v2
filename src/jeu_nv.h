#ifndef ABZ_JEU

#define ABZ_JEU

#include <SDL2/SDL.h>

// corp du jeu
void jeu(SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);

// compose la grille
typedef struct CaseGrille{

    int joueur;
                 /*
                 0 = case vide
                 1 = joueur 1
                 2 = joueur 2
                 3 = joueur 3
                 */

     int etat;
                /*
                0 = case vide
                1 = normal
                2 = vient d'être joue
                3 = gagne
                */

} caseGrille;

// gere le mode hardcore
typedef struct Hardcore{

	   int mode;
	               /*
	               0 = desactive
	               1 = mode 15 secondes
	               2 = mode 10 secondes
	               */

   	int tempsRestant;
} Hardcore;

typedef struct Pion{
	   int x;// milieu du pion sur l'axe x

	   int y;// milieu du pion sur l'axe y

	   int velociteY;/* vitesse du pion sur l'axe y
	                 - = descend
	                 + = monte

	                 ! important ! avec SDL, si on fait y + 30, le pion va descendre de 30 pixels,
	                 il faut donc inverser et faire y - velociteY pour ne pas avoir d'erreurs.
	                 */
} pion;


typedef struct Strat{
	   int colonne;// colonne du pion inférieur gauche de la strategie

	   int ligne;// ligne du pion inférieur gauche de la strategie

	   int type;/*
                    strategie utilisee

                    type est negatif pour itilisé la stratégie en "miroir"
                */
} strat;


typedef struct Game{
    Hardcore hardcore;


} game;

#endif // ABZ_JEU
