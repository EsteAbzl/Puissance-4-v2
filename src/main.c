#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "debug.h"

#include "main.h"
#include "video.h"



int main(int argc, char** argv)
{

    srand(time(NULL)); // permet de creer un nombre aleatoire dans la suite du code


    //initialisation du fichier d'erreur ('fDebug')
    fDebug = NULL;

    if((fDebug = fopen("./Debug/erreur.txt","w+")) == NULL){
        fprintf(stdin,"ERREUR: impossible d'ouvrir le fichier 'erreur.txt'\n");
        return -1;
    }

    /*---*/


    initFenetre(fDebug);// ouvre la fenetre et fait lien avec le corp du jeu

    return 10;

}
