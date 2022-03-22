#ifndef PRINT_H_
#define PRINT_H_

/*Fonctions print pour afficher les maps & piles :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void printMap3dDebug(char *** map); // affiche la map 3D
void printMap2D(char ** map2D); // affiche la map 2D
void printStacks(char ** stacksArray); // affiche les piles
int printMapEmptySDL(SDL_Texture * textureMapVide, SDL_Renderer * renderer); // affiche la map vide

#endif