
/*Fonctions free pour libérer la mémoire :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void vider_buffer(void)
{
  int c; 
  do 
  {
    c = getchar();
  } while(c != '\n' && c != EOF);
}

void freeTabCase(SDL_Rect ** tableauCase)
{
  for(int j = 0 ; j < N ; j++)
    free(tableauCase[j]);
  free(tableauCase);
}

void freeMap(char *** map)
{
  if(map)
  {
    for(int i = 0 ; i < N ; ++i)
    {
      if(map[i])
      {
        for(int j = 0 ; j < N ; ++j)
        {
            free(map[i][j]);
            map[i][j] = NULL;
        }
        free(map[i]);
        map[i] = NULL;
      }
    }
    free(map);
    map = NULL;
  }
}

void freeMap2D(char ** map2D)
{
  printMap2D(map2D);
  if(map2D != NULL)
  {
    for(int i = 0; i < N; i++)
    {
      if (map2D[i] != NULL)
      {
        free(map2D[i]); 
      }
    }
    free(map2D); 
    map2D = NULL;
  }
}

void freeStack(char ** stackArray)
{
  if(stackArray)
  {
    for(int i = 0; i < N-1; i++)
    {
      free(stackArray[i]) ; stackArray[i] = NULL;
    }
    free(stackArray) ; stackArray = NULL;
  }
}

void freeSDL(SDL_Window * window, SDL_Renderer * renderer, Mix_Music * mainMusic, SDL_Texture ** textureTableauPion, SDL_Texture **  tableauTextureMapVide, SDL_Texture ** textureTableauOptionMenu,SDL_Texture ** textureBackground, point ** tableauDePoint, SDL_Surface * icones, SDL_Rect ** tableauCase){
  if(mainMusic) Mix_FreeMusic(mainMusic); // free musique principale

  /************************** FREE TEXTURE **************************/
  if(textureTableauPion) {
    for(int i=0; i<(N*2)*2; ++i) // nombres d'images de piont
      SDL_DestroyTexture(textureTableauPion[i]);
    free(textureTableauPion);
  }
  if(tableauTextureMapVide) {
    for(int i=0; i<3; ++i) // free 3 map : 1 map vert, 1 map rouge quand joueur rouge joue et 1 map bleu quand joueur bleu joue
      SDL_DestroyTexture(tableauTextureMapVide[i]);
    free(tableauTextureMapVide);
  }
  if(textureBackground) {
    for(int i = 0; i < 400; i++)                // nombres d'images de pions généré grace à Blender par DUPOIS Thomas
      SDL_DestroyTexture(textureBackground[i]);
    free(textureBackground);
  }
  if(textureTableauOptionMenu) {
    for(int i = 0; i < 5; i++)                  // nombres options menus
      SDL_DestroyTexture(textureTableauOptionMenu[i]);
    free(textureTableauOptionMenu);
  }
  /************************** END TEXTURE **************************/

  if(tableauDePoint) {
    for(int i=0; i < ((N*N) + (N*2)); ++i)      // nombres d'images de piont
      free(tableauDePoint[i]);
    free(tableauDePoint);
  }
  if(tableauCase) {
    for(int i=0; i < ((N*N) + (N*2)); ++i) // nombres d'images de piont
      free(tableauCase[i]);
    free(tableauCase);
  }
  if (icones) SDL_FreeSurface(icones); //free le logo du logiciel
  if (renderer) SDL_DestroyRenderer(renderer);  // renderer
  if(window) SDL_DestroyWindow(window); // libere la fenetre
}

void freeBaseGame(char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2){
  freeMap(map3D); freeMap2D(map2D); freeStack(pileJ1); freeStack(pileJ2);
}