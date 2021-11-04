#ifndef ABZ_ACTION

#define ABZ_ACTION

#include "jeu.h"
#include "video.h"
#include "image.h"

// autre:

    // appel de 'fermetureFenetre' (video.h) qui ferme le jeu
    void aQuit(Image* images, InfoJeu* jeu, InfoFenetre* fenetre, FILE* fDebug);

    void afficheDebug();

    // selection des modes de hardcore
    void aHardcore(Hardcore* hardcore, unsigned int temps);

    // confirme la difficultee des bots
    void aValide(Image* images, InfoJeu* jeu, InfoFenetre* fenetre);

#endif // ABZ_ACTION

