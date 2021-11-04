/*
execute divers actions selon les evenements
*/

#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

#include "action.h"
#include "video.h"
#include "image.h"

// autre:

// appel de 'fermetureFenetre' (video.h) qui ferme le jeu

void aQuit(Image* images, InfoJeu* jeu, InfoFenetre* fenetre, FILE* fDebug){
    fermetureFenetre(images, fenetre, fDebug, jeu->fSauvegarde);
}

void afficheDebug(){
    debugWindow_Apparition();
}

// Accueil


// selection des modes de hardcore
void aHardcore(Hardcore* hardcore, unsigned int temps){
	if(temps >= 1000){  // reste appuye plus de 1 secondes
   		   if(hardcore->mode != 2){ // le mode est different de 2
   		       hardcore->mode = 2;  // mode 2: 10 secondes pour jouer
   		   }
   		   else{    // le mode est 2
   		       hardcore->mode = 0;   // mode 0: pas de temps limite
   		   }
   	}
   	else if(hardcore->mode == 0){   // reste appuyee moins de 1 secondes et le mode est 0
   		   hardcore->mode = 1;  // mode 1: 15 secondes pour jouer
    }
    else{   // reste appuyee moins de 1 secondes et le mode est different de 0
    	   hardcore->mode = 0;// mode 0: pas de temps limite
    }
}


// confirme la difficultee des bots
void aValide(Image* images, InfoJeu* jeu, InfoFenetre* fenetre){
    // la difficultee des bot a ete choisie
    if((jeu->mode == 2 && jeu->bot1.difficulte) || (jeu->mode == 4 && (jeu->bot1.difficulte && jeu->bot1.difficulte))){
        fenetre->ecran = JEU;   // lancement du jeu
    }
    else{
        images->image[accueil_SELECTIONNEZ_UNE_DIFFICULTEE].temps = SDL_GetTicks();
    }
}


