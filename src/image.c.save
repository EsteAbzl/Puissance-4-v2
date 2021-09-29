/*
Charge les images
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>


#include "image.h"

    void changeDest(SDL_Rect* dest, int x, int y)
    {
        dest->x = x;
        dest->y = y;
        dest->w = 0;
        dest->h = 0;
    }

    // charge une image et renvoit un pointeur dessus
    SDL_Texture* chargeImage(const char* localisation, SDL_Renderer* pRenderer, FILE* fDebug)
    {

        //chargement de l'image
        SDL_Surface *pSprite = IMG_Load(localisation);
        if(pSprite)
        {
            //creation de la texture
            SDL_Texture *pTexture = SDL_CreateTextureFromSurface(pRenderer, pSprite);

            {//desallocation
                SDL_FreeSurface(pSprite);
            }

            if(pTexture)
            {
                return pTexture;
            }
            else // debug
            {
                fprintf(fDebug,"Erreur: creation de '%s' (%s)", localisation, SDL_GetError());
                exit(-3);
            }

        }
        else // debug
        {
            fprintf(fDebug,"Erreur: creation de pSprite de '%s' (%s)", localisation, SDL_GetError());
            exit(-3);
        }
    }

    // supprime (si elle existe) la texture demande
    void supprimeTexture(SDL_Texture* pTexture)
    {
        if(pTexture)
        {
            SDL_DestroyTexture(pTexture);
        }

    }

    // affiche une texture a l'endroit demande
    void afficheImage(SDL_Texture* pTexture, SDL_Rect* dest, SDL_Renderer* pRenderer, FILE* fDebug)
    {
        // taille de la texture
        int w, h;
        SDL_QueryTexture(pTexture, NULL, NULL, &w, &h);

        dest->w = w;
        dest->h = h;

        // affiche la texture
        if(SDL_RenderCopy(pRenderer, pTexture, NULL, dest))
        {
            fprintf(fDebug,"Erreur: copie de texture (%s)\n", SDL_GetError());
            fseek(fDebug, 0, SEEK_CUR);
        }

    }

    // affiche une texture a l'endroit demande en la centrant
    void afficheImage_Centre(SDL_Texture* pTexture, SDL_Rect* dest, SDL_Renderer* pRenderer, FILE* fDebug)
    {
        // taille de la texture
        int w, h;
        SDL_QueryTexture(pTexture, NULL, NULL, &w, &h);

        // centre la texture
        dest->x = dest->x - (w / 2);
        dest->y = dest->y - (h / 2);
        dest->w = w;
        dest->h = h;

        // affiche la texture
        if(SDL_RenderCopy(pRenderer, pTexture, NULL, dest))
        {
            fprintf(fDebug,"Erreur: copie de texture (%s)\n", SDL_GetError());
            fseek(fDebug, 0, SEEK_CUR);
        }
    }

