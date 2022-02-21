#include <stdio.h>
#include <stdlib.h>
#include "fonction.c"
#include "../include/SDL2/SDL.h"

/*
char 'b' pour joeur blanc ,
char 'n' pour joeur noir  ,
char '0' pour case vide   ,

*/
int main(int argc, char ** argv)
{
  SDL_version np;
  SDL_VERSION(&np);
  printf("Bienvenue sur_ la SDL %d %d %d\n", np.major, np.minor, np.patch);
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Color orange = {255, 127, 40, 255};
  SDL_Rect rect = {100, 100, 100, 100};
  SDL_RenderDrawRect(renderer, &rect);
  int statut = EXIT_FAILURE;

  if(0 != SDL_Init(SDL_INIT_VIDEO))
  {
    fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
    goto Quit;
  }
  window = SDL_CreateWindow("SDL2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
  if(NULL == window)
  {
    fprintf(stderr, "Erreur SDL_CreateWindow : %s", SDL_GetError());
    goto Quit;
  }
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if(NULL == renderer)
  {
    fprintf(stderr, "Erreur SDL_CreateRenderer : %s", SDL_GetError());
    goto Quit;
  }
  if(0 != SDL_SetRenderDrawColor(renderer, orange.r, orange.g, orange.b, orange.a))
  {
    fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
    goto Quit;
  }
  if(0 != SDL_RenderClear(renderer))
  {
    fprintf(stderr, "Erreur SDL_SetRenderDrawColor : %s", SDL_GetError());
    goto Quit;
  }
  SDL_SetWindowTitle(window, "Gobble");
  /*char ** pileJ1 = createStack('b');
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
  freeStack(pileJ2);*/
  statut = EXIT_SUCCESS;
  SDL_Delay(3000);
  SDL_RenderPresent(renderer);
  SDL_Delay(3000);
Quit:
  if(NULL != window)
    SDL_DestroyWindow(window);
  if(NULL != renderer)
    SDL_DestroyRenderer(renderer);
  SDL_Quit();
  return statut;
}