#include <SDL2/SDL.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "debug.h"

#include "grille.h"
#include "video.h"
#include "image.h"

#include "jeu.h"

// remet a zero la grille, la structure 'case'
void res_Grille(CaseGrille grille[9][9])
{
	   // pour toute la grille
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
        	   // initialise la structure
            grille[i][j].joueur = 0;
            grille[i][j].etat = 0;

            grille[i][j].pion.image = 0;
            grille[i][j].pion.velociteY = 0;
            grille[i][j].pion.x = 0;
            grille[i][j].pion.y = 0;
        }
    }
}

// trouve a quelle case placer le pion, et le place
void placePion(InfoJeu* jeu, InfoFenetre* fenetre)
{

    // nombre de lignes different selon le mode
    int ligneMax = (jeu->mode == 3)? 8 : 6;
    int debutPion = (jeu->mode == 3)? fenetre->w/2 - 400 : fenetre->w/2 - 300;

    infosGrille(jeu);

    if(jeu->infoGrille[jeu->colonne]){
        remplacePion_joue(jeu);

    // animationPion()

        jeu->grille[jeu->colonne][ligneMax - jeu->infoGrille[jeu->colonne]].joueur = jeu->joueur;// la case jouee est assigne au joueur
        jeu->grille[jeu->colonne][ligneMax - jeu->infoGrille[jeu->colonne]].etat = 2;// elle prend l'etat 'pion_joue'
        jeu->grille[jeu->colonne][ligneMax - jeu->infoGrille[jeu->colonne]].pion.image = pion1 + (jeu->grille[jeu->colonne][ligneMax - jeu->infoGrille[jeu->colonne]].joueur - 1) + ((jeu->grille[jeu->colonne][ligneMax - jeu->infoGrille[jeu->colonne]].etat - 1) * 3);
        jeu->grille[jeu->colonne][ligneMax - jeu->infoGrille[jeu->colonne]].pion.x = debutPion + (jeu->colonne * 100);
        jeu->grille[jeu->colonne][ligneMax - jeu->infoGrille[jeu->colonne]].pion.y = fenetre->h/2 - 350 + (jeu->infoGrille[jeu->colonne] * 100);
        fprintf(fDebug, "%d, %d", jeu->grille[jeu->colonne][ligneMax - jeu->infoGrille[jeu->colonne]].pion.x, jeu->grille[jeu->colonne][ligneMax - jeu->infoGrille[jeu->colonne]].pion.y);
        DEBUG("\n")
    }
}

// change les "pion_joue" en "pion"
void remplacePion_joue(InfoJeu* jeu)
{
    for(int colonne = 0; colonne < 9; colonne++){
        for(int ligne = 0; ligne < 8; ligne++){
            if(jeu->grille[colonne][ligne].etat == 2){// chercher un 'pion_joue'
                jeu->grille[colonne][ligne].etat = 1;// le remplace par un pion normal
                jeu->grille[colonne][ligne].pion.image = pion1 + (jeu->grille[colonne][ligne].joueur - 1) + ((jeu->grille[colonne][ligne].etat - 1) * 3);
            }
        }
    }
}

// verifie les puissance 4
void aligne4(CaseGrille grille[9][9], InfoJeu* jeu)
{

    int mode = jeu->mode;

    int fin = 0;// indique le joueur qui gagne
    int ligneMax, colonneMax;

    if(mode != 3)
    {
        ligneMax = 6;
        colonneMax = 7;
    }
    else
    {
        ligneMax = 8;
        colonneMax = 9;
    }

    for(int pion = 1; pion < 4; pion++)
    {
        for(int colonne = 0; colonne < colonneMax; colonne++)
        {
            for(int l = 0, ll = 1, lll = 2, llll = 3; llll < ligneMax ; l++, ll++, lll++, llll++)
            {
                // |
                if(grille[colonne][llll].joueur == pion   //  |
                    &&grille[colonne][lll].joueur == pion //  |
                    &&grille[colonne][ll].joueur == pion  //  |
                    &&grille[colonne][l].joueur == pion)  //  |
                {
                    grille[colonne][llll].etat = 3;
                    grille[colonne][lll].etat = 3;
                    grille[colonne][ll].etat = 3;
                    grille[colonne][l].etat = 3;

                    fin = pion;
                }
            }
        }


        for(int ligne = 0; ligne < ligneMax; ligne++)
        {
            for(int c = 0, cc = 1, ccc = 2, cccc = 3; cccc < colonneMax; c++, cc++, ccc++, cccc++)
            {
                // —
                if(grille[c][ligne].joueur == pion          //  * - - -
                    &&grille[cc][ligne].joueur == pion      //  - * - -
                    &&grille[ccc][ligne].joueur == pion     //  - - * -
                    &&grille[cccc][ligne].joueur == pion)   //  - - - *
                {
                    grille[c][ligne].etat = 3;
                    grille[cc][ligne].etat = 3;
                    grille[ccc][ligne].etat = 3;
                    grille[cccc][ligne].etat = 3;

                    fin = pion;
                }
            }
        }


        for(int c = 0, cc = 1, ccc = 2, cccc = 3; cccc < colonneMax; c++, cc++, ccc++, cccc++)
        {
            for(int l = 0, ll = 1, lll = 2, llll = 3; llll < ligneMax ; l++, ll++, lll++, llll++)
            {
                // /
                if(grille[cccc][llll].joueur == pion    //       /
                    &&grille[ccc][lll].joueur == pion   //     /
                    &&grille[cc][ll].joueur == pion     //   /
                    &&grille[c][l].joueur == pion)      // /
                {
                    grille[cccc][llll].etat = 3;
                    grille[ccc][lll].etat = 3;
                    grille[cc][ll].etat = 3;
                    grille[c][l].etat = 3;

                    fin = pion;
                }
            }
        }



        for(int c = 0, cc = 1, ccc = 2, cccc = 3; cccc < colonneMax; c++, cc++, ccc++, cccc++)
        {
            for(int l = 0, ll = 1, lll = 2, llll = 3; llll < ligneMax ; l++, ll++, lll++, llll++)
            {
                /* \ */
                if(grille[cccc][l].joueur == pion       /* \        */
                    &&grille[ccc][ll].joueur == pion    /*   \      */
                    &&grille[cc][lll].joueur == pion    /*     \    */
                    &&grille[c][llll].joueur == pion)   /*       \  */
                {
                    grille[cccc][l].etat = 3;
                    grille[ccc][ll].etat = 3;
                    grille[cc][lll].etat = 3;
                    grille[c][llll].etat = 3;

                    fin = pion;
                }
            }
        }
    }

    jeu->fin = fin;

}

// recupere le nombre de cases vides de chaques colonne
void infosGrille(InfoJeu* jeu)
{
    int colonne = (jeu->mode == 3)? 9 : 7;
    int ligne = (jeu->mode == 3)? 8 : 6;



    for(int i = 0; i < colonne; i++){
        jeu->infoGrille[i] = 0;
        for(int j = 0; j < ligne; j++){
            if(jeu->grille[i][j].joueur == 0){// cherche une case vide
            	   jeu->infoGrille[i]++;
            }
        }
    }
}

// sauvegarde la grille dans un fichier
void sauvegardeGrille(InfoJeu* jeu, FILE* fDebug)
{
	   // place le curseur virtuel a la fin du fichier

	   fseek(jeu->fSauvegarde, 0, SEEK_CUR);

	   fprintf(jeu->fSauvegarde, ":%d %d\n", jeu->tour, jeu->joueur);   // infos de tour
	   for(int i = 7; i > -1; i--){
	   	  for(int j = 0; j < 9; j++){
	   	  	   fprintf(jeu->fSauvegarde, " %d/%d", jeu->grille[j][i].joueur, jeu->grille[j][i].etat);   // joueur et etat du pion
	   	  }
	   	  fputc('\n', jeu->fSauvegarde);
	   }
	   fputc('\n', jeu->fSauvegarde);

}

// lis un fichier a la recherche d'un tour donne et remplace la grille actuelle par celle sauvegardee
void recupereGrille(Image* images, InfoJeu* jeu, InfoFenetre* fenetre, FILE* fDebug){

    // place le curseur virtuel au debut du fichier
    fseek(jeu->fSauvegarde, 0, SEEK_SET);

    int lecture = 1, securite2 = 0;
    long securite = 0;

    // trouve le bon tour dans le fichier
    while(lecture){

        while(fgetc(jeu->fSauvegarde) != ':'){
            securite++;
            if(securite > 10000000) // dans le cas où le fichier a été suprimé ou altéré
                DEBUG("fSauvegarde altéré, fermeture du programme")
                fermetureFenetre(images, fenetre, fDebug, jeu->fSauvegarde);
        }

        char infoTour[4];
        sprintf(infoTour, "   ");

        for(int j = 0, c = 0; c != ' '; j++){
            c = fgetc(jeu->fSauvegarde);
            infoTour[j] = c;
        }

        if(atoi(infoTour) == (jeu->tour) - 1){
            lecture = 0;
            jeu->tour -= 2;
        }

        securite2++;
        if(securite2 > 100){
            DEBUG("fSauvegarde altéré, fermeture du programme")
            fermetureFenetre(images, fenetre, fDebug, jeu->fSauvegarde);
        }
    }

    int joueur = 0;

    char chiffre[2];
    chiffre[0] = ' ';
    chiffre[1] = '\0';

    while(joueur != 1 && joueur != 2 && joueur != 3){
        chiffre[0] = fgetc(jeu->fSauvegarde);
        joueur = atoi(chiffre);// recupere les infos de joueur
    }

    jeu->joueur = joueur;

    fgetc(jeu->fSauvegarde);// on passe le \n

    for(int i = 7; i > -1; i--){
        for(int j = 0; j < 9; j++){

            fgetc(jeu->fSauvegarde);// ' '
            chiffre[0] = fgetc(jeu->fSauvegarde);
            jeu->grille[j][i].joueur = atoi(chiffre); // joueur auquel appartient la case
            fgetc(jeu->fSauvegarde);// '/'
            chiffre[0] = fgetc(jeu->fSauvegarde);
            jeu->grille[j][i].etat = atoi(chiffre); // etat de la case
        }
        fgetc(jeu->fSauvegarde);// \n
    }

    fgetc(jeu->fSauvegarde);// \n
}
