#ifndef ABZ_VIDEO

#define ABZ_VIDEO

#include "jeu.h"
#include "image.h"


// fenetre


// cree la fenetre et le renderer, fait lien avec le corp du jeu
void fenetre(FILE* fDebug, FILE* fSauvegarde);
// desalloue
void fermetureFenetre(Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);


// image


//reset la structure Images ( dans image.h)
void resetImages(Images* Images);
// charge les images de section du jeu
void chargeSectionImage(int section, Images* Images, SDL_Renderer* pRenderer, FILE* fDebug);
// decharge toutes les images du jeu
void dechargeToutesImages(Images* Images);


// action


// affiche les parametres: joueurCommence,
void parametre(int mode, int* joueurCommence, Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);

// affiche les accueils et fait intervenir les evenements lié
void accueil(int accueil, int* mode, int* joueurCommence, int* difficulteBot1, int* difficulteBot2, Hardcore* hardcore, Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);

// permet de jouer une colonne, affiche les images et fait intervenir les evenements liés
void jouerColonne(int mode, int* joueurCommence, int tour, int joueur, caseGrille grille[9][9], Hardcore* hardcore, int* colonne, int* retour, int* rejouerPartie, int* retourAccueil, Images* Images, SDL_Window*  pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);

// (en cour de partie) permet de recommencer une partie/ retourner a l'accueil/ reprendre une partie/ quitter le jeu
void menu(int* rejouerPartie, int* retourAccueil, Hardcore* hardcore, int mode, int joueur, int tour, int* joueurCommence, caseGrille grille[9][9], Images* Images, SDL_Window*  pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);
// (en fin de partie) permet de recommencer une partie/ retourner a l'accueil/ quitter le jeu
void finPartie(int* rejouerPartie, Hardcore* hardcore, int fin, int mode, int joueur, int* joueurCommence, caseGrille grille[9][9], Images* Images, SDL_Window*  pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);


// groupe d'image


// gere l'affichage du jeu: background, grille, pion, colonneActive
void affiche(int utilisation, int mode, int joueur, int tour, int colonneActive, caseGrille grille[9][9], Images* Images, SDL_Renderer* pRenderer, FILE* fDebug);
// ecran de fin, affiche le gagnant
void afficheFin(int utilisation, int fin, int mode, int joueur, int tour, int *rejouerPartie, int *retourAccueil, Hardcore* hardcore, int* joueurCommence, caseGrille grille[9][9], Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);

// affiche les pions
void affichePion(int mode, int colonne, int ligne, int pionJoueur, int pionEtat, Images* Images, SDL_Renderer* pRenderer, FILE* fDebug);

// positionne les joueurs dans l'ordre de jeu
void positionneJoueur(int mode, int joueur, Images* Images, SDL_Renderer* pRenderer, FILE* fDebug);
// affiche les joueurs
void afficheJoueur(int type, int position, Images* Images, SDL_Renderer* pRenderer, FILE* fDebug);

// affiche la barre de temps restant au mode hardcore
void afficheHardcore(Hardcore* hardcore, Images* Images, SDL_Renderer* pRenderer, FILE* fDebug);

// affiche des nombres
void nombre(int nombre, SDL_Rect* dest, Images* Images, SDL_Renderer* pRenderer, FILE* fDebug);


// animation


// anime le grillage du menu qui tombe
void animationGrillage(int utilisation, int fin, int mode, int joueur, int tour, Hardcore* hardcore, caseGrille grille[9][9], Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);
// anime les pions qui tombent
void animationPion(int colonne, int joueur, int mode, int tour, int *rejouerPartie, int *retourAccueil, int* joueurCommence, Hardcore* hardcore, caseGrille grille[9][9], Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);

#endif // ABZ_VIDEO
