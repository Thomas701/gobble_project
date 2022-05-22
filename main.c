/**
 * \file main.c
 * \brief Fonction principale, entrée du programme.
 * \author DUPOIS Thomas 
 * \author VILLEPREUX Thibault 
 * 
 */


#ifdef WINDOWS
//Chemin d'accès bibliothèques SDL2 pour WINDOWS.
#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/SDL2/SDL_mixer.h"

#else
//Chemin d'accès bibliothèques SDL2 pour LINUX.
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#endif

//Chemin d'accès bibliothèques standards pour LINUX & WINDOWS.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 * \def HEIGHT 
 * \brief Représente la taille de la fenêtre en largeur.
 */
#define HEIGHT 800 // hauteur fenetre

/**
 * \def WIDTH
 * \brief Représente la taille de la fenêtre en hauteur.
 */
#define WIDTH  1280 // largeur fenetre

/** \def N
 * \brief Représente la taille de la grille et le nombres de cases vaut N*N.
 */
#define N 3

/** \def Z3
 * \brief Représente le zoom en interface graphique pour un pion situé sur la ligne 3 (la dernière).
 */
#define Z3 0.77

/** \def Z2
 * \brief Représente le zoom en interface graphique pour un pion situé sur la ligne 2 (milieu).
 */
#define Z2 0.86

/** \def D
 * \brief Représente la restriction de distance d'une case. 0 si pas de restriction sinon 1.
 */
#define D 1

//Chemin d'accès de nos headers
#include "headers/fonction.h"
#include "headers/get.h"
#include "headers/creation.h"
#include "headers/demande.h"
#include "headers/error.h"
#include "headers/graphique.h"
#include "headers/init.h"
#include "headers/print.h"
#include "headers/saveFile.h"
#include "headers/verification.h"
#include "headers/free.h"
#include "headers/liste.h"
#include "headers/ia.h"

// inclusions des src

#include "src/fonction.c"
#include "src/get.c"
#include "src/demande.c"
#include "src/verification.c"
#include "src/graphique.c"
#include "src/creation.c"
#include "src/print.c"
#include "src/free.c"
#include "src/init.c"
#include "src/saveFile.c"
#include "src/error.c"
#include "src/liste.c"
#include "src/ia.c"

/**
 * \fn int main(int argc, char ** argv)
 * \brief Fonction principale, entrée du programme.
 * 
 * \param[in] int argc : compte le nombre de paramètre de l'éxecutable.
 * \param[in] char ** argv : stocke sous forme de chaine de caractères les paramètres données lors de l'éxecution.\n
 * Par exemple "./main -c" ou "./main --console" lance le jeu uniquement dans le terminal.\n
 * Par défault, il se lance en interface graphique.\n
 * \return EXIT_SUCCESS - Arrêt **normal** du programme.\n
 * \return EXIT_FAILURE - Arrêt **anormal** du programme (probleme provenant dans la plus cas des cas de l'initialisation de la SDL2 ou des textures).\n
 *
 * \author DUPOIS Thomas & VILLEPREUX Thibault
 */
int main(int argc, char ** argv){
  srand(time(NULL));
  char ** pileJ1 = createStack('b'); char ** pileJ2 = createStack('n');  // pile joueur 1 & 2
  char *** map3D = createMap();      char ** map2D = createMap2D();      // map 3D et 2D, pour stocker pion, 2D pour parcours plus rapide
  initMap(map3D);                    initMap2D(map2D, map3D);            // remplie la map que du char '0'
  int statut = EXIT_FAILURE ;                                            // par default jusqu'à preuve du contraire le programme n'est pas 
                                                                         //arrivé jusqu'à la fin donc erreur
  int deplacement = D;

  if (argc > 1 && (strcmp(argv[1],"--console") || strcmp(argv[1],"-c")) ){ // lancement console
    int tour = 0; char c;               // tour %2 permet de connaitre le jour et c stocke la lettre du joeuur qui doit jouer
    
    while (!check_End_Game(map2D)) {   // tant que la partie n'est pas finie
      c = (tour % 2 == 0) ? 'b' : 'n'; // on regarde c'est à quelle joueur de jouer le tour
      if (c == 'b') gameOption(pileJ1, map3D, map2D, c, deplacement); // on appelle la fonction qui va permettre au joueur -->
      else          gameOption(pileJ2, map3D, map2D, c, deplacement); // de jouer avec le bon numero de pile
      tour++;
    }
    if (count_pion(map2D, N, 'b') && count_pion(map2D, N, 'n')) printf("Egalite!\n");             // les deux joueurs ont alignés N pions
    else if (count_pion(map2D, N, 'b'))                         printf("Le joueur 1 a gagne!\n"); // joueur 1 a aligné N pions.
    else                                                        printf("Le joueur 2 a gagne!\n"); // joueur 2 a aligné N pions.
    printMap3dDebug(map3D);
    statut = EXIT_SUCCESS; // la partie c'est déroulé normalement et le programme va quitter sans erreur
  }
  else { // lancement interface graphique
    SDL_Window * window = NULL ; // fenetre principale, on va travailler sur uniquement une fenêtre(pas besoin de plus)
    SDL_Renderer * renderer = NULL; // renderer principale

    /********************************* ENSEMBLE DE TEXTURES *********************************/
    SDL_Texture ** textureBackground = NULL;        // contient l'animation de fond dans menu de 400 cases
    SDL_Texture **  tableauTextureMapVide = NULL;   // 0 map avec gobble en vert , 1 en bleu et 2 en rouge. Change selon la couleur du joueur
    SDL_Texture ** textureTableauOptionMenu = NULL; // contient les options dans le menu 1VS1, 1VSIA, QUIT GAME and SOUND
    SDL_Texture ** textureTableauPion = NULL;       // contient les images des pions sélectionnés et déselectionner
    SDL_Texture ** textureTableauWin = NULL;        // tableau contenant les images de victoires et d'égalité
    /****************************************************************************************/

    SDL_Rect ** tableauCase = NULL; // contient des rect qui indique la taille et positions des cases de la map
    point ** tableauDePoint = NULL; // tableau de point acceuillant le tableau de point en dur des centres cases map + emplacement piles 0 à 8 pour les cases 9, 10 , 11 et 12 pour les piles bleu puis rouge, et chaque case est un pointeur vers un point
    Mix_Music * mainMusic = NULL;   // musique principal Zelda Ocarina of Time remix libre de droits : https://youtu.be/AysrSoY1GdM
    SDL_Surface * icones = NULL;    // icones fenêtres 

    // boolean 
    int etatS = 1 ;          // 1 si on est dans le menu, 0 sinon
    int * p_etatS = &etatS;  // on manipule un pointeur
    int boolPlayMusic = 1;   // permet de savoir si on joue de la musique (possibilité de la désactiver pendant une game)
    char c = 'b';            // variable definissant le joueur qui commence à joueur
    char * p_c = &c;         // pointeur sur la variable qui définit quel joueur joue
    int ia = 0;              // variable correspondant à l'ia
    int * p_ia = &ia;        // pointeur sur la variable ia

    // chargement SDL / fenetre / renderer / textureMenu et background
    if (0 != initialiseDebutProgramme(&window, &textureBackground, &tableauTextureMapVide, &icones, &renderer, &textureTableauOptionMenu, &textureTableauPion, &textureTableauWin, &tableauDePoint, &tableauCase)) {
       fprintf(stderr, "Error in initialiseDebutProgramme : %s \n",SDL_GetError()); 
       goto Quit; // si erreur quitte le programme
     }

    intro_authors(&renderer);          // intro image authors + son , pas de quit si erreur
    loadAndPlayMainMusic(&mainMusic);  // lancement musique, si plante pas de music mais pas d'arret du jeu

    while (etatS)
    {
      if (etatS == 1) // lancement menu
        lancementMenu(renderer, textureBackground, textureTableauOptionMenu, p_etatS, boolPlayMusic, p_ia); // lancementMenu
      else if (etatS == 2) // lancement du jeu (si choisie dans le menu)
        lancementJeu1VS1(renderer, tableauTextureMapVide, tableauDePoint, textureTableauWin, p_etatS, boolPlayMusic, textureTableauOptionMenu, tableauCase, textureTableauPion, map3D, map2D, pileJ1, pileJ2, deplacement, p_c, p_ia);
      else if (etatS == 3) // menu pause
        pause(renderer, textureTableauOptionMenu, p_etatS, boolPlayMusic, tableauTextureMapVide, textureTableauPion, tableauDePoint, map3D);
      else if (etatS == 4) // entrainement IA
        IAGame(renderer, tableauTextureMapVide, tableauDePoint, textureTableauWin, p_etatS, boolPlayMusic, textureTableauOptionMenu, tableauCase, textureTableauPion, map3D, map2D, pileJ1, pileJ2, deplacement, p_c, p_ia);
      else
        return 0;
    }
    statut = EXIT_SUCCESS; // si on arrive ici ca veut dire que tout c'est bien passé et que l'utillisateur à voulue partir

Quit :
    freeSDL(window, renderer, mainMusic, textureTableauPion, tableauTextureMapVide, textureTableauOptionMenu, textureBackground, tableauDePoint, icones, tableauCase, textureTableauWin);
    Mix_CloseAudio(); // liberation de la gestion musique
    SDL_Quit();       // libere SDL_INIT uniquement pas les images / polices...
  } // fin else (lancement programme en SDL)
  freeBaseGame(map3D, map2D, pileJ1, pileJ2);
  return statut;
}
