// Utilisation:
/*
sprintf(debugTexte[0].txt,"mode séléctionné: %d", mode);
*/

// debugLigneUtilise:
/*
    0: [jeu.c]/jeu()            - titre: generale
    1: [jeu.c]/jeu()            - mode séléctionné
    2: [jeu.c]/jeu()            - tour actuel
    3
    4: [jeu.c]/jeu()            - titre: bot
    5: [jeu.c]/jeu()            - strat choisie
    6: [bot.c]/trouveStrat()    - ressemblance
    7
    8: [bot.c]/bot()            - black list joueur
    9: [bot.c]/bot()            - black list type
    10
    11: [bot.c]/checStrat()     - nombre d'erreurs de stratégie
    12: [bot.c]/checStrat()     - précision des erreurs

*/


#ifndef ABZ_DEBU

#define ABZ_DEBUG

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

FILE *fDebug;


SDL_Window *debugWindow;
SDL_Renderer *debugRenderer;
TTF_Font *police;
SDL_Color noir;

int showDebugWindow;
int dWindowX, dWindowY, dWindowW, dWindowH;

typedef struct Texte{
    char txt[100];
} Texte;

Texte debugTexte[100];

#define DEBUG(probleme) fprintf(fDebug, "ERREUR : %s", probleme);\
                        fclose(fDebug);\
                        if((fDebug = fopen("./Debug/erreur.txt","a")) == NULL)\
                        {\
                        fprintf(stdin, "ERREUR: impossible d'ouvrir le fichier 'erreur.txt'\n");\
                        exit(100);\
                        }

void debugWindow_Init();
void debugWindow_Quit();

void debugWindow_Affiche();
void debugWindow_Apparition();

void debugWindow_Clear();
void debugWindow_Refresh();



#endif // ABZ_DEBUG
