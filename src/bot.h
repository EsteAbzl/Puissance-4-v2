#ifndef ABZ_BOT

#define ABZ_BOT

#include "jeu.h"


typedef struct blkList blkList;
struct blkList
{

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


};


// choisit une colonne de differentes façons selon la difficultee
int bot(int bot, int difficulte, caseGrille grille[9][9], strat *stratActive);

// verifie les puissance 3: *xxx / xxx*
int aligne3(int bot, caseGrille grille[9][9], blkList blacklist[7]);
/*
// verifie s'il y a un trou dans un puissance 4: x*xx / xx*x
int aligneEntre(int bot, caseGrille grille[9][9], blkList blacklist[7]);
// verifie des cas qui ont la meme priorite que 'aligne3'
int casAPart(int bot, caseGrille grille[9][9], blkList blacklist[7]);
// verifie les puissance 2: *xx- / -xx*
*/
int aligne2(int bot, caseGrille grille[9][9], blkList blacklist[7]);

// permet au bot de trouver une stratégie
void trouveStrat(int bot, caseGrille grille[9][9], blkList blacklist[7], strat *stratActive);
// permet au bot d'appliquer sa strategies
int strategie(int bot, caseGrille grille[9][9], blkList blacklist[7], strat *stratActive);
// verifie que la stratégie est encore applicable
int* checStrat(int bot, caseGrille grille[9][9], blkList blacklist[7], strat *stratActive, int *nombreErreur, int *erreur);



#endif // ABZ_BOT
