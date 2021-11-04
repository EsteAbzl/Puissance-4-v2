#ifndef ABZ_VIDEO

#define ABZ_VIDEO

#include "jeu.h"
#include "image.h"


// fenetre
typedef enum Ecran{
    LENCEMENT, ACCUEIL_MENU, ACCUEIL_BOT, JEU
}Ecran;


typedef struct InfoFenetre{
    SDL_Window* pWindow;

    SDL_Renderer* pRenderer;

    int w, h;

    Ecran ecran;
    int menu;
    int parametre;
    int fin;


} InfoFenetre;

void res_InfoFenetre(InfoFenetre* fenetre);

// cree la fenetre et le renderer, fait lien avec le corp du jeu
void initFenetre(FILE* fDebug);
// desalloue
void fermetureFenetre(Image* Images, InfoFenetre* fenetre, FILE* fDebug, FILE* fSauvegarde);


void affichage(Image* images, struct InfoJeu* jeu, InfoFenetre* fenetre, FILE* fDebug);

void place_acceuil_bot(int jaune, int x, int difficulte, Image* images, InfoFenetre* fenetre, FILE* fDebug);

void positionnePion(Image* images, struct InfoJeu* jeu, InfoFenetre* fenetre, FILE* fDebug);

void positionneHardcore(Image* images, struct InfoJeu* jeu, InfoFenetre* fenetre, FILE* fDebug);


// groupe d'image

/*
// ecran de fin, affiche le gagnant
void afficheFin(int utilisation, int fin, int mode, int joueur, int tour, int *rejouerPartie, int *retourAccueil, Hardcore* hardcore, int* joueurCommence, caseGrille grille[9][9], Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);

// positionne les joueurs dans l'ordre de jeu
void positionneJoueur(int mode, int joueur, Images* Images, SDL_Renderer* pRenderer, FILE* fDebug);
// affiche les joueurs
void afficheJoueur(int type, int position, Images* Images, SDL_Renderer* pRenderer, FILE* fDebug);

// affiche des nombres
void nombre(int nombre, SDL_Rect* dest, Images* Images, SDL_Renderer* pRenderer, FILE* fDebug);
*/

// animation

/*
// anime le grillage du menu qui tombe
void animationGrillage(int utilisation, int fin, int mode, int joueur, int tour, Hardcore* hardcore, caseGrille grille[9][9], Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);
// anime les pions qui tombent
void animationPion(int colonne, int joueur, int mode, int tour, int *rejouerPartie, int *retourAccueil, int* joueurCommence, Hardcore* hardcore, caseGrille grille[9][9], Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);
*/

#endif // ABZ_VIDEO
