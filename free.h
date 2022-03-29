#ifndef FREE_H_
#define FREE_H_

/*Fonctions free pour libérer la mémoire :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void vider_buffer(void); // vide le buffer
void freeTabCase(SDL_Rect ** tableauCase);
void freeMap(char *** map); // libere la mémoire de la map 3D
void freeMap2D(char ** map2D); // libere la memoire de la map 2D
void freeStack(char ** stackArray); // libere la memoire de la pile

#endif