/*
gere les evenements
*/


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>


#include "event.h"
#include "action.h"


// event qui permet au joueur d'effectuer des actions lors d'une annimation ou autre
void eventSpectateur(int *rejouerPartie, int *retourAccueil, Hardcore* hardcore, int mode, int joueur, int tour, int* joueurCommence, caseGrille grille[9][9], Images* Images, SDL_Window *pWindow, SDL_Renderer *pRenderer, FILE *fDebug, FILE *fSauvegarde)
{
	   // desactivation des enenements ininteressants
	   SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_DISABLE);
	   SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);
	   SDL_EventState(SDL_MOUSEWHEEL, SDL_DISABLE);
	   SDL_EventState(SDL_KEYDOWN, SDL_DISABLE);

	   // activation des enenements interessants
	   SDL_EventState(SDL_KEYUP, SDL_ENABLE);
	   SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);

    SDL_Event eventSpectateur;// variable d'event

    while(SDL_PollEvent(&eventSpectateur))// recuperation d'un evenement
    {
    	   // taille du renderer
        int x = 0, y = 0;
        SDL_GetRendererOutputSize(pRenderer, &x, &y);

        switch(eventSpectateur.type)// selon le type de l'evenement
        {
            case SDL_QUIT:// action de quitter la fenetre (alt+F4 / croix de la fenetre / ..)
            {
                aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
            }
            break;

            case SDL_WINDOWEVENT:
            {
                if(eventSpectateur.window.event == SDL_WINDOWEVENT_MINIMIZED)// met en pause le jeu si on le reduit
                {
                    if((SDL_GetWindowFlags(pWindow) & SDL_WINDOW_MINIMIZED) == SDL_WINDOW_MINIMIZED){
                        aMenu(rejouerPartie, retourAccueil, hardcore, mode, joueur, tour, joueurCommence, grille, Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }

                }
            }
            break;

            case SDL_KEYUP:// relachement d'une touche du clavier
            {
                if ( eventSpectateur.key.keysym.sym == SDLK_ESCAPE )   // Clic sur echap
                {
                    aMenu(rejouerPartie, retourAccueil, hardcore, mode, joueur, tour, joueurCommence, grille, Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                }

                else if(eventSpectateur.key.keysym.scancode == SDL_SCANCODE_GRAVE)
                {
                    afficheDebug();
                }

            }
            break;

            case SDL_MOUSEBUTTONUP:// relachement d'un bouton de la souris
            {
                if (eventSpectateur.button.button == SDL_BUTTON_LEFT)  // Clic gauche
                {
                                                                               // clique sur 'croix'
                    if(((x-50 <= eventSpectateur.button.x) && (eventSpectateur.button.x <= x))&&
                       (0 <= eventSpectateur.button.y) && (eventSpectateur.button.y <= 50 ))
                    {
                        aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }

                                                                                // clique sur 'menu_logo'
                    if(((50 <= eventSpectateur.button.x) && (eventSpectateur.button.x <= 50 + 50))&&
                       (50 <= eventSpectateur.button.y) && (eventSpectateur.button.y <= 50 + 50))
                    {
                        aMenu(rejouerPartie, retourAccueil, hardcore, mode, joueur, tour, joueurCommence, grille, Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }

                }
            }
            break;

        }
    }
}


// event de parametre
int eventParametre(int mode, int* joueurCommence, Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde)
{
    // desactivation des enenements ininteressants
	   SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_DISABLE);
	   SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);
	   SDL_EventState(SDL_MOUSEWHEEL, SDL_DISABLE);
	   SDL_EventState(SDL_KEYDOWN, SDL_DISABLE);

	   // activation des enenements interessants
	   SDL_EventState(SDL_KEYUP, SDL_ENABLE);
	   SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);

    SDL_Event eventParametre;// variable d'event

    while(SDL_PollEvent(&eventParametre))// recuperation d'un evenement
    {
        // taille du renderer
        int x = 0, y = 0;
        SDL_GetRendererOutputSize(pRenderer, &x, &y);

        switch(eventParametre.type)// selon le type de l'evenement
        {
            case SDL_QUIT:// action de quitter la fenetre (alt+F4 / croix de la fenetre / ..)
            {
                aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
            }
            break;

            case SDL_KEYUP:// relachement d'une touche du clavier
            {
                if( eventParametre.key.keysym.sym == SDLK_ESCAPE )   // Clic sur echap
                {
                    return 0;// on retourne a l'accueil / au menu
                }
                else if(eventParametre.key.keysym.scancode == SDL_SCANCODE_GRAVE)
                {
                    afficheDebug();
                }

            }
            break;

            case SDL_MOUSEBUTTONUP:// relachement d'un bouton de la souris
            {
                if (eventParametre.button.button == SDL_BUTTON_LEFT)  // Clic gauche
                {

                                                                    // clique sur 'croix'
                    if(((x-50 <= eventParametre.button.x) && (eventParametre.button.x <= x))&&
                       (0 <= eventParametre.button.y) && (eventParametre.button.y <= 50 ))
                    {
                        aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }


                                                                   // clique en dehors du background des parametres
                    if((eventParametre.button.x <= x/2 - 720) || (x/2 + 720 <= eventParametre.button.x) ||
                       (eventParametre.button.y <= 9*y/16 - 337.5) || (9*y/16 + 337.5 <= eventParametre.button.y))
                    {
                        return 0;// on retourne a l'accueil / menu
                    }


                    // joueurCommence
                                                                    // clique sur 'joueur1Commence'
                    if((x/2 - 360 - 200 <= eventParametre.button.x) && (eventParametre.button.x <= x/2 - 360 + 200)&&
                       (9*y/16 - 97.5 - 50 <= eventParametre.button.y) && (eventParametre.button.y <= 9*y/16 - 97.5 + 50 ))
                    {
                        (*joueurCommence) = 1;
                    }

                                                                    // clique sur 'joueur2Commence'
                    if((x/2 - 360 - 200 <= eventParametre.button.x) && (eventParametre.button.x <= x/2 - 360 + 200)&&
                       (9*y/16 + 26.5 - 50 <= eventParametre.button.y) && (eventParametre.button.y <= 9*y/16 + 26.5 + 50))
                    {
                        (*joueurCommence) = 2;
                    }

                                                                    // clique sur 'joueur3Commence'
                    if((x/2 - 360 - 200 <= eventParametre.button.x) && (eventParametre.button.x <= x/2 - 360 + 200)&&
                       (9*y/16 + 151.5 - 50 <= eventParametre.button.y) && (eventParametre.button.y <= 9*y/16 + 151.5 + 50))
                    {
                        if(mode == 0 || mode == 3)
                            (*joueurCommence) = 3;
                    }



                }

            }
            break;

        }

    }

    return 1;// reste dans les parametres

}


// evenements de l'accueil 0: quitter / appuyer pour jouer
int eventAccueil_0(int* accueil, Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde)
{
    // desactivation des enenements ininteressants
	   SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_DISABLE);
	   SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);
	   SDL_EventState(SDL_MOUSEWHEEL, SDL_DISABLE);
	   SDL_EventState(SDL_KEYDOWN, SDL_DISABLE);

	   // activation des enenements interessants
	   SDL_EventState(SDL_KEYUP, SDL_ENABLE);
	   SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);

    SDL_Event eventAccueil_0;// variable d'event

    while(SDL_PollEvent(&eventAccueil_0))// recuperation d'un evenement
    {

    	   // taille du renderer
        int x = 0, y = 0;
        SDL_GetRendererOutputSize(pRenderer, &x, &y);

        switch(eventAccueil_0.type)// selon le type de l'evenement
        {
            case SDL_QUIT:// action de quitter la fenetre (alt+F4 / croix de la fenetre / ..)
            {
                aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
            }
            break;

            case SDL_KEYUP:// relachement d'une touche du clavier
            {
                if ( eventAccueil_0.key.keysym.sym == SDLK_ESCAPE )   // Clic sur echap
                {
                    aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                }
                else if(eventAccueil_0.key.keysym.scancode == SDL_SCANCODE_GRAVE)
                {
                    afficheDebug();
                }
                else
                {
                	   aToucheAppuye(accueil);// (action.h)
                }

            }
            break;

            case SDL_MOUSEBUTTONUP:// relachement d'un bouton de la souris
            {
                if (eventAccueil_0.button.button == SDL_BUTTON_LEFT)  // Clic gauche
                {

                                                                    // clique sur 'croix'
                    if(((x-50 <= eventAccueil_0.button.x) && (eventAccueil_0.button.x <= x))&&
                       (0 <= eventAccueil_0.button.y) && (eventAccueil_0.button.y <= 50 ))
                    {
                        aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }
                    else
                    {
                    	   aToucheAppuye(accueil);// (action.h)
                    }

                }
                else
                {
                	   aToucheAppuye(accueil);// (action.h)
                }

            }
            break;

        }

    }
    return 1;

}

// evenements de l'accueil 1: quitter / selection mode / mode hardcore
int eventAccueil_1(int* accueil, int* mode, int* joueurCommence, Hardcore* hardcore, Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde)
{
   	// desactivation des enenements ininteressants
	   SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);
	   SDL_EventState(SDL_MOUSEWHEEL, SDL_DISABLE);
	   SDL_EventState(SDL_KEYDOWN, SDL_DISABLE);

	   // activation des enenements interessants
	   SDL_EventState(SDL_KEYUP, SDL_ENABLE);
	   SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_ENABLE);
	   SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);


	   static float presse = 0.0;// permet de calculer le temps entre la pression et le relachement d'une touche

    SDL_Event eventAccueil_1;// variable d'event

    while(SDL_PollEvent(&eventAccueil_1))// recuperation d'un evenement
    {

    	   // taille du renderer
        int x = 0, y = 0;
        SDL_GetRendererOutputSize(pRenderer, &x, &y);

        switch(eventAccueil_1.type)// selon le type de l'evenement
        {
            case SDL_QUIT:// action de quitter la fenetre (alt+F4 / croix de la fenetre / ..)
            {
                aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
            }
            break;

            case SDL_KEYUP:// relachement d'une touche du clavier
            {
                if ( eventAccueil_1.key.keysym.sym == SDLK_ESCAPE )   // Clic sur echap
                {
                    aParametre(*mode, joueurCommence, Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                }
                else if(eventAccueil_1.key.keysym.scancode == SDL_SCANCODE_GRAVE)
                {
                    afficheDebug();
                }

            }
            break;

            case SDL_MOUSEBUTTONDOWN:// appui d'un bouton de la souris
            {
            	   if (eventAccueil_1.button.button == SDL_BUTTON_LEFT)  // Clic gauche
                {

                                                                    // clique sur 'hardcore'
                    if((7*x/8 - 100 <= eventAccueil_1.button.x) && (eventAccueil_1.button.x <= 7*x/8 + 100)&&
                       (3*y/8 - 50 <= eventAccueil_1.button.y) && (eventAccueil_1.button.y <= 3*y/8 + 50))
                    {
                        	presse = eventAccueil_1.button.timestamp; // on note le moment ou le bouton a ete presse

                        	return 1;
                    }
                    else// permet de passer le declic immediat que fait le programme apres un clic
                        return 1;
                }
            }

            case SDL_MOUSEBUTTONUP:// relachement d'un bouton de la souris
            {
                if (eventAccueil_1.button.button == SDL_BUTTON_LEFT)  // Clic gauche
                {

                                                                    // clique sur 'croix'
                    if(((x-50 <= eventAccueil_1.button.x) && (eventAccueil_1.button.x <= x))&&
                       (0 <= eventAccueil_1.button.y) && (eventAccueil_1.button.y <= 50 ))
                    {
                        aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }


                                                                    // clique sur 'parametre_logo'
                    if(((50 <= eventAccueil_1.button.x) && (eventAccueil_1.button.x <= 50 + 50))&&
                       (50 <= eventAccueil_1.button.y) && (eventAccueil_1.button.y <= 50 + 50))
                    {
                        aParametre(*mode, joueurCommence, Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }


                                                                    // clique sur 'hardcore'
                    if((7*x/8 - 100 <= eventAccueil_1.button.x) && (eventAccueil_1.button.x <= 7*x/8 + 100)&&
                       (3*y/8 - 50 <= eventAccueil_1.button.y) && (eventAccueil_1.button.y <= 3*y/8 + 50))
                    {
                    	presse = eventAccueil_1.button.timestamp - presse;// temps de pression du bouton en miliseconde

                        aHardcore(hardcore, presse);// (action.h)

                        return 1; // on retourne 1 pour rester dans la boucle de l'event Accueil 1
                    }


                                                                    // clique sur 'mode 1'
                    if((5*x/16 - 200 <= eventAccueil_1.button.x) && (eventAccueil_1.button.x <= 5*x/16 + 200)&&
                       (y/2 - 100 <= eventAccueil_1.button.y) && (eventAccueil_1.button.y <= y/2 + 100))
                    {
                        aMode1(accueil, mode);// (action.h)
                        return 0;
                    }
                                                                    // clique sur 'mode 3'
                    if((5*x/16 - 200 <= eventAccueil_1.button.x) && (eventAccueil_1.button.x <= 5*x/16 + 200)&&
                       (3*y/4 - 100 <= eventAccueil_1.button.y) && (eventAccueil_1.button.y <= 3*y/4 + 100))
                    {
                        aMode3(accueil, mode);// (action.h)
                        return 0;
                    }
                                                                    // clique sur 'mode 2'
                    if((11*x/16 - 200 <= eventAccueil_1.button.x) && (eventAccueil_1.button.x <= 11*x/16 + 200)&&
                       (y/2 - 100 <= eventAccueil_1.button.y) && (eventAccueil_1.button.y <= y/2 + 100))
                    {
                        aMode2(accueil, mode);// (action.h)
                        return 0;
                    }
                                                                    // clique sur 'mode 4'
                    if((11*x/16 - 200 <= eventAccueil_1.button.x) && (eventAccueil_1.button.x <= 11*x/16 + 200)&&
                       (3*y/4 - 100 <= eventAccueil_1.button.y) && (eventAccueil_1.button.y <= 3*y/4 + 100))
                    {
                        aMode4(accueil, mode);// (action.h)
                        return 0;
                    }

                    presse = 0;// la touche est relache donc le temps de pression est reinitialise

                }

            }
            break;

        }

    }
    return 1;

}

// evenements de l'accueil 2: quitter / choix difficulte des bots / retour
int eventAccueil_2(int* accueil, int* mode, int* joueurCommence, int* difficulteBot1, int* difficulteBot2, int* pasValide, Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde)
{
    // desactivation des enenements ininteressants
	   SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_DISABLE);
	   SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);
	   SDL_EventState(SDL_MOUSEWHEEL, SDL_DISABLE);
	   SDL_EventState(SDL_KEYDOWN, SDL_DISABLE);

	   // activation des enenements interessants
	   SDL_EventState(SDL_KEYUP, SDL_ENABLE);
	   SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);

    SDL_Event eventAccueil_2;// variable d'event

    while(SDL_PollEvent(&eventAccueil_2))// recuperation d'un evenement
    {

    	   // taille du renderer
        int x = 0, y = 0;
        SDL_GetRendererOutputSize(pRenderer, &x, &y);

        switch(eventAccueil_2.type)// selon le type de l'evenement
        {
            case SDL_QUIT:// action de quitter la fenetre (alt+F4 / croix de la fenetre / ..)
            {
                aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
            }
            break;

            case SDL_KEYUP:// relachement d'une touche du clavier
            {
                if ( eventAccueil_2.key.keysym.sym == SDLK_ESCAPE )   // Clic sur echap
                {
                    aParametre(*mode, joueurCommence, Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                }
                else if(eventAccueil_2.key.keysym.scancode == SDL_SCANCODE_GRAVE)
                {
                    afficheDebug();
                }

            }
            break;

            case SDL_MOUSEBUTTONUP:// relachement d'un bouton de la souris
            {
                if (eventAccueil_2.button.button == SDL_BUTTON_LEFT)  // Clic gauche
                {

                                                                    // clique sur 'croix'
                    if(((x-50 <= eventAccueil_2.button.x) && (eventAccueil_2.button.x <= x))&&
                       (0 <= eventAccueil_2.button.y) && (eventAccueil_2.button.y <= 50 ))
                    {
                        aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }


                                                                    // clique sur 'parametre_logo'
                    if(((50 <= eventAccueil_2.button.x) && (eventAccueil_2.button.x <= 50 + 50))&&
                       (50 <= eventAccueil_2.button.y) && (eventAccueil_2.button.y <= 50 + 50))
                    {
                        aParametre(*mode, joueurCommence, Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }

                                                                    // clique sur 'retour'
                    if((1*x/16 - 100 <= eventAccueil_2.button.x) && (eventAccueil_2.button.x <= 1*x/16 + 100)&&
                       (7*y/8 - 50 <= eventAccueil_2.button.y) && (eventAccueil_2.button.y <= 7*y/8 + 50))
                    {
                        aRetour(accueil);// (action.h)
                        return 0;
                    }
                                                                    // clique sur 'valide'
                    if((29*x/32 - 100 <= eventAccueil_2.button.x) && (eventAccueil_2.button.x <= 29*x/32 + 100)&&
                       (y/2 - 100 <= eventAccueil_2.button.y) && (eventAccueil_2.button.y <= y/2 + 100))
                    {
                        *pasValide = aValide(accueil, mode, difficulteBot1, difficulteBot2);// (action.h)
                        return *pasValide;
                    }

                    if(*mode==2)
                    {
                                                                        // clique sur 'bot1Facile'
                        if((x/2 - 200 <= eventAccueil_2.button.x) && (eventAccueil_2.button.x <= x/2 + 200)&&
                           (7*y/16 - 100 <= eventAccueil_2.button.y) && (eventAccueil_2.button.y <= 7*y/16 + 100))
                        {
                            aBotFacile(difficulteBot1);// (action.h)
                            return 1;
                        }
                                                                        // clique sur 'bot1Normal'
                        if((x/2 - 200 <= eventAccueil_2.button.x) && (eventAccueil_2.button.x <= x/2 + 200)&&
                           (10*y/16 - 100 <= eventAccueil_2.button.y) && (eventAccueil_2.button.y <= 10*y/16 + 100))
                        {
                            aBotNormal(difficulteBot1);// (action.h)
                            return 1;
                        }
                                                                        // clique sur 'bot1Difficile'
                        if((x/2 - 200 <= eventAccueil_2.button.x) && (eventAccueil_2.button.x <= x/2 + 200)&&
                           (13*y/16 - 100 <= eventAccueil_2.button.y) && (eventAccueil_2.button.y <= 13*y/16 + 100))
                        {
                            aBotDifficile(difficulteBot1);// (action.h)
                            return 1;
                        }
                    }


                    else if(*mode==4)
                    {
                        // bot 1
                                                                        // clique sur 'bot1Facile'
                        if((5*x/16 - 200 <= eventAccueil_2.button.x) && (eventAccueil_2.button.x <= 5*x/16 + 200)&&
                           (7*y/16 - 100 <= eventAccueil_2.button.y) && (eventAccueil_2.button.y <= 7*y/16 + 100))
                        {
                            aBotFacile(difficulteBot1);// (action.h)
                            return 1;
                        }
                                                                        // clique sur 'bot1Normal'
                        if((5*x/16 - 200 <= eventAccueil_2.button.x) && (eventAccueil_2.button.x <= 5*x/16 + 200)&&
                           (10*y/16 - 100 <= eventAccueil_2.button.y) && (eventAccueil_2.button.y <= 10*y/16 + 100))
                        {
                            aBotNormal(difficulteBot1);// (action.h)
                            return 1;
                        }
                                                                        // clique sur 'bot1Difficile'
                        if((5*x/16 - 200 <= eventAccueil_2.button.x) && (eventAccueil_2.button.x <= 5*x/16 + 200)&&
                           (13*y/16 - 100 <= eventAccueil_2.button.y) && (eventAccueil_2.button.y <= 13*y/16 + 100))
                        {
                            aBotDifficile(difficulteBot1);// (action.h)
                            return 1;
                        }

                        // bot 2
                                                                        // clique sur 'bot2Facile'
                        if((11*x/16 - 200 <= eventAccueil_2.button.x) && (eventAccueil_2.button.x <= 11*x/16 + 200)&&
                           (7*y/16 - 100 <= eventAccueil_2.button.y) && (eventAccueil_2.button.y <= 7*y/16 + 100))
                        {
                            aBotFacile(difficulteBot2);// (action.h)
                            return 1;
                        }
                                                                        // clique sur 'bot2Normal'
                        if((11*x/16 - 200 <= eventAccueil_2.button.x) && (eventAccueil_2.button.x <= 11*x/16 + 200)&&
                           (10*y/16 - 100 <= eventAccueil_2.button.y) && (eventAccueil_2.button.y <= 10*y/16 + 100))
                        {
                            aBotNormal(difficulteBot2);// (action.h)
                            return 1;
                        }
                                                                        // clique sur 'bot2Difficile'
                        if((11*x/16 - 200 <= eventAccueil_2.button.x) && (eventAccueil_2.button.x <= 11*x/16 + 200)&&
                           (13*y/16 - 100 <= eventAccueil_2.button.y) && (eventAccueil_2.button.y <= 13*y/16 + 100))
                        {
                            aBotDifficile(difficulteBot2);// (action.h)
                            return 1;
                        }
                    }

                }

            }
            break;

        }

    }
    return 1;

}


// event de jeu: quitter / menu / colonne active / colonne selectionnee / jeu retour
void eventJouer(int mode, int* joueurCommence, int joueur, int tour, int *colonneActive, int* colonne, int* retour, int* rejouerPartie, int* retourAccueil, int infoGrille[9], Hardcore* hardcore, caseGrille grille[9][9], Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde)
{
    // desactivation des enenements ininteressants
	   SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_DISABLE);
	   SDL_EventState(SDL_MOUSEWHEEL, SDL_DISABLE);
	   SDL_EventState(SDL_KEYDOWN, SDL_DISABLE);

	   // activation des enenements interessants
	   SDL_EventState(SDL_KEYUP, SDL_ENABLE);
	   SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);
	   SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);

    SDL_Event eventJouer;// variable d'event

    while(SDL_PollEvent(&eventJouer))// recuperation d'un evenement
    {
    	   // taille du renderer
        int x = 0, y = 0;
        SDL_GetRendererOutputSize(pRenderer, &x, &y);

        switch(eventJouer.type)// selon le type de l'evenement
        {
            case SDL_QUIT:// action de quitter la fenetre (alt+F4 / croix de la fenetre / ..)
            {
                aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
            }
            break;

            case SDL_WINDOWEVENT:
            {
                if(eventJouer.window.event == SDL_WINDOWEVENT_MINIMIZED)// met en pause le jeu si on le reduit
                {
                    if((SDL_GetWindowFlags(pWindow) & SDL_WINDOW_MINIMIZED) == SDL_WINDOW_MINIMIZED){
                        aMenu(rejouerPartie, retourAccueil, hardcore, mode, joueur, tour, joueurCommence, grille, Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }
                }
            }
            break;

            case SDL_KEYUP:// relachement d'une touche du clavier
            {
                if ( eventJouer.key.keysym.sym == SDLK_ESCAPE )   // Clic sur echap
                {
                    aMenu(rejouerPartie, retourAccueil, hardcore, mode, joueur, tour, joueurCommence, grille, Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                }
                else if(eventJouer.key.keysym.scancode == SDL_SCANCODE_GRAVE)
                {
                    afficheDebug();
                }

            }
            break;


            case SDL_MOUSEMOTION:// mouvement de la souris
            {
            	   if(mode != 3)
                {
                                                                // survol 'colonne 0'
                    if((x/2 - (3.5*100) + 2 <= eventJouer.motion.x) && (eventJouer.motion.x <= x/2 - (3.5*100) + 100)&&
                       (y/2 - 400 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 300))
                    {
                    	   *colonneActive = 0;
                    }

                                                                // survol 'colonne 1'
                    else if((x/2 - (2.5*100) + 2 <= eventJouer.motion.x) && (eventJouer.motion.x <= x/2 - (2.5*100) + 100)&&
                       (y/2 - 400 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 300))
                    {
                         *colonneActive = 1;
                    }

                                                                // survol 'colonne 2'
                    else if((x/2 - (1.5*100) + 2 <= eventJouer.motion.x) && (eventJouer.motion.x <= x/2 - (1.5*100) + 100)&&
                       (y/2 - 400 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 300))
                    {
                        *colonneActive = 2;
                    }

                                                                // curvol 'colonne 3'
                    else if((x/2 - (0.5*100) + 2 <= eventJouer.motion.x) && (eventJouer.motion.x <= x/2 - (0.5*100) + 100)&&
                       (y/2 - 400 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 300))
                    {
                        *colonneActive = 3;
                    }

                                                                // survol 'colonne 4'
                    else if((x/2 + (0.5*100) + 2 <= eventJouer.motion.x) && (eventJouer.motion.x <= x/2 + (0.5*100) + 100)&&
                       (y/2 - 400 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 300))
                    {
                        *colonneActive = 4;
                    }

                                                                // survol 'colonne 5'
                    else if((x/2 + (1.5*100) + 2 <= eventJouer.motion.x) && (eventJouer.motion.x <= x/2 + (1.5*100) + 100)&&
                       (y/2 - 400 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 300))
                    {
                        *colonneActive = 5;
                    }

                                                                    // survol 'colonne 6'
                    else if((x/2 + (2.5*100) + 2 <= eventJouer.motion.x) && (eventJouer.motion.x <= x/2 + (2.5*100) + 100)&&
                       (y/2 - 400 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 300))
                    {
                        *colonneActive = 6;
                    }

                    else
                    {
                    	   *colonneActive = -1;
                    }

                }
                else
                {

                	                                               // survol 'colonne 0'
                    if((x/2 - (4.5*100) + 2 <= eventJouer.motion.x) && (eventJouer.motion.x <= x/2 - (4.5*100) + 100)&&
                       (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                    {
                        *colonneActive = 0;
                    }

                	                                               // survol 'colonne 1'
                    else if((x/2 - (3.5*100) + 2 <= eventJouer.motion.x) && (eventJouer.motion.x <= x/2 - (3.5*100) + 100)&&
                       (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                    {
                        *colonneActive = 1;
                    }

                                                                // survol 'colonne 2'
                    else if((x/2 - (2.5*100) + 2 <= eventJouer.motion.x) && (eventJouer.motion.x <= x/2 - (2.5*100) + 100)&&
                       (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                    {
                        *colonneActive = 2;
                    }

                                                                // survol 'colonne 3'
                    else if((x/2 - (1.5*100) + 2 <= eventJouer.motion.x) && (eventJouer.motion.x <= x/2 - (1.5*100) + 100)&&
                       (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                    {
                        *colonneActive = 3;
                    }

                                                                // survol 'colonne 4'
                    else if((x/2 - (0.5*100) + 2 <= eventJouer.motion.x) && (eventJouer.motion.x <= x/2 - (0.5*100) + 100)&&
                       (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                    {
                        *colonneActive = 4;
                    }

                                                                // survol 'colonne 5'
                    else if((x/2 + (0.5*100) + 2 <= eventJouer.motion.x) && (eventJouer.motion.x <= x/2 + (0.5*100) + 100)&&
                       (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                    {
                        *colonneActive = 5;
                    }

                                                                // survol 'colonne 6'
                    else if((x/2 + (1.5*100) + 2 <= eventJouer.motion.x) && (eventJouer.motion.x <= x/2 + (1.5*100) + 100)&&
                       (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                    {
                        *colonneActive = 6;
                    }

                                                                // survol 'colonne 7'
                    else if((x/2 + (2.5*100) + 2 <= eventJouer.motion.x) && (eventJouer.motion.x <= x/2 + (2.5*100) + 100)&&
                       (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                    {
                        *colonneActive = 7;
                    }

                    	                                           // survol 'colonne 8'
                    else if((x/2 + (3.5*100) + 2 <= eventJouer.motion.x) && (eventJouer.motion.x <= x/2 + (3.5*100) + 100)&&
                       (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                    {
                        *colonneActive = 8;
                    }

                    else
                    {
                    	   *colonneActive = -1;
                    }

                }

            }
            break;


            case SDL_MOUSEBUTTONUP:// relachement d'un bouton de la souris
            {
                if (eventJouer.button.button == SDL_BUTTON_LEFT)  // Clic gauche
                {
                                                                               // clique sur 'croix'
                    if(((x-50 <= eventJouer.button.x) && (eventJouer.button.x <= x))&&
                       (0 <= eventJouer.button.y) && (eventJouer.button.y <= 50 ))
                    {
                        aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }


                                                                    // clique sur 'menu_logo'
                    if(((50 <= eventJouer.button.x) && (eventJouer.button.x <= 50 + 50))&&
                       (50 <= eventJouer.button.y) && (eventJouer.button.y <= 50 + 50))
                    {
                        aMenu(rejouerPartie, retourAccueil, hardcore, mode, joueur, tour, joueurCommence, grille, Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }


                    if(tour != 0)
                    {                                                    // clique sur 'jeu_retour'
                        if(((x/2 - 650 - 100 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 - 650 + 100))&&
                           (y/2 - 50 <= eventJouer.button.y) && (eventJouer.button.y <= y/2 + 50 ))
                        {
                        	   *retour = 1;// le jeu vas charger le tour precedent
                        }
                    }


                    if(mode != 3)
                    {
                                                                    // clique sur 'colonne 0'
                        if((x/2 - (3.5*100) + 2 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 - (3.5*100) + 100)&&
                           (y/2 - 400 <= eventJouer.button.y) && (eventJouer.button.y <= y/2 + 300))
                        {
                        	   aJouerColonne(0, colonne, infoGrille);// (action.h)
                        }

                                                                    // clique sur 'colonne 1'
                        if((x/2 - (2.5*100) + 2 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 - (2.5*100) + 100)&&
                           (y/2 - 400 <= eventJouer.button.y) && (eventJouer.button.y <= y/2 + 300))
                        {
                            aJouerColonne(1, colonne, infoGrille);// (action.h)
                        }

                                                                    // clique sur 'colonne 2'
                        if((x/2 - (1.5*100) + 2 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 - (1.5*100) + 100)&&
                           (y/2 - 400 <= eventJouer.button.y) && (eventJouer.button.y <= y/2 + 300))
                        {
                            aJouerColonne(2, colonne, infoGrille);// (action.h)
                        }

                                                                    // clique sur 'colonne 3'
                        if((x/2 - (0.5*100) + 2 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 - (0.5*100) + 100)&&
                           (y/2 - 400 <= eventJouer.button.y) && (eventJouer.button.y <= y/2 + 300))
                        {
                            aJouerColonne(3, colonne, infoGrille);// (action.h)
                        }

                                                                    // clique sur 'colonne 4'
                        if((x/2 + (0.5*100) + 2 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 + (0.5*100) + 100)&&
                           (y/2 - 400 <= eventJouer.button.y) && (eventJouer.button.y <= y/2 + 300))
                        {
                            aJouerColonne(4, colonne, infoGrille);// (action.h)
                        }

                                                                    // clique sur 'colonne 5'
                        if((x/2 + (1.5*100) + 2 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 + (1.5*100) + 100)&&
                           (y/2 - 400 <= eventJouer.button.y) && (eventJouer.button.y <= y/2 + 300))
                        {
                            aJouerColonne(5, colonne, infoGrille);// (action.h)
                        }

                                                                    // clique sur 'colonne 6'
                        if((x/2 + (2.5*100) + 2 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 + (2.5*100) + 100)&&
                           (y/2 - 400 <= eventJouer.button.y) && (eventJouer.button.y <= y/2 + 300))
                        {
                            aJouerColonne(6, colonne, infoGrille);// (action.h)
                        }

                    }
                    else
                    {

                    	                                               // clique sur 'colonne 0'
                        if((x/2 - (4.5*100) + 2 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 - (4.5*100) + 100)&&
                            (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                        {
                            aJouerColonne(0, colonne, infoGrille);// (action.h)
                        }

                    	                                               // clique sur 'colonne 1'
                        if((x/2 - (3.5*100) + 2 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 - (3.5*100) + 100)&&
                           (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                        {
                            aJouerColonne(1, colonne, infoGrille);// (action.h)
                        }

                                                                    // clique sur 'colonne 2'
                        if((x/2 - (2.5*100) + 2 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 - (2.5*100) + 100)&&
                           (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                        {
                            aJouerColonne(2, colonne, infoGrille);// (action.h)
                        }

                                                                    // clique sur 'colonne 3'
                        if((x/2 - (1.5*100) + 2 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 - (1.5*100) + 100)&&
                           (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                        {
                            aJouerColonne(3, colonne, infoGrille);// (action.h)
                        }

                                                                    // clique sur 'colonne 4'
                        if((x/2 - (0.5*100) + 2 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 - (0.5*100) + 100)&&
                           (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                        {
                            aJouerColonne(4, colonne, infoGrille);// (action.h)
                        }

                                                                    // clique sur 'colonne 5'
                        if((x/2 + (0.5*100) + 2 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 + (0.5*100) + 100)&&
                           (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                        {
                            aJouerColonne(5, colonne, infoGrille);// (action.h)
                        }

                                                                    // clique sur 'colonne 6'
                        if((x/2 + (1.5*100) + 2 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 + (1.5*100) + 100)&&
                           (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                        {
                            aJouerColonne(6, colonne, infoGrille);// (action.h)
                        }

                                                                    // clique sur 'colonne 7'
                        if((x/2 + (2.5*100) + 2 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 + (2.5*100) + 100)&&
                           (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                        {
                            aJouerColonne(7, colonne, infoGrille);// (action.h)
                        }

                    	                                               // clique sur 'colonne 8'
                        if((x/2 + (3.5*100) + 2 <= eventJouer.button.x) && (eventJouer.button.x <= x/2 + (3.5*100) + 100)&&
                           (y/2 - 500 <= eventJouer.motion.y) && (eventJouer.motion.y <= y/2 + 500))
                        {
                            aJouerColonne(8, colonne, infoGrille);// (action.h)
                        }

                    }


                }

            }
            break;

        }

    }

}

// event qui permet au joueur d'effectuer des actions lorsque le bot joue
void eventBot(int *rejouerPartie, int *retourAccueil, Hardcore* hardcore, int mode, int joueur, int tour, int* retour, int* joueurCommence, caseGrille grille[9][9], Images* Images, SDL_Window *pWindow, SDL_Renderer *pRenderer, FILE *fDebug, FILE *fSauvegarde)
{
	   // desactivation des enenements ininteressants
	   SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_DISABLE);
	   SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);
	   SDL_EventState(SDL_MOUSEWHEEL, SDL_DISABLE);
	   SDL_EventState(SDL_KEYDOWN, SDL_DISABLE);

	   // activation des enenements interessants
	   SDL_EventState(SDL_KEYUP, SDL_ENABLE);
	   SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);

    SDL_Event eventBot;// variable d'event

    while(SDL_PollEvent(&eventBot))// recuperation d'un evenement
    {
    	   // taille du renderer
        int x = 0, y = 0;
        SDL_GetRendererOutputSize(pRenderer, &x, &y);

        switch(eventBot.type)// selon le type de l'evenement
        {
            case SDL_QUIT:// action de quitter la fenetre (alt+F4 / croix de la fenetre / ..)
            {
                aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
            }
            break;

            case SDL_WINDOWEVENT:
            {
                if(eventBot.window.event == SDL_WINDOWEVENT_MINIMIZED)// met en pause le jeu si on le reduit
                {
                    if((SDL_GetWindowFlags(pWindow) & SDL_WINDOW_MINIMIZED) == SDL_WINDOW_MINIMIZED){
                        aMenu(rejouerPartie, retourAccueil, hardcore, mode, joueur, tour, joueurCommence, grille, Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }
                }
            }
            break;

            case SDL_KEYUP:// relachement d'une touche du clavier
            {
                if ( eventBot.key.keysym.sym == SDLK_ESCAPE )   // Clic sur echap
                {
                    aMenu(rejouerPartie, retourAccueil, hardcore, mode, joueur, tour, joueurCommence, grille, Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                }
                else if(eventBot.key.keysym.scancode == SDL_SCANCODE_GRAVE)
                {
                    afficheDebug();
                }

            }
            break;

            case SDL_MOUSEBUTTONUP:// relachement d'un bouton de la souris
            {
                if (eventBot.button.button == SDL_BUTTON_LEFT)  // Clic gauche
                {
                                                                               // clique sur 'croix'
                    if(((x-50 <= eventBot.button.x) && (eventBot.button.x <= x))&&
                       (0 <= eventBot.button.y) && (eventBot.button.y <= 50 ))
                    {
                        aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }

                                                                                // clique sur 'menu_logo'
                    if(((50 <= eventBot.button.x) && (eventBot.button.x <= 50 + 50))&&
                       (50 <= eventBot.button.y) && (eventBot.button.y <= 50 + 50))
                    {
                        aMenu(rejouerPartie, retourAccueil, hardcore, mode, joueur, tour, joueurCommence, grille, Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }


                    if(tour != 0)
                    {                                                    // clique sur 'jeu_retour'
                        if(((x/2 - 650 - 100 <= eventBot.button.x) && (eventBot.button.x <= x/2 - 650 + 100))&&
                           (y/2 - 50 <= eventBot.button.y) && (eventBot.button.y <= y/2 + 50 ))
                        {
                               *retour = 1;// le jeu vas charger le tour precedent
                        }
                    }
                }

            }
            break;

        }
    }
}


// event de menu: quitter / reprendre / recommencer une partie / retour a l'accueil
int eventMenu(int mode, int* joueurCommence, int* rejouerPartie, int* retourAccueil, Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde)
{
    // desactivation des enenements ininteressants
	   SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_DISABLE);
	   SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);
	   SDL_EventState(SDL_MOUSEWHEEL, SDL_DISABLE);
	   SDL_EventState(SDL_KEYDOWN, SDL_DISABLE);

	   // activation des enenements interessants
	   SDL_EventState(SDL_KEYUP, SDL_ENABLE);
	   SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);

    SDL_Event eventMenu;// variable d'event

    while(SDL_PollEvent(&eventMenu))// recuperation d'un evenement
    {
        // taille du renderer
        int x = 0, y = 0;
        SDL_GetRendererOutputSize(pRenderer, &x, &y);

        switch(eventMenu.type)// selon le type de l'evenement
        {
            case SDL_QUIT:// action de quitter la fenetre (alt+F4 / croix de la fenetre / ..)
            {
                aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
            }
            break;

            case SDL_KEYUP:// relachement d'une touche du clavier
            {
                if ( eventMenu.key.keysym.sym == SDLK_ESCAPE )   // Clic sur echap
                {
                    return 0;// on reprend la partie
                }
                else if(eventMenu.key.keysym.scancode == SDL_SCANCODE_GRAVE)
                {
                    afficheDebug();
                }

            }
            break;

            case SDL_MOUSEBUTTONUP:// relachement d'un bouton de la souris
            {
                if (eventMenu.button.button == SDL_BUTTON_LEFT)  // Clic gauche
                {

                                                                    // clique sur 'croix'
                    if(((x-50 <= eventMenu.button.x) && (eventMenu.button.x <= x))&&
                       (0 <= eventMenu.button.y) && (eventMenu.button.y <= 50 ))
                    {
                        aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }

                                                                    // clique sur 'parametre_logo'
                    if(((50 <= eventMenu.button.x) && (eventMenu.button.x <= 50 + 50))&&
                       (50 <= eventMenu.button.y) && (eventMenu.button.y <= 50 + 50))
                    {
                        aParametre(mode, joueurCommence, Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }


                                                                   // clique sur 'reprendre'
                    if((x/2 - 200 <= eventMenu.button.x) && (eventMenu.button.x <= x/2 + 200)&&
                       (2*y/16 - 100 <= eventMenu.button.y) && (eventMenu.button.y <= 2*y/16 + 100))
                    {
                        return 0;// on reprend la partie
                    }

                                                                    // clique sur 'rejouer'
                    if((x/2 - 200 <= eventMenu.button.x) && (eventMenu.button.x <= x/2 + 200)&&
                       (6*y/16 - 100 <= eventMenu.button.y) && (eventMenu.button.y <= 6*y/16 + 100))
                    {
                        *rejouerPartie = 1; // indique au jeu que l'on veut recommencer une partie
                        return 0;
                    }

                                                                    // clique sur 'retourAccueil'
                    if((x/2 - 200 <= eventMenu.button.x) && (eventMenu.button.x <= x/2 + 200)&&
                       (10*y/16 - 100 <= eventMenu.button.y) && (eventMenu.button.y <= 10*y/16 + 100))
                    {
                        *retourAccueil = 1;// indique au jeu que l'on veut retourner a l'accueil
                        return 0;
                    }

                                                                  // clique sur 'quitter'
                    if((x/2 - 200 <= eventMenu.button.x) && (eventMenu.button.x <= x/2 + 200)&&
                       (14*y/16 - 100 <= eventMenu.button.y) && (eventMenu.button.y <= 14*y/16 + 100))
                    {
                        aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                        return 0;
                    }


                }

            }
            break;

        }

    }
    return 1;

}

// event de menu: quitter / recommencer une partie / retour a l'accueil
int eventFin(int mode, int* joueurCommence, int* rejouer, Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde)
{
    // desactivation des enenements ininteressants
	   SDL_EventState(SDL_MOUSEBUTTONDOWN, SDL_DISABLE);
	   SDL_EventState(SDL_MOUSEMOTION, SDL_DISABLE);
	   SDL_EventState(SDL_MOUSEWHEEL, SDL_DISABLE);
	   SDL_EventState(SDL_KEYDOWN, SDL_DISABLE);

	   // activation des enenements interessants
	   SDL_EventState(SDL_KEYUP, SDL_ENABLE);
	   SDL_EventState(SDL_MOUSEBUTTONUP, SDL_ENABLE);

    SDL_Event eventFin; // variable d'event

    while(SDL_PollEvent(&eventFin))// recuperation d'un evenement
    {
    	   // taille du renderer
        int x = 0, y = 0;
        SDL_GetRendererOutputSize(pRenderer, &x, &y);

        switch(eventFin.type)// selon le type de l'evenement
        {
            case SDL_QUIT:// action de quitter la fenetre (alt+F4 / croix de la fenetre / ..)
            {
                aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
            }
            break;

            case SDL_KEYUP: // relachement d'une touche du clavier
            {
                if ( eventFin.key.keysym.sym == SDLK_ESCAPE )   // Clic sur echap
                {
                    aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                }
                else if(eventFin.key.keysym.scancode == SDL_SCANCODE_GRAVE)
                {
                    afficheDebug();
                }

            }
            break;

            case SDL_MOUSEBUTTONUP: // relachement d'un bouton de la souris
            {
                if (eventFin.button.button == SDL_BUTTON_LEFT)  // Clic gauche
                {

                                                                    // clique sur 'croix'
                    if(((x-50 <= eventFin.button.x) && (eventFin.button.x <= x))&&
                       (0 <= eventFin.button.y) && (eventFin.button.y <= 50 ))
                    {
                        aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }

                                                                    // clique sur 'parametre_logo'
                    if(((50 <= eventFin.button.x) && (eventFin.button.x <= 50 + 50))&&
                       (50 <= eventFin.button.y) && (eventFin.button.y <= 50 + 50))
                    {
                        aParametre(mode, joueurCommence, Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                    }


                                                                    // clique sur 'rejouer'
                    if((x/2 - 200 <= eventFin.button.x) && (eventFin.button.x <= x/2 + 200)&&
                       (3*y/16 - 100 <= eventFin.button.y) && (eventFin.button.y <= 3*y/16 + 100))
                    {
                        *rejouer = 1;// indique au jeu que l'on veut recommencer une partie
                        return 0;
                    }

                                                                    // clique sur 'retourAccueil'
                    if((x/2- 200 <= eventFin.button.x) && (eventFin.button.x <= x/2 + 200)&&
                       (8*y/16 - 100 <= eventFin.button.y) && (eventFin.button.y <= 8*y/16 + 100))
                    {
                        *rejouer = 0;// indique au jeu que l'on veut retourner a l'accueil
                        return 0;
                    }

                                                                  // clique sur 'quitter'
                    if((x/2- 200 <= eventFin.button.x) && (eventFin.button.x <= x/2 + 200)&&
                       (13*y/16 - 100 <= eventFin.button.y) && (eventFin.button.y <= 13*y/16 + 100))
                    {
                        aQuit(Images, pWindow, pRenderer, fDebug, fSauvegarde);// (action.h)
                        return 0;
                    }


                }

            }
            break;

        }

    }
    return 1;

}
