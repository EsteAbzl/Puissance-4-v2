/*
Corp du jeu:
appelle les fonctions graphiques
appelle les fontions du jeu
*/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

#include "jeu.h"
#include "grille.h"
#include "bot.h"

#include "video.h"
#include "image.h"

#include "event.h"

void res_Hardcore(Hardcore* hardcore){
    hardcore->mode = 0;
    hardcore->tempsRestant = 0;
}

void res_Strat(Strat* strat){
    strat->colonne = 0;
    strat->ligne = 0;
    strat->type = 0;
}

void res_Bot(Bot* bot){
    bot->difficulte = 0;
    res_Strat(&bot->strat);
}

void res_InfoJeu(InfoJeu* jeu){
    jeu->m_x = 0;
    jeu->m_y = 0;

    res_Grille(jeu->grille);

    for(int i = 0; i < 9; i++){
        jeu->infoGrille[i] = 0;
    }

    //initialisation du fichier de sauvegarde de la partie ('fSauvegarde')
    jeu->fSauvegarde = NULL;
    if((jeu->fSauvegarde = fopen("./data/sauvegarde.txt","w+")) == NULL){
        fprintf(fDebug, "ERREUR: impossible d'ouvrir le fichier 'fSauvegarde.txt'");
    }

    jeu->mode = 0;

    res_Hardcore(&jeu->hardcore);

    res_Bot(&jeu->bot1);
    res_Bot(&jeu->bot2);

    jeu->joueurCommence = 1;
    jeu->joueur = 0;

    jeu->colonne = -1;
    jeu->tour = 0;
    jeu->retour = 0;

    jeu->rejouerPartie = 0;
    jeu->retourAccueil = 0;
    jeu->fin = 0;
}

void res_InfoPartie(InfoJeu* jeu){
    res_Grille(jeu->grille);

    for(int i = 0; i < 9; i++){
        jeu->infoGrille[i] = 0;
    }

    if(jeu->hardcore.mode == 1)
        jeu->hardcore.tempsRestant = 10;
    else if(jeu->hardcore.mode == 2)
        jeu->hardcore.tempsRestant = 3;

    // clear du fichiers de sauvegarde
    fclose(jeu->fSauvegarde);
    jeu->fSauvegarde = NULL;
    remove("./data/sauvegarde.txt");

    if((jeu->fSauvegarde = fopen("./data/sauvegarde.txt","w+")) == NULL){
        fprintf(fDebug, "ERREUR: impossible d'ouvrir le fichier 'fSauvegarde.txt'");
        exit(-1);
    }

    res_Strat(&jeu->bot1.strat);
    res_Strat(&jeu->bot2.strat);

    jeu->colonne = -1;
    jeu->tour = 0;
    jeu->retour = 0;

    jeu->rejouerPartie = 0;
    jeu->retourAccueil = 0;
    jeu->fin = 0;
}

// corp du jeu
void fonctionJeu(InfoFenetre* fenetre, FILE* fDebug){

    // chargement des images
    InfoJeu jeu;
    res_InfoJeu(&jeu);

    Image images; // voir image.h

    res_Image(&images, 0);

    fenetre->ecran = LENCEMENT;

    while(1){ // jeu

        res_InfoJeu(&jeu);

        while(fenetre->ecran != JEU){

            affichage(&images, &jeu, fenetre, fDebug);

            evenement(&images, &jeu, fenetre, fDebug);
        }

        do// une partie
        {
            res_InfoPartie(&jeu);

            if(jeu.mode != 3 && jeu.joueurCommence == 3)
                jeu.joueurCommence = 1;

            jeu.joueur = jeu.joueurCommence;

            while(jeu.fin == 0 && jeu.rejouerPartie == 0 && jeu.retourAccueil == 0){

                affichage(&images, &jeu, fenetre, fDebug);

                evenement(&images, &jeu, fenetre, fDebug);


                sprintf(debugTexte[0].txt,"=--=--= GENERAL =--=--=");
                sprintf(debugTexte[3].txt,"mode séléctionné: %d", jeu.mode);
                sprintf(debugTexte[2].txt,"tour actuel: %d", jeu.tour);


                if(jeu.hardcore.mode){
                    if((SDL_GetTicks() - images.image[hardcore_bg].temps) > 1000){
                        jeu.hardcore.tempsRestant--;
                        if(jeu.hardcore.tempsRestant == 0){ // ici info sert a savoir si l'image est visible
                            jeu.colonne = (rand() % 7);
                        }

                        images.image[hardcore_bg].temps = SDL_GetTicks();
                    }
                }


                if((jeu.mode == 2 && jeu.joueur == 2) || jeu.mode == 4)// le bot joue
                {
                    if(jeu.mode == 2 && jeu.joueur == 2){
                        bot(&jeu.bot1, &jeu);
                    }
                    else{
                        if(jeu.joueur == 1){
                            bot(&jeu.bot1, &jeu);
                        }
                        else{
                            bot(&jeu.bot2, &jeu);
                        }
                    }

                    sprintf(debugTexte[4].txt, "=--=--= Bot =--=--=");

                    sprintf(debugTexte[5].txt, "strat choisie: bot 1: c: %d l: %d type: %d", jeu.bot1.strat.colonne, jeu.bot1.strat.ligne, jeu.bot1.strat.type);

                    /*
                    for(int temps = 0; (temps < 1000) && (retour == 0) && (rejouerPartie == 0) && (retourAccueil == 0); temps += 17)// rajoute du realisme en faisant attendre 1 seconde
                        {
                            if(temps < 500) // affiche le pion en haut de la grille
                                affiche(0, mode, joueur, tour, -1, grille, &images, pRenderer, fDebug);
                            else // fait tomber le pion
                                affiche(0, mode, joueur, tour, colonne, grille, &images, pRenderer, fDebug);

                            afficheImage(images.autre.croix, [x - 50, 0], pRenderer, fDebug);

                            afficheImage(images.menu.menu_logo, [75, 75], OUI, pRenderer, fDebug);// logo du menu

                            SDL_RenderPresent(pRenderer);

                            SDL_Delay(17);

                            eventBot(&rejouerPartie, &retourAccueil, &hardcore, mode, joueur, tour, &retour, &joueurCommence, grille, &Images, pWindow, pRenderer, fDebug, fSauvegarde);

                        }
                    */
                }

                if(jeu.colonne != -1){ // la colonne a été joué
                    placePion(&jeu, fenetre);

                    jeu.tour++;

                    // res du temps limite selon le mode hardcore
                    if(jeu.hardcore.mode == 1)
                        jeu.hardcore.tempsRestant = 10;
                    else if(jeu.hardcore.mode == 2)
                        jeu.hardcore.tempsRestant = 3;


                    if(jeu.retour){
                        recupereGrille(&images, &jeu, fenetre, fDebug);// charge la grille du tour precedent
                    }
                    else{
                        sauvegardeGrille(&jeu, fDebug); // sauvegarde de la grille actuelle
                    }

                    jeu.retour = 0; // reset de retour


                    jeu.colonne = -1;

                    // changement de joueur
                    if((jeu.mode != 3 && jeu.joueur == 1) || (jeu.mode == 3 && (jeu.joueur == 1 || jeu.joueur == 2))){
                        jeu.joueur++;
                    }
                    else{
                        jeu.joueur = 1;
                    }

                    aligne4(jeu.grille, &jeu); // cherche un puissance 4 et renvoi le joueur gagnant

                    // verifie s'il y a egalite

                    if((jeu.mode != 3 && jeu.tour == 42) || (jeu.mode == 3 && jeu.tour == 72)){
                        jeu.fin = -1;
                    }
                }

            }

            fenetre->fin = 1;

            while(jeu.rejouerPartie == 0 && jeu.retourAccueil == 0){// si la fin n'a pas ete choisie dans le menu
                //afficheFin(1, jeu.fin, jeu.joueur, jeu.mode, jeu.tour, jeu.rejouerPartie, jeu.retourAcceuil, jeu.hardcore, jeu.joueurCommence, jeu.grille, images, pWindow, pRenderer, fDebug, fSauvegarde);// affichage de la fin
                affichage(&images, &jeu, fenetre, fDebug);

                evenement(&images, &jeu, fenetre, fDebug);
            }

        }while(jeu.rejouerPartie);

    }// jeux
}
