#ifndef ABZ_IMAGE

#define ABZ_IMAGE

#include <SDL2/SDL.h>

// AUTRE
typedef struct Autre Autre;
struct Autre
{
    SDL_Texture* croix;
    SDL_Texture* CHARGEMENT;
};



// NOMBRES
typedef struct Nombres Nombres;
struct Nombres
{
    SDL_Texture* nb_0;
    SDL_Texture* nb_1;
    SDL_Texture* nb_2;
    SDL_Texture* nb_3;
    SDL_Texture* nb_4;
    SDL_Texture* nb_5;
    SDL_Texture* nb_6;
    SDL_Texture* nb_7;
    SDL_Texture* nb_8;
    SDL_Texture* nb_9;
};



// PARAMETRE
typedef struct JoueurCommence JoueurCommence;
struct JoueurCommence
{
    SDL_Texture* joueurCommence_bg;

    SDL_Texture* joueur1Commence;
    SDL_Texture* joueur2Commence;
    SDL_Texture* joueur3Commence;

    SDL_Texture* joueur1Commence_actif;
    SDL_Texture* joueur2Commence_actif;
    SDL_Texture* joueur3Commence_actif;
};

typedef struct Parametre Parametre;
struct Parametre
{
    SDL_Texture* parametre_logo;
    SDL_Texture* parametre_bg;

    JoueurCommence JoueurCommence;
};



// MENU
typedef struct Grillage Grillage;
struct Grillage
{
    SDL_Texture* menu_Grillage;
    SDL_Texture* menu_Grillage1;
    SDL_Texture* menu_Grillage2;
    SDL_Texture* menu_BordureGrillage;
};

typedef struct Bouton Bouton;
struct Bouton
{
    SDL_Texture* menu_Reprendre;
    SDL_Texture* menu_Rejouer;
    SDL_Texture* menu_RetourAccueil;
    SDL_Texture* menu_Quitter;
};

typedef struct Menu Menu;
struct Menu
{
    SDL_Texture* menu_logo;

    Grillage Grillage;

    Bouton Bouton;
};


// ACCUEIL
typedef struct Accueil_0 Accueil_0;
struct Accueil_0
{
    SDL_Texture* accueil_APPUYEZ_SUR_UNE_TOUCHE_POUR_JOUER;
    SDL_Texture* accueil_jouer;
};

typedef struct Accueil_1 Accueil_1;
struct Accueil_1
{
    // hardcore
    SDL_Texture* hardcore_inactif;
    SDL_Texture* hardcore_1;
    SDL_Texture* hardcore_2;

    // mode
    SDL_Texture* accueil_mode1;
    SDL_Texture* accueil_mode2;
    SDL_Texture* accueil_mode3;
    SDL_Texture* accueil_mode4;
};

typedef struct Accueil_2 Accueil_2;
struct Accueil_2
{
    // autre
    SDL_Texture* accueil_SELECTIONNEZ_UNE_DIFFICULTEE;
    SDL_Texture* accueil_SELECTIONNEZ_UNE_DIFFICULTEE_efface;

    // background
    SDL_Texture* accueil_botJaune;
    SDL_Texture* accueil_botRouge;
    SDL_Texture* accueil_bot_inactif;

    // bot actif
    SDL_Texture* accueil_botFacile_actif;
    SDL_Texture* accueil_botNormal_actif;
    SDL_Texture* accueil_botDifficile_actif;

    // bot inactif
    SDL_Texture* accueil_botFacile_inactif;
    SDL_Texture* accueil_botNormal_inactif;
    SDL_Texture* accueil_botDifficile_inactif;
};

typedef struct Accueil Accueil;
struct Accueil
{
    SDL_Texture* accueil_bg;
    SDL_Texture* accueil_retour;
    SDL_Texture* accueil_valide;

    Accueil_0 Accueil_0;
    Accueil_1 Accueil_1;
    Accueil_2 Accueil_2;

};



// JEU
typedef struct Joueur Joueur;
struct Joueur
{
    // normal
    SDL_Texture* joueur1;
    SDL_Texture* joueur2;
    SDL_Texture* joueur3;
    SDL_Texture* bot1;
    SDL_Texture* bot2;

    // actif
    SDL_Texture* joueur1_actif;
    SDL_Texture* joueur2_actif;
    SDL_Texture* joueur3_actif;
    SDL_Texture* bot1_actif;
    SDL_Texture* bot2_actif;
};

typedef struct Grille Grille;
struct Grille
{
    SDL_Texture* grille7x6;
    SDL_Texture* grille9x8;
};

typedef struct Hardcore_ Hardcore_;
struct Hardcore_
{
    SDL_Texture* hardcore_bg;

    SDL_Texture* hardcore_Temps_Vert;
    SDL_Texture* hardcore_Temps_Orange;
    SDL_Texture* hardcore_Temps_Rouge;
};

typedef struct Colonne Colonne;
struct Colonne
{
    SDL_Texture* jeu_Colonne_Desactive;

    SDL_Texture* jeu_ColonneTaille1_Active;
    SDL_Texture* jeu_ColonneTaille2_Active;
    SDL_Texture* jeu_ColonneTaille3_Active;
    SDL_Texture* jeu_ColonneTaille4_Active;
    SDL_Texture* jeu_ColonneTaille5_Active;
    SDL_Texture* jeu_ColonneTaille6_Active;
    SDL_Texture* jeu_ColonneTaille7_Active;
    SDL_Texture* jeu_ColonneTaille8_Active;
};

typedef struct Pions Pions;
struct Pions
{
    // normal
    SDL_Texture* pion1;
    SDL_Texture* pion2;
    SDL_Texture* pion3;

    // joue
    SDL_Texture* pion1_joue;
    SDL_Texture* pion2_joue;
    SDL_Texture* pion3_joue;

    // gagne
    SDL_Texture* pion1_gagne;
    SDL_Texture* pion2_gagne;
    SDL_Texture* pion3_gagne;
};

typedef struct Jeu Jeu;
struct Jeu
{
    SDL_Texture* jeu_bg;
    SDL_Texture* jeu_retour;

    Joueur Joueur;

    Grille Grille;

    Hardcore_ Hardcore_;

    Colonne Colonne;

    Pions Pions;
};



// FIN
typedef struct Fin Fin;
struct Fin
{
    SDL_Texture* fin_LE_JOUEUR;
    SDL_Texture* fin_GAGNE;
    SDL_Texture* fin_EGALITE;
};


// structure qui stoque l'adresse des images en mémoire
typedef struct Images Images;
struct Images
{
    Autre Autre;

    Nombres Nombres;

    Parametre Parametre;

    Menu Menu;

    Accueil Accueil;

    Jeu Jeu;

    Fin Fin;
};


void changeDest(SDL_Rect* dest, int x, int y);


// charge une image et renvoit un pointeur dessus
SDL_Texture* chargeImage(const char* localisation, SDL_Renderer* pRenderer, FILE* fDebug);

// supprime (si elle existe) la texture demande
void supprimeTexture(SDL_Texture* pTexture);

// affiche une texture a l'endroit demande
void afficheImage(SDL_Texture* pTexture, SDL_Rect* dest, SDL_Renderer* pRenderer, FILE* fDebug);
// affiche une texture a l'endroit demande en la centrant
void afficheImage_Centre(SDL_Texture* pTexture, SDL_Rect* dest, SDL_Renderer* pRenderer, FILE* fDebug);

#endif // ABZ_IMAGE
