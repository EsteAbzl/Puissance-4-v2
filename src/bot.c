#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "bot.h"
#include "grille.h"
#include "jeu.h"
#include "debug.h"

/*!!! NE PAS OUBLIER DE METTRE "srand(time(NULL));" DANS LE MAIN DU PROGRAMME*/

//choisit une colonne de differentes façons selon la difficultee
int bot(int bot, int difficulte, caseGrille grille[9][9], strat *stratActive)
{
/*
	difficulte:
 1: 3 aligne, sinon 2 aligne, sinon hazard (blacklist desactivé)
 2: 3 aligne, sinon 2 aligne, sinon hazard (blacklist activé)
 3: 3 aligne, sinon stratégie, sinon 2 aligne, sinon hazard (blacklist activé)
*/


    int	colonne = -1;


    blkList blacklist[7]; // voir bot.h

    // les colonnes remplies ne peuvent pas etre jouee
    int infoGrille[9];
    infosGrille(4, infoGrille, grille);

    for(int i = 0; i < 7; i++)
    {
        if(infoGrille[i] == 0)
            blacklist[i].type = 2;
        else
            blacklist[i].type = 0;

        blacklist[i].ligne = -1;

        blacklist[i].joueur = -1;
    }


    if(difficulte == 1)// 3 aligne, sinon 2 aligne, sinon hazard (blacklist desactivé)
    {
        colonne = aligne3(bot, grille, NULL);// 3 aligne

        if(colonne == -1)
        {
            colonne = aligne2(bot, grille, NULL);// 2 aligne

            if(colonne == -1)
            {
                while(colonne == -1 || blacklist[colonne].type)
                    colonne = (rand() % 7);// hasard
            }
        }
    }


    else if(difficulte == 2)// 3 aligne, sinon 2 aligne, sinon hazard (blacklist activé)
    {
        colonne = aligne3(bot, grille, blacklist);// 3 aligne

        if(colonne == -1)
        {
            colonne = aligne2(bot, grille, blacklist);// 2 aligne

            if(colonne == -1)
            {
                int colonnesLibres = 0;

                for(int i = 0; i < 7; i++)
                {
                    if(blacklist[i].type == 0)
                        colonnesLibres++;
                }

                if (colonnesLibres == 0)// si aucune colonne est libre
                {
                    for(int i = 0; i < 7; i++)
                        blacklist[i].type--;
                }

                while(colonne == -1 || blacklist[colonne].type)
                    colonne = (rand() % 7);// hasard
            }
        }
    }


    else if(difficulte == 3)// 3 aligne, sinon stratégie, sinon 2 aligne, sinon hazard (blacklist activé)
    {
        colonne = aligne3(bot, grille, blacklist);// 3 aligne

        if(colonne == -1)
        {

            if(1)
            {
                //if((rand() % 3) == 0) // 1 chance sur 3 de débuter une stratégie
                {
                    trouveStrat(bot, grille, blacklist, stratActive);
                    colonne = strategie(bot, grille, blacklist, stratActive);
                }
            }
            else
            {
                colonne = strategie(bot, grille, blacklist, stratActive);

                if(stratActive->type == 0)
                {
                    trouveStrat(bot, grille, blacklist, stratActive);
                    colonne = strategie(bot, grille, blacklist, stratActive);
                }
            }

            if(colonne == -1)
            {
                colonne = aligne2(bot, grille, blacklist);// 2 aligne

                if(colonne == -1)
                {
                    int colonnesLibres = 0;

                    for(int i = 0; i < 7; i++)
                    {
                        if(blacklist[i].type == 0)
                            colonnesLibres++;
                    }

                    if (colonnesLibres == 0)// si aucune colonne est libre
                    {
                        for(int i = 0; i < 7; i++)
                            blacklist[i].type--;
                    }

                    while(colonne == -1 || blacklist[colonne].type)
                        colonne = (rand() % 7);// hasard
                }
            }
        }



    }


    if(blacklist){ // affichage pour le debug
        sprintf(debugTexte[8].txt,"black list [joueur]: ");
        sprintf(debugTexte[9].txt,"black list [type]:   ");

        for(int i = 0; i < 7; i++){
            switch(blacklist[i].joueur){
            case -1:
                strcat(debugTexte[8].txt, "| "); // pas de blacklist
                break;
            case 1:
                strcat(debugTexte[8].txt, "|J"); // avantage le joueur jaune
                break;
            case 2:
                strcat(debugTexte[8].txt, "|R"); // avantage le joueur rouge
                break;
            }

            switch(blacklist[i].type){
            case 0:
                strcat(debugTexte[9].txt, "| "); // pas de blacklist
                break;
            case 1:
                strcat(debugTexte[9].txt, "|!"); // danger de puissance 4
                break;
            case 2:
                strcat(debugTexte[9].txt, "|X"); // colonne pleine
                break;
            case 3:
                strcat(debugTexte[9].txt, "|S"); // dedié à la stratégie
                break;
            }
        }
        strcat(debugTexte[8].txt, "|");
        strcat(debugTexte[9].txt, "|");
    }


    return colonne;

}


// verifie les puissance 3: *xxx / xxx*
int aligne3(int bot, caseGrille grille[9][9], blkList blacklist[7])
{
    int jeton = bot;// on commence par chercher le bot qui joue
    int tour = 0;// incremente a chaques tours

    int *colonneTrouve = NULL;
    colonneTrouve = malloc(sizeof(int));

    int nombreColonneTrouve = 0;


    while(nombreColonneTrouve == 0 && jeton == bot)
    {

        // on change le joueur cherché
        if(tour == 1)
        {
            if(jeton == 1)
                jeton = 2;
            else
                jeton = 1;
        }


        for(int colonne = 0; colonne < 7; colonne++) // |
        {
            for(int l = 0, ll = 1, lll = 2, llll = 3; llll < 6; l++, ll++, lll++, llll++)
            {

                if(((grille[colonne][l].joueur == jeton)// |
                    &(grille[colonne][ll].joueur == jeton)
                    &(grille[colonne][lll].joueur == jeton))

                    &&grille[colonne][llll].joueur == 0)
                {
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = colonne;
                }

            }
        }


        for(int ligne = 0; ligne < 6; ligne++) // _
        {
            for(int c = 0, cc = 1, ccc = 2, cccc = 3; cccc < 7; c++, cc++, ccc++, cccc++)
            {

                if(((grille[c][ligne].joueur == jeton)// ---*
                    &(grille[cc][ligne].joueur == jeton)
                    &(grille[ccc][ligne].joueur == jeton))

                    &&(grille[cccc][ligne].joueur == 0))
                {
                    if(ligne == 0 || grille[cccc][ligne - 1].joueur != 0) // ligne - 1 sert a verifier que la case en dessous de l'objectif est pleine (support)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = cccc;
                    }
                    // ayant constaté qu'il n'y a pas de 'support' pour l'objectif, on verrifie que l'on ne vas pas en cree un. ce qui pourrais etre fatal pour le bot
                    else if(ligne == 1 || grille[cccc][ligne - 2].joueur != 0)
                    {
                        if(blacklist)
                        {
                            blacklist[cccc].type = 1;
                            blacklist[cccc].joueur = jeton;
                            blacklist[cccc].ligne = ligne;
                        }
                    }
                }

                if(((grille[cccc][ligne].joueur == jeton)// *---
                    &(grille[ccc][ligne].joueur == jeton)
                    &(grille[cc][ligne].joueur == jeton))

                    &&(grille[c][ligne].joueur == 0))
                {
                    if(ligne == 0 || grille[c][ligne - 1].joueur != 0)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = c;
                    }
                    else if(ligne == 1 || grille[c][ligne - 2].joueur != 0)
                    {
                        if(blacklist)
                        {
                            blacklist[c].type = 1;
                            blacklist[c].joueur = jeton;
                            blacklist[c].ligne = ligne;
                        }
                    }
                }

                /**//**//**//**//* Aligne Entre *//**//**//**//**/

                if(((grille[c][ligne].joueur == jeton)// --*-
                    &(grille[cc][ligne].joueur == jeton)
                    &(grille[cccc][ligne].joueur == jeton))

                    &&((grille[ccc][ligne].joueur == 0)))
                {
                    if(ligne == 0 || grille[ccc][ligne - 1].joueur != 0)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = ccc;
                    }
                    else if(ligne == 1 || grille[ccc][ligne - 2].joueur != 0)
                    {
                        if(blacklist)
                        {
                            blacklist[ccc].type = 1;
                            blacklist[ccc].joueur = jeton;
                            blacklist[ccc].ligne = ligne;
                        }
                    }
                }

                if(((grille[cccc][ligne].joueur == jeton)// -*--
                    &(grille[ccc][ligne].joueur == jeton)
                    &(grille[c][ligne].joueur == jeton))

                    &&((grille[cc][ligne].joueur == 0)))
                {
                    if(ligne == 0 || grille[cc][ligne - 1].joueur != 0)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = cc;
                    }
                    else if(ligne == 1 || grille[cc][ligne - 2].joueur != 0)
                    {
                        if(blacklist)
                        {
                            blacklist[cc].type = 1;
                            blacklist[cc].joueur = jeton;
                            blacklist[cc].ligne = ligne;
                        }
                    }
                }
            }
        }


        for(int c = 0, cc = 1, ccc = 2, cccc = 3; cccc < 7; c++, cc++, ccc++, cccc++) // /
        {
            for(int l = 0, ll = 1, lll = 2, llll = 3; llll < 6; l++, ll++, lll++, llll++)
            {
                if(((grille[c][l].joueur == 0))&&// ./

                    ((grille[cc][ll].joueur == jeton)
                    &(grille[ccc][lll].joueur == jeton)
                    &(grille[cccc][llll].joueur == jeton)))
                {
                    if(l == 0 || grille[c][l - 1].joueur != 0)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = c;
                    }
                    else if(l == 1 || grille[c][l - 2].joueur != 0)
                    {
                        if(blacklist)
                        {
                            blacklist[c].type = 1;
                            blacklist[c].joueur = jeton;
                            blacklist[c].ligne = l;
                        }
                    }
                }

                if(((grille[cccc][llll].joueur == 0))&&// /°

                    ((grille[ccc][lll].joueur == jeton)
                    &(grille[cc][ll].joueur == jeton)
                    &(grille[c][l].joueur == jeton)))
                {
                    if(grille[cccc][llll - 1].joueur != 0)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = cccc;
                    }
                    else if(grille[cccc][llll - 2].joueur != 0)
                    {
                        if(blacklist)
                        {
                            blacklist[cccc].type = 1;
                            blacklist[cccc].joueur = jeton;
                            blacklist[cccc].ligne = llll;
                        }
                    }
                }

                if(((grille[c][llll].joueur == 0))&&/* °\ */

                    ((grille[cc][lll].joueur == jeton)
                    &(grille[ccc][ll].joueur == jeton)
                    &(grille[cccc][l].joueur == jeton)))
                {
                    if(grille[c][llll - 1].joueur != 0)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = c;
                    }
                    else if(grille[c][llll - 2].joueur != 0)
                    {
                        if(blacklist)
                        {
                            blacklist[c].type = 1;
                            blacklist[c].joueur = jeton;
                            blacklist[c].ligne = llll;
                        }
                    }
                }

                if(((grille[cccc][l].joueur == 0))&&/* \. */

                    ((grille[ccc][ll].joueur == jeton)
                    &(grille[cc][lll].joueur == jeton)
                    &(grille[c][llll].joueur == jeton)))
                {
                    if(l == 0 || grille[cccc][l - 1].joueur != 0)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = cccc;
                    }
                    else if(l == 1 || grille[cccc][l - 2].joueur != 0)
                    {
                        if(blacklist)
                        {
                            blacklist[cccc].type = 1;
                            blacklist[cccc].joueur = jeton;
                            blacklist[cccc].ligne = l;
                        }
                    }
                }

                /**//**//**//**//* aligne Entre *//**//**//**//**/

                if(((grille[cc][ll].joueur == 0))&&// ./

                    ((grille[c][l].joueur == jeton)
                    &(grille[ccc][lll].joueur == jeton)
                    &(grille[cccc][llll].joueur == jeton)))
                {
                    if(grille[cc][ll - 1].joueur != 0)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = cc;
                    }
                    else if(ll == 1 || grille[cc][ll - 2].joueur != 0)
                    {
                        if(blacklist)
                        {
                            blacklist[cc].type = 1;
                            blacklist[cc].joueur = jeton;
                            blacklist[cc].ligne = ll;
                        }
                    }
                }

                if(((grille[ccc][lll].joueur == 0))&&// /°

                    ((grille[cccc][llll].joueur == jeton)
                    &(grille[cc][ll].joueur == jeton)
                    &(grille[c][l].joueur == jeton)))
                {
                    if(grille[ccc][lll - 1].joueur != 0)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = ccc;
                    }
                    else if(grille[ccc][lll - 2].joueur != 0)
                    {
                        if(blacklist)
                        {
                            blacklist[ccc].type = 1;
                            blacklist[ccc].joueur = jeton;
                            blacklist[ccc].ligne = lll;
                        }
                    }
                }

                if(((grille[cc][lll].joueur == 0))&&/* °\ */

                    ((grille[c][llll].joueur == jeton)
                    &(grille[ccc][ll].joueur == jeton)
                    &(grille[cccc][l].joueur == jeton)))
                {
                    if(grille[cc][lll - 1].joueur != 0)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = cc;
                    }
                    else if(grille[cc][lll - 2].joueur != 0)
                    {
                        if(blacklist)
                        {
                            blacklist[cc].type = 1;
                            blacklist[cc].joueur = jeton;
                            blacklist[cc].ligne = lll;
                        }
                    }
                }

                if(((grille[ccc][ll].joueur == 0))&&/* \. */

                    ((grille[cccc][l].joueur == jeton)
                    &(grille[cc][lll].joueur == jeton)
                    &(grille[c][llll].joueur == jeton)))
                {
                    if(grille[ccc][ll - 1].joueur != 0)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = ccc;
                    }
                    else if(ll == 1 || grille[ccc][ll - 2].joueur != 0)
                    {
                        if(blacklist)
                        {
                            blacklist[ccc].type = 1;
                            blacklist[ccc].joueur = jeton;
                            blacklist[ccc].ligne = ll;
                        }
                    }
                }
            }
        }


        for(int ligne = 0; ligne < 6; ligne++) // spécial
        {
            for(int c = 0, cc = 1, ccc = 2, cccc = 3, ccccc = 4; ccccc < 7; c++, cc++, ccc++, cccc++, ccccc++)
            {

                if(((grille[c][ligne].joueur == 0)// _-*-_
                    &(ligne == 0 || grille[c][ligne - 1].joueur != 0)
                    &(grille[cc][ligne].joueur == jeton)
                    &(grille[cccc][ligne].joueur == jeton)
                    &(grille[ccccc][ligne].joueur == 0)
                    &(ligne == 0 || grille[ccccc][ligne - 1].joueur != 0))

                    &(grille[ccc][ligne].joueur == 0))
                {
                    if(ligne == 0 || grille[ccc][ligne - 1].joueur != 0)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = ccc;
                    }
                    else if(ligne == 1 || grille[ccc][ligne - 2].joueur != 0)
                    {
                        if(blacklist)
                        {
                            blacklist[ccc].type = 1;
                            blacklist[ccc].joueur = jeton;
                            blacklist[ccc].ligne = ligne;
                        }
                    }
                }


                if(((grille[c][ligne].joueur == 0)// _--*_
                    &(ligne == 0 || grille[c][ligne - 1].joueur != 0)
                    &(grille[cc][ligne].joueur == jeton)
                    &(grille[ccc][ligne].joueur == jeton)
                    &(grille[ccccc][ligne].joueur == 0)
                    &(ligne == 0 || grille[ccccc][ligne - 1].joueur != 0))

                    &(grille[cccc][ligne].joueur == 0))
                {
                    if(ligne == 0 || grille[cccc][ligne - 1].joueur != 0)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = cccc;
                    }
                    else if(ligne == 1 || grille[cccc][ligne - 2].joueur != 0)
                    {
                        if(blacklist)
                        {
                            blacklist[cccc].type = 1;
                            blacklist[cccc].joueur = jeton;
                            blacklist[cccc].ligne = ligne;
                        }
                    }
                }


                if(((grille[c][ligne].joueur == 0)// _*--_
                    &(ligne == 0 || grille[c][ligne - 1].joueur != 0)
                    &(grille[ccc][ligne].joueur == jeton)
                    &(grille[cccc][ligne].joueur == jeton)
                    &(grille[ccccc][ligne].joueur == 0)
                    &(ligne == 0 || grille[ccccc][ligne - 1].joueur != 0))

                    &((grille[cc][ligne].joueur == 0)))
                {
                    if(ligne == 0 || grille[cc][ligne - 1].joueur != 0)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = cc;
                    }
                    else if(ligne == 1 || grille[cc][ligne - 2].joueur != 0)
                    {
                        if(blacklist)
                        {
                            blacklist[cc].type = 1;
                            blacklist[cc].joueur = jeton;
                            blacklist[cc].ligne = ligne;
                        }
                    }
                }
            }
        }

        tour++;

    }

    int colonne = -1;

    if(nombreColonneTrouve)
        colonne = colonneTrouve[(rand() % nombreColonneTrouve)]; //choisit parmit les colonnes trouvés

    free(colonneTrouve);

    return colonne;

}


// verifie les puissance 2: *xx- / -xx*
int aligne2(int bot, caseGrille grille[9][9], blkList blacklist[7])
{
    int jeton = bot;// on commence par chercher le bot qui joue
    int tour = 0;// incremente a chaques tours

    int *colonneTrouve = NULL;
    colonneTrouve = malloc(sizeof(int));

    int nombreColonneTrouve = 0;


    while(nombreColonneTrouve == 0 && jeton == bot)
    {

        // on change le bot cherché
        if(tour == 1)
        {
            if(jeton == 1)
                jeton = 2;
            else
                jeton = 1;
        }


        for(int colonne = 0; colonne < 7; colonne++)
        {
            for(int l = 0, ll = 1, lll = 2, llll = 3; llll < 6; l++, ll++, lll++, llll++)
            {

                if(((grille[colonne][l].joueur == jeton)// |
                    &(grille[colonne][ll].joueur == jeton))

                    && grille[colonne][lll].joueur == 0)
                {
                    if(blacklist)
                    {
                        if(blacklist[colonne].type == 0)
                        {
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = colonne;
                        }
                    }
                    else
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = colonne;
                    }
                }
            }
        }


        for(int ligne = 0; ligne < 6; ligne++)
        {
            for(int c = 0, cc = 1, ccc = 2, cccc = 3; cccc < 7; c++, cc++, ccc++, cccc++)
            {

                if(((grille[c][ligne].joueur == jeton)// --*_
                    &(grille[cc][ligne].joueur == jeton))
                    &(grille[cccc][ligne].joueur == 0)

                    &&((grille[ccc][ligne].joueur == 0)))
                {
                    if(ligne == 0 || grille[ccc][ligne - 1].joueur != 0)
                    {
                        if(blacklist)
                        {
                            if(blacklist[ccc].type == 0)
                            {
                                nombreColonneTrouve++;
                                colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                                colonneTrouve[nombreColonneTrouve - 1] = ccc;
                            }
                        }
                        else
                        {
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = ccc;
                        }
                    }
                }


                if(((grille[c][ligne].joueur == 0)// _--*
                    &(grille[cc][ligne].joueur == jeton))
                    &(grille[ccc][ligne].joueur == jeton)

                    &&((grille[cccc][ligne].joueur == 0)))
                {
                    if(ligne == 0 || grille[cccc][ligne - 1].joueur != 0)
                    {
                        if(blacklist)
                        {
                            if(blacklist[cccc].type == 0)
                            {
                                nombreColonneTrouve++;
                                colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                                colonneTrouve[nombreColonneTrouve - 1] = cccc;
                            }
                        }
                        else
                        {
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = cccc;
                        }
                    }
                }


                if(((grille[c][ligne].joueur == 0)// _*--
                    &(grille[ccc][ligne].joueur == jeton))
                    &(grille[cccc][ligne].joueur == jeton)

                    &&((grille[cc][ligne].joueur == 0)))
                {
                    if(ligne == 0 || grille[cc][ligne - 1].joueur != 0)
                    {
                        if(blacklist)
                        {
                            if(blacklist[cc].type == 0)
                            {
                                nombreColonneTrouve++;
                                colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                                colonneTrouve[nombreColonneTrouve - 1] = cc;
                            }
                        }
                        else
                        {
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = cc;
                        }
                    }
                }


                if(((grille[cc][ligne].joueur == jeton)// *--_
                    &(grille[ccc][ligne].joueur == jeton))
                    &(grille[cccc][ligne].joueur == 0)

                    &&((grille[c][ligne].joueur == 0)))
                {
                    if(ligne == 0 || grille[c][ligne - 1].joueur != 0)
                    {
                        if(blacklist)
                        {
                            if(blacklist[c].type == 0)
                            {
                                nombreColonneTrouve++;
                                colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                                colonneTrouve[nombreColonneTrouve - 1] = c;
                            }
                        }
                        else
                        {
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = c;
                        }
                    }
                }
            }
        }


        for(int c = 0, cc = 1, ccc = 2, cccc = 3; cccc < 7; c++, cc++, ccc++, cccc++)
        {
            for(int l = 0, ll = 1, lll = 2, llll = 3; llll < 6; l++, ll++, lll++, llll++)
            {

                if(((grille[cc][ll].joueur == jeton)// .//_
                    &(grille[ccc][lll].joueur == jeton)
                    &(grille[cccc][llll].joueur == 0))

                    &&(grille[c][l].joueur == 0))
                {
                    if(l == 0 || grille[c][l - 1].joueur != 0)
                    {
                        if(blacklist)
                        {
                            if(blacklist[c].type == 0)
                            {
                                nombreColonneTrouve++;
                                colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                                colonneTrouve[nombreColonneTrouve - 1] = c;
                            }
                        }
                        else
                        {
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = c;
                        }
                    }
                }


                if(((grille[c][l].joueur == 0)// _.//
                    &(grille[ccc][lll].joueur == jeton)
                    &(grille[cccc][llll].joueur == jeton))

                    &&(grille[cc][ll].joueur == 0))
                {
                    if(grille[cc][ll - 1].joueur != 0)
                    {
                        if(blacklist)
                        {
                            if(blacklist[cc].type == 0)
                            {
                                nombreColonneTrouve++;
                                colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                                colonneTrouve[nombreColonneTrouve - 1] = cc;
                            }
                        }
                        else
                        {
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = cc;
                        }
                    }
                }


                if(((grille[c][l].joueur == 0)// _//°
                    &(grille[cc][ll].joueur == jeton)
                    &(grille[ccc][lll].joueur == jeton))

                    &&(grille[cccc][llll].joueur == 0))
                {
                    if(grille[cccc][llll - 1].joueur != 0)
                    {
                        if(blacklist)
                        {
                            if(blacklist[cccc].type == 0)
                            {
                                nombreColonneTrouve++;
                                colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                                colonneTrouve[nombreColonneTrouve - 1] = cccc;
                            }
                        }
                        else
                        {
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = cccc;
                        }
                    }
                }

                if(((grille[c][l].joueur == jeton)// //°_
                    &(grille[cc][ll].joueur == jeton)
                    &(grille[cccc][llll].joueur == 0))

                    &&(grille[ccc][lll].joueur == 0))
                {
                    if(grille[ccc][lll - 1].joueur != 0)
                    {
                        if(blacklist)
                        {
                            if(blacklist[ccc].type == 0)
                            {
                                nombreColonneTrouve++;
                                colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                                colonneTrouve[nombreColonneTrouve - 1] = ccc;
                            }
                        }
                        else
                        {
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = ccc;
                        }
                    }
                }


                if(((grille[cc][lll].joueur == jeton)/* °\\_     */
                    &(grille[ccc][ll].joueur == jeton)
                    &(grille[cccc][l].joueur == 0))

                    &&(grille[c][llll].joueur == 0))
                {
                    if(grille[c][llll - 1].joueur != 0)
                    {
                        if(blacklist)
                        {
                            if(blacklist[c].type == 0)
                            {
                                nombreColonneTrouve++;
                                colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                                colonneTrouve[nombreColonneTrouve - 1] = c;
                            }
                        }
                        else
                        {
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = c;
                        }
                    }
                }


                if(((grille[c][llll].joueur == 0)/* _°\\     */
                    &(grille[ccc][ll].joueur == jeton)
                    &(grille[cccc][l].joueur == jeton))

                    &&(grille[cc][lll].joueur == 0))
                {
                    if(grille[cc][lll - 1].joueur != 0)
                    {
                        if(blacklist)
                        {
                            if(blacklist[cc].type == 0)
                            {
                                nombreColonneTrouve++;
                                colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                                colonneTrouve[nombreColonneTrouve - 1] = cc;
                            }
                        }
                        else
                        {
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = cc;
                        }
                    }
                }


                if(((grille[c][llll].joueur == 0)/* _\\.     */
                    &(grille[cc][lll].joueur == jeton)
                    &(grille[ccc][ll].joueur == jeton))

                    &&(grille[cccc][l].joueur == 0))
                {
                    if(l == 0 || grille[cccc][l - 1].joueur != 0)
                    {
                        if(blacklist)
                        {
                            if(blacklist[cccc].type == 0)
                            {
                                nombreColonneTrouve++;
                                colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                                colonneTrouve[nombreColonneTrouve - 1] = cccc;
                            }
                        }
                        else
                        {
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = cccc;
                        }
                    }
                }


                if(((grille[c][llll].joueur == jeton)/* \\._     */
                    &(grille[cc][lll].joueur == jeton)
                    &(grille[cccc][l].joueur == 0))

                    &&(grille[ccc][ll].joueur == 0))
                {
                    if(grille[ccc][ll - 1].joueur != 0)
                    {
                        if(blacklist)
                        {
                            if(blacklist[ccc].type == 0)
                            {
                                nombreColonneTrouve++;
                                colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                                colonneTrouve[nombreColonneTrouve - 1] = ccc;
                            }
                        }
                        else
                        {
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = ccc;
                        }
                    }
                }
            }
        }


        tour++;

    }

    int colonne = -1;

    if(nombreColonneTrouve)
        colonne = colonneTrouve[(rand() % nombreColonneTrouve)]; //choisit parmit les colonnes trouvés

    free(colonneTrouve);

    return colonne;
}



// permet au bot de trouver une stratégie
void trouveStrat(int bot, caseGrille grille[9][9], blkList blacklist[7], strat *stratActive)
{
    // si pionDejaPlace > pionDejaPlaceMax alors on supprime "stratPossible" et on le recrée avec des strat plus avancée. on choisira une strat au hazard parmi celle du tableau a la fin


    int autreJoueur = 0;
    if(bot == 1)
        autreJoueur = 2;
    else
        autreJoueur = 1;


    strat *stratPossible;
    stratPossible = malloc(sizeof(int) * 3);

    int tailleTableau = 0;
    int pionDejaPlace = 0;
    int pionDejaPlaceMax = 0;
    int abandonneStrat = 0;


    for( int colonne = 0; colonne < 4; colonne++)
    {
        for( int ligne = 0; ligne < 3; ligne++)
        {
            if(blacklist[colonne].type != 1 && blacklist[colonne + 1].type != 1 && blacklist[colonne + 2].type != 1 && blacklist[colonne + 3].type != 1)// on vérifie que la stratégie n'est pas sur une zone blacklisté
            {
                //strategie 1
                                /*
                                0
                                x -
                                0 - 0 0
                                x - x 0
                                */
                {

                    if(grille[colonne][ligne].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 1][ligne].joueur == 0)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 2][ligne].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne].joueur != 0)
                        abandonneStrat = 1;



                    if(grille[colonne][ligne + 1].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 1][ligne + 1].joueur == 0)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 2][ligne + 1].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne + 1].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne + 1].joueur != 0)
                        abandonneStrat = 1;



                    if(grille[colonne][ligne + 2].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne][ligne + 2].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 1][ligne + 2].joueur == 0)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne + 2].joueur != 0)
                        abandonneStrat = 1;



                    if(grille[colonne][ligne + 3].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne][ligne + 3].joueur != 0)
                        abandonneStrat = 1;



                    if(abandonneStrat)
                    {
                        abandonneStrat = 0;
                    }
                    else
                    {
                        if(pionDejaPlace == pionDejaPlaceMax)
                        {
                            tailleTableau++;
                            stratPossible = realloc(stratPossible, sizeof(int) * 3 * tailleTableau);
                        }
                        else if(pionDejaPlace > pionDejaPlaceMax)
                        {
                            tailleTableau = 1;
                            stratPossible = realloc(stratPossible, sizeof(int) * 3 * tailleTableau);
                            pionDejaPlaceMax = pionDejaPlace;
                        }

                        if(pionDejaPlace == pionDejaPlaceMax) // on ajoute une stratégie a la liste des tratégie possibles
                        {
                            stratPossible[tailleTableau - 1].colonne = colonne;
                            stratPossible[tailleTableau - 1].ligne = ligne;
                            stratPossible[tailleTableau - 1].type = 1;

                        }
                    }

                    pionDejaPlace = 0;
                }

                //inversé 1
                                /*
                                      0
                                    - x
                                0 0 - 0
                                0 x - x
                                */
                {

                    if(grille[colonne][ligne].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 1][ligne].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 2][ligne].joueur == 0)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne].joueur != 0)
                        abandonneStrat = 1;



                    if(grille[colonne][ligne + 1].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 1][ligne + 1].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 2][ligne + 1].joueur == 0)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne + 1].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne + 1].joueur != 0)
                        abandonneStrat = 1;



                    if(grille[colonne + 2][ligne + 2].joueur == 0)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne + 2].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne + 2].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne + 2].joueur != 0)
                        abandonneStrat = 1;



                    if(grille[colonne + 3][ligne + 3].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne + 3].joueur != 0)
                        abandonneStrat = 1;



                    if(abandonneStrat)
                    {
                        abandonneStrat = 0;
                    }
                    else
                    {
                        if(pionDejaPlace == pionDejaPlaceMax)
                        {
                            tailleTableau++;
                            stratPossible = realloc(stratPossible, ((sizeof(int) * 3) * tailleTableau) );
                        }
                        else if(pionDejaPlace > pionDejaPlaceMax)
                        {
                            tailleTableau = 1;
                            stratPossible = realloc(stratPossible, sizeof(int) * 3 * tailleTableau);
                            pionDejaPlaceMax = pionDejaPlace;
                        }

                        if(pionDejaPlace == pionDejaPlaceMax) // on ajoute une stratégie a la liste des tratégie possibles
                        {
                            stratPossible[tailleTableau - 1].colonne = colonne;
                            stratPossible[tailleTableau - 1].ligne = ligne;
                            stratPossible[tailleTableau - 1].type = -1;
                        }
                    }

                    pionDejaPlace = 0;
                }


                //strategie 2
                                /*
                                      *
                                - 0 0 0
                                x x 0 x
                                * s x 0
                                */
                {

                    if(grille[colonne][ligne].joueur == autreJoueur || grille[colonne][ligne].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 1][ligne].joueur == autreJoueur || grille[colonne + 1][ligne].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 2][ligne].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne].joueur != 0)
                        abandonneStrat = 1;



                    if(grille[colonne][ligne + 1].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 1][ligne + 1].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 2][ligne + 1].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne + 1].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne + 1].joueur != 0)
                        abandonneStrat = 1;



                    if(grille[colonne][ligne + 2].joueur == 0)
                        pionDejaPlace++;
                    else if(grille[colonne][ligne + 2].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 1][ligne + 2].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne + 2].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 2][ligne + 2].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne + 2].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne + 2].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne + 2].joueur != 0)
                        abandonneStrat = 1;




                    if(abandonneStrat)
                    {
                        abandonneStrat = 0;
                    }
                    else
                    {
                        if(pionDejaPlace == pionDejaPlaceMax)
                        {
                            tailleTableau++;
                            stratPossible = realloc(stratPossible, sizeof(int) * 3 * tailleTableau);
                        }
                        else if(pionDejaPlace > pionDejaPlaceMax)
                        {
                            tailleTableau = 1;
                            stratPossible = realloc(stratPossible, sizeof(int) * 3 * tailleTableau);
                            pionDejaPlaceMax = pionDejaPlace;
                        }

                        if(pionDejaPlace == pionDejaPlaceMax) // on ajoute une stratégie a la liste des tratégie possibles
                        {
                            stratPossible[tailleTableau - 1].colonne = colonne;
                            stratPossible[tailleTableau - 1].ligne = ligne;
                            stratPossible[tailleTableau - 1].type = 2;
                        }
                    }

                    pionDejaPlace = 0;
                }


                //inversé 2
                                /*
                                *
                                0 0 0 -
                                x 0 x x
                                0 x s *
                                */
                {

                    if(grille[colonne][ligne].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 1][ligne].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 2][ligne].joueur == autreJoueur || grille[colonne + 2][ligne].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne].joueur == autreJoueur || grille[colonne + 3][ligne].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne].joueur != 0)
                        abandonneStrat = 1;



                    if(grille[colonne][ligne + 1].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 1][ligne + 1].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 2][ligne + 1].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne + 1].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne + 1].joueur != 0)
                        abandonneStrat = 1;



                    if(grille[colonne][ligne + 2].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne][ligne + 2].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 1][ligne + 2].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne + 2].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 2][ligne + 2].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne + 2].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne + 2].joueur == 0)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne + 2].joueur != 0)
                        abandonneStrat = 1;




                    if(abandonneStrat)
                    {
                        abandonneStrat = 0;
                    }
                    else
                    {
                        if(pionDejaPlace == pionDejaPlaceMax)
                        {
                            tailleTableau++;
                            stratPossible = realloc(stratPossible, sizeof(int) * 3 * tailleTableau);
                        }
                        else if(pionDejaPlace > pionDejaPlaceMax)
                        {
                            tailleTableau = 1;
                            stratPossible = realloc(stratPossible, sizeof(int) * 3 * tailleTableau);
                            pionDejaPlaceMax = pionDejaPlace;
                        }

                        if(pionDejaPlace == pionDejaPlaceMax) // on ajoute une stratégie a la liste des tratégie possibles
                        {
                            stratPossible[tailleTableau - 1].colonne = colonne;
                            stratPossible[tailleTableau - 1].ligne = ligne;
                            stratPossible[tailleTableau - 1].type = -2;
                        }
                    }

                    pionDejaPlace = 0;
                }


            }
        }
    }


    for( int colonne = 0; colonne < 3; colonne++)
    {
        for( int ligne = 0; ligne < 3; ligne++)
        {
            if(blacklist[colonne].type != 1 && blacklist[colonne + 1].type != 1 && blacklist[colonne + 2].type != 1 && blacklist[colonne + 3].type != 1 && blacklist[colonne + 4].type != 1 )// on vérifie que la stratégie n'est pas sur une zone blacklisté
            {

                //strategie 3
                                /*
                                      -
                                  0 0 - 0
                                  0 x x x
                                0 x s s s
                                */
                {

                    if(grille[colonne][ligne].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 1][ligne].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 2][ligne].joueur == autreJoueur || grille[colonne + 2][ligne].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne].joueur == autreJoueur || grille[colonne + 3][ligne].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 4][ligne].joueur == autreJoueur || grille[colonne + 4][ligne].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 4][ligne].joueur != 0)
                        abandonneStrat = 1;



                    if(grille[colonne + 1][ligne + 1].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 2][ligne + 1].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne + 1].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 4][ligne + 1].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 4][ligne + 1].joueur != 0)
                        abandonneStrat = 1;



                    if(grille[colonne + 1][ligne + 2].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne + 2].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 2][ligne + 2].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne + 2].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne + 2].joueur == 0)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne + 2].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 4][ligne + 2].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 4][ligne + 2].joueur != 0)
                        abandonneStrat = 1;


                    if(abandonneStrat)
                    {
                        abandonneStrat = 0;
                    }
                    else
                    {
                        if(pionDejaPlace == pionDejaPlaceMax)
                        {
                            tailleTableau++;
                            stratPossible = realloc(stratPossible, sizeof(int) * 3 * tailleTableau);
                        }
                        else if(pionDejaPlace > pionDejaPlaceMax)
                        {
                            tailleTableau = 1;
                            stratPossible = realloc(stratPossible, sizeof(int) * 3 * tailleTableau);
                            pionDejaPlaceMax = pionDejaPlace;
                        }

                        if(pionDejaPlace == pionDejaPlaceMax) // on ajoute une stratégie a la liste des tratégie possibles
                        {
                            stratPossible[tailleTableau - 1].colonne = colonne;
                            stratPossible[tailleTableau - 1].ligne = ligne;
                            stratPossible[tailleTableau - 1].type = 3;
                        }
                    }

                    pionDejaPlace = 0;
                }

                //inversé 3
                                /*
                                  -
                                0 - 0 0
                                x x x 0
                                s s s x 0
                                */
                {

                    if(grille[colonne][ligne].joueur == autreJoueur || grille[colonne][ligne].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 1][ligne].joueur == autreJoueur || grille[colonne + 1][ligne].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 2][ligne].joueur == autreJoueur || grille[colonne + 2][ligne].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 4][ligne].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 4][ligne].joueur != 0)
                        abandonneStrat = 1;



                    if(grille[colonne][ligne + 1].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 1][ligne + 1].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 2][ligne + 1].joueur == autreJoueur)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne + 1].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne + 1].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne + 1].joueur != 0)
                        abandonneStrat = 1;



                    if(grille[colonne][ligne + 2].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne][ligne + 2].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 1][ligne + 2].joueur == 0)
                        pionDejaPlace++;
                    else if(grille[colonne + 1][ligne + 2].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 2][ligne + 2].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 2][ligne + 2].joueur != 0)
                        abandonneStrat = 1;

                    if(grille[colonne + 3][ligne + 2].joueur == bot)
                        pionDejaPlace++;
                    else if(grille[colonne + 3][ligne + 2].joueur != 0)
                        abandonneStrat = 1;


                    if(abandonneStrat)
                    {
                        abandonneStrat = 0;
                    }
                    else
                    {
                        if(pionDejaPlace == pionDejaPlaceMax)
                        {
                            tailleTableau++;
                            stratPossible = realloc(stratPossible, sizeof(int) * 3 * tailleTableau);
                        }
                        else if(pionDejaPlace > pionDejaPlaceMax)
                        {
                            tailleTableau = 1;
                            stratPossible = realloc(stratPossible, sizeof(int) * 3 * tailleTableau);
                            pionDejaPlaceMax = pionDejaPlace;
                        }

                        if(pionDejaPlace == pionDejaPlaceMax) // on ajoute une stratégie a la liste des tratégie possibles
                        {
                            stratPossible[tailleTableau - 1].colonne = colonne;
                            stratPossible[tailleTableau - 1].ligne = ligne;
                            stratPossible[tailleTableau - 1].type = -3;
                        }
                    }

                    pionDejaPlace = 0;
                }

            }
        }
    }

    fprintf(fDebug,"ressemblance %d\n", pionDejaPlaceMax);
    sprintf(debugTexte[6].txt,"ressemblance %d", pionDejaPlaceMax);

    for(int i = 0;i < tailleTableau;i++)
    {
        fprintf(fDebug,"choix %d: %d, %d, %d\n",i+1, stratPossible[i].colonne, stratPossible[i].ligne, stratPossible[i].type);
        DEBUG(" ")
    }
    DEBUG("\n\n")

    if(tailleTableau)
    {
        int stratChoisie = (rand() % tailleTableau);
        stratActive->colonne = stratPossible[stratChoisie].colonne;
        stratActive->ligne = stratPossible[stratChoisie].ligne;
        stratActive->type = stratPossible[stratChoisie].type;
    }

    pionDejaPlaceMax = 0;
    free(stratPossible);
}

// permet au bot d'appliquer sa strategies
int strategie(int bot, caseGrille grille[9][9], blkList blacklist[7], strat *stratActive)
{

    int stop = 0;
    int nombreErreur = 0;
    int *erreur = NULL; /* stoque dynamiquement chaques erreurs:
                            -2 = normal
                            -1 = pion mal placé
                            0 - 4 = blacklist*/
    erreur = malloc(sizeof(int));
    *erreur = -2;
    erreur = checStrat(bot, grille, blacklist, stratActive, &nombreErreur, erreur);
                                                                /*
                                                                    valeur:
                                                                        - "-2" -> normal
                                                                        - "-1" -> erreur placement pion
                                                                        - "0 à 4" -> erreur blacklist
                                                                */


    int *colonneTrouve = NULL;
    colonneTrouve = malloc(sizeof(int));

    int nombreColonneTrouve = 0;


    int colonneABlacklist[9] = {0};
    int nombreColonneABlacklist = 0;

    int support = 1;    /*
                        On prefere placer des pion important que des pions support.
                        Cette variable indique si un pion important a déjà ete placé ce qui empéchera d'ajouter un pion support a la selection de fin.*/

    int autreJoueur = 0;
    if(bot == 1)
        autreJoueur = 2;
    else
        autreJoueur = 1;

    if(erreur[0] == -1){// erreur de placement
        stop = 1;
    }
    else if(nombreErreur){
        for(int i = 0; i < nombreErreur; i++){
            if(blacklist[erreur[i]].type == 1 /*&& blacklist[erreur[i]].joueur != autreJoueur*/){
                stop = 1;
            }
        }
    }


    /*sprintf(debugTexte[6].txt,"changement de strat? %d", stop);*/

    if(stop)
    {
        stratActive->type = 0;
        stratActive->colonne = 0;
        stratActive->ligne = 0;

        return -1;
    }


    // on applique la strat
    int complet = 0; // complet indique que la strat est terminé, le bot va ainsi jouer au endroit critiques

    switch(stratActive->type)
    {

        case 1:
        {
            /*
            0
            x -
            0 - 0 0
            x - x 0
            */

            // première colonne
            if(grille[stratActive->colonne][stratActive->ligne + 3].joueur == 0)
            {
                if(grille[stratActive->colonne][stratActive->ligne + 2].joueur != 0)
                {
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne;
                }
                else
                {
                    if(grille[stratActive->colonne][stratActive->ligne + 1].joueur != 0)
                    {
                        nombreColonneABlacklist++;
                        colonneABlacklist[stratActive->colonne] = 3;
                    }
                    else
                    {
                        if(grille[stratActive->colonne][stratActive->ligne].joueur != 0)
                        {
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne;
                        }
                        else if(stratActive->ligne == 0 || grille[stratActive->colonne][stratActive->ligne - 1].joueur != 0)
                        {
                            nombreColonneABlacklist++;
                            colonneABlacklist[stratActive->colonne] = 3;
                        }
                    }
                }
            }
            else
                complet++;


            // deuxième colonne
            nombreColonneABlacklist++;
            colonneABlacklist[stratActive->colonne + 1] = 3;
            complet++;


            // troisième colonne
            if(grille[stratActive->colonne + 2][stratActive->ligne + 1].joueur == 0)
            {
                if(grille[stratActive->colonne + 2][stratActive->ligne].joueur != 0)
                {
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 2;
                }
                else if(stratActive->ligne == 0 || grille[stratActive->colonne + 2][stratActive->ligne - 1].joueur != 0)
                {
                    nombreColonneABlacklist++;
                    colonneABlacklist[stratActive->colonne + 2] = 3;
                }
            }
            else
                complet++;


            // quatrième colonne
            if(grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur == 0)
            {
                if(grille[stratActive->colonne + 3][stratActive->ligne].joueur != 0)
                {
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 3;
                }
                else
                {
                    if(stratActive->ligne == 0 || grille[stratActive->colonne + 3][stratActive->ligne - 1].joueur != 0)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 3;
                    }
                    else if(stratActive->ligne == 1 || grille[stratActive->colonne + 3][stratActive->ligne - 2].joueur != 0)
                    {
                        nombreColonneABlacklist++;
                        colonneABlacklist[stratActive->colonne + 3] = 3;
                    }
                }
            }
            else
                complet++;


            if(complet == 4)
                return (stratActive->colonne + 1);
        }
        break;

        case -1:
        {
            /*
                  0
                - x
            0 0 - 0
            0 x - x
            */
            // première colonne
            if(grille[stratActive->colonne][stratActive->ligne + 1].joueur == 0)
            {
                if(grille[stratActive->colonne][stratActive->ligne].joueur != 0)
                {
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne;
                }
                else
                {
                    if(stratActive->ligne == 0 || grille[stratActive->colonne][stratActive->ligne - 1].joueur != 0)
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne;
                    }
                    else if(stratActive->ligne == 1 || grille[stratActive->colonne][stratActive->ligne - 2].joueur != 0)
                    {
                        nombreColonneABlacklist++;
                        colonneABlacklist[stratActive->colonne] = 3;
                    }
                }
            }
            else
                complet++;


            // deuxième colonne
            if(grille[stratActive->colonne + 1][stratActive->ligne + 1].joueur == 0)
            {
                if(grille[stratActive->colonne + 1][stratActive->ligne].joueur != 0)
                {
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 1;
                }
                else if(stratActive->ligne == 0 || grille[stratActive->colonne + 1][stratActive->ligne - 1].joueur != 0)
                {
                    nombreColonneABlacklist++;
                    colonneABlacklist[stratActive->colonne + 1] = 3;
                }
            }
            else
                complet++;



            // troisième colonne
            nombreColonneABlacklist++;
            colonneABlacklist[stratActive->colonne + 2] = 3;
            complet++;


            // quatrième colonne
            if(grille[stratActive->colonne + 3][stratActive->ligne + 3].joueur == 0)
            {
                if(grille[stratActive->colonne + 3][stratActive->ligne + 2].joueur != 0)
                {
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 3;
                }
                else
                {
                    if(grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur != 0)
                    {
                        nombreColonneABlacklist++;
                        colonneABlacklist[stratActive->colonne + 3] = 3;
                    }
                    else
                    {
                        if(grille[stratActive->colonne + 3][stratActive->ligne].joueur != 0)
                        {
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 3;
                        }
                        else if(stratActive->ligne == 0 || grille[stratActive->colonne + 3][stratActive->ligne - 1].joueur != 0)
                        {
                            nombreColonneABlacklist++;
                            colonneABlacklist[stratActive->colonne + 3] = 3;
                        }
                    }
                }
            }
            else
                complet++;


            if(complet == 4)
                return (stratActive->colonne + 2);
        }
        break;

        case 2:
        {
            /*
                  *
            - 0 0 0
            x x 0 x
            * s x 0
            */


            // première colonne
            nombreColonneABlacklist++;
            colonneABlacklist[stratActive->colonne] = 3;
            complet++;


            // deuxième colonne
            if(grille[stratActive->colonne + 1][stratActive->ligne + 2].joueur == 0)
            {
                if(grille[stratActive->colonne + 1][stratActive->ligne + 1].joueur != 0)
                {
                    if(support)
                    {
                        support = 0;
                        nombreColonneTrouve = 0;
                    }
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 1;
                }
                else
                {
                    if(grille[stratActive->colonne + 1][stratActive->ligne].joueur != 0)
                    {
                        nombreColonneABlacklist++;
                        colonneABlacklist[stratActive->colonne + 1] = 3;
                    }
                    else if(support && (stratActive->ligne == 0 || grille[stratActive->colonne + 1][stratActive->ligne - 1].joueur != 0))
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 1;
                    }
                }
            }
            else
                complet++;


            // troisième colonne
            if(grille[stratActive->colonne + 2][stratActive->ligne + 2].joueur == 0)
            {
                if(grille[stratActive->colonne + 2][stratActive->ligne + 1].joueur != 0)
                {
                    if(support)
                    {
                        support = 0;
                        nombreColonneTrouve = 0;
                    }
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 2;
                }
                else
                {
                    if(grille[stratActive->colonne + 2][stratActive->ligne].joueur != 0)
                    {
                        if(support)
                        {
                            support = 0;
                            nombreColonneTrouve = 0;
                        }
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 2;
                    }
                    else if(stratActive->ligne == 0 || grille[stratActive->colonne + 2][stratActive->ligne - 1].joueur != 0)
                    {
                        nombreColonneABlacklist++;
                        colonneABlacklist[stratActive->colonne + 2] = 3;
                    }
                }
            }
            else
                complet++;


            // quatrième colonne
            if(grille[stratActive->colonne + 3][stratActive->ligne + 2].joueur == 0)
            {
                if(grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur != 0)
                {
                    if(support)
                    {
                        support = 0;
                        nombreColonneTrouve = 0;
                    }
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 3;
                }
                else
                {
                    if(grille[stratActive->colonne + 3][stratActive->ligne].joueur != 0)
                    {
                        nombreColonneABlacklist++;
                        colonneABlacklist[stratActive->colonne + 3] = 3;
                    }
                    else
                    {
                        if(stratActive->ligne == 0 || grille[stratActive->colonne + 3][stratActive->ligne - 1].joueur != 0)
                        {
                            if(support)
                            {
                                support = 0;
                                nombreColonneTrouve = 0;
                            }
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 3;
                        }
                        else if(stratActive->ligne == 1 || grille[stratActive->colonne + 3][stratActive->ligne - 2].joueur != 0)
                        {
                            nombreColonneABlacklist++;
                            colonneABlacklist[stratActive->colonne + 3] = 3;
                        }
                    }
                }
            }
            else
                complet++;

            if(complet == 4)
                return (stratActive->colonne);
        }
        break;

        case -2:
        {
            /*
            *
            0 0 0 -
            x 0 x x
            0 x s *
            */


            // première colonne
            if(grille[stratActive->colonne][stratActive->ligne + 2].joueur == 0)
            {
                if(grille[stratActive->colonne][stratActive->ligne + 1].joueur != 0)
                {
                    if(support)
                    {
                        support = 0;
                        nombreColonneTrouve = 0;
                    }
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne;
                }
                else
                {
                    if(grille[stratActive->colonne][stratActive->ligne].joueur != 0)
                    {
                        nombreColonneABlacklist++;
                        colonneABlacklist[stratActive->colonne] = 3;
                    }
                    else
                    {
                        if(stratActive->ligne == 0 || grille[stratActive->colonne][stratActive->ligne - 1].joueur != 0)
                        {
                            if(support)
                            {
                                support = 0;
                                nombreColonneTrouve = 0;
                            }
                            nombreColonneTrouve++;
                            colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                            colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne;
                        }
                        else if(stratActive->ligne == 1 || grille[stratActive->colonne][stratActive->ligne - 2].joueur != 0)
                        {
                            nombreColonneABlacklist++;
                            colonneABlacklist[stratActive->colonne] = 3;
                        }
                    }
                }
            }
            else
                complet++;


            // deuxième colonne
            if(grille[stratActive->colonne + 1][stratActive->ligne + 2].joueur == 0)
            {
                if(grille[stratActive->colonne + 1][stratActive->ligne + 1].joueur != 0)
                {
                    if(support)
                    {
                        support = 0;
                        nombreColonneTrouve = 0;
                    }
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 1;
                }
                else
                {
                    if(grille[stratActive->colonne + 1][stratActive->ligne].joueur != 0)
                    {
                        if(support)
                        {
                            support = 0;
                            nombreColonneTrouve = 0;
                        }
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 1;
                    }
                    else if(stratActive->ligne == 0 || grille[stratActive->colonne + 1][stratActive->ligne - 1].joueur != 0)
                    {
                        nombreColonneABlacklist++;
                        colonneABlacklist[stratActive->colonne + 1] = 3;
                    }
                }
            }
            else
                complet++;


            // troisième colonne
            if(grille[stratActive->colonne + 2][stratActive->ligne + 2].joueur == 0)
            {
                if(grille[stratActive->colonne + 2][stratActive->ligne + 1].joueur != 0)
                {
                    if(support)
                    {
                        support = 0;
                        nombreColonneTrouve = 0;
                    }
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 2;
                }
                else
                {
                    if(grille[stratActive->colonne + 2][stratActive->ligne].joueur != 0)
                    {
                        nombreColonneABlacklist++;
                        colonneABlacklist[stratActive->colonne + 2] = 3;
                    }
                    else if(support && (stratActive->ligne == 0 || grille[stratActive->colonne + 2][stratActive->ligne - 1].joueur != 0))
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 2;
                    }
                }
            }
            else
                complet++;


            // quatrième colonne
            nombreColonneABlacklist++;
            colonneABlacklist[stratActive->colonne + 3] = 3;
            complet++;


            if(complet == 4)
                return (stratActive->colonne + 3);
        }
        break;

        case 3:
        {
            /*
                  -
              0 0 - 0
              0 x x x
            0 x s s s
            */

            // première colonne
            if(grille[stratActive->colonne][stratActive->ligne].joueur == 0)
            {
                if(stratActive->ligne == 0 || grille[stratActive->colonne][stratActive->ligne - 1].joueur != 0)
                {
                    if(support)
                    {
                        support = 0;
                        nombreColonneTrouve = 0;
                    }
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne;
                }
                else if(stratActive->ligne == 1 || grille[stratActive->colonne][stratActive->ligne - 2].joueur != 0)
                {
                    nombreColonneABlacklist++;
                    colonneABlacklist[stratActive->colonne] = 3;
                }
            }
            else
                complet++;


            // deuxième colonne
            if(grille[stratActive->colonne + 1][stratActive->ligne + 2].joueur == 0)
            {
                if(grille[stratActive->colonne + 1][stratActive->ligne + 1].joueur != 0)
                {
                    if(support)
                    {
                        support = 0;
                        nombreColonneTrouve = 0;
                    }
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 1;
                }
                else
                {
                    if(grille[stratActive->colonne + 1][stratActive->ligne].joueur != 0)
                    {
                        if(support)
                        {
                            support = 0;
                            nombreColonneTrouve = 0;
                        }
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 1;
                    }
                    else if(stratActive->ligne == 0 || grille[stratActive->colonne + 1][stratActive->ligne - 1].joueur != 0)
                    {
                        nombreColonneABlacklist++;
                        colonneABlacklist[stratActive->colonne + 1] = 3;
                    }
                }
            }
            else
                complet++;


            // troisième colonne
            if(grille[stratActive->colonne + 2][stratActive->ligne + 2].joueur == 0)
            {
                if(grille[stratActive->colonne + 2][stratActive->ligne + 1].joueur != 0)
                {
                    if(support)
                    {
                        support = 0;
                        nombreColonneTrouve = 0;
                    }
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 2;
                }
                else
                {
                    if(grille[stratActive->colonne + 2][stratActive->ligne].joueur != 0)
                    {
                        nombreColonneABlacklist++;
                        colonneABlacklist[stratActive->colonne + 2] = 3;
                    }
                    else if(support && (stratActive->ligne == 0 || grille[stratActive->colonne + 2][stratActive->ligne - 1].joueur != 0))
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 2;
                    }
                }
            }
            else
                complet++;


            // quatrième colonne
            if(grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur == 0)
            {
                if(grille[stratActive->colonne + 3][stratActive->ligne].joueur != 0)
                {
                    nombreColonneABlacklist++;
                    colonneABlacklist[stratActive->colonne + 3] = 3;
                }
                else if(support && (stratActive->ligne == 0 || grille[stratActive->colonne + 3][stratActive->ligne - 1].joueur != 0))
                {
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 3;
                }
            }
            else
            {
                nombreColonneABlacklist++;
                colonneABlacklist[stratActive->colonne + 3] = 3;
            }
            complet++;


            // cinquième colonne
            if(grille[stratActive->colonne + 4][stratActive->ligne + 2].joueur == 0)
            {
                if(grille[stratActive->colonne + 4][stratActive->ligne + 1].joueur != 0)
                {
                    if(support)
                    {
                        support = 0;
                        nombreColonneTrouve = 0;
                    }
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 4;
                }
                else
                {
                    if(grille[stratActive->colonne + 4][stratActive->ligne].joueur != 0)
                    {
                        nombreColonneABlacklist++;
                        colonneABlacklist[stratActive->colonne + 4] = 3;
                    }
                    else if(support && (stratActive->ligne == 0 || grille[stratActive->colonne + 4][stratActive->ligne - 1].joueur != 0))
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 4;
                    }
                }
            }
            else
                complet++;


            if(complet == 5)
                return (stratActive->colonne + 3);
        }
        break;

        case -3:
        {
            /*
              -
            0 - 0 0
            x x x 0
            s s s x 0
            */

            // première colonne
            if(grille[stratActive->colonne][stratActive->ligne + 2].joueur == 0)
            {
                if(grille[stratActive->colonne][stratActive->ligne + 1].joueur != 0)
                {
                    if(support)
                    {
                        support = 0;
                        nombreColonneTrouve = 0;
                    }
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne;
                }
                else
                {
                    if(grille[stratActive->colonne][stratActive->ligne].joueur != 0)
                    {
                        nombreColonneABlacklist++;
                        colonneABlacklist[stratActive->colonne] = 3;
                    }
                    else if(support && (stratActive->ligne == 0 || grille[stratActive->colonne][stratActive->ligne - 1].joueur != 0))
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne;
                    }
                }
            }
            else
                complet++;


            // deuxième colonne
            if(grille[stratActive->colonne + 1][stratActive->ligne + 1].joueur == 0)
            {
                if(grille[stratActive->colonne + 1][stratActive->ligne].joueur != 0)
                {
                    nombreColonneABlacklist++;
                    colonneABlacklist[stratActive->colonne + 1] = 3;
                }
                else if(support && (stratActive->ligne == 0 || grille[stratActive->colonne + 1][stratActive->ligne - 1].joueur != 0))
                {
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 1;
                }
            }
            else
            {
                nombreColonneABlacklist++;
                colonneABlacklist[stratActive->colonne + 1] = 3;
            }
            complet++;


            // troisième colonne
            if(grille[stratActive->colonne + 2][stratActive->ligne + 2].joueur == 0)
            {
                if(grille[stratActive->colonne + 2][stratActive->ligne + 1].joueur != 0)
                {
                    if(support)
                    {
                        support = 0;
                        nombreColonneTrouve = 0;
                    }
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 2;
                }
                else
                {
                    if(grille[stratActive->colonne + 2][stratActive->ligne].joueur != 0)
                    {
                        nombreColonneABlacklist++;
                        colonneABlacklist[stratActive->colonne + 2] = 3;
                    }
                    else if(support && (stratActive->ligne == 0 || grille[stratActive->colonne + 2][stratActive->ligne - 1].joueur != 0))
                    {
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 2;
                    }
                }
            }
            else
                complet++;


            // quatrième colonne
            if(grille[stratActive->colonne + 3][stratActive->ligne + 2].joueur == 0)
            {
                if(grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur != 0)
                {
                    if(support)
                    {
                        support = 0;
                        nombreColonneTrouve = 0;
                    }
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 3;
                }
                else
                {
                    if(grille[stratActive->colonne + 3][stratActive->ligne].joueur != 0)
                    {
                        if(support)
                        {
                            support = 0;
                            nombreColonneTrouve = 0;
                        }
                        nombreColonneTrouve++;
                        colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                        colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 3;
                    }
                    else if(stratActive->ligne == 0 || grille[stratActive->colonne + 3][stratActive->ligne - 1].joueur != 0)
                    {
                        nombreColonneABlacklist++;
                        colonneABlacklist[stratActive->colonne + 3] = 3;
                    }
                }
            }
            else
                complet++;


            // cinquième colonne
            if(grille[stratActive->colonne + 4][stratActive->ligne].joueur == 0)
            {
                if(stratActive->ligne == 0 || grille[stratActive->colonne + 4][stratActive->ligne - 1].joueur != 0)
                {
                    if(support)
                    {
                        support = 0;
                        nombreColonneTrouve = 0;
                    }
                    nombreColonneTrouve++;
                    colonneTrouve = realloc(colonneTrouve, sizeof(int) * nombreColonneTrouve);
                    colonneTrouve[nombreColonneTrouve - 1] = stratActive->colonne + 4;
                }
                else if(stratActive->ligne == 1 || grille[stratActive->colonne + 4][stratActive->ligne - 2].joueur != 0)
                {
                    nombreColonneABlacklist++;
                    colonneABlacklist[stratActive->colonne + 4] = 3;
                }
            }
            else
                complet++;


            if(complet == 5)
                return (stratActive->colonne + 1);
        }
        break;

    }


    DEBUG("colonnes trouvée\n")

    // on vérifie que l'on peut blacklist les colonnes de la stratégie sans bloquer le jeu
    int colonneLibre = 7;

    for(int colonne = 0; colonne < 7; colonne++)
    {
        if(blacklist[colonne].type)
            colonneLibre--;
    }

    if((colonneLibre - nombreColonneABlacklist) > 0)
    {
        for(int colonne = 0; colonne < 7; colonne++)
        {
            if(colonneABlacklist[colonne])
                blacklist[colonne].type = colonneABlacklist[colonne];
        }
    }

    DEBUG("blacklisté\n")
    int colonne = -1;

    if(nombreColonneTrouve)
        colonne = colonneTrouve[(rand() % nombreColonneTrouve)]; //choisit parmit les colonnes trouvés

    free(colonneTrouve);
    free(erreur);

    DEBUG("colonne jouée \n")

    return colonne;
}

// verifie que la stratégie est encore applicable
int* checStrat(int bot, caseGrille grille[9][9], blkList blacklist[7], strat *stratActive, int *nombreErreur, int *erreur)
{
            /*
                retour:
                    - "-2" -> normal
                    - "-1" -> erreur placement pion
                    - "0 à 4" -> erreur blacklist
            */


    int autreJoueur = 0;
    if(bot == 1)
        autreJoueur = 2;
    else
        autreJoueur = 1;


    // certain pion sont mal placé
    switch(stratActive->type)
    {
        case 1:
        {
            /*
            0
            x -
            0 - 0 0
            x - x 0
            */
            if(grille[stratActive->colonne][stratActive->ligne].joueur != autreJoueur && grille[stratActive->colonne][stratActive->ligne].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 1][stratActive->ligne].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 2][stratActive->ligne].joueur != autreJoueur && grille[stratActive->colonne + 2][stratActive->ligne].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 3][stratActive->ligne].joueur != bot && grille[stratActive->colonne + 3][stratActive->ligne].joueur != 0)
                *erreur = -1;



            else if(grille[stratActive->colonne][stratActive->ligne + 1].joueur != bot && grille[stratActive->colonne][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 1][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 2][stratActive->ligne + 1].joueur != bot && grille[stratActive->colonne + 2][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur != bot && grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;



            else if(grille[stratActive->colonne][stratActive->ligne + 2].joueur != autreJoueur && grille[stratActive->colonne][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 1][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;



            else if(grille[stratActive->colonne][stratActive->ligne + 3].joueur != bot && grille[stratActive->colonne][stratActive->ligne + 3].joueur != 0)
                *erreur = -1;
        }
        break;

        case -1:
        {
            /*
                  0
                - x
            0 0 - 0
            0 x - x
            */
            if(grille[stratActive->colonne][stratActive->ligne].joueur != bot && grille[stratActive->colonne][stratActive->ligne].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 1][stratActive->ligne].joueur != autreJoueur && grille[stratActive->colonne + 1][stratActive->ligne].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 2][stratActive->ligne].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 3][stratActive->ligne].joueur != autreJoueur && grille[stratActive->colonne + 3][stratActive->ligne].joueur != 0)
                *erreur = -1;



            else if(grille[stratActive->colonne][stratActive->ligne + 1].joueur != bot && grille[stratActive->colonne][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 1][stratActive->ligne + 1].joueur != bot && grille[stratActive->colonne + 1][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 2][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur != bot && grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;



            else if(grille[stratActive->colonne + 2][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 3][stratActive->ligne + 2].joueur != autreJoueur && grille[stratActive->colonne + 3][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;



            else if(grille[stratActive->colonne + 3][stratActive->ligne + 3].joueur != bot && grille[stratActive->colonne + 3][stratActive->ligne + 3].joueur != 0)
                *erreur = -1;

        }
        break;

        case 2:
        {
            /*
                  *
            - 0 0 0
            x x 0 x
            * s x 0
            */


            if(grille[stratActive->colonne + 2][stratActive->ligne].joueur != autreJoueur && grille[stratActive->colonne + 2][stratActive->ligne].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 3][stratActive->ligne].joueur != bot && grille[stratActive->colonne + 3][stratActive->ligne].joueur != 0)
                *erreur = -1;



            else if(grille[stratActive->colonne][stratActive->ligne + 1].joueur != autreJoueur && grille[stratActive->colonne][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 1][stratActive->ligne + 1].joueur != autreJoueur && grille[stratActive->colonne + 1][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 2][stratActive->ligne + 1].joueur != bot && grille[stratActive->colonne + 2][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur != autreJoueur && grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;



            else if(grille[stratActive->colonne][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 1][stratActive->ligne + 2].joueur != bot && grille[stratActive->colonne + 1][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 2][stratActive->ligne + 2].joueur != bot && grille[stratActive->colonne + 2][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 3][stratActive->ligne + 2].joueur != bot && grille[stratActive->colonne + 3][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;
        }
        break;

        case -2:
        {
            /*
            *
            0 0 0 -
            x 0 x x
            0 x s *
            */

            if(grille[stratActive->colonne][stratActive->ligne].joueur != bot && grille[stratActive->colonne][stratActive->ligne].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 1][stratActive->ligne].joueur != autreJoueur && grille[stratActive->colonne + 1][stratActive->ligne].joueur != 0)
                *erreur = -1;



            else if(grille[stratActive->colonne][stratActive->ligne + 1].joueur != autreJoueur && grille[stratActive->colonne][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 1][stratActive->ligne + 1].joueur != bot && grille[stratActive->colonne + 1][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 2][stratActive->ligne + 1].joueur != autreJoueur && grille[stratActive->colonne + 2][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur != autreJoueur && grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;



            else if(grille[stratActive->colonne][stratActive->ligne + 2].joueur != bot && grille[stratActive->colonne][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 1][stratActive->ligne + 2].joueur != bot && grille[stratActive->colonne + 1][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 2][stratActive->ligne + 2].joueur != bot && grille[stratActive->colonne + 2][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 3][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;
        }
        break;

        case 3:
        {
            /*
                  -
              0 0 - 0
              0 x x x
            0 x s s s
            */

            if(grille[stratActive->colonne][stratActive->ligne].joueur != bot && grille[stratActive->colonne][stratActive->ligne].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 1][stratActive->ligne].joueur != autreJoueur && grille[stratActive->colonne + 1][stratActive->ligne].joueur != 0)
                *erreur = -1;



            else if(grille[stratActive->colonne + 1][stratActive->ligne + 1].joueur != bot && grille[stratActive->colonne + 1][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 2][stratActive->ligne + 1].joueur != autreJoueur && grille[stratActive->colonne + 2][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur != autreJoueur && grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 4][stratActive->ligne + 1].joueur != autreJoueur && grille[stratActive->colonne + 4][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;



            else if(grille[stratActive->colonne + 1][stratActive->ligne + 2].joueur != bot && grille[stratActive->colonne + 1][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 2][stratActive->ligne + 2].joueur != bot && grille[stratActive->colonne + 2][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 3][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 4][stratActive->ligne + 2].joueur != bot && grille[stratActive->colonne + 4][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;
        }
        break;

        case -3:
        {
            /*
              -
            0 - 0 0
            x x x 0
            s s s x 0
            */

            if(grille[stratActive->colonne + 3][stratActive->ligne].joueur != autreJoueur && grille[stratActive->colonne + 3][stratActive->ligne].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 4][stratActive->ligne].joueur != bot && grille[stratActive->colonne + 4][stratActive->ligne].joueur != 0)
                *erreur = -1;



            else if(grille[stratActive->colonne][stratActive->ligne + 1].joueur != autreJoueur && grille[stratActive->colonne][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 1][stratActive->ligne + 1].joueur != autreJoueur && grille[stratActive->colonne + 1][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 2][stratActive->ligne + 1].joueur != autreJoueur && grille[stratActive->colonne + 2][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur != bot && grille[stratActive->colonne + 3][stratActive->ligne + 1].joueur != 0)
                *erreur = -1;



            else if(grille[stratActive->colonne][stratActive->ligne + 2].joueur != bot && grille[stratActive->colonne][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 1][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 2][stratActive->ligne + 2].joueur != bot && grille[stratActive->colonne + 2][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;

            else if(grille[stratActive->colonne + 3][stratActive->ligne + 2].joueur != bot && grille[stratActive->colonne + 3][stratActive->ligne + 2].joueur != 0)
                *erreur = -1;
        }
        break;
    }

    if(*erreur == -1) // si un seul pion est mal placé, on annule la stratégie, pas besoin de plus d'erreurs
    {
        *nombreErreur = 1;
    }
    else
    {
        // la stratégie est dans une zone blackliste
        for(int i = (abs(stratActive->type == 3))? 4 : 3; i >= 0; i--){
            if(blacklist[stratActive->colonne + i].type){
                *nombreErreur = (*nombreErreur) + 1;
                erreur = realloc(erreur, sizeof(int) * (*nombreErreur));
                erreur[*nombreErreur - 1] = stratActive->colonne + i;
            }
        }
    }

    sprintf(debugTexte[11].txt,"nombre d'erreurs de strategie = %d ", *nombreErreur);

    char number[4] = {0};
    number[0] = '\0';


    sprintf(debugTexte[12].txt,"Erreurs:");
    for(int i = 0; i < (*nombreErreur); i++){
        itoa(erreur[i], number, 10);
        strcat(debugTexte[12].txt, number);
        strcat(debugTexte[12].txt, ", ");
    }

    return erreur;
}

























