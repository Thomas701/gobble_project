#include "fonction.h"



/*Fonctions essentielles map :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

char *** createMap() 
{
  char *** map = NULL;
  map = (char ***) malloc(sizeof(char **)*N);

  if(!map) errorInCreate3D() ; // map == NULL

  for(int i = 0 ; i < N; ++i) 
  {
    map[i] = NULL;
    map[i] = (char **) malloc(sizeof(char *)*N);

    if(!map[i]) errorInCreate3D() ;

    for(int j=0; j<N; ++j)
    {
      map[i][j] = NULL;
      map[i][j] = (char *) malloc(sizeof(char) * N);

      if(!map[i][j]) errorInCreate3D() ;

    }
  }
  return map ;
}

void initMap(char *** map) 
{
  for(int i=0; i<N; ++i) 
  {
    for(int j=0; j<N; ++j)
    {
      for(int k=0; k<N; ++k)
      {
        map[i][j][k] = ' ';
      }
    }
  }
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
          if(map[i][j])
          {
            free(map[i][j]);
            map[i][j] = NULL;
          }
        }
        free(map[i]);
        map[i] = NULL;
      }
    }
    free(map);
    map = NULL;
  }
}

void printMapDebug(char *** map)
{
  for(int i = 0 ; i < N ; ++i)
  {
    for(int j = 0 ; j < N ; ++j)
    {
      printf("[ ");
      for(int k = 0; k < N; ++k)
      {
        printf("'%c' ", map[i][j][k]);
      }
      printf("]    ");
    }
    printf("\n\n");
  }
  printf("\n");
}




/*Fonctions d'erreur pour eviter la répétition :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void errorInCreate3D() {
    perror("ERROR ALLOCATION MEMORY in create3DArray\n");
    exit(1);
}