#ifndef ABZ_BOT

#define ABZ_BOT

#include "jeu.h"


typedef struct BlkList{

    int ligne;

    int type;
                /*
                    - 0: libre
                    - 1: danger puissance 4
                    - 2: colonne pleine
                    - 3: dedié a la stratégie
                */
    int joueur;
                /*
                    - -1: personne n'a de blacklist dans cette colonne
                    - 1: joueur 1
                    - 2: joueur 2
                */


} BlkList;


// choisit une colonne de differentes façons selon la difficultee
void bot(Bot* info_bot, InfoJeu* jeu);

// verifie les puissance 3: *xxx / xxx*
int aligne3(int bot, CaseGrille grille[9][9], BlkList blacklist[7]);
/*
// verifie s'il y a un trou dans un puissance 4: x*xx / xx*x
int aligneEntre(int bot, CaseGrille grille[9][9], BlkList blacklist[7]);
// verifie des cas qui ont la meme priorite que 'aligne3'
int casAPart(int bot, CaseGrille grille[9][9], BlkList blacklist[7]);
// verifie les puissance 2: *xx- / -xx*
*/
int aligne2(int bot, CaseGrille grille[9][9], BlkList blacklist[7]);

// permet au bot de trouver une stratégie
void trouveStrat(int bot, CaseGrille grille[9][9], BlkList blacklist[7], Strat *stratActive);
// permet au bot d'appliquer sa strategies
int strategie(int bot, CaseGrille grille[9][9], BlkList blacklist[7], Strat *stratActive);
// verifie que la stratégie est encore applicable
int* checStrat(int bot, CaseGrille grille[9][9], BlkList blacklist[7], Strat *stratActive, int *nombreErreur, int *erreur);



#endif // ABZ_BOT
