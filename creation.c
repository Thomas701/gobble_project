#include "fonction.h"

/*Fonctions création de maps, piles, images :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

SDL_Rect ** mallocTab()
{
  SDL_Rect ** tableauCase = (SDL_Rect **) malloc(sizeof(SDL_Rect *)*((N*N) + (N*2)));

  for(int i = 0 ; i < ((N*N) + (N*2)) ; i++)
  {
    tableauCase[i] = malloc(sizeof(SDL_Rect *) * 1);
    if(!tableauCase[i])
    {
      perror("Error allocation memory in createCase for tableauCase[i] \n");
      freeTabCase(tableauCase);
      exit(-1);
    }
  }
  return tableauCase;
}

char ** createStack(char c)
{
  char ** pile = (char **) malloc(sizeof(char *)*(N-1));
  if(!pile) 
    errorInCreatePile();

  for(int i = 0; i < N-1; i++)
  {
    pile[i] = (char*) malloc(sizeof(char)*N);
    if(!pile[i])
    {
      for(int l = 0; l < i; l++) { free(pile[l]); pile[l] = NULL; }
      free(pile); pile = NULL;
      errorInCreatePile() ;
    }
  }

  for (int i = 0; i < N-1; i++)
  {
    for (int j = 0; j < N; j++)
      pile[i][j] = c;
  }
  return pile;
}

char *** createMap() 
{
  char *** map;

  map = (char ***) malloc(sizeof(char **)*N);
  if(!map) errorInCreate3D() ; // map == NULL

  for(int i = 0 ; i < N; i++) 
  {
    map[i] = (char **) malloc(sizeof(char *)*N);
    if(!map[i])
    {
      for(int l = 0; l < i; l++) { free(map[l]); map[l] = NULL; }
      free(map); map = NULL;
      errorInCreate3D() ;
    }

    for(int j = 0; j<N; j++)
    {
      map[i][j] = (char *) malloc(sizeof(char) * N);
      if(!map[i][j])
      {
        for(int m = 0; m < j; m++) { free(map[i][m]); map[i][m] = NULL; }
        for(int n = 0; n < i; n++) { free(map[n]); map[n] = NULL; }
        free(map); map = NULL;
        errorInCreate3D() ;
      }
    }
  }
  return map ;
}

char ** createMap2D()
{
  char ** map2D = (char **) malloc(sizeof(char *)*N);
  if(map2D == NULL)
    errorInCreate2D();
  for(int i = 0; i < N; i++)
  {
    map2D[i] = (char *) malloc(sizeof(char)*N);
    if(map2D[i] == NULL)
    {
      for(int j = 0; j < i; j++)
      {
        free(map2D[j]); 
        map2D[j] = NULL;
      }
      free(map2D);
      errorInCreate2D();
    }
  }
  return map2D;
}

SDL_Texture * loadImage(const char * path, SDL_Renderer *renderer)
{
  SDL_Surface *tmp = NULL;
  SDL_Texture *texture = NULL;
  tmp = IMG_Load(path);

  if(!tmp) // probleme chargement image
  {
    fprintf(stderr, "Erreur SDL_Load : %s\n", SDL_GetError());
    return NULL;
  }
  texture = SDL_CreateTextureFromSurface(renderer, tmp);
  SDL_FreeSurface(tmp);

  if(!texture) // probleme transfo image en texture
  {
    fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
    return NULL;
  }
  return texture;
}

int createPoint(point *** pTableauDePoint)
{
  point ** tableauDePoint = (point ** ) malloc(sizeof(point *) * 15);
  for(int i = 0 ; i < 15 ; ++i)
  {
    tableauDePoint[i] = malloc(sizeof(point) * 1);
    if(!tableauDePoint[i])
    {
      perror("Error allocation memory in createPoint for tableauDePoint[i] \n");
      for(int j = 0 ; j < i ; ++j)
        free(tableauDePoint[j]);
      free(tableauDePoint);
      return -1;
    }
  }
  tableauDePoint[ 0]->x = 502 ;  tableauDePoint[ 0]->y = 404 ;
  tableauDePoint[ 1]->x = 658 ;  tableauDePoint[ 1]->y = 405 ;
  tableauDePoint[ 2]->x = 807 ;  tableauDePoint[ 2]->y = 406 ;
  tableauDePoint[ 3]->x = 486 ;  tableauDePoint[ 3]->y = 517 ;
  tableauDePoint[ 4]->x = 664 ;  tableauDePoint[ 4]->y = 519 ;
  tableauDePoint[ 5]->x = 828 ;  tableauDePoint[ 5]->y = 517 ;
  tableauDePoint[ 6]->x = 465 ;  tableauDePoint[ 6]->y = 655 ;
  tableauDePoint[ 7]->x = 664 ;  tableauDePoint[ 7]->y = 649 ;
  tableauDePoint[ 8]->x = 854 ;  tableauDePoint[ 8]->y = 652 ;
  tableauDePoint[ 9]->x = 286 ;  tableauDePoint[ 9]->y = 388 ;
  tableauDePoint[10]->x = 239 ;  tableauDePoint[10]->y = 503 ;
  tableauDePoint[11]->x = 183 ;  tableauDePoint[11]->y = 641 ;
  tableauDePoint[12]->x = 985 ;  tableauDePoint[12]->y = 389 ;
  tableauDePoint[13]->x = 1044;  tableauDePoint[13]->y = 506 ;
  tableauDePoint[14]->x = 1107;  tableauDePoint[14]->y = 646 ;
  * pTableauDePoint = tableauDePoint;
  return 0;
}

int createCase(SDL_Rect *** pTableauCase)
{
  SDL_Rect ** tableauCase = (SDL_Rect **) malloc(sizeof(SDL_Rect *)*((N*N) + (N*2)));

  for(int i = 0 ; i < ((N*N) + (N*2)) ; i++)
  {
    tableauCase[i] = malloc(sizeof(SDL_Rect *) * 1);
    if(!tableauCase[i])
    {
      perror("Error allocation memory in createCase for tableauCase[i] \n");
      for(int j = 0 ; j < i ; ++j)
        free(tableauCase[j]);
      free(tableauCase);
      return -1;
    }
  }
  tableauCase[ 0]->w = 152 ; tableauCase[ 0]->h = 89 ;
  tableauCase[ 0]->x = 419 ; tableauCase[ 0]->y = 359 ;
  tableauCase[ 1]->w = 141 ; tableauCase[ 1]->h = 89 ;
  tableauCase[ 1]->x = 585 ; tableauCase[ 1]->y = 358 ;
  tableauCase[ 2]->w = 134 ; tableauCase[ 2]->h = 89 ;
  tableauCase[ 2]->x = 738 ; tableauCase[ 2]->y = 358 ;
  tableauCase[ 3]->w = 171 ; tableauCase[ 3]->h = 106 ;
  tableauCase[ 3]->x = 392 ; tableauCase[ 3]->y = 462 ;
  tableauCase[ 4]->w = 159 ; tableauCase[ 4]->h = 108 ;  // 107
  tableauCase[ 4]->x = 579 ; tableauCase[ 4]->y = 461 ;
  tableauCase[ 5]->w = 152 ; tableauCase[ 5]->h = 107 ;
  tableauCase[ 5]->x = 751 ; tableauCase[ 5]->y = 461 ;
  tableauCase[ 6]->w = 195 ; tableauCase[ 6]->h = 129 ;
  tableauCase[ 6]->x = 358 ; tableauCase[ 6]->y = 587 ;
  tableauCase[ 7]->w = 182 ; tableauCase[ 7]->h = 130 ;
  tableauCase[ 7]->x = 571 ; tableauCase[ 7]->y = 586 ;
  tableauCase[ 8]->w = 174 ; tableauCase[ 8]->h = 129 ;
  tableauCase[ 8]->x = 765 ; tableauCase[ 8]->y = 586 ;
  tableauCase[ 9]->w = 128 ; tableauCase[ 9]->h = 131 ;   //  bleu fond
  tableauCase[ 9]->x = 223 ; tableauCase[ 9]->y = 293 ;
  tableauCase[ 10]->w = 148 ; tableauCase[ 10]->h = 123 ;  //  bleu moyen
  tableauCase[ 10]->x = 167 ; tableauCase[ 10]->y = 431 ;
  tableauCase[ 11]->w = 143 ; tableauCase[ 11]->h = 110 ;  //  bleu devant
  tableauCase[ 11]->x = 112 ; tableauCase[ 11]->y = 579 ;
  tableauCase[ 12]->w = 119 ; tableauCase[ 12]->h = 129 ;  //  rouge fond
  tableauCase[ 12]->x = 927 ; tableauCase[ 12]->y = 294 ;
  tableauCase[ 13]->w = 117 ; tableauCase[ 13]->h = 116 ;  //  rouge moyen
  tableauCase[ 13]->x = 987 ; tableauCase[ 13]->y = 430 ;
  tableauCase[ 14]->w = 122 ; tableauCase[ 14]->h = 114 ;  //  rouge devant
  tableauCase[ 14]->x = 1050 ; tableauCase[ 14]->y = 579 ;
  
  debugTab(tableauCase);

  * pTableauCase = tableauCase;
  return 0;
}

void initTableauCase(SDL_Rect ** tableauCase)
{
  tableauCase[ 0]->w = 152 ; tableauCase[ 0]->h = 89 ;
  tableauCase[ 0]->x = 419 ; tableauCase[ 0]->y = 359 ;
  tableauCase[ 1]->w = 141 ; tableauCase[ 1]->h = 89 ;
  tableauCase[ 1]->x = 585 ; tableauCase[ 1]->y = 358 ;
  tableauCase[ 2]->w = 134 ; tableauCase[ 2]->h = 89 ;
  tableauCase[ 2]->x = 738 ; tableauCase[ 2]->y = 358 ;
  tableauCase[ 3]->w = 171 ; tableauCase[ 3]->h = 106 ;
  tableauCase[ 3]->x = 392 ; tableauCase[ 3]->y = 462 ;
  tableauCase[ 4]->w = 159 ; tableauCase[ 4]->h = 108 ;  // 107
  tableauCase[ 4]->x = 579 ; tableauCase[ 4]->y = 461 ;
  tableauCase[ 5]->w = 152 ; tableauCase[ 5]->h = 107 ;
  tableauCase[ 5]->x = 751 ; tableauCase[ 5]->y = 461 ;
  tableauCase[ 6]->w = 195 ; tableauCase[ 6]->h = 129 ;
  tableauCase[ 6]->x = 358 ; tableauCase[ 6]->y = 587 ;
  tableauCase[ 7]->w = 182 ; tableauCase[ 7]->h = 130 ;
  tableauCase[ 7]->x = 571 ; tableauCase[ 7]->y = 586 ;
  tableauCase[ 8]->w = 174 ; tableauCase[ 8]->h = 129 ;
  tableauCase[ 8]->x = 765 ; tableauCase[ 8]->y = 586 ;
  tableauCase[ 9]->w = 128 ; tableauCase[ 9]->h = 131 ;   //  bleu fond
  tableauCase[ 9]->x = 223 ; tableauCase[ 9]->y = 293 ;
  tableauCase[ 10]->w = 148 ; tableauCase[ 10]->h = 123 ;  //  bleu moyen
  tableauCase[ 10]->x = 167 ; tableauCase[ 10]->y = 431 ;
  tableauCase[ 11]->w = 143 ; tableauCase[ 11]->h = 110 ;  //  bleu devant
  tableauCase[ 11]->x = 112 ; tableauCase[ 11]->y = 579 ;
  tableauCase[ 12]->w = 119 ; tableauCase[ 12]->h = 129 ;  //  rouge fond
  tableauCase[ 12]->x = 927 ; tableauCase[ 12]->y = 294 ;
  tableauCase[ 13]->w = 117 ; tableauCase[ 13]->h = 116 ;  //  rouge moyen
  tableauCase[ 13]->x = 987 ; tableauCase[ 13]->y = 430 ;
  tableauCase[ 14]->w = 122 ; tableauCase[ 14]->h = 114 ;  //  rouge devant
  tableauCase[ 14]->x = 1050 ; tableauCase[ 14]->y = 579 ;
}