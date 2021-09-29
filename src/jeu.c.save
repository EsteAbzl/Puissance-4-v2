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

// corp du jeu
void jeu(SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde)
{

    // chargement des images

    Images Images; // voir image.h

    resetImages(&Images);

    chargeSectionImage(-1, &Images, pRenderer, fDebug);

    SDL_Rect dest; // destination d'une image

    changeDest(&dest, 0, 0);
    afficheImage(Images.Autre.CHARGEMENT, &dest, pRenderer, fDebug);

    SDL_RenderPresent(pRenderer);

    chargeSectionImage(1, &Images, pRenderer, fDebug);

    // ecran d'accueil
    accueil(0, NULL, NULL, NULL, NULL, NULL, &Images, pWindow, pRenderer, fDebug, fSauvegarde);

    caseGrille grille[9][9]; // grille de jeu (structure dans jeu.h)

    while(1) // jeu
    {

        // taille du renderer
        int x = 0, y = 0;
        SDL_GetRendererOutputSize(pRenderer, &x, &y);

        chargeSectionImage(1, &Images, pRenderer, fDebug);

    	   int mode = 0;    /*
    	                    1 : Joueur contre Joueur
    	                    2 : Joueur contre Ordinateur
    	                    3 : Joueur contre Joueur contre Joueur
    	                    4 : Ordinateur contre Ordinateur
    	                    */

    	   int difficulteBot1 = 0, difficulteBot2 = 0;    /*
    	                 	                 	              1 : facile
    	       	                 	                 	      2 : normal
    	       	                 	                 	      3 : difficile
    	       	                 	                 	      */

    	   Hardcore hardcore;// structure dans jeu.h
    	   hardcore.mode = 0;

    	   int tour = 0;// incremente a chaques tours, permet de detecter une egalite
    	   int retour = 0;// permet de revenir au tour precedent
    	   int fin = 0;    /*
    	                   -1 : egalite
    	                   0 : pas termine
    	                   1 : victoire du joueur 1
    	                   2 : victoire du joueur 2
    	                   3 : victoire du joueur 3
    	                   */

    	   int joueurCommence = 1;
    	   int joueur = 0;// joueur actuel
    	   int colonne = -1;// colonne jouee
    	   int rejouerPartie = 0, retourAccueil = 0;

    	   // ecran de choix des modes
        accueil(1, &mode, &joueurCommence, &difficulteBot1, &difficulteBot2, &hardcore, &Images, pWindow, pRenderer, fDebug, fSauvegarde);

        changeDest(&dest, 0, 0);
        afficheImage(Images.Autre.CHARGEMENT, &dest, pRenderer, fDebug);

        SDL_RenderPresent(pRenderer);

        do// une partie
        {


            chargeSectionImage(2, &Images, pRenderer, fDebug);

            rejouerPartie = 0;
            retourAccueil = 0;

            fin = 0;
            tour = 0;

            if(mode != 3 && joueurCommence == 3)
                joueurCommence = 1;

            joueur = joueurCommence;

            resetGrille(grille);// reset la grille

            strat stratBot1; // voir jeu.h
                stratBot1.colonne = 0;
                stratBot1.ligne = 0;
                stratBot1.type = 0;
            strat stratBot2;
                stratBot2.colonne = 0;
                stratBot2.ligne = 0;
                stratBot2.type = 0;


            do// un tour
            {
                sprintf(debugTexte[0].txt,"=--=--= GENERAL =--=--=");

                sprintf(debugTexte[1].txt,"mode séléctionné: %d", mode);

                sprintf(debugTexte[2].txt,"tour actuel: %d", tour);

            	   // temps limite selon le mode hardcore
            	   if(hardcore.mode == 1)
            	       hardcore.tempsRestant = 10;
            	   else if(hardcore.mode == 2)
            	       hardcore.tempsRestant = 3;


                    if(retour == 0) // permet au retour de fonctionner. si retour = 1 alors on ne sauvegarde pas la grille qui vien d'etre jouer et on charge la précédente.
                        sauvegardeGrille(tour, joueur, grille, fDebug, fSauvegarde); // sauvegarde de la grille actuelle

                    retour = 0; // reset de retour


                    // affichage du jeu
                    affiche(NULL, mode, joueur, tour, -1, grille, &Images, pRenderer, fDebug); // affichage du jeu

                    afficheHardcore(&hardcore, &Images, pRenderer, fDebug); // affiche du mode hardcore

                    changeDest(&dest, x - 50, 0);
                    afficheImage(Images.Autre.croix, &dest, pRenderer, fDebug);

                    SDL_RenderPresent(pRenderer);




                    do// selection de la colonne a jouer
                    {
            	   	   // le joueur joue
                        if(mode == 1 || (mode == 2 && joueur == 1) || mode == 3)
                        {
                            jouerColonne(mode, &joueurCommence, tour, joueur, grille, &hardcore, &colonne, &retour, &rejouerPartie, &retourAccueil, &Images, pWindow, pRenderer, fDebug, fSauvegarde);

                        }
                        else// le bot joue
                        {
                            if(mode == 2 && joueur == 2)
                            {
                                colonne = bot(2, difficulteBot1, grille, &stratBot1);

                            }

                            else if(mode == 4 && joueur == 1)
                            {
                                colonne = bot(1, difficulteBot1, grille, &stratBot1);

                            }
                            else if(mode == 4 && joueur == 2)
                            {
                                colonne = bot(2, difficulteBot2, grille, &stratBot2);

                            }

                            sprintf(debugTexte[4].txt, "=--=--= Bot =--=--=");

                            sprintf(debugTexte[5].txt, "strat choisie: bot 1: c: %d l: %d type: %d", stratBot1.colonne, stratBot1.ligne, stratBot1.type);

                            for(int temps = 0; (temps < 1000) && (retour == 0) && (rejouerPartie == 0) && (retourAccueil == 0); temps += 17)// rajoute du realisme en faisant attendre 1 seconde
                                {
                                    if(temps < 500) // affiche le pion en haut de la grille
                                        affiche(0, mode, joueur, tour, -1, grille, &Images, pRenderer, fDebug);
                                    else // fait tomber le pion
                                        affiche(0, mode, joueur, tour, colonne, grille, &Images, pRenderer, fDebug);

                                    changeDest(&dest, x-50, 0);
                                    afficheImage(Images.Autre.croix, &dest, pRenderer, fDebug);

                                    changeDest(&dest, 75, 75);
                                    afficheImage_Centre(Images.Menu.menu_logo, &dest, pRenderer, fDebug);// logo du menu

                                    SDL_RenderPresent(pRenderer);

                                    SDL_Delay(17);

                                    eventBot(&rejouerPartie, &retourAccueil, &hardcore, mode, joueur, tour, &retour, &joueurCommence, grille, &Images, pWindow, pRenderer, fDebug, fSauvegarde);

                                }
                        }



                    }while((retour == 0) && (rejouerPartie == 0) && (retourAccueil == 0) && (placePion(joueur, colonne, mode, tour, &rejouerPartie, &retourAccueil, &joueurCommence, &hardcore, grille, &Images, pWindow, pRenderer, fDebug, fSauvegarde))/* verifie que le pion est joue*/);


            	   colonne = -1; // reset de colonne

            	   // changement de joueur
            	   if((mode != 3 && joueur == 1) || (mode == 3 && (joueur == 1 || joueur == 2)))
            	   {
            	   	   joueur++;
            	   }
            	   else
            	   {
            	   	   joueur = 1;
            	   }


            	   if(retour)
            	   {
            	   	   recupereGrille(&tour, &joueur, grille, &Images, pWindow, pRenderer, fDebug, fSauvegarde);// charge la grille du tour precedent
            	   }


            	   fin = aligne4(grille, mode); // cherche un puissance 4 et renvoi le joueur gagnant

                    tour++;

            	   // verifie s'il y a egalite
            	   if((mode != 3 && tour == 42) || (mode == 3 && tour == 72))
            	   {
            	   	   fin = -1;
            	   }

            }while(fin == 0 && rejouerPartie == 0 && retourAccueil == 0); // tour


            if(rejouerPartie == 0 && retourAccueil == 0)// si la fin n'a pas ete choisie dans le menu
            {
                afficheFin(1, fin, joueur, mode, tour, &rejouerPartie, &retourAccueil, &hardcore, &joueurCommence, grille, &Images, pWindow, pRenderer, fDebug, fSauvegarde);// affichage de la fin

                if(rejouerPartie == 0 && retourAccueil == 0)// si la fin n'a pas ete choisie dans le menu
                {
                    finPartie(&rejouerPartie, &hardcore, fin, mode, joueur, &joueurCommence, grille, &Images, pWindow, pRenderer, fDebug, fSauvegarde);// menu de fin
                }
            }


            // clear du fichiers de sauvegarde
            fclose(fSauvegarde);
            remove("./data/sauvegarde.txt");

            if((fSauvegarde = fopen("./data/sauvegarde.txt","w+")) == NULL)
            {
                fprintf(fDebug, "ERREUR: impossible d'ouvrir le fichier 'fSauvegarde.txt'");
                exit(-1);
            }

        }while(rejouerPartie);// partie

        changeDest(&dest, 0, 0);
        afficheImage(Images.Autre.CHARGEMENT, &dest, pRenderer, fDebug);

        SDL_RenderPresent(pRenderer);


    }// jeux
}
