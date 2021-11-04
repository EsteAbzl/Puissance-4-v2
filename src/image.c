/*
Charge les images
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"


#include "image.h"

void Image_localisation(Image* images){
    sprintf(images->image[chargement].localisation, "./data/autre/CHARGEMENT.png");

    //AUTRE
    sprintf(images->image[croix].localisation, "./data/autre/croix.png");
    sprintf(images->image[nb_0].localisation, "./data/nombre/nb_0.png");
    sprintf(images->image[nb_1].localisation, "./data/nombre/nb_1.png");
    sprintf(images->image[nb_2].localisation, "./data/nombre/nb_2.png");
    sprintf(images->image[nb_3].localisation, "./data/nombre/nb_3.png");
    sprintf(images->image[nb_4].localisation, "./data/nombre/nb_4.png");
    sprintf(images->image[nb_5].localisation, "./data/nombre/nb_5.png");
    sprintf(images->image[nb_6].localisation, "./data/nombre/nb_6.png");
    sprintf(images->image[nb_7].localisation, "./data/nombre/nb_7.png");
    sprintf(images->image[nb_8].localisation, "./data/nombre/nb_8.png");
    sprintf(images->image[nb_9].localisation, "./data/nombre/nb_9.png");
    sprintf(images->image[parametre_logo].localisation, "./data/parametre/autre/parametre_logo.png");
    sprintf(images->image[parametre_bg].localisation, "./data/parametre/autre/parametre_bg.png");
    sprintf(images->image[joueurCommence_bg].localisation, "./data/parametre/joueurCommence/joueurCommence_bg.png");
    sprintf(images->image[joueur1Commence].localisation, "./data/parametre/joueurCommence/joueur1Commence.png");
    sprintf(images->image[joueur2Commence].localisation, "./data/parametre/joueurCommence/joueur2Commence.png");
    sprintf(images->image[joueur3Commence].localisation, "./data/parametre/joueurCommence/joueur3Commence.png");
    sprintf(images->image[joueur1Commence_actif].localisation, "./data/parametre/joueurCommence/joueur1Commence_actif.png");
    sprintf(images->image[joueur2Commence_actif].localisation, "./data/parametre/joueurCommence/joueur2Commence_actif.png");
    sprintf(images->image[joueur3Commence_actif].localisation, "./data/parametre/joueurCommence/joueur3Commence_actif.png");

    //ACCUEIL
    sprintf(images->image[accueil_bg].localisation, "./data/accueil/autre/accueil_bg.png");
    sprintf(images->image[accueil_retour].localisation, "./data/accueil/autre/accueil_retour.png");
    sprintf(images->image[accueil_valide].localisation, "./data/accueil/autre/accueil_valide.png");
    sprintf(images->image[accueil_APPUYEZ_SUR_UNE_TOUCHE_POUR_JOUER].localisation, "./data/accueil/autre/accueil_APPUYEZ_SUR_UNE_TOUCHE_POUR_JOUER.png");
    sprintf(images->image[hardcore_inactif].localisation, "./data/accueil/hardcore/hardcore_inactif.png");
    sprintf(images->image[hardcore_1].localisation, "./data/accueil/hardcore/hardcore_1.png");
    sprintf(images->image[hardcore_2].localisation, "./data/accueil/hardcore/hardcore_2.png");
    sprintf(images->image[accueil_mode1].localisation, "./data/accueil/mode/accueil_mode1.png");
    sprintf(images->image[accueil_mode2].localisation, "./data/accueil/mode/accueil_mode2.png");
    sprintf(images->image[accueil_mode3].localisation, "./data/accueil/mode/accueil_mode3.png");
    sprintf(images->image[accueil_mode4].localisation, "./data/accueil/mode/accueil_mode4.png");
    sprintf(images->image[accueil_SELECTIONNEZ_UNE_DIFFICULTEE].localisation, "./data/accueil/bot/SELECTIONNEZ_UNE_DIFFICULTEE.png");
    sprintf(images->image[accueil_SELECTIONNEZ_UNE_DIFFICULTEE_efface].localisation, "./data/accueil/bot/SELECTIONNEZ_UNE_DIFFICULTEE_efface.png");
    sprintf(images->image[accueil_botJaune].localisation, "./data/accueil/bot/accueil_botJaune.png");
    sprintf(images->image[accueil_botRouge].localisation, "./data/accueil/bot/accueil_botRouge.png");
    sprintf(images->image[accueil_bot_inactif].localisation, "./data/accueil/bot/accueil_bot_inactif.png");
    sprintf(images->image[accueil_botFacile_actif].localisation, "./data/accueil/bot/accueil_botFacile_actif.png");
    sprintf(images->image[accueil_botNormal_actif].localisation, "./data/accueil/bot/accueil_botNormal_actif.png");
    sprintf(images->image[accueil_botDifficile_actif].localisation, "./data/accueil/bot/accueil_botDifficile_actif.png");
    sprintf(images->image[accueil_botFacile_inactif].localisation, "./data/accueil/bot/accueil_botFacile_inactif.png");
    sprintf(images->image[accueil_botNormal_inactif].localisation, "./data/accueil/bot/accueil_botNormal_inactif.png");
    sprintf(images->image[accueil_botDifficile_inactif].localisation, "./data/accueil/bot/accueil_botDifficile_inactif.png");

    //JEU
    sprintf(images->image[menu_logo].localisation, "./data/menu/autre/menu_logo.png");
    sprintf(images->image[menu_Grillage].localisation, "./data/menu/grillage/menu_grillage.png");
    sprintf(images->image[menu_Grillage1].localisation, "./data/menu/grillage/menu_grillage1.png");
    sprintf(images->image[menu_Grillage2].localisation, "./data/menu/grillage/menu_grillage2.png");
    sprintf(images->image[menu_BordureGrillage].localisation, "./data/menu/grillage/menu_Borduregrillage.png");
    sprintf(images->image[menu_Reprendre].localisation, "./data/menu/bouton/menu_Reprendre.png");
    sprintf(images->image[menu_Rejouer].localisation, "./data/menu/bouton/menu_Rejouer.png");
    sprintf(images->image[menu_RetourAccueil].localisation, "./data/menu/bouton/menu_RetourAccueil.png");
    sprintf(images->image[menu_Quitter].localisation, "./data/menu/bouton/menu_Quitter.png");
    sprintf(images->image[jeu_bg].localisation, "./data/jeu/autre/jeu_bg.png");
    sprintf(images->image[jeu_retour].localisation, "./data/jeu/autre/jeu_retour.png");
    sprintf(images->image[joueur1].localisation, "./data/jeu/joueur/joueur1.png");
    sprintf(images->image[joueur2].localisation, "./data/jeu/joueur/joueur2.png");
    sprintf(images->image[joueur3].localisation, "./data/jeu/joueur/joueur3.png");
    sprintf(images->image[bot1].localisation, "./data/jeu/joueur/bot1.png");
    sprintf(images->image[bot2].localisation, "./data/jeu/joueur/bot2.png");
    sprintf(images->image[joueur1_actif].localisation, "./data/jeu/joueur/joueur1_actif.png");
    sprintf(images->image[joueur2_actif].localisation, "./data/jeu/joueur/joueur2_actif.png");
    sprintf(images->image[joueur3_actif].localisation, "./data/jeu/joueur/joueur3_actif.png");
    sprintf(images->image[bot1_actif].localisation, "./data/jeu/joueur/bot1_actif.png");
    sprintf(images->image[bot2_actif].localisation, "./data/jeu/joueur/bot2_actif.png");
    sprintf(images->image[grille7x6].localisation, "./data/jeu/grille/grille7x6.png");
    sprintf(images->image[grille9x8].localisation, "./data/jeu/grille/grille9x8.png");
    sprintf(images->image[hardcore_bg].localisation, "./data/jeu/hardcore/hardcore_bg.png");
    sprintf(images->image[hardcore_Temps_Vert].localisation, "./data/jeu/hardcore/hardcore_Temps_Vert.png");
    sprintf(images->image[hardcore_Temps_Orange].localisation, "./data/jeu/hardcore/hardcore_Temps_Orange.png");
    sprintf(images->image[hardcore_Temps_Rouge].localisation, "./data/jeu/hardcore/hardcore_Temps_Rouge.png");
    sprintf(images->image[jeu_Colonne_Desactive].localisation, "./data/jeu/colonne/jeu_colonne_Desactive.png");
    sprintf(images->image[jeu_ColonneTaille1_Active].localisation, "./data/jeu/colonne/jeu_ColonneTaille1_Active.png");
    sprintf(images->image[jeu_ColonneTaille2_Active].localisation, "./data/jeu/colonne/jeu_ColonneTaille2_Active.png");
    sprintf(images->image[jeu_ColonneTaille3_Active].localisation, "./data/jeu/colonne/jeu_ColonneTaille3_Active.png");
    sprintf(images->image[jeu_ColonneTaille4_Active].localisation, "./data/jeu/colonne/jeu_ColonneTaille4_Active.png");
    sprintf(images->image[jeu_ColonneTaille5_Active].localisation, "./data/jeu/colonne/jeu_ColonneTaille5_Active.png");
    sprintf(images->image[jeu_ColonneTaille6_Active].localisation, "./data/jeu/colonne/jeu_ColonneTaille6_Active.png");
    sprintf(images->image[jeu_ColonneTaille7_Active].localisation, "./data/jeu/colonne/jeu_ColonneTaille7_Active.png");
    sprintf(images->image[jeu_ColonneTaille8_Active].localisation, "./data/jeu/colonne/jeu_ColonneTaille8_Active.png");
    sprintf(images->image[pion1].localisation, "./data/jeu/pion/pion1.png");
    sprintf(images->image[pion2].localisation, "./data/jeu/pion/pion2.png");
    sprintf(images->image[pion3].localisation, "./data/jeu/pion/pion3.png");
    sprintf(images->image[pion1_joue].localisation, "./data/jeu/pion/pion1_joue.png");
    sprintf(images->image[pion2_joue].localisation, "./data/jeu/pion/pion2_joue.png");
    sprintf(images->image[pion3_joue].localisation, "./data/jeu/pion/pion3_joue.png");
    sprintf(images->image[pion1_gagne].localisation, "./data/jeu/pion/pion1_gagne.png");
    sprintf(images->image[pion2_gagne].localisation, "./data/jeu/pion/pion2_gagne.png");
    sprintf(images->image[pion3_gagne].localisation, "./data/jeu/pion/pion3_gagne.png");
    sprintf(images->image[fin_LE_JOUEUR].localisation, "./data/fin/texte/fin_LE_JOUEUR.png");
    sprintf(images->image[fin_GAGNE].localisation, "./data/fin/texte/fin_GAGNE.png");
    sprintf(images->image[fin_EGALITE].localisation, "./data/fin/texte/fin_EGALITE.png");
}

//reset la structure Images
void res_Image(Image* images, int decharge){
    images->section_autre = 0;
    images->section_acceuil = 0;
    images->section_jeu = 0;

    Image_localisation(images);

    for(int i = 0; i < NBR_IMAGE; i++){
        if(images->image[i].pTexture && decharge){
            SDL_DestroyTexture(images->image[i].pTexture);
        }
        images->image[i].pTexture = NULL;
        images->image[i].temps = 0;
        images->image[i].info = 0;
    }
}

void chargeSectionImage(Section section, Image* images, SDL_Renderer* pRenderer, FILE* fDebug){

    afficheImage(images->image[chargement], 0, 0, NON, pRenderer, fDebug);

    SDL_RenderPresent(pRenderer);

    switch(section){
        case S_AUTRE:
            if(images->section_autre == 0){
                images->section_autre = 1;

                for(int i = D_SECTION_AUTRE; i < F_SECTION_AUTRE + 1; i++){
                    chargeImage(&images->image[i], pRenderer, fDebug);
                }
            }
            break;

        case S_ACCUEIL:
            if(images->section_acceuil == 0){
                images->section_acceuil = 1;
                for(int i = D_SECTION_ACCUEIL; i < F_SECTION_ACCUEIL + 1; i++){
                    chargeImage(&images->image[i], pRenderer, fDebug);
                }
            }
            if(images->section_jeu == 1){
                images->section_jeu = 0;
                for(int i = D_SECTION_JEU; i < F_SECTION_JEU + 1; i++){
                    supprimeTexture(&images->image[i].pTexture);
                }
            }
            break;

        case S_JEU:
            if(images->section_jeu == 0){
                images->section_jeu = 1;
                for(int i = D_SECTION_JEU; i < F_SECTION_JEU + 1; i++){
                    chargeImage(&images->image[i], pRenderer, fDebug);
                }
            }
            if(images->section_acceuil == 1){
                images->section_acceuil = 0;
                for(int i = D_SECTION_ACCUEIL; i < F_SECTION_ACCUEIL + 1; i++){
                    supprimeTexture(&images->image[i].pTexture);
                }
            }
            break;
    }
}

// charge une image et renvoit un pointeur dessus
void chargeImage(InfoImage* image, SDL_Renderer* pRenderer, FILE* fDebug){

    //chargement de l'image
    SDL_Surface *pSprite = NULL;
    if((pSprite = IMG_Load(image->localisation)) != NULL){
        //creation de la texture
        image->pTexture = SDL_CreateTextureFromSurface(pRenderer, pSprite);
        image->temps = 0;

        SDL_FreeSurface(pSprite);

        if(image->pTexture == NULL){   // erreur
            fprintf(fDebug,"Erreur: creation de '%s' (%s)", image->localisation, SDL_GetError());
            exit(-3);
        }
    }
    else{ // erreur
        fprintf(fDebug,"Erreur: creation de pSprite de '%s' (%s)", image->localisation, SDL_GetError());
        exit(-3);
    }
}

// supprime (si elle existe) la texture demande
void supprimeTexture(SDL_Texture* pTexture)
{
    if(pTexture){
        SDL_DestroyTexture(pTexture);
        pTexture == NULL;
    }
}

// affiche une image
void afficheImage(InfoImage image, int x, int y, Centre centre, SDL_Renderer* pRenderer, FILE* fDebug)
{
    // centre prend OUI : 2 ou NON : 0

    SDL_Texture* pTexture = image.pTexture;

    // surface de l'image
    int w, h;
    SDL_QueryTexture(pTexture, NULL, NULL, &w, &h);

    SDL_Rect dest; // info de l'image

    dest.x = x - (w/2 * centre);
    dest.y = y - (h/2 * centre);
    dest.w = w;
    dest.h = h;

    // affiche la texture
    if(SDL_RenderCopy(pRenderer, pTexture, NULL, &dest)){
        fprintf(fDebug,"Erreur: copie de texture de %s (%s)\n", image.localisation, SDL_GetError());
        DEBUG("")
        fseek(fDebug, 0, SEEK_CUR);
    }
}


