#ifndef ABZ_JEU

#define ABZ_JEU

#include <SDL2/SDL.h>

#include "video.h"
#include "image.h"


typedef struct Pion{
	   int x;// milieu du pion sur l'axe x

	   int y;// milieu du pion sur l'axe y

	   En_Image image;

	   int velociteY;/* vitesse du pion sur l'axe y
	                 - = descend
	                 + = monte

	                 ! important ! avec SDL, si on fait y + 30, le pion va descendre de 30 pixels,
	                 il faut donc inverser et faire y - velociteY pour ne pas avoir d'erreurs.
	                 */
} Pion;

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
    Pion pion;


} CaseGrille;

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


typedef struct Strat{
    int colonne;    // colonne du pion inférieur gauche de la strategie

    int ligne;      // ligne du pion inférieur gauche de la strategie

    int type;       /*
                    strategie utilisée

                    type est negatif pour itilisé la stratégie en "miroir"
                    */
} Strat;


typedef struct Bot{
    Strat strat;

    int difficulte;     /*
                        1 : facile
                        2 : normal
                        3 : difficile
                        */
} Bot;

typedef struct InfoJeu{
    int m_x, m_y;   // positions de la souris

    CaseGrille grille[9][9];// grille de jeu

    int infoGrille[9]; // permet de connaitre le nombre de pions restant dans chaques colonne

    FILE* fSauvegarde;
    Hardcore hardcore;

    int mode;   /*
                1 : Joueur contre Joueur
                2 : Joueur contre Ordinateur
                3 : Joueur contre Joueur contre Joueur
                4 : Ordinateur contre Ordinateur
                */

    Bot bot1, bot2;

    int joueurCommence;
    int joueur; // joueur actuel

    int colonne;// colonne jouee
    int tour;   // incremente a chaques tours, permet de detecter une egalite
    int retour; // permet de revenir au tour precedent

    int rejouerPartie;
    int retourAccueil;
    int fin;        /*
                    -1 : egalite
                    0 : pas termine
                    1 : victoire du joueur 1
                    2 : victoire du joueur 2
                    3 : victoire du joueur 3
                    */

} InfoJeu;

void res_Hardcore(Hardcore* hardcore);

void res_Strat(Strat* strat);

void res_Bot(Bot* bot);

void res_InfoJeu(InfoJeu* jeu);

void res_InfoPartie(InfoJeu* jeu);

// corp du jeu
void fonctionJeu(struct InfoFenetre* fenetre, FILE* fDebug);


#endif // ABZ_JEU
