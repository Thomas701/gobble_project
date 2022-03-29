#ifndef CREATION_H_
#define CREATION_H_

/*Fonctions création de maps et piles :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

SDL_Rect ** mallocTab();
char ** createStack(char c);
char *** createMap();
char ** createMap2D();
SDL_Texture * loadImage(const char * path, SDL_Renderer *renderer);
int createPoint(point *** pTableauDePoint);
int createCase(SDL_Rect *** pTableauCase);
void initTableauCase(SDL_Rect ** tableauCase);

#endif