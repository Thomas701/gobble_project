#include "fonction.h"

/*Fonctions free pour libérer la mémoire  :
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