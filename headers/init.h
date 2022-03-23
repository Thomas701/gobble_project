#ifndef INIT_H_
#define INIT_H_

/*Fonctions initialisation de maps :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void initMap(char *** map); // initialise la map 3D
void initMap2D(char ** map2D, char *** map3D); // initialise la map 2D
void initPile(char ** pile, char c); // remplie une pile
int loadTextureOptionMenu(SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu);
int initialiseDebutProgramme(SDL_Window ** window, SDL_Texture *** textureBackground, SDL_Texture *** ptableauTextureMapVide, SDL_Surface ** icones, SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu, SDL_Texture *** pTextureTableauPiont, SDL_Texture *** pTextureTableauWin, point *** pTableauDePoint, SDL_Rect *** pTableauCase);
int initSDL(); // initialise la SDL
int initWindows(SDL_Window ** window); // initialise la fenêtre
int initRenderer(SDL_Window ** window, SDL_Renderer ** renderer); // initialise le renderer
int initIcon(SDL_Window ** window, SDL_Surface ** icones); // initialise l'icon
int initSound(); // initialise la carte son
int initBackgroung(SDL_Renderer ** renderer, SDL_Texture *** textureBackground); // initialise texture background
int initTextureMapVide(SDL_Renderer ** renderer, SDL_Texture *** ptableauTextureMapVide); //initialise texture map vide
int initTextureOptionMenu(SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu); // initialise les options du menu
int initTexturePion(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauPiont); // initialise la texture des pionts
int initTableauDePoint(point *** pTableauDePoint); // initialise les coordonnées des cases
int initCase(SDL_Rect *** pTableauCase); // initialise les rectangles correspondants aux cases
int initTextureWin(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauWin); // initialise les images des victoires
int loadPiont(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauPiont); //charge les pionts dans un tableau de pionts
int loadBackgroundMenu(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauBack); //charge les images background du menu dans un tableau
int loadTextureWin(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauWin);
int loadTextureTableauMap(SDL_Renderer ** renderer, SDL_Texture *** ptableauTextureMapVide); // 0 mapVerte, 1mapBleu, 2 mapRouge
void loadAndPlayMainMusic(Mix_Music ** mainMusic);
#endif