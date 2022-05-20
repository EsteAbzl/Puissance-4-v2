#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include <stdio.h>
#include <stdlib.h>

#include "debug.h"


void debugWindow_Init()
{

    TTF_Init();

    debugWindow = NULL;

    dWindowX = 100;
    dWindowY = 300;
    dWindowW = 500;
    dWindowH = 300;

    fps = 0;
    T_fps = 0;

    debugWindow = SDL_CreateWindow("Debug Window", dWindowX, dWindowY, dWindowW, dWindowH, SDL_WINDOW_ALWAYS_ON_TOP|SDL_WINDOW_SHOWN|SDL_WINDOW_RESIZABLE);
    if(debugWindow == NULL)
    {
        DEBUG("erreur de l'initialisation de 'debugWindow'")
        exit(-100);
    }

    showDebugWindow = 1;



    debugRenderer = NULL;
    debugRenderer = SDL_CreateRenderer(debugWindow, -1, SDL_RENDERER_ACCELERATED);
    if(debugRenderer == NULL)
    {
        DEBUG("erreur de l'initialisation de 'debugRenderer'")
        exit(-100);
    }

    SDL_SetRenderDrawColor(debugRenderer, 200, 255, 200, 255);
    SDL_RenderClear(debugRenderer);
    SDL_SetRenderDrawColor(debugRenderer, 200, 255, 200, 255);



    police = NULL;
    police = TTF_OpenFont("./data/consola.ttf", 22);
    if(police == NULL)
    {
        DEBUG("erreur de l'initialisation de 'police'")
        exit(-100);
    }

    noir.r = 10;
    noir.g = 10;
    noir.b = 10;
    noir.a = 255;


    for(int i = 0; i < 100; i++)
    {
        for(int j = 0; j < 100; j++)
        {
            debugTexte[i].txt[j] = 0;
        }
    }


}

void debugWindow_Quit()
{

    if(debugWindow)
    {
        TTF_CloseFont(police);

        SDL_DestroyRenderer(debugRenderer);

        SDL_DestroyWindow(debugWindow);

        TTF_Quit();
    }
}


void debugWindow_Affiche()
{
    if(debugWindow)
    {
        SDL_Surface *texte_Surface = NULL;
        SDL_Texture *texte_Texture = NULL;

        int texteW = 0, texteH = 0;
        SDL_Rect texteDest;

        int debugLigneUtilise[100];
        int nombreDeLigne = 0;
        int ligne = 0;

        for(int i = 0; i < 100; i++){
            debugLigneUtilise[i] = -1;
            if(debugTexte[i].txt[0]){
                debugLigneUtilise[nombreDeLigne] = i;
                nombreDeLigne ++;
            }
        }

        for(int i = 0; i < nombreDeLigne; i++){

            ligne = debugLigneUtilise[i];
            if(ligne == -1)
            {
                DEBUG("erreur du chargement du numero de la ligne de debug")
            }

            texte_Surface = TTF_RenderUTF8_Solid(police, debugTexte[ligne].txt, noir);
            if(texte_Surface == NULL)
            {
                DEBUG("erreur de la création de 'texte_Surface'")
                exit(-100);
            }

            texte_Texture = SDL_CreateTextureFromSurface(debugRenderer, texte_Surface);
            if(texte_Texture == NULL)
            {
                DEBUG("erreur de la création de 'texte_Texture'")
                exit(-100);
            }


            texteW = 0;
            texteH = 0;

            SDL_QueryTexture(texte_Texture, NULL, NULL, &texteW, &texteH);

            texteDest.x = 5;
            texteDest.y = ligne * 20 + 5;
            texteDest.w = texteW;
            texteDest.h = texteH;


            SDL_RenderCopy(debugRenderer, texte_Texture, NULL, &texteDest);


            SDL_FreeSurface(texte_Surface);
            SDL_DestroyTexture(texte_Texture);
        }

        SDL_RenderPresent(debugRenderer);
        SDL_RenderClear(debugRenderer);

    }
}

void debugWindow_Apparition(){

    if(debugWindow){

        if((SDL_GetWindowFlags(debugWindow) & SDL_WINDOW_MAXIMIZED) == SDL_WINDOW_MAXIMIZED){

            SDL_GetWindowPosition(debugWindow, &dWindowX, &dWindowY);
            SDL_GetWindowSize(debugWindow, &dWindowW, &dWindowH);

            SDL_MinimizeWindow(debugWindow);
        }
        else{

            SDL_MaximizeWindow(debugWindow);

            SDL_SetWindowPosition(debugWindow, dWindowX, dWindowY);
            SDL_SetWindowSize(debugWindow, dWindowW, dWindowH);
        }
    }
    else{
        debugWindow_Init();
    }
}


void debugWindow_Clear()
{
    if(debugWindow)
    {
        SDL_RenderClear(debugRenderer);
    }
}

void debugWindow_Refresh()
{
    if(debugWindow)
    {
        DEBUG("dWindow rafraichie \n")
        SDL_RenderPresent(debugRenderer);
    }
}
