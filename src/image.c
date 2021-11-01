/*
Charge les images
*/

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>


#include "image.h"

void Image_localisation(Image* images){
    images->image[chargement].localisation = "./data/autre/CHARGEMENT.png";

    //AUTRE
    images->image[croix].localisation = "./data/autre/croix.png";
    images->image[nb_0].localisation = "./data/nombre/nb_0.png";
    images->image[nb_1].localisation = "./data/nombre/nb_1.png";
    images->image[nb_2].localisation = "./data/nombre/nb_2.png";
    images->image[nb_3].localisation = "./data/nombre/nb_3.png";
    images->image[nb_4].localisation = "./data/nombre/nb_4.png";
    images->image[nb_5].localisation = "./data/nombre/nb_5.png";
    images->image[nb_6].localisation = "./data/nombre/nb_6.png";
    images->image[nb_7].localisation = "./data/nombre/nb_7.png";
    images->image[nb_8].localisation = "./data/nombre/nb_8.png";
    images->image[nb_9].localisation = "./data/nombre/nb_9.png";
    images->image[parametre_logo].localisation = "./data/parametre/autre/parametre_logo.png";
    images->image[parametre_bg].localisation = "./data/parametre/autre/parametre_bg.png";
    images->image[joueurCommence_bg].localisation = "./data/parametre/joueurCommence/joueurCommence_bg.png";
    images->image[joueur1Commence].localisation = "./data/parametre/joueurCommence/joueur1Commence.png";
    images->image[joueur2Commence].localisation = "./data/parametre/joueurCommence/joueur2Commence.png";
    images->image[joueur3Commence].localisation = "./data/parametre/joueurCommence/joueur3Commence.png";
    images->image[joueur1Commence_actif].localisation = "./data/parametre/joueurCommence/joueur1Commence_actif.png";
    images->image[joueur2Commence_actif].localisation = "./data/parametre/joueurCommence/joueur2Commence_actif.png";
    images->image[joueur3Commence_actif].localisation = "./data/parametre/joueurCommence/joueur3Commence_actif.png";

    //ACCUEIL
    images->image[accueil_bg].localisation = "./data/accueil/autre/accueil_bg.png";
    images->image[accueil_retour].localisation = "./data/accueil/autre/accueil_retour.png";
    images->image[accueil_valide].localisation = "./data/accueil/autre/accueil_valide.png";
    images->image[accueil_APPUYEZ_SUR_UNE_TOUCHE_POUR_JOUER].localisation = "./data/accueil/autre/accueil_APPUYEZ_SUR_UNE_TOUCHE_POUR_JOUER.png";
    images->image[hardcore_inactif].localisation = "./data/accueil/hardcore/hardcore_inactif.png";
    images->image[hardcore_1].localisation = "./data/accueil/hardcore/hardcore_1.png";
    images->image[hardcore_2].localisation = "./data/accueil/hardcore/hardcore_2.png";
    images->image[accueil_mode1].localisation = "./data/accueil/mode/accueil_mode1.png";
    images->image[accueil_mode2].localisation = "./data/accueil/mode/accueil_mode2.png";
    images->image[accueil_mode3].localisation = "./data/accueil/mode/accueil_mode3.png";
    images->image[accueil_mode4].localisation = "./data/accueil/mode/accueil_mode4.png";
    images->image[accueil_SELECTIONNEZ_UNE_DIFFICULTEE].localisation = "./data/accueil/bot/SELECTIONNEZ_UNE_DIFFICULTEE.png";
    images->image[accueil_SELECTIONNEZ_UNE_DIFFICULTEE_efface].localisation = "./data/accueil/bot/SELECTIONNEZ_UNE_DIFFICULTEE_efface.png";
    images->image[accueil_botJaune].localisation = "./data/accueil/bot/accueil_botJaune.png";
    images->image[accueil_botRouge].localisation = "./data/accueil/bot/accueil_botRouge.png";
    images->image[accueil_bot_inactif].localisation = "./data/accueil/bot/accueil_bot_inactif.png";
    images->image[accueil_botFacile_actif].localisation = "./data/accueil/bot/accueil_botFacile_actif.png";
    images->image[accueil_botNormal_actif].localisation = "./data/accueil/bot/accueil_botNormal_actif.png";
    images->image[accueil_botDifficile_actif].localisation = "./data/accueil/bot/accueil_botDifficile_actif.png";
    images->image[accueil_botFacile_inactif].localisation = "./data/accueil/bot/accueil_botFacile_inactif.png";
    images->image[accueil_botNormal_inactif].localisation = "./data/accueil/bot/accueil_botNormal_inactif.png";
    images->image[accueil_botDifficile_inactif].localisation = "./data/accueil/bot/accueil_botDifficile_inactif.png";

    //JEU
    images->image[menu_logo].localisation = "./data/menu/autre/menu_logo.png";
    images->image[menu_grillage].localisation = "./data/menu/grillage/menu_grillage.png";
    images->image[menu_grillage1].localisation = "./data/menu/grillage/menu_grillage1.png";
    images->image[menu_grillage2].localisation = "./data/menu/grillage/menu_grillage2.png";
    images->image[menu_Borduregrillage].localisation = "./data/menu/grillage/menu_Borduregrillage.png";
    images->image[menu_Reprendre].localisation = "./data/menu/bouton/menu_Reprendre.png";
    images->image[menu_Rejouer].localisation = "./data/menu/bouton/menu_Rejouer.png";
    images->image[menu_RetourAccueil].localisation = "./data/menu/bouton/menu_RetourAccueil.png";
    images->image[menu_Quitter].localisation = "./data/menu/bouton/menu_Quitter.png";
    images->image[jeu_bg].localisation = "./data/jeu/autre/jeu_bg.png";
    images->image[jeu_retour].localisation = "./data/jeu/autre/jeu_retour.png";
    images->image[joueur1].localisation = "./data/jeu/joueur/joueur1.png";
    images->image[joueur2].localisation = "./data/jeu/joueur/joueur2.png";
    images->image[joueur3].localisation = "./data/jeu/joueur/joueur3.png";
    images->image[bot1].localisation = "./data/jeu/joueur/bot1.png";
    images->image[bot2].localisation = "./data/jeu/joueur/bot2.png";
    images->image[joueur1_actif].localisation = "./data/jeu/joueur/joueur1_actif.png";
    images->image[joueur2_actif].localisation = "./data/jeu/joueur/joueur2_actif.png";
    images->image[joueur3_actif].localisation = "./data/jeu/joueur/joueur3_actif.png";
    images->image[bot1_actif].localisation = "./data/jeu/joueur/bot1_actif.png";
    images->image[bot2_actif].localisation = "./data/jeu/joueur/bot2_actif.png";
    images->image[grille7x6].localisation = "./data/jeu/grille/grille7x6.png";
    images->image[grille9x8].localisation = "./data/jeu/grille/grille9x8.png";
    images->image[hardcore_bg].localisation = "./data/jeu/hardcore/hardcore_bg.png";
    images->image[hardcore_Temps_Vert].localisation = "./data/jeu/hardcore/hardcore_Temps_Vert.png";
    images->image[hardcore_Temps_Orange].localisation = "./data/jeu/hardcore/hardcore_Temps_Orange.png";
    images->image[hardcore_Temps_Rouge].localisation = "./data/jeu/hardcore/hardcore_Temps_Rouge.png";
    images->image[jeu_colonne_Desactive].localisation = "./data/jeu/colonne/jeu_colonne_Desactive.png";
    images->image[jeu_colonneTaille1_Active].localisation = "./data/jeu/colonne/jeu_colonneTaille1_Active.png";
    images->image[jeu_colonneTaille2_Active].localisation = "./data/jeu/colonne/jeu_colonneTaille2_Active.png";
    images->image[jeu_colonneTaille3_Active].localisation = "./data/jeu/colonne/jeu_colonneTaille3Active.png";
    images->image[jeu_colonneTaille4_Active].localisation = "./data/jeu/colonne/jeu_colonneTaille4_Active.png";
    images->image[jeu_colonneTaille5_Active].localisation = "./data/jeu/colonne/jeu_colonneTaille5_Active.png";
    images->image[jeu_colonneTaille6_Active].localisation = "./data/jeu/colonne/jeu_colonneTaille6_Active.png";
    images->image[jeu_colonneTaille7_Active].localisation = "./data/jeu/colonne/jeu_colonneTaille7_Active.png";
    images->image[jeu_colonneTaille8_Active].localisation = "./data/jeu/colonne/jeu_colonneTaille8_Active.png";
    images->image[pion1].localisation = "./data/jeu/pion/pion1.png";
    images->image[pion2].localisation = "./data/jeu/pion/pion2.png";
    images->image[pion3].localisation = "./data/jeu/pion/pion3.png";
    images->image[pion1_joue].localisation = "./data/jeu/pion/pion1_joue.png";
    images->image[pion2_joue].localisation = "./data/jeu/pion/pion2_joue.png";
    images->image[pion3_joue].localisation = "./data/jeu/pion/pion3_joue.png";
    images->image[pion1_gagne].localisation = "./data/jeu/pion/pion1_gagne.png";
    images->image[pion2_gagne].localisation = "./data/jeu/pion/pion2_gagne.png";
    images->image[pion3_gagne].localisation = "./data/jeu/pion/pion3_gagne.png";
    images->image[fin_LE_JOUEUR].localisation = "./data/fin/texte/fin_LE_JOUEUR.png";
    images->image[fin_GAGNE].localisation = "./data/fin/texte/fin_GAGNE.png";
    images->image[fin_EGALITE].localisation = "./data/fin/texte/fin_EGALITE.png";

}

//reset la structure Images
void res_Image(Image* images){
    images->section_autre = 0;
    images->section_acceuil = 0;
    images->section_jeu = 0;

    Image_localisation(images);

    for(i = 0; i < NBR_IMAGE; i++){
        if(images->image[i].pTexture){
            SDL_DestroyTexture(images->image[i].pTexture);
        }
        images->image[i].pTexture = NULL;
        images->image.temps = 0;
    }
}

void chargeSectionImage(Section section, Image* images, SDL_Renderer* pRenderer, FILE* fDebug){

    switch(section){
        case AUTRE:
            if(images->section_autre == 0){
                images->section_autre = 1;

                for(i = D_SECTION_AUTRE; i < F_SECTION_AUTRE + 1; i++){
                    chargeImage(&images->image[i]);
                }
            }
            break;

        case ACCUEIL:
            if(images->section_acceuil == 0){
                images->section_acceuil = 1;
                for(i = D_SECTION_ACCUEIL; i < F_SECTION_ACCUEIL + 1; i++){
                    chargeImage(&images->image[i]);
                }
            }
            if(images->section_jeu == 1){
                images->section_jeu = 0;
                for(i = D_SECTION_JEU; i < F_SECTION_JEU + 1; i++){
                    supprimeTexture(&images->image[i].pTexture);
                }
            }
            break;

        case JEU:
            if(images->section_jeu == 0){
                images->section_jeu = 1;
                for(i = D_SECTION_JEU; i < F_SECTION_JEU + 1; i++){
                    chargeImage(&images->image[i]);
                }
            }
            if(images->section_acceuil == 1){
                images->section_acceuil = 0;
                for(i = D_SECTION_ACCUEIL; i < F_SECTION_ACCUEIL + 1; i++){
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
void afficheImage(SDL_Texture* pTexture, int coordonnee[2], Centre centre, SDL_Renderer* pRenderer, FILE* fDebug)
{
    // centre prend OUI : 2 ou NON : 0

    // surface de l'image
    int w, h;
    SDL_QueryTexture(pTexture, NULL, NULL, &w, &h);

    SDL_Rect dest = {coordonnee[0] - (w/centre), coordonnee[1] - (h/centre), w, h}; // info de l'image

    // affiche la texture
    if(SDL_RenderCopy(pRenderer, pTexture, NULL, &dest)){
        fprintf(fDebug,"Erreur: copie de texture (%s)\n", SDL_GetError());
        fseek(fDebug, 0, SEEK_CUR);
    }
}


