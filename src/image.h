#ifndef ABZ_IMAGE

#define ABZ_IMAGE

#include <SDL2/SDL.h>

#define NBR_IMAGE 100 // 91
#define D_SECTION_AUTRE 1
#define F_SECTION_AUTRE 20
#define D_SECTION_ACCUEIL 21
#define F_SECTION_ACCUEIL 42
#define D_SECTION_JEU 43
#define F_SECTION_JEU 90


typedef enum Section{
    S_AUTRE, S_ACCUEIL, S_JEU
}Section;


typedef enum Centre{
    OUI = 1, NON = 0
}Centre;


typedef enum En_Image{
    chargement,

    // AUTRE
    croix,
    // nombres
    nb_0,
    nb_1,
    nb_2,
    nb_3,
    nb_4,
    nb_5,
    nb_6,
    nb_7,
    nb_8,
    nb_9,
    // parametre
    parametre_logo,
    parametre_bg,

    joueurCommence_bg,
    joueur1Commence,
    joueur2Commence,
    joueur3Commence,
    joueur1Commence_actif,
    joueur2Commence_actif,
    joueur3Commence_actif,

    // ACCUEIL
    accueil_bg,
    accueil_retour,
    accueil_valide,

    //0
    accueil_APPUYEZ_SUR_UNE_TOUCHE_POUR_JOUER,

    //1
    // hardcore
    hardcore_inactif,
    hardcore_1,
    hardcore_2,
    // mode
    accueil_mode1,
    accueil_mode2,
    accueil_mode3,
    accueil_mode4,

    //2
    // autre
    accueil_SELECTIONNEZ_UNE_DIFFICULTEE,
    accueil_SELECTIONNEZ_UNE_DIFFICULTEE_efface,
    // background
    accueil_botJaune,
    accueil_botRouge,
    accueil_bot_inactif,
    // bot actif
    accueil_botFacile_actif,
    accueil_botNormal_actif,
    accueil_botDifficile_actif,
    // bot inactif
    accueil_botFacile_inactif,
    accueil_botNormal_inactif,
    accueil_botDifficile_inactif,

    // JEU
    // menu
    menu_logo,

    menu_Grillage,
    menu_Grillage1,
    menu_Grillage2,
    menu_BordureGrillage,

    menu_Reprendre,
    menu_Rejouer,
    menu_RetourAccueil,
    menu_Quitter,

    //jeu
    jeu_bg,
    jeu_retour,

    grille7x6,
    grille9x8,

    hardcore_bg,
    hardcore_Temps_Vert,
    hardcore_Temps_Orange,
    hardcore_Temps_Rouge,

    // normal
    joueur1,
    joueur2,
    joueur3,
    bot1,
    bot2,
    // actif
    joueur1_actif,
    joueur2_actif,
    joueur3_actif,
    bot1_actif,
    bot2_actif,

    jeu_Colonne_Desactive,
    jeu_ColonneTaille1_Active,
    jeu_ColonneTaille2_Active,
    jeu_ColonneTaille3_Active,
    jeu_ColonneTaille4_Active,
    jeu_ColonneTaille5_Active,
    jeu_ColonneTaille6_Active,
    jeu_ColonneTaille7_Active,
    jeu_ColonneTaille8_Active,

    // normal
    pion1,
    pion2,
    pion3,
    // joue
    pion1_joue,
    pion2_joue,
    pion3_joue,
    // gagne
    pion1_gagne,
    pion2_gagne,
    pion3_gagne,

    // FIN
    fin_LE_JOUEUR,
    fin_GAGNE,
    fin_EGALITE,

}En_Image;

typedef struct InfoImage{
    SDL_Texture* pTexture;
    char localisation[100]; //localisation est la l'emplacement de l'image a charger dans les fichiers

    unsigned int temps;  // permet de faire des animations
    int info;   // permet de garder divers info
} InfoImage;

typedef struct Image{       // structure qui stoque les données des images en mémoire
    int section_autre, section_acceuil, section_jeu;
    InfoImage image[NBR_IMAGE];

} Image;


void Image_localisation(Image* images); // attribue la localisation de chaques images
void res_Image(Image* images, int decharge);

void chargeSectionImage(Section section, Image* images, SDL_Renderer* pRenderer, FILE* fDebug);     // charge une section d'image en mémoire
void chargeImage(InfoImage* image, SDL_Renderer* pRenderer, FILE* fDebug);                          // charge une image en mémoire
void supprimeTexture(SDL_Texture* pTexture);                                                        // supprime (si elle existe) la texture demande
void afficheImage(InfoImage image, int x, int y, Centre centrer, SDL_Renderer* pRenderer, FILE* fDebug);    // affiche une image (peut être centrée)

#endif // ABZ_IMAGE
