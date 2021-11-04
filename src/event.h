#ifndef ABZ_EVENT

#define ABZ_EVENT

#include <SDL2/SDL.h>
#include "jeu.h"
#include "video.h"
#include "image.h"

void evenement(Image* images, InfoJeu* jeu, InfoFenetre* fenetre, FILE* fDebug);

void evenement_difficulteBot(int x, int f_h, int m_x, int m_y, int* difficulte);

#endif // ABZ_EVENT
