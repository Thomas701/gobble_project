
/*Fonctions print pour afficher les maps & piles :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void printMap3dDebug(char *** map)
{
  for(int i = 0 ; i < N ; ++i)
  {
    for(int j = 0 ; j < N ; ++j)
    {
      printf("[%d][ ", j+i*N);
      for(int k = 0; k < N; ++k)
        printf("'%c' ", map[i][j][k]);
      printf("]    ");
    }
    printf("\n\n");
  }
  printf("\n");
}

void printMap2D(char ** map2D)
{
  for(int i=0; i<N; ++i)
  {
    for(int j=0; j<N; ++j)
       printf("%c ", map2D[i][j]);
    printf("\n");
  }
  printf("\n");
}

void printStacks(char ** stacksArray)
{
  for(int i = 0; i < N-1 ; i++)
  {
    printf("pile numéro %d : |", i);
    for(int j=0; j < N ; j++)
      printf(" %c |", stacksArray[i][j]);
    printf("\n");
  }
}

/* -1 si erreur , 0 sinon*/
int printMapEmptySDL(SDL_Texture * textureMapVide, SDL_Renderer * renderer)
{
  if (0 !=  SDL_RenderCopy(renderer, textureMapVide, NULL, NULL)) 
    { 
      fprintf(stderr, "Error SDL_RenderCopy in printMapEmptySDL : %s \n", SDL_GetError());
      return -1; 
    }
  return 0;
}