#ifndef FREE_H_
#define FREE_H_

/*Fonctions free pour libérer la mémoire :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void vider_buffer(void); // vide le buffer
void freeTabCase(SDL_Rect ** tableauCase);
void freeMap(char *** map); // libere la mémoire de la map 3D
void freeMap2D(char ** map2D); // libere la memoire de la map 2D
void freeStack(char ** stackArray); // libere la memoire de la pile
void freeSDL(SDL_Window * window, SDL_Renderer * renderer, Mix_Music * mainMusic, SDL_Texture ** textureTableauPion, SDL_Texture **  tableauTextureMapVide, SDL_Texture ** textureTableauOptionMenu,SDL_Texture ** textureBackground, point ** tableauDePoint, SDL_Surface * icones, SDL_Rect ** tableauCase); // free textures + musiques + icones + renderer + windows
void freeBaseGame(char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2);
#endif