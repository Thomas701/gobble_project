#include "../include/SDL2/SDL.h"
#include "../include/SDL2/SDL_image.h"
#include "../include/SDL2/SDL_mixer.h"

/*#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fonction.c"

#define HEIGHT 1280 // hauteur fenetre
#define WIDTH  800 // largeur fenetre

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
    SDL_Window *window = NULL ;

    // textures
    SDL_Texture * textureMenu = NULL;
    SDL_Texture * textureBackground = NULL;

    // renderer
    SDL_Renderer * renderer = NULL;

    // point
    // dans l'image menu
    SDL_Point pointChoice1VS1_HG = {160,240};
    SDL_Point pointChoice1VS1_BD = {990, 355};

    SDL_Point pointChoiceIA_HG = {170,430};
    SDL_Point pointChoiceIA_BD = {975, 550};

    SDL_Point pointQuitter_HG  = {170, 650};
    SDL_Point pointQuitter_BD  = {1000, 780};

    SDL_Point pointSound_HG = {1120,0};
    SDL_Point pointSound_BD = {1280, 185};

    // souris pour evenement
    SDL_Point pointMouse = {0 , 0};
    
    // boolean
    int programOn = 1 ;   // 0 si quitter 
    int menu = 0 ;        // 1 si on est dans le menu, 0 sinon
    int boolPlayMusic = 1 ;   // si on joue de la musique ?

    // musiques
    Mix_Music * mainMusic = NULL;

    // icones fenetres 
    SDL_Surface * icones = NULL;

    int statut = EXIT_FAILURE ;

    // initialise le systeme gestion de rendu, d'évenements , audio et temps + test
    if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_TIMER))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        goto Quit;
    }

    // alloue la fenetre
    window = SDL_CreateWindow("GOOBLE PROJECT - PREP'ISIMA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, HEIGHT, WIDTH, SDL_WINDOW_SHOWN) ;

    if(!window)
    {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
        goto Quit ;
    }

    // chargement de l'icones
    icones = IMG_Load("Frames/icones.png");
    if (!icones)
    SDL_Log("Erreur chargement icones IMG_Load : %s\n", Mix_GetError());
    else
    SDL_SetWindowIcon(window, icones);

    // chargement carte son
    if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0) // création de la configuration de la carte son
    {
        SDL_Log("Erreur initialisation SDL_mixer : %s\n", Mix_GetError());
        goto Quit ;
    }
    
    // intro image authors + son
    intro_authors(window);

    // initialisation renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer)
    {
        fprintf(stderr, "Error SDL_CreateRenderer for renderer: %s\n", SDL_GetError());
        goto Quit;
    }

    // initialisation de la musique
    mainMusic = Mix_LoadMUS("Music/mainMusic.mp3");
    Mix_VolumeMusic(MIX_MAX_VOLUME/8);
    if(!mainMusic)
    {
        fprintf(stderr, "Error for load mainMusic : %s \n",SDL_GetError());
    }

    if(0 != Mix_PlayMusic(mainMusic, -1)) 
    {
        fprintf(stderr, "Error in Mix_PlayMusic %s\n", SDL_GetError());
        boolPlayMusic = 0;
    }

    menu = 1 ;

    if (!lancementMenu(renderer, textureBackground, textureMenu))
    {
        fprintf(stderr, "Error un lancementMenu : %s \n", SDL_GetError());
        goto Quit ;
    }

    while(programOn) // boucle principale
    {
        SDL_Event event;
        while(programOn && SDL_PollEvent(&event)) // programme continue et un nouveau evenement dans la file
        {
            switch(event.type)
            {
                case SDL_QUIT :                       // utilisateur veut quitter
                    goto Quit ;
                break ;

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
                
                case SDL_MOUSEBUTTONDOWN :           // bouton souris enfonce
                    if(menu)                         // on se trouve dans le menu
                    {
                        if (event.button.button == SDL_BUTTON_LEFT) // bouton souris gauche
                        {
                            SDL_GetMouseState(&pointMouse.x, &pointMouse.y); // recupere coord souris
                            if (isInRect(pointMouse , pointChoice1VS1_HG, pointChoice1VS1_BD)) // choix 2 joueurs en local
                            {
                                menu = 0 ;
                                SDL_RenderClear(renderer);
                                SDL_RenderPresent(renderer);
                                printf("Lancement jeu 1VS1 \n");
                            }
                            else if(isInRect(pointMouse , pointChoiceIA_HG, pointChoiceIA_BD)) // choix 2 joueurs en local
                            {
                                menu = 0;
                                SDL_RenderClear(renderer);
                                SDL_RenderPresent(renderer);
                                printf("Lancement jeu contre IA \n");
                            }
                            else if(isInRect(pointMouse , pointSound_HG, pointSound_BD)) // choix contre IA
                            {
                                if(boolPlayMusic == 0) // cas ou on a pas de musique
                                {
                                    boolPlayMusic = 1;// on met de bool a 1
                                    Mix_ResumeMusic();
                                }
                                else                  // cas ou on a de la musique et on veut l'arreter
                                {
                                    boolPlayMusic = 0; // on met le bool a 0 pour stopper
                                    Mix_PauseMusic();
                                }
                            }
                            else if(isInRect(pointMouse , pointQuitter_HG, pointQuitter_BD)) // choix QUITTER
                            {
                                goto Quit;
                            }
                        }
                    }
                break ;

                default :
                break ;
            }  
        }
      }

      statut = EXIT_SUCCESS;



  /*goto*/
  Quit :
      // musiques
      if(mainMusic) Mix_FreeMusic(mainMusic);

      //surfaces
      if (icones) SDL_FreeSurface(icones);

      // textures
      if(textureMenu) SDL_DestroyTexture(textureMenu);
      if(textureBackground) SDL_DestroyTexture(textureBackground);

      // renderer
      if (renderer) SDL_DestroyRenderer(renderer);

      // fenetre
      if(window) SDL_DestroyWindow(window); // libere la fenetre

      Mix_CloseAudio(); // liberation de la gestion musqie
      SDL_Quit(); // libere SDL_INIT uniquement pas les images / polices...
      return statut;
  }
}