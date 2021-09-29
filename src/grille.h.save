#ifndef ABZ_GRILLE

#define ABZ_GRILLE

#include "jeu.h"
#include "image.h"

// remet a zero la grille, la structure 'case'
void resetGrille(caseGrille grille[9][9]);

// trouve a quelle case placer le pion, et le place
int placePion(int joueur, int colonne, int mode, int tour, int *rejouerPartie, int *retourAccueil, int* joueurCommence, Hardcore* hardcore, caseGrille grille[9][9], Images* Images, SDL_Window *pWindow, SDL_Renderer *pRenderer, FILE *fDebug, FILE *fSauvegarde);
// change les "pion_joue" en "pion"
void remplacePion_joue(caseGrille grille[9][9]);

// verifie les puissance 4
int aligne4(caseGrille grille[9][9], int mode);

// recupere le nombre de cases vides de chaques colonne
void infosGrille(int mode, int infoGrille[9], caseGrille grille[9][9]);

// sauvegarde la grille dans un fichier
void sauvegardeGrille(int tour, int joueur, caseGrille grille[9][9], FILE* fDebug, FILE* fSauvegarde);
// lis un fichier a la recherche d'un tour donne et remplace la grille actuelle par celle sauvegardee
void recupereGrille(int* tour, int* joueur, caseGrille grille[9][9], Images* Images, SDL_Window *pWindow, SDL_Renderer *pRenderer, FILE* fDebug, FILE* fSauvegarde);


#endif // ABZ_GRILLE
