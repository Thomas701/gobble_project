#include "fonction.h"

/*Fonctions essentielles map :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

char *** createMap() 
{
  char *** map;

  map = (char ***) malloc(sizeof(char **)*N);
  if(!map) errorInCreate3D() ; // map == NULL

  for(int i = 0 ; i < N; ++i) 
  {
    map[i] = (char **) malloc(sizeof(char *)*N);
    if(!map[i]) errorInCreate3D() ;

    for(int j=0; j<N; ++j)
    {
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
        map[i][j][k] = '0';
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
        printf("'%c' ", map[i][j][k]);
      printf("]    ");
    }
    printf("\n\n");
  }
  printf("\n");
}

int canMoove(char *** map, int posDep, int posEnd)
{
  x = (posDeb - posDep % N) / N;
  y = posDeb % N;
  x2 = (posEnd - posEnd % N) / N;
  y2 = posEnd % N;
  count = 0;
  count2 = 0;
  for (int i = 0; i < N-1; i++)
  {
    if (map[x][y][i] != '0')
      count = i;
    if (map[x2][y2][i] != '0')
      count2 = i;
  }
  if (count > count2)
    return 1;
  else
    return 0;
}

int moove(char *** map, int posDep, int posEnd)
{
  if (canMoove(map, posDep, posEnd) == 0)
    return 0;
  else
  {
    x = (posDeb - posDep % N) / N;
    y = posDeb % N;
    x2 = (posEnd - posEnd % N) / N;
    y2 = posEnd % N;
    for (int i = N-1; i > 0; i--)
    {
      if (map[x][y][i] != '0')
      {
        map[x2][y2][i] = map[x][y][i];
        map[x][y][i] = '0';
        return;
      }
    }
    return;
  }
}

int check_End_Game(char *** map)
{
  char map_Temporaire[N][N];
  int count_L = 0;
  int count_C = 0;
  int count_DD = 0;
  int count_DG = 0;

/* Initialisation tableau temporaire */
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
      map_Temporaire[i][j] = '0';
  }

/* Mise en parrallèle du tableau temporelle au tableau initial */
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      for (int k = N-1; i > 0; i--)
      {
        if (map[i][j][k] != '0' && map_Temporaire[i][j] == '0')
        {
          map_Temporaire[i][j] = map[i][j][k];
          k = 0;
        }
      }  
    }
  }

/* Vérification si il y a une ligne, colonne ou diagonale complété */
  for (int i = 0; i < N-1; i++)
  {
    for (int j = 0; j < N-1; j++)
    {
      if (map_Temporaire[i][j] == map_Temporaire[i][j+1])
        count_L++;
      if (map_Temporaire[j][i] == map_Temporaire[j+1][i])
        count_C++;
      if (map_Temporaire[i][j] == map_Temporaire[i+1][j+1]
        count_DD++;
      if (map_Temporaire[N-1-i][j] == map_Temporaire[N-1-(i+1)][j+1]
        count_DG++;
    }
    if (count_C == N-1 || count_L -- N-1 || count_DD == N-1 || count_DG == N-1) /* partie terminée */
      return 1;
    else
      count_C = 0; count_L = 0; count_DD = 0; count_DG = 0;
  }
  return 0;                                                                     /* partie non-terminée */
}


/*Fonctions d'erreur pour eviter la répétition :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void errorInCreate3D() 
{
    perror("ERROR ALLOCATION MEMORY in create3DArray\n");
    exit(1);
}