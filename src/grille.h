#ifndef ABZ_GRILLE

#define ABZ_GRILLE

#include "jeu.h"
#include "video.h"
#include "image.h"

// remet a zero la grille, la structure 'case'
void res_Grille(CaseGrille grille[9][9]);

// trouve a quelle case placer le pion, et le place
void placePion(InfoJeu* jeu, InfoFenetre* fenetre);

void remplacePion_joue(InfoJeu* jeu);

// verifie les puissance 4
void aligne4(CaseGrille grille[9][9], InfoJeu* jeu);

// recupere le nombre de cases vides de chaques colonne
void infosGrille(InfoJeu* jeu);

// sauvegarde la grille dans un fichier
void sauvegardeGrille(InfoJeu* jeu, FILE* fDebug);
// lis un fichier a la recherche d'un tour donne et remplace la grille actuelle par celle sauvegardee
void recupereGrille(Image* images, InfoJeu* jeu, InfoFenetre* fenetre, FILE* fDebug);

#endif // ABZ_GRILLE
