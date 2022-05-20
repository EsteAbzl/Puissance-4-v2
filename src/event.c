/*
gere les evenements
*/


#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"


#include "event.h"
#include "action.h"

void evenement(Image* images, InfoJeu* jeu, InfoFenetre* fenetre, FILE* fDebug){

    int eventDispo = 1; // comme son nom l'indique, permet d'eviter d'effectuer plusieur action a partir d'un même event

    SDL_GetMouseState(&jeu->m_x, &jeu->m_y);
    int m_x = jeu->m_x;
    int m_y = jeu->m_y;
    int f_w = fenetre->w;
    int f_h = fenetre->h;

    SDL_Event event;

    while(SDL_PollEvent(&event)){

        // evenements communs
        switch(event.type){
            case SDL_QUIT:{             // quitte la fenetre (alt+F4 / croix de la fenetre / ..)
                    aQuit(images, jeu, fenetre, fDebug);
                }
                break;

            case SDL_WINDOWEVENT:{      // met en pause le jeu si on le reduit
                    if(event.window.event == SDL_WINDOWEVENT_MINIMIZED){
                        if((SDL_GetWindowFlags(fenetre->pWindow) & SDL_WINDOW_MINIMIZED) == SDL_WINDOW_MINIMIZED){
                            fenetre->menu = 1;
                        }
                    }
                }
                break;

            case SDL_KEYUP:{            // fait 'echap" ou "²"
                    if(event.key.keysym.sym == SDLK_ESCAPE){  // "echap"
                        // affiche les parametres
                        if(fenetre->ecran == ACCUEIL_MENU || fenetre->ecran == ACCUEIL_BOT || fenetre->fin){
                            if(fenetre->parametre){
                                fenetre->parametre = 0;
                            }
                            else{
                                fenetre->parametre = 1;
                            }
                        }
                        // affiche le menu
                        else if(fenetre->ecran == JEU){
                            if(fenetre->menu){
                                if(fenetre->parametre){
                                    fenetre->parametre = 0;
                                }
                                else{
                                    fenetre->menu = 0;
                                }
                            }
                            else if(fenetre->fin){
                                if(fenetre->parametre){
                                    fenetre->parametre = 0;
                                }
                                else{
                                    aQuit(images, jeu, fenetre, fDebug);
                                }
                            }
                            else{
                                fenetre->menu = 1;
                            }
                        }
                        // quitte
                        else{
                            aQuit(images, jeu, fenetre, fDebug);
                        }
                    }
                    else if(event.key.keysym.scancode == SDL_SCANCODE_GRAVE){
                        afficheDebug();
                        eventDispo = 0;
                    }
                }
                break;

            case SDL_MOUSEBUTTONUP:{    // clique sur "croix" ou "parametre_logo"
                    if (event.button.button == SDL_BUTTON_LEFT){
                        if(((f_w-50 <= m_x)&&(m_x <= f_w)) && (0 <= m_y)&&(m_y <= 50 )){
                            aQuit(images, jeu, fenetre, fDebug);
                        }
                        if(eventDispo && (fenetre->ecran == ACCUEIL_MENU || fenetre->ecran == ACCUEIL_BOT || fenetre->menu || fenetre->fin)){
                            if(((50 - 25 <= m_x)&&(m_x <= 50 + 25)) && (50 - 25 <= m_y)&&(m_y <= 50 + 25 )){
                                fenetre->parametre = 1;
                                eventDispo = 0;
                            }
                        }
                    }
                }
                break;
        }


        if(fenetre->menu || fenetre->parametre || fenetre->fin){
            if(fenetre->parametre){
                if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT){
                    // clique en dehors des parametres
                    if(eventDispo && (((m_x <= f_w/2 - 720)||(f_w/2 + 720 <= m_x)) || (m_y <= f_h*9/16 - 338)||(f_h*9/16 + 338 <= m_y))){
                        fenetre->parametre = 0;
                        eventDispo = 0;
                    }

                    // clique sur 'joueur1Commence'
                    if(((f_w/2 - 360 - 200 <= m_x)&&(m_x <= f_w/2 - 360 + 200)) && ((f_h*9/16 - 98 - 50 <= m_y)&&(m_y <= f_h*9/16 - 98 + 50))){
                        jeu->joueurCommence = 1;
                    }
                    // clique sur 'joueur2Commence'
                    if(((f_w/2 - 360 - 200 <= m_x)&&(m_x <= f_w/2 - 360 + 200)) && ((f_h*9/16 - 98 + 125 - 50 <= m_y)&&(m_y <= f_h*9/16 - 98 + 125 + 50))){
                        jeu->joueurCommence = 2;
                    }
                    // clique sur 'joueur3Commence'
                    if(((f_w/2 - 360 - 200 <= m_x)&&(m_x <= f_w/2 - 360 + 200)) && ((f_h*9/16 - 98 + 250 - 50 <= m_y)&&(m_y <= f_h*9/16 - 98 + 250 + 50))){
                        if(jeu->mode == 0 || jeu->mode == 3){
                            jeu->joueurCommence = 3;
                        }
                    }
                }
            }
            else if(fenetre->menu){
                if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT){
                    // clique sur 'reprendre'
                    if(((f_w/2 - 200 <= m_x)&&(m_x <= f_w/2 + 200)) && (f_h*2/16 - 100 <= m_y)&&(m_y <= f_h*2/16 + 100)){
                        fenetre->menu = 0;
                    }
                    // clique sur 'rejouer'
                    if(((f_w/2 - 200 <= m_x)&&(m_x <= f_w/2 + 200)) && (f_h*6/16 - 100 <= m_y)&&(m_y <= f_h*6/16 + 100)){
                        jeu->rejouerPartie = 1;
                    }
                    // clique sur 'retourAccueil'
                    if(((f_w/2 - 200 <= m_x)&&(m_x <= f_w/2 + 200)) && (f_h*10/16 - 100 <= m_y)&&(m_y <= f_h*10/16 + 100)){
                        jeu->retourAccueil = 1;
                    }
                    // clique sur 'quitter'
                    if(((f_w/2 - 200 <= m_x)&&(m_x <= f_w/2 + 200)) && (f_h*14/16 - 100 <= m_y)&&(m_y <= f_h*14/16 + 100)){
                        aQuit(images, jeu, fenetre, fDebug);
                    }
                }
            }
            else if(fenetre->fin){
                if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT){
                    // clique sur 'rejouer'
                    if(((f_w/2 - 200 <= m_x)&&(m_x <= f_w/2 + 200)) && (f_h*3/16 - 100 <= m_y)&&(m_y <= f_h*3/16 + 100)){
                        jeu->rejouerPartie = 1;
                    }
                    // clique sur 'retourAccueil'
                    if(((f_w/2 - 200 <= m_x)&&(m_x <= f_w/2 + 200)) && (f_h*8/16 - 100 <= m_y)&&(m_y <= f_h*8/16 + 100)){
                        jeu->retourAccueil = 1;
                    }
                    // clique sur 'quitter'
                    if(((f_w/2 - 200 <= m_x)&&(m_x <= f_w/2 + 200)) && (f_h*13/16 - 100 <= m_y)&&(m_y <= f_h*13/16 + 100)){
                        aQuit(images, jeu, fenetre, fDebug);
                    }
                }
            }
        }
        else{   // evenements relatifs a chaque ecran
            switch(fenetre->ecran){
                case LENCEMENT:{
                        if(eventDispo && (event.type == SDL_KEYUP || event.type == SDL_MOUSEBUTTONUP)){
                            fenetre->ecran = ACCUEIL_MENU;
                            eventDispo = 0;
                        }
                    }
                    break;

                case ACCUEIL_MENU:{
                        switch(event.type){
                            case SDL_MOUSEBUTTONDOWN:{
                                    /* on veut savoir combien de temps le clic est enfoncé donc
                                    on enregistre le temps du clic (pour definir le mode hardcore)*/
                                    if (event.button.button == SDL_BUTTON_LEFT){
                                        images->image[hardcore_inactif].temps = SDL_GetTicks();
                                    }
                                }
                                break;
                            case SDL_MOUSEBUTTONUP:{
                                    if (event.button.button == SDL_BUTTON_LEFT){
                                        // clique sur 'hardcore'
                                        if(((f_w*7/8 - 100 <= m_x)&&(m_x <= f_w*7/8 + 100)) && (f_h*3/8 - 50 <= m_y)&&(m_y <= f_h*3/8 + 50)){
                                            aHardcore(&jeu->hardcore, (SDL_GetTicks() - images->image[hardcore_inactif].temps));
                                        }

                                        // clique sur 'mode 1'
                                        if(((f_w*5/16 - 200 <= m_x)&&(m_x <= f_w*5/16 + 200)) && (f_h/2 - 100 <= m_y)&&(m_y <= f_h/2 + 100)){
                                            fenetre->ecran = JEU;
                                            jeu->mode = 1;
                                        }
                                        // clique sur 'mode 2'
                                        if(((f_w*11/16 - 200 <= m_x)&&(m_x <= f_w*11/16 + 200)) && (f_h/2 - 100 <= m_y)&&(m_y <= f_h/2 + 100)){
                                            fenetre->ecran = ACCUEIL_BOT;
                                            jeu->mode = 2;
                                        }
                                        // clique sur 'mode 3'
                                        if(((f_w*5/16 - 200 <= m_x)&&(m_x <= f_w*5/16 + 200)) && (f_h*3/4 - 100 <= m_y)&&(m_y <= f_h*3/4 + 100)){
                                            fenetre->ecran = JEU;
                                            jeu->mode = 3;
                                        }
                                        // clique sur 'mode 4'
                                        if(((f_w*11/16 - 200 <= m_x)&&(m_x <= f_w*11/16 + 200)) && (f_h*3/4 - 100)&&(m_y <= f_h*3/4 + 100)){
                                            fenetre->ecran = ACCUEIL_BOT;
                                            jeu->mode = 4;
                                        }
                                    }
                                }
                                break;
                        }
                    }
                    break;

                case ACCUEIL_BOT:{
                        if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT){
                            // clique sur 'retour'
                            if(((f_w/16 - 100 <= m_x)&&(m_x <= f_w/16 + 100)) && (f_h*7/8 - 50 <= m_y)&&(m_y <= f_h*7/8 + 50)){
                                fenetre->ecran = ACCUEIL_MENU;
                                jeu->mode = 0;
                            }

                            // clique sur 'valide'
                            if(((f_w*29/32 - 100 <= m_x)&&(m_x <= f_w*29/32 + 100)) && (f_h/2 - 50 <= m_y)&&(m_y <= f_h/2 + 50)){
                                aValide(images, jeu, fenetre);
                            }

                            if(jeu->mode == 2){
                                evenement_difficulteBot(f_w/2, f_h, m_x, m_y, &jeu->bot1.difficulte);
                            }
                            if(jeu->mode == 4){
                                evenement_difficulteBot(f_w*5/16, f_h, m_x, m_y, &jeu->bot1.difficulte);
                                evenement_difficulteBot(f_w*11/16, f_h, m_x, m_y, &jeu->bot2.difficulte);
                            }
                        }
                    }
                    break;

                case JEU:{
                        if(event.type == SDL_MOUSEBUTTONUP && event.button.button == SDL_BUTTON_LEFT){
                            // clique sur 'jeu_retour'
                            if(((50 - 25 <= m_x)&&(m_x <= 50 + 25)) && (50 - 25 <= m_y)&&(m_y <= 50 + 25)){
                                fenetre->menu = 1;
                            }

                            if(jeu->tour){
                                // clique sur 'jeu_retour'
                                if(((f_w/2 - 650 - 100 <= m_x)&&(m_x <= f_w/2 - 650 + 100)) && (f_h/2 - 50 <= m_y)&&(m_y <= f_h/2 + 50)){
                                    jeu->retour = 1;
                                }
                            }

                            // selection de la colonne pour jouer-
                            int debutColonne_x = (jeu->mode == 3)? fenetre->w/2 - 450 : fenetre->w/2 - 350;

                            int colonneSurvole = (m_y >= fenetre->h/2 - 400 && ((jeu->mode != 3 && m_y <= fenetre->h/2 + 300) || (jeu->mode == 3 && m_y <= fenetre->h/2 + 500)))? ((m_x - debutColonne_x) / 100) : -1;
                            int colonneActive = (colonneSurvole >= 0 && ((jeu->mode != 3 && colonneSurvole <= 7) || (jeu->mode == 3 && colonneSurvole <= 9)))? colonneSurvole : -1;

                            infosGrille(jeu);
                            if(colonneActive != -1 && jeu->infoGrille[colonneActive]){
                                jeu->colonne = colonneActive;
                            }
                        }
                    }
                    break;
            }
        }


    }
}

void evenement_difficulteBot(int x, int f_h, int m_x, int m_y, int* difficulte){

    // clique sur 'botFacile'
    if(((x - 200 <= m_x)&&(m_x <= x + 200)) && (f_h*7/16 - 100 <= m_y)&&(m_y <= f_h*7/16 + 100)){
        *difficulte = 1;
    }
    // clique sur 'botNormal'
    if(((x - 200 <= m_x)&&(m_x <= x + 200)) && (f_h*10/16 - 100 <= m_y)&&(m_y <= f_h*10/16 + 100)){
        *difficulte = 2;
    }
    // clique sur 'botDifficile'
    if(((x - 200 <= m_x)&&(m_x <= x + 200)) && (f_h*13/16 - 100 <= m_y)&&(m_y <= f_h*13/16 + 100)){
        *difficulte = 3;
    }
}



