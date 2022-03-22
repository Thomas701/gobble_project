#include "fonction.h"

/*Fonctions initialisation  :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void initMap(char *** map) 
{
  for(int i = 0; i < N; i++) 
  {
    for(int j = 0; j < N; j++)
    {
      for(int k = 0; k < N; k++)
        map[i][j][k] = '0';
    }
  }
}

void initMap2D(char ** map2D, char *** map3D)
{
  for(int i = 0; i < N; i++)
  {
    for(int j = 0; j < N; j++)
      map2D[i][j] = '0';
  }

  for(int i=0; i < N; i++)
  {
    for(int j = 0; j < N; j++)
    {
      for(int k = (N-1); k >= 0; k--)
      {
        if(map3D[i][j][k] != '0')       //&& '0' == map2D[i][j] ?
        {
          map2D[i][j] = map3D[i][j][k];
          k = -1;
        }
      }
    }
  }
}

void initPile(char ** pile, char c)
{
  for (int i = 0; i < N-1; i++)
  {
    for (int j = 0; j < N; j++)
      pile[i][j] = c;
  }
}

int loadTextureOptionMenu(SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu)
{
  SDL_Texture ** textureTableauOptionMenu = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*5);
  if (! textureTableauOptionMenu)
  {
    fprintf(stderr, "Erreur allocation memory in textureTableauOptionMenu\n"); 
    return -1;
  }
  for (int i = 0; i < 5; i++)
  {
    char nom[30];
    sprintf(nom, "Frames/option%d.png", i+1);

    textureTableauOptionMenu[i] = loadImage(nom, * renderer);
    if(!textureTableauOptionMenu[i]) {
      fprintf(stderr, "Error loadTextureOptionMenu for textureTableauOptionMenu : %s\n", SDL_GetError()); 
      return -1; 
    }
  }
  * ptextureTableauOptionMenu = textureTableauOptionMenu;
  return 0;
}

/* return -1 si erreur 0 sinon*/
int initialiseDebutProgramme(SDL_Window ** window, SDL_Texture *** textureBackground, SDL_Texture *** ptableauTextureMapVide, SDL_Surface ** icones, SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu, SDL_Texture *** pTextureTableauPiont, SDL_Texture *** pTextureTableauWin, point *** pTableauDePoint, SDL_Rect *** pTableauCase)
{
  initSDL();
  initWindows(window);
  initRenderer(window, renderer);
  initIcon(window, icones);
  initSound();
  initBackgroung(renderer, textureBackground);
  initTextureMapVide(renderer, ptableauTextureMapVide);
  initTextureOptionMenu(renderer, ptextureTableauOptionMenu);
  initTexturePion(renderer, pTextureTableauPiont);
  initTableauDePoint(pTableauDePoint);
  initCase(pTableauCase);
  initTextureWin(renderer, pTextureTableauWin);
  return 0;
}

int initSDL()
{
  // initialise le systeme gestion de rendu, d'évenements , audio et temps + test
  if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_TIMER))
  {
    fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
    return -1;
  }
}

int initWindows(SDL_Window ** window)
{
  // alloue la fenetre
  * window = SDL_CreateWindow("GOBBLE GAME - PREP'ISIMA 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN) ;
  if(!* window)
  {
    fprintf(stderr, "Erreur SDL_CreateWindow : %s\n", SDL_GetError());
    return -1 ;
  }
}

int initRenderer(SDL_Window ** window, SDL_Renderer ** renderer)
{
  // initialisation renderer
  * renderer = SDL_CreateRenderer(* window, -1, SDL_RENDERER_ACCELERATED);
  if(!*renderer)
  {
    fprintf(stderr, "Error SDL_CreateRenderer for mainRenderer: %s\n", SDL_GetError());
    return -1;
  }
}

int initIcon(SDL_Window ** window, SDL_Surface ** icones)
{
  // chargement de l'icones
  * icones = IMG_Load("Frames/icones.png");
  if (!* icones)
    SDL_Log("Erreur chargement icones IMG_Load : %s\n", Mix_GetError());
  else
    SDL_SetWindowIcon(* window, * icones);
}

int initSound()
{
  // chargement carte son
  if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0) // création de la configuration de la carte son
  {
    SDL_Log("Erreur initialisation SDL_mixer : %s\n", Mix_GetError());
    return -1 ;
  }
}

int initBackgroung(SDL_Renderer ** renderer, SDL_Texture *** textureBackground)
{
  // init texture background
  if(loadBackgroundMenu(renderer, textureBackground) != 0)
  {
    fprintf(stderr, "Error loadImage for textureBackground : %s\n", SDL_GetError());
    return -1;
  }
}

int initTextureMapVide(SDL_Renderer ** renderer, SDL_Texture *** ptableauTextureMapVide)
{
  // init texture map vide
  if(0 != loadTextureTableauMap(renderer, ptableauTextureMapVide))
  {
    fprintf(stderr, "Error loadTextureTableauMap for ptableauTextureMapVide : %s\n", SDL_GetError());
    return -1;
  }
}

int initTextureOptionMenu(SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu)
{
  if (0 != loadTextureOptionMenu(renderer, ptextureTableauOptionMenu))
  {
    fprintf(stderr, "Error loadTextureOptionMenu for ptextureTableauOptionMenu : %s\n", SDL_GetError());
    return -1;
  }
}

int initTexturePion(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauPiont)
{
  if (0 != loadPiont(renderer, pTextureTableauPiont))
  {
    fprintf(stderr, "Error in loadPiont : %s \n",SDL_GetError());
    return 1;
  }
}

int initTableauDePoint(point *** pTableauDePoint)
{
  if(0 != createPoint(pTableauDePoint))
  {
    fprintf(stderr, "Error in createPoint : %s \n",SDL_GetError());
    return 1;
  }
}

int initCase(SDL_Rect *** pTableauCase)
{
  if(0 != createCase(pTableauCase))
  {
    fprintf(stderr, "Error in createCase : %s \n",SDL_GetError());
    return 1;
  }
}

int initTextureWin(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauWin)
{
  if(0 != loadTextureWin(renderer, pTextureTableauWin))
  {
    fprintf(stderr, "Error in loadTextureWin : %s \n",SDL_GetError());
    return 1;
  }
}

int loadTextureTableauMap(SDL_Renderer ** renderer, SDL_Texture *** ptableauTextureMapVide)
{
  SDL_Texture ** tableauTextureMapVide = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*3); 
  // 0 map vert, 1 map bleau, 2 map rouge
  if(!tableauTextureMapVide) { fprintf(stderr, "Error malloc in loadTextureTableauMap for tableauTextureMapVide\n"); return -1; }

  for (int i = 0; i < 3; i++) // il n'y a que 3 images map a charger
  {
    char nom[30];
    sprintf(nom, "Frames/map%d.png", i+1);
    tableauTextureMapVide[i] = loadImage(nom, * renderer);
    if(!tableauTextureMapVide[i]) { fprintf(stderr, "Error loadTextureTableauMap for tableauTextureMapVide : %s\n", SDL_GetError()); return -1; }
  }
  * ptableauTextureMapVide = tableauTextureMapVide;
  return 0;
}

int loadPiont(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauPiont)/*return 0 si ok, -1 sinon*/
{
    SDL_Texture ** textureTableauPiont = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*(N*2)*2);
    if (!textureTableauPiont) {
        fprintf(stderr, "Erreur allocation memory in loadPion\n");
        return -1;
    }
    for (int i = 0; i < (N*2)*2; i++)
    {
        char nom[30];
        sprintf(nom, "Frames/pion%d.png", i+1);

        textureTableauPiont[i] = loadImage(nom, * renderer);
        if(!textureTableauPiont[i]) { 
        fprintf(stderr, "Error loadTextureOptionMenu for textureTableauPiont : %s\n", SDL_GetError()); 
        return -1; 
        }
    }
    * pTextureTableauPiont = textureTableauPiont;
    return 0;
}


int loadBackgroundMenu(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauBack)
{
  SDL_Texture ** textureTableauBack = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*400);

  if (! textureTableauBack) {fprintf(stderr, "Erreur allocation memory in loadBackgroundMenu\n"); return -1;}
  for (int i = 0; i < 400; i++)
  {
    char nom[30];
    sprintf(nom, "Frames/background2/p (%d).png", i+1);
    textureTableauBack[i] = loadImage(nom, * renderer);
    if(!textureTableauBack[i]) { fprintf(stderr, "Error loadPiont for loadBackgroundMenu : %s\n", SDL_GetError()); return -1; }
  }
  * pTextureTableauBack = textureTableauBack;
  return 0;
}

int loadTextureWin(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauWin)
{
  SDL_Texture ** TextureTableauWin = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*8);

  if (! TextureTableauWin) {fprintf(stderr, "Erreur allocation memory in loadTextureWin\n"); return -1;}
  for (int i = 0; i < 8; i++)
  {
    char nom[30];
    sprintf(nom, "Frames/win%d.png", i+1);
    TextureTableauWin[i] = loadImage(nom, * renderer);
    if(!TextureTableauWin[i]) { fprintf(stderr, "Error loadTextureWin for TextureTableauWin : %s\n", SDL_GetError()); return -1; }
  }
  * pTextureTableauWin = TextureTableauWin;
  return 0;
}