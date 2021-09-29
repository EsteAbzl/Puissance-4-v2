#ifndef ABZ_EVENT

#define ABZ_EVENT

#include <SDL2/SDL.h>
#include "jeu.h"
#include "image.h"

// event qui permet au joueur d'effectuer des actions lors d'une annimation ou autre
void eventSpectateur(int *rejouerPartie, int *retourAccueil, Hardcore* hardcore, int mode, int joueur, int tour, int* joueurCommence, caseGrille grille[9][9], Images* Images, SDL_Window *pWindow, SDL_Renderer *pRenderer, FILE *fDebug, FILE *fSauvegarde);

// evenements des parametres: joueurCommence / volume musique / volume effets / volume general
int eventParametre(int mode, int* joueurCommence, Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);

// evenements de l'accueil 0: quitter / appuyer pour jouer
int eventAccueil_0(int* accueil, Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);
// evenements de l'accueil 1: quitter / selection mode / mode hardcore
int eventAccueil_1(int* accueil, int* mode, int* joueurCommence, Hardcore* hardcore, Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);
// evenements de l'accueil 2: quitter / choix difficulte des bots / retour
int eventAccueil_2(int* accueil, int* mode, int* joueurCommence, int* difficulteBot1, int* difficulteBot2, int* pasValide, Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);

// event de jeu: quitter / menu / colonne active / colonne selectionnee / jeu retour
void eventJouer(int mode, int* joueurCommence, int joueur, int tour, int *colonneActive, int* colonne, int* retour, int* rejouerPartie, int* retourAccueil, int infoGrille[9], Hardcore* hardcore, caseGrille grille[9][9], Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);
// event qui permet au joueur d'effectuer des actions lorsque le bot joue
void eventBot(int *rejouerPartie, int *retourAccueil, Hardcore* hardcore, int mode, int joueur, int tour, int* retour, int* joueurCommence, caseGrille grille[9][9], Images* Images, SDL_Window *pWindow, SDL_Renderer *pRenderer, FILE *fDebug, FILE *fSauvegarde);

// event de menu: quitter / reprendre / recommencer une partie / retour a l'accueil
int eventMenu(int mode, int* joueurCommence, int* rejouerPartie, int* retourAccueil, Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);
// event de menu: quitter / recommencer une partie / retour a l'accueil
int eventFin(int mode, int* joueurCommence, int* rejouer, Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);

#endif // ABZ_EVENT
