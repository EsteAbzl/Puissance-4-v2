/*
Corp de la gestion de la fenetre.
*/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "debug.h"

#include "video.h"
#include "image.h"

#include "jeu.h"
#include "grille.h"

#include "event.h"



// fenetre

void res_InfoFenetre(InfoFenetre* fenetre){
    fenetre->pWindow = NULL;

    fenetre->pRenderer = NULL;

    fenetre->w = 0;
    fenetre->h = 0;

    fenetre->ecran = 0;
    fenetre->menu = 0;
    fenetre->parametre = 0;
    fenetre->fin = 0;
}


// cree la fenetre et le renderer, fait lien avec le corp du jeu
void initFenetre(FILE* fDebug)
{
    int fenetreW = 1920, fenetreH = 1080;

    InfoFenetre fenetre;
    res_InfoFenetre(&fenetre);


    if(SDL_Init(SDL_INIT_VIDEO) != 0){                                                      // initialisation de la partie video de SDL
        fprintf(fDebug,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        exit(-2);
    }
                                                            // creation de la fenetre
    fenetre.pWindow = SDL_CreateWindow("Puissance4 2.0",SDL_WINDOWPOS_UNDEFINED,
                                                SDL_WINDOWPOS_UNDEFINED,
                                                fenetreW,
                                                fenetreH,
                                                SDL_WINDOW_SHOWN);

    if(fenetre.pWindow){
        fenetre.pRenderer = SDL_CreateRenderer(fenetre.pWindow, -1, SDL_RENDERER_ACCELERATED);  // pRenderer
        if(fenetre.pRenderer){
            // clean le renderer
            SDL_SetRenderDrawColor(fenetre.pRenderer, 255, 255, 255, 255);
            SDL_RenderClear(fenetre.pRenderer);
            SDL_RenderPresent(fenetre.pRenderer);
            debugWindow_Affiche();

            SDL_GetRendererOutputSize(fenetre.pRenderer, &fenetre.w, &fenetre.h);

            fonctionJeu(&fenetre, fDebug);  // corp du jeu
        }
        else{
            fprintf(fDebug,"Erreur d'initialisation de pRenderer (%s)",SDL_GetError());
            DEBUG("")
            exit(-4);
        }
    }
    else{
        fprintf(fDebug,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        DEBUG("")
        exit(-3);
    }
}

// desallocation
void fermetureFenetre(Image* images, InfoFenetre* fenetre, FILE* fDebug, FILE* fSauvegarde)
{
    res_Image(images, 1); // destuction de toutes les textures pour la fermeture du jeu

    fprintf(fDebug,"Rapport de fin TTF: %s \n", TTF_GetError); // exprime un message d'erreur

    debugWindow_Quit();


    fprintf(fDebug,"Rapport de fin SDL: %s \n", SDL_GetError()); // exprime un message d'erreur

    SDL_DestroyRenderer(fenetre->pRenderer); // desallocation du renderer

    SDL_DestroyWindow(fenetre->pWindow);     // desallocation de la fenetre

    SDL_Quit();                     // arret de SDL

    fclose(fDebug);                 // fermeture du fichier 'fDebug'

    fclose(fSauvegarde);            // fermeture et suppression du fichier 'fSauvegarde'

    exit(0);
}




void affichage(Image* images, InfoJeu* jeu, InfoFenetre* fenetre, FILE* fDebug){
    InfoImage* image = images->image;   // tableau stockant les infos des images
    SDL_Renderer* pRenderer = fenetre->pRenderer;

    SDL_GetRendererOutputSize(pRenderer, &fenetre->w, &fenetre->h);

    if(image[chargement].pTexture == NULL){
        chargeImage(&images->image[chargement], pRenderer, fDebug);
    }

    if(images->section_autre == 0){
        chargeSectionImage(S_AUTRE, images, pRenderer, fDebug);
    }


    if(fenetre->ecran == LENCEMENT || fenetre->ecran == ACCUEIL_MENU || fenetre->ecran == ACCUEIL_BOT){
        if(images->section_acceuil == 0){
            chargeSectionImage(S_ACCUEIL, images, pRenderer, fDebug);
        }

        afficheImage(image[accueil_bg], 0, 0, NON, pRenderer, fDebug);
    }

    switch(fenetre->ecran){
        case LENCEMENT:{
                // animation de clignotement
                if((SDL_GetTicks() - image[accueil_APPUYEZ_SUR_UNE_TOUCHE_POUR_JOUER].temps) > 700){
                    if(image[accueil_APPUYEZ_SUR_UNE_TOUCHE_POUR_JOUER].info){ // ici info sert a savoir si l'image est visible
                        image[accueil_APPUYEZ_SUR_UNE_TOUCHE_POUR_JOUER].info = 0;
                    }
                    else{
                        image[accueil_APPUYEZ_SUR_UNE_TOUCHE_POUR_JOUER].info = 1;
                    }

                    image[accueil_APPUYEZ_SUR_UNE_TOUCHE_POUR_JOUER].temps = SDL_GetTicks();
                }

                if(image[accueil_APPUYEZ_SUR_UNE_TOUCHE_POUR_JOUER].info){
                    afficheImage(image[accueil_APPUYEZ_SUR_UNE_TOUCHE_POUR_JOUER], fenetre->w/2, fenetre->h*3/4, OUI, pRenderer, fDebug);
                }
            }
            break;

        case ACCUEIL_MENU:{
                afficheImage(image[hardcore_inactif + jeu->hardcore.mode], fenetre->w*7/8, fenetre->h*3/8, OUI, pRenderer, fDebug); //  les différent mode de 'hardcore' son a la suite dans la liste des images

                afficheImage(image[accueil_mode1], fenetre->w*5/16, fenetre->h/2, OUI, pRenderer, fDebug);
                afficheImage(image[accueil_mode2], fenetre->w*11/16, fenetre->h/2, OUI, pRenderer, fDebug);
                afficheImage(image[accueil_mode3], fenetre->w*5/16, fenetre->h*3/4, OUI, pRenderer, fDebug);
                afficheImage(image[accueil_mode4], fenetre->w*11/16, fenetre->h*3/4, OUI, pRenderer, fDebug);
            }
            break;

        case ACCUEIL_BOT:{
                afficheImage(image[accueil_retour], fenetre->w/16, fenetre->h*7/8, OUI, pRenderer, fDebug);
                afficheImage(image[accueil_valide], fenetre->w*29/32, fenetre->h/2, OUI, pRenderer, fDebug);

                if(jeu->mode == 2){
                    place_acceuil_bot(0, fenetre->w/2, jeu->bot1.difficulte, images, fenetre, fDebug);
                }
                else if(jeu->mode == 4){
                    place_acceuil_bot(1, fenetre->w*5/16, jeu->bot1.difficulte, images, fenetre, fDebug);
                    place_acceuil_bot(0, fenetre->w*11/16, jeu->bot2.difficulte, images, fenetre, fDebug);
                }

                if((SDL_GetTicks() - image[accueil_SELECTIONNEZ_UNE_DIFFICULTEE].temps) / 1000 < 0.5){
                    afficheImage(image[accueil_SELECTIONNEZ_UNE_DIFFICULTEE], fenetre->w/2, fenetre->h*15/64, OUI, pRenderer, fDebug);
                }
                else if((SDL_GetTicks() - image[accueil_SELECTIONNEZ_UNE_DIFFICULTEE].temps) / 1000 < 0.7){
                    afficheImage(image[accueil_SELECTIONNEZ_UNE_DIFFICULTEE_efface], fenetre->w/2, fenetre->h*15/64, OUI, pRenderer, fDebug);
                }
            }
            break;

        case JEU:{
                if(images->section_jeu == 0){
                    chargeSectionImage(S_JEU, images, fenetre->pRenderer, fDebug);
                }

                afficheImage(image[jeu_bg], 0, 0, NON, pRenderer, fDebug);

                /* positionneJoueur(images, jeu); */

                int debutColonne_x = 0;
                if(jeu->mode == 3)
                    debutColonne_x = fenetre->w/2 - 450;
                else
                    debutColonne_x = fenetre->w/2 - 350;

                int colonneSurvole = 0;
                if(jeu->m_y >= fenetre->h/2 - 400 && ((jeu->mode != 3 && jeu->m_y <= fenetre->h/2 + 300) || (jeu->mode == 3 && jeu->m_y <= fenetre->h/2 + 500)))
                    colonneSurvole = ((jeu->m_x - debutColonne_x) / 100);
                else
                    colonneSurvole = -1;

                int colonneActive = 0;
                if(colonneSurvole >= 0 && (jeu->mode != 3 && colonneSurvole <= 7) || (jeu->mode == 3 && colonneSurvole <= 9))
                    colonneActive = colonneSurvole;
                else
                    colonneActive = -1;

                infosGrille(jeu);
                if(jeu->infoGrille[colonneActive] && colonneActive != -1 && (fenetre->menu == 0 && fenetre->fin == 0)){
                    afficheImage(image[jeu_Colonne_Desactive + jeu->infoGrille[colonneActive]], debutColonne_x + (colonneActive * 100), fenetre->h/2 - 400, NON, pRenderer, fDebug);
                    // on affiche un pion au dessus de la colonne
                    afficheImage(image[pion1 + (jeu->joueur - 1)], debutColonne_x + 50 + (colonneActive * 100), fenetre->h/2 - 350, OUI, pRenderer, fDebug);
                }

                positionnePion(images, jeu, fenetre, fDebug);

                positionneHardcore(images, jeu, fenetre, fDebug);


                if(jeu->mode == 3){
                    afficheImage(image[grille9x8], fenetre->w/2, fenetre->h/2 + 100, OUI, pRenderer, fDebug);
                }
                else{
                    afficheImage(image[grille7x6], fenetre->w/2, fenetre->h/2, OUI, pRenderer, fDebug);
                }

                if(jeu->tour){
                    afficheImage(image[jeu_retour], fenetre->w/2 - 650, fenetre->h/2, OUI, pRenderer, fDebug);
                }

                if(fenetre->menu == 0 && fenetre->fin == 0){
                    afficheImage(image[menu_logo], 50, 50, OUI, pRenderer, fDebug);
                }
            }
            break;
    }

    if(fenetre->menu){
        //animationGrillage(images, fenetre, fDebug);

        afficheImage(image[menu_Grillage], 0, 0, NON, pRenderer, fDebug);

        afficheImage(image[menu_Reprendre], fenetre->w/2, fenetre->h*2/16, OUI, pRenderer, fDebug);
        afficheImage(image[menu_Rejouer], fenetre->w/2, fenetre->h*6/16, OUI, pRenderer, fDebug);
        afficheImage(image[menu_RetourAccueil], fenetre->w/2, fenetre->h*10/16, OUI, pRenderer, fDebug);
        afficheImage(image[menu_Quitter], fenetre->w/2, fenetre->h*14/16, OUI, pRenderer, fDebug);
    }

    if(fenetre->fin){
        //animationFin(images, jeu, fenetre, fDebug);

        //animationGrillage(images, fenetre, fDebug);

        afficheImage(image[menu_Grillage], 0, 0, NON, pRenderer, fDebug);

        afficheImage(image[menu_Rejouer], fenetre->w/2, fenetre->h*3/16, OUI, pRenderer, fDebug);
        afficheImage(image[menu_RetourAccueil], fenetre->w/2, fenetre->h*8/16, OUI, pRenderer, fDebug);
        afficheImage(image[menu_Quitter], fenetre->w/2, fenetre->h*13/16, OUI, pRenderer, fDebug);
    }

    if(fenetre->parametre){ // affiche les parametres
        afficheImage(image[parametre_bg], fenetre->w/2, fenetre->h*9/16, OUI, pRenderer, fDebug);
        afficheImage(image[joueurCommence_bg], fenetre->w/2 - 360, fenetre->h*9/16, OUI, pRenderer, fDebug);

        for(int i = 0; i < 3; i++){
            afficheImage(image[joueur1Commence + i], fenetre->w/2 - 360, fenetre->h*9/16 - 98 + (i*125), OUI, pRenderer, fDebug);
        }
        afficheImage(image[joueur1Commence_actif + (jeu->joueurCommence - 1)], fenetre->w/2 - 360, fenetre->h*9/16 - 98 + ((jeu->joueurCommence-1)*125), OUI, pRenderer, fDebug);
    }


    if(fenetre->ecran == ACCUEIL_MENU || fenetre->ecran == ACCUEIL_BOT || fenetre->menu || fenetre->fin){
        afficheImage(image[parametre_logo], 50, 50, OUI, pRenderer, fDebug);
    }
    afficheImage(image[croix], fenetre->w - 50, 0, NON, pRenderer, fDebug);

    SDL_Delay(17);
    fps++;

    if((SDL_GetTicks() - T_fps) > 1000){
        sprintf(debugTexte[1].txt,"fps: %d", fps);
        T_fps = SDL_GetTicks();
        fps = 0;
    }


    SDL_RenderPresent(pRenderer);
    debugWindow_Affiche();

}


void place_acceuil_bot(int jaune, int x, int difficulte, Image* images, InfoFenetre* fenetre, FILE* fDebug){
    if(jaune){
        afficheImage(images->image[accueil_botJaune], x, fenetre->h*10/16, OUI, fenetre->pRenderer, fDebug);
    }
    else{
        afficheImage(images->image[accueil_botRouge], x, fenetre->h*10/16, OUI, fenetre->pRenderer, fDebug);
    }
    afficheImage(images->image[accueil_botFacile_inactif], x, fenetre->h*7/16, OUI, fenetre->pRenderer, fDebug);
    afficheImage(images->image[accueil_botNormal_inactif], x, fenetre->h*10/16, OUI, fenetre->pRenderer, fDebug);
    afficheImage(images->image[accueil_botDifficile_inactif], x, fenetre->h*13/16, OUI, fenetre->pRenderer, fDebug);

    afficheImage(images->image[accueil_botFacile_actif + difficulte - 1], x, fenetre->h*(7+((difficulte-1)*3))/16, OUI, fenetre->pRenderer, fDebug);
}

void positionnePion(Image* images, InfoJeu* jeu, InfoFenetre* fenetre, FILE* fDebug){

    for(int colonne = 0; colonne < 9; colonne++){
        for(int ligne = 0; ligne < 8; ligne++){
            if(jeu->grille[colonne][ligne].joueur){
                afficheImage(images->image[jeu->grille[colonne][ligne].pion.image], jeu->grille[colonne][ligne].pion.x, jeu->grille[colonne][ligne].pion.y, OUI, fenetre->pRenderer, fDebug);
            }
        }
    }
}

void positionneHardcore(Image* images, InfoJeu* jeu, InfoFenetre* fenetre, FILE* fDebug){

    Hardcore hardcore = jeu->hardcore;

    if(hardcore.mode){
    afficheImage(images->image[hardcore_bg], fenetre->w/2 + 700, fenetre->h/2, OUI, fenetre->pRenderer, fDebug);

    if(hardcore.tempsRestant >= 10){
        afficheImage(images->image[nb_1], fenetre->w/2 + 625, fenetre->h/2 - 400, OUI, fenetre->pRenderer, fDebug);
        afficheImage(images->image[nb_0 + (hardcore.tempsRestant - 10)], fenetre->w/2 + 775, fenetre->h/2 - 400, OUI, fenetre->pRenderer, fDebug);
    }
    else{
        afficheImage(images->image[nb_0 + hardcore.tempsRestant], fenetre->w/2 + 700, fenetre->h/2 - 400, OUI, fenetre->pRenderer, fDebug);
    }

    switch(hardcore.mode){
        case 1:{
                for(int i = 0; i < hardcore.tempsRestant; i++){
                    // changement de couleur selon te temps restant
                    if(hardcore.tempsRestant >= 5){
                        afficheImage(images->image[hardcore_Temps_Vert], fenetre->w/2 + 700, fenetre->h/2 + 300 - (( i + 1) * (600 / 11)), OUI, fenetre->pRenderer, fDebug);
                    }
                    else if(hardcore.tempsRestant >= 3){
                        afficheImage(images->image[hardcore_Temps_Orange], fenetre->w/2 + 700, fenetre->h/2 + 300 - (( i + 1) * (600 / 11)), OUI, fenetre->pRenderer, fDebug);
                    }
                    else{
                        afficheImage(images->image[hardcore_Temps_Rouge], fenetre->w/2 + 700, fenetre->h/2 + 300 - (( i + 1) * (600 / 11)), OUI, fenetre->pRenderer, fDebug);
                    }
                }
            }
            break;

        case 2:{
                for(int i = 0; i < hardcore.tempsRestant; i++){
                    // changement de couleur selon te temps restant
                    if(hardcore.tempsRestant >= 3){
                        afficheImage(images->image[hardcore_Temps_Vert], fenetre->w/2 + 700, fenetre->h/2 + 300 - (( i + 1) * (600 / 4)), OUI, fenetre->pRenderer, fDebug);
                    }
                    else if(hardcore.tempsRestant >= 2){
                        afficheImage(images->image[hardcore_Temps_Orange], fenetre->w/2 + 700, fenetre->h/2 + 300 - (( i + 1) * (600 / 4)), OUI, fenetre->pRenderer, fDebug);
                    }
                    else{
                        afficheImage(images->image[hardcore_Temps_Rouge], fenetre->w/2 + 700, fenetre->h/2 + 300 - (( i + 1) * (600 / 4)), OUI, fenetre->pRenderer, fDebug);
                    }
                }
            }
            break;
    }
}
}


// groupe d'image

/*

void afficheFin(int utilisation, int fin, int joueur, int mode, int tour, int *rejouerPartie, int *retourAccueil, Hardcore* hardcore, int* joueurCommence, caseGrille grille[9][9], Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde)// ecrans de fin
{


	   //la variable utilisation a pour fonctions:
	   //si elle est positive, elle affiche met du delai
	   //si elle est neutre, elle ne met pas de delai

// positionne les joueurs dans l'ordre de jeu
void positionneJoueur(int mode, int joueur, Images* Images, SDL_Renderer* pRenderer, FILE* fDebug)
{

	   switch(mode)
	   {
	   	   case 1:
	   	       if(joueur == 1)
	   	       {
	   	           afficheJoueur(1, 1, Images, pRenderer, fDebug);
	   	           afficheJoueur(2, 2, Images, pRenderer, fDebug);
	   	       }
	   	       else
	   	       {
	   	           afficheJoueur(2, 1, Images, pRenderer, fDebug);
	   	           afficheJoueur(1, 2, Images, pRenderer, fDebug);
	   	       }

	   	   break;

	   	   case 2:
	   	       if(joueur == 1)
	   	       {
	   	           afficheJoueur(1, 1, Images, pRenderer, fDebug);
	   	           afficheJoueur(5, 2, Images, pRenderer, fDebug);
	   	       }
	   	       else
	   	       {
	   	           afficheJoueur(5, 1, Images, pRenderer, fDebug);
	   	           afficheJoueur(1, 2, Images, pRenderer, fDebug);
	   	       }

	   	   break;

	   	   case 3:
	   	       if(joueur == 1)
	   	       {
	   	           afficheJoueur(1, 1, Images, pRenderer, fDebug);
	   	           afficheJoueur(2, 2, Images, pRenderer, fDebug);
	   	           afficheJoueur(3, 3, Images, pRenderer, fDebug);
	   	       }
	   	       else if(joueur == 2)
	   	       {
	   	           afficheJoueur(2, 1, Images, pRenderer, fDebug);
	   	           afficheJoueur(3, 2, Images, pRenderer, fDebug);
	   	           afficheJoueur(1, 3, Images, pRenderer, fDebug);
	   	       }
	   	       else
	   	       {
	   	           afficheJoueur(3, 1, Images, pRenderer, fDebug);
	   	           afficheJoueur(1, 2, Images, pRenderer, fDebug);
	   	           afficheJoueur(2, 3, Images, pRenderer, fDebug);
	   	       }

	   	   break;

	   	   case 4:
	   	       if(joueur == 1)
	   	       {
	   	           afficheJoueur(4, 1, Images, pRenderer, fDebug);
	   	           afficheJoueur(5, 2, Images, pRenderer, fDebug);
	   	       }
	   	       else
	   	       {
	   	           afficheJoueur(5, 1, Images, pRenderer, fDebug);
	   	           afficheJoueur(4, 2, Images, pRenderer, fDebug);
	   	       }
	   	   break;
	   }
}

// affiche les joueurs
void afficheJoueur(int type, int position, Images* Images, SDL_Renderer* pRenderer, FILE* fDebug)
{

//type:
    //1 = joueur 1
	//2 = joueur 2
	//3 = joueur 3
	//4 = bot 1
	//5 = bot 2


    // taille du renderer
    int x = 0, y = 0;
    SDL_GetRendererOutputSize(pRenderer, &x, &y);

    SDL_Rect dest = {x/2 - 750, y/16 + position*100, 0, 0};


    if(position == 1)// le joueur qui doit jouer est mis en valeur
    {
        switch(type)
        {
            case 1:
                afficheImage_Centre(Images->Jeu.Joueur.joueur1_actif, &dest, pRenderer, fDebug);
            break;

            case 2:
                afficheImage_Centre(Images->Jeu.Joueur.joueur2_actif, &dest, pRenderer, fDebug);
            break;

            case 3:
                afficheImage_Centre(Images->Jeu.Joueur.joueur3_actif, &dest, pRenderer, fDebug);
            break;

            case 4:
                afficheImage_Centre(Images->Jeu.Joueur.bot1_actif, &dest, pRenderer, fDebug);
            break;

            case 5:
                afficheImage_Centre(Images->Jeu.Joueur.bot2_actif, &dest, pRenderer, fDebug);
            break;

        }
    }
    else
    {
        switch(type)
        {
            case 1:
                afficheImage_Centre(Images->Jeu.Joueur.joueur1, &dest, pRenderer, fDebug);
            break;

            case 2:
                afficheImage_Centre(Images->Jeu.Joueur.joueur2, &dest, pRenderer, fDebug);
            break;

            case 3:
                afficheImage_Centre(Images->Jeu.Joueur.joueur3, &dest, pRenderer, fDebug);
            break;

            case 4:
                afficheImage_Centre(Images->Jeu.Joueur.bot1, &dest, pRenderer, fDebug);
            break;

            case 5:
                afficheImage_Centre(Images->Jeu.Joueur.bot2, &dest, pRenderer, fDebug);
            break;

        }
    }
}

// affiche des nombres
void nombre(int nombre, SDL_Rect* dest, Images* Images, SDL_Renderer* pRenderer, FILE* fDebug)
{
    switch(nombre)
    {
        case 0:
            afficheImage_Centre(Images->Nombres.nb_0, dest, pRenderer, fDebug);
        break;

        case 1:
            afficheImage_Centre(Images->Nombres.nb_1, dest, pRenderer, fDebug);
        break;

        case 2:
            afficheImage_Centre(Images->Nombres.nb_2, dest, pRenderer, fDebug);
        break;

        case 3:
            afficheImage_Centre(Images->Nombres.nb_3, dest, pRenderer, fDebug);
        break;

        case 4:
            afficheImage_Centre(Images->Nombres.nb_4, dest, pRenderer, fDebug);
        break;

        case 5:
            afficheImage_Centre(Images->Nombres.nb_5, dest, pRenderer, fDebug);
        break;

        case 6:
            afficheImage_Centre(Images->Nombres.nb_6, dest, pRenderer, fDebug);
        break;

        case 7:
            afficheImage_Centre(Images->Nombres.nb_7, dest, pRenderer, fDebug);
        break;

        case 8:
            afficheImage_Centre(Images->Nombres.nb_8, dest, pRenderer, fDebug);
        break;

        case 9:
            afficheImage_Centre(Images->Nombres.nb_9, dest, pRenderer, fDebug);
        break;

    }
}

*/

// animation

/*
// anime le grillage du menu qui tombe
void animationGrillage(int utilisation, int fin, int mode, int joueur, int tour, Hardcore* hardcore, caseGrille grille[9][9], Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde)
{

        //la variable utilisation a 2 fonctions:
        //si elle est positive, elle affiche la grille en mode fin
        //si son absolu est égal a 2, elle affiche la grille sans animation



        //ordre d'affichage:
        //-affiche (background, pion, grille,...)
        //-hardcore
        //-grillage


    // taille du renderer
    int x = 0, y = 0;
    SDL_GetRendererOutputSize(pRenderer, &x, &y);

    SDL_Rect dest;

    for(int nombreLigne = 1; nombreLigne <= (y/16); nombreLigne += 6)// nombre de ligne ( /2 car l'image d'une ligne fait 2pxls)
    {


        if(utilisation > 0)// si c'est la fin
            afficheFin(0, fin, joueur, mode, NULL, NULL, NULL, NULL, NULL, grille, Images, pWindow, pRenderer, fDebug, fSauvegarde);
        else
        {
            affiche(0, mode, joueur, tour, -1, grille, Images, pRenderer, fDebug);

            if(mode!=4)
                afficheHardcore(hardcore, Images, pRenderer, fDebug);
        }

        changeDest(&dest, 75, 75);
        afficheImage_Centre(Images->Menu.menu_logo, &dest, pRenderer, fDebug);// logo du menu


        // affichage du la grillage
        for(int ligne = 0, i = 8; ligne < nombreLigne; ligne++, i += 16)
        {
            changeDest(&dest, x/2, i);

            if((nombreLigne - 1) % 12)
            {
                if((i+8) % 32)
                    afficheImage_Centre(Images->Menu.Grillage.menu_Grillage1, &dest, pRenderer, fDebug);
                else
                    afficheImage_Centre(Images->Menu.Grillage.menu_Grillage2, &dest, pRenderer, fDebug);
            }
            else
            {
                if((i+8) % 32)
                    afficheImage_Centre(Images->Menu.Grillage.menu_Grillage2, &dest, pRenderer, fDebug);
                else
                    afficheImage_Centre(Images->Menu.Grillage.menu_Grillage1, &dest, pRenderer, fDebug);
            }

        }

        if(nombreLigne + 1 <= (y/16))
        {
            changeDest(&dest, x/2, (nombreLigne) * 16);
            afficheImage_Centre(Images->Menu.Grillage.menu_BordureGrillage, &dest, pRenderer, fDebug);// se situe en bas du grillage et permet de rajouter du style
        }


        changeDest(&dest, x-50, 0);
        afficheImage(Images->Autre.croix, &dest, pRenderer, fDebug);


        SDL_RenderPresent(pRenderer);
        debugWindow_Affiche();

        SDL_Delay(17); // (= 0.017 s)

    }

    SDL_RenderPresent(pRenderer);
    debugWindow_Affiche();

}


// anime les pions qui tombent
void animationPion(int colonne, int joueur, int mode, int tour,int *rejouerPartie, int *retourAccueil, int* joueurCommence, Hardcore* hardcore, caseGrille grille[9][9], Images* Images, SDL_Window* pWindow, SDL_Renderer* pRenderer, FILE* fDebug, FILE* fSauvegarde)
{

    // taille du renderer
    int x = 0, y = 0;
    SDL_GetRendererOutputSize(pRenderer, &x, &y);

    SDL_Rect dest;


    int infoGrille[9] = {0};// permet de connaitre le nombre de pions restant dans chaques colonne
    infosGrille(mode, infoGrille, grille);

    pion pion = {mode != 3? (x/2 - 300) + (colonne * 100) : (x/2 - 400) + (colonne * 100), mode != 3? y/2 - 350 : y/2 - 350, 0};// info du pion: x, y, velociteY


    int distance = infoGrille[colonne]*100;// distance que le pion doit encore parcourir

    while(distance != 0 || pion.velociteY != 0)// animation
    {

        // mouvement
        distance += pion.velociteY;
        pion.y -= pion.velociteY;

        // depasse la case
        if(distance < 0)
        {
            distance = 0;
            pion.y = mode != 3? y/2 - 350 : y/2 - 350;
            pion.y += infoGrille[colonne]*100;
        }


        {//affichage du reste

            affiche(1, mode, joueur, tour, -1, grille, Images, pRenderer, fDebug);

            changeDest(&dest, x-50, 0);
            afficheImage(Images->Autre.croix, &dest, pRenderer, fDebug);

            changeDest(&dest, 75, 75);
            afficheImage_Centre(Images->Menu.menu_logo, &dest, pRenderer, fDebug);// logo du menu

            {// affichage du pion
                changeDest(&dest, pion.x, pion.y);

                switch(joueur)
                {
                    case 1:
                        afficheImage_Centre(Images->Jeu.Pions.pion1_joue, &dest, pRenderer, fDebug);
                    break;

                    case 2:
                        afficheImage_Centre(Images->Jeu.Pions.pion2_joue, &dest, pRenderer, fDebug);
                    break;

                    case 3:
                        afficheImage_Centre(Images->Jeu.Pions.pion3_joue, &dest, pRenderer, fDebug);
                    break;
                }
            }

            if(mode!=3)
            {
                changeDest(&dest, x/2, y/2);
                afficheImage_Centre(Images->Jeu.Grille.grille7x6, &dest, pRenderer, fDebug);
            }
            else
            {
                changeDest(&dest, x/2, y/2 + 100);
                afficheImage_Centre(Images->Jeu.Grille.grille9x8, &dest, pRenderer, fDebug);
            }


            if(mode!=4)
                afficheHardcore(hardcore, Images, pRenderer, fDebug);

        }

        SDL_RenderPresent(pRenderer);
        debugWindow_Affiche();

        if(0 > pion.velociteY && pion.velociteY > -25)// le pion tombe
            pion.velociteY -= 3;// gagne 3 px de velocite par frames
        else if(pion.velociteY > 0)// le pion monte
            pion.velociteY -= 5;// pert 10 px de velocite par frames

        if(abs(distance) < 25 && ( (-15 <= pion.velociteY) && (pion.velociteY <= 0) ))// le pion est presque a l'arret et a sa case
        {
            // on arrete le pion
            distance = 0;
            pion.y = mode != 3? y/2 - 350 : y/2 - 350;
            pion.y += infoGrille[colonne]*100;
            pion.velociteY = 0;
        }
        else// le pion est a l'arret mais pas a sa case
        {
            pion.velociteY -= 2;
        }

        if(distance <= 0)// le pion atteint sa case
            pion.velociteY = abs(pion.velociteY)/2;// on inverse sa vitesse, ce qui le fait rebondir

        // event qui permet au joueur d'effectuer des actions lors d'une annimation ou autre
        eventSpectateur(rejouerPartie, retourAccueil, hardcore, mode, joueur, tour, joueurCommence, grille, Images, pWindow, pRenderer, fDebug, fSauvegarde);

        SDL_Delay(17);
    }

}

*/
