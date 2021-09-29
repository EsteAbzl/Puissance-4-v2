#ifndef ABZ_ACTION

#define ABZ_ACTION

#include "jeu.h"
#include "image.h"

// autre:

    // appel de 'fermetureFenetre' (video.h) qui ferme le jeu
    void aQuit(Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);

    void afficheDebug();

// Parametre

// appel des parametres
    void aParametre(int mode, int* joueurCommence, Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde);

// Accueil

    // fait retourner a l'accueil precedent
    void aRetour(int* accueil);


    // 0:

        // sort de l'ecran d'accueil
        void aToucheAppuye(int* accueil);

    // 1:

        // selection des modes de hardcore
        void aHardcore(Hardcore* hardcore, float temps);

        // 1v1
        void aMode1(int* accueil, int* mode);
        // 1vBot
        void aMode2(int* accueil, int* mode);
        // 1v1v1
        void aMode3(int* accueil, int* mode);
        // BotvBot
        void aMode4(int* accueil, int* mode);

    // 2:

        // difficultee du bot mise a facile
        void aBotFacile(int* botDifficulte);
        // difficultee du bot mise a normale
        void aBotNormal(int* botDifficulte);
        // difficultee du bot mise a difficile
        void aBotDifficile(int* botDifficulte);

        // confirme la difficultee des bots
        int aValide(int* accueil, int* mode, int* difficulteBot1, int* difficulteBot2);

// Jeu

    // assigne la colonne cliquee a la variable 'colonne'
    void aJouerColonne(int c, int* colonne, int infoGrille[9]);
    // appel du menu (video.h)
    void aMenu(int *rejouerPartie, int *retourAccueil, Hardcore* hardcore, int mode, int joueur, int tour, int* joueurCommence, caseGrille grille[9][9], Images* Images, SDL_Window *pWindow, SDL_Renderer *pRenderer, FILE *fDebug, FILE *fSauvegarde);

#endif // ABZ_ACTION

