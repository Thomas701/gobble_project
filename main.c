#ifdef WINDOWS

#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/SDL2/SDL_mixer.h"

#else

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define HEIGHT 800 // hauteur fenetre
#define WIDTH  1280 // largeur fenetre
#include "fonction.c"


/*
int deplacementPiont(SDL_Texture * texturePiont, SDL_Renderer * renderer, SDL_Point * pointDep, SDL_Point * pointArr)
{
  int incrX = (pointDep.x < pointArr.x) ? 1 : -1 ;
  int incrY = (pointDep.y < pointArr.y) ? 1 : -1  ;
  while(pointDep.x != pointArr.x && pointDep.y != pointArr.y)
  {
    pointDep.x += incrX ;
    pointDep.y += incrY ;    
  }
}
*/

/*return 0 if success else -1*/

int main(int argc, char ** argv) 
{
  if (argc > 1 && (strcmp(argv[1],"--console") || strcmp(argv[1],"-c")) ) // lancement console
  {
    char ** pileJ1 = createStack('b');
    char ** pileJ2 = createStack('n');
    char *** map3D = createMap();
    char ** map2D = createMap2D();
    initMap(map3D);
    initMap2D(map2D, map3D);
    int tour = 0;
    char c;
    while (!check_End_Game(map3D))
    {
      c = (tour % 2 == 0) ? 'b' : 'n';
      if (c == 'b') gameOption(pileJ1, map3D, map2D, c);
      else gameOption(pileJ2, map3D, map2D, c);
      tour++;
    }
    if (count_pion(map3D, N, 'b')) printf("Le joueur 1 a gagne!\n");
    else printf("Le joueur 2 a gagne!\n");
    freeMap(map3D);
    freeMap2D(map2D);
    freeStack(pileJ1);
    freeStack(pileJ2);
      
    return EXIT_SUCCESS;
  }
  else // lancement interface graphique
  {
    srand(time(NULL));
    // fenetre principale
    SDL_Window * window = NULL ;
    
    // textures
    SDL_Texture ** textureBackground = NULL;
    SDL_Texture *  textureMapVide = NULL;
    SDL_Texture ** textureTableauOptionMenu = NULL;
    SDL_Texture ** textureTableauPiont = NULL;

    // tableau de point acceuillant le tableau de point en dur des centres cases map + emplacement piles 0 à 8 pour les cases 
    // 9, 10 , 11 et 12 pour les piles bleu puis rouge, et chaque case est un pointeur vers un point
    point ** tableauDePoint = NULL;
    if( 0!= createPoint(&tableauDePoint))
      goto Quit;

    // renderer
    SDL_Renderer * renderer = NULL;
    
    // boolean
    int etatS = 1 ;        // 1 si on est dans le menu, 0 sinon
    int * p_etatS = &etatS;
    int boolPlayMusic = 1;   // si on joue de la musique ?

    // musiques
    Mix_Music * mainMusic = NULL;

    // icones fenetres 
    SDL_Surface * icones = NULL;

    int statut = EXIT_FAILURE ;
    
    // chargement SDL / fenetre / renderer / textureMenu et background
    if (0 != initialiseDebutProgramme(&window, &textureBackground, &textureMapVide, &icones, &renderer, &textureTableauOptionMenu, &textureTableauPiont))
    {
       fprintf(stderr, "Error in initialiseDebutProgramme : %s \n",SDL_GetError());
       goto Quit;
    }

    // intro image authors + son
    intro_authors(&window, &renderer);

    // lancement musique
    loadAndPlayMainMusic(&mainMusic);

    // lancementMenu
    //lancementMenu(renderer, textureBackground, textureMenu, p_etatS, boolPlayMusic);

    statut = EXIT_SUCCESS;

Quit :
    // musiques
    if(mainMusic) Mix_FreeMusic(mainMusic);

    //surfaces
    if (icones) SDL_FreeSurface(icones);

    // textures
    if(textureMenu) SDL_DestroyTexture(textureMenu);
    if(textureMapVide) SDL_DestroyTexture(textureMapVide);
    
    if(textureTableauPiont)
    {
      for(int i=0; i<6; ++i) // nombres d'images de piont
        SDL_DestroyTexture(textureTableauPiont[i]);
      free(textureTableauPiont);
    }

    if(textureBackground)
    {
      for(int i = 0; i < 400; i++) // nombres d'images de piont
        SDL_DestroyTexture(textureBackground[i]);
      free(textureBackground);
    }
    
    if(tableauDePoint)
    {
      for(int i=0; i<13; ++i) // nombres d'images de piont
        free(tableauDePoint[i]);
      free(tableauDePoint);
    }

    // renderer
    if (renderer) SDL_DestroyRenderer(renderer);

    // fenetre
    if(window) SDL_DestroyWindow(window); // libere la fenetre

    Mix_CloseAudio(); // liberation de la gestion musqie
    SDL_Quit(); // libere SDL_INIT uniquement pas les images / polices...
    return statut;
  }
}


/*
        case SDL_KEYDOWN :                   // utilisateur a taper une touche
          if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) // echape pour afficher ou quitter le menu
          {
            if(menu == 0) // cas ou on a pas de menu
            {
              menu = 1;// on met de bool a 1
              lancementMenu(renderer, textureBackground, textureMenu);
            }
            else  // cas ou on a un menu et on veut continuer de jouer
            {
              menu = 0; // on met le bool a 0 pour stopper
              SDL_RenderClear(renderer);
              SDL_RenderPresent(renderer);
              printf("Retour au jeu\n");
            }
          }
          break;

*/
