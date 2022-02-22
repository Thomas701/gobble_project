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
      if (c == 'b')
	gameOption(pileJ1, map3D, map2D, c);
      else
	gameOption(pileJ2, map3D, map2D, c);
      tour++;
    }
    if (count_pion(map3D, N, 'b'))
      printf("Le joueur 1 a gagne!\n");
    else
      printf("Le joueur 2 a gagne!\n");
    freeMap(map3D);
    freeMap2D(map2D);
    freeStack(pileJ1);
    freeStack(pileJ2);
      
    return EXIT_SUCCESS;
  }
  else // lancement interface graphique
  {
    // fenetre principale
    SDL_Window * window = NULL ;
    
    // textures
    SDL_Texture * textureMenu = NULL;
    SDL_Texture * textureBackground = NULL;
    SDL_Texture * textureMapVide = NULL;
    // textures Pionts
    SDL_Texture * texturePiont1R = NULL;
    SDL_Texture * texturePiont2R = NULL;
    SDL_Texture * texturePiont3R = NULL;
    SDL_Texture * texturePiont1B = NULL;
    SDL_Texture * texturePiont2B = NULL;
    SDL_Texture * texturePiont3B = NULL;

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
    if (0 != initialiseDebutProgramme(&window, &textureMenu, &textureBackground, &textureMapVide,&icones, &renderer))
    {
       fprintf(stderr, "Error in initialiseDebutProgramme : %s \n",SDL_GetError());
       goto Quit;
    }

    // texture piont
    if (0 != loadPiont(&renderer, &texturePiont1R, &texturePiont2R, &texturePiont3R, &texturePiont1B, &texturePiont2B, &texturePiont3B))
    {
       fprintf(stderr, "Error in loadPiont : %s \n",SDL_GetError());
       goto Quit;
    }

    // intro image authors + son
    //intro_authors(&window, &renderer);

    // lancement musique
    //loadAndPlayMainMusic(&mainMusic);

    // affiche map vide
    printMapEmptySDL(textureMapVide, renderer);

    
    char ** pileJ1 = createStack('b');
    char ** pileJ2 = createStack('n');

    pileJ1[0][2] = '0';

    pileJ1[1][2] = '0';
    pileJ1[1][1] = '0';


    pileJ2[1][2] = '0';
    pileJ2[1][1] = '0';
    pileJ2[1][0] = '0';
    
    // affiche piles joueurs
    affichePileSDL(renderer, textureMapVide, texturePiont1R, texturePiont2R, texturePiont3R, texturePiont1B, texturePiont2B, texturePiont3B, pileJ1, pileJ2);
    
    // lancementMenu
    lancementMenu(renderer, textureBackground, textureMenu, p_etatS, boolPlayMusic);

    statut = EXIT_SUCCESS;

Quit :
    // musiques
    if(mainMusic) Mix_FreeMusic(mainMusic);

    //surfaces
    if (icones) SDL_FreeSurface(icones);

    // textures
    if(textureMenu) SDL_DestroyTexture(textureMenu);
    if(textureBackground) SDL_DestroyTexture(textureBackground);
    if(textureMapVide) SDL_DestroyTexture(textureMapVide);
    if(texturePiont1R) SDL_DestroyTexture(texturePiont1R);
    if(texturePiont2R) SDL_DestroyTexture(texturePiont2R);
    if(texturePiont3R) SDL_DestroyTexture(texturePiont3R);
    if(texturePiont1B) SDL_DestroyTexture(texturePiont1B);
    if(texturePiont2B) SDL_DestroyTexture(texturePiont2B);
    if(texturePiont3B) SDL_DestroyTexture(texturePiont3B);
    
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
