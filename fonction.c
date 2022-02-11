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
    if(!map[i])
    {
      for(int l=0; l<i; ++l)
      {
        free(map[l]); map[l] = NULL;
      }
      free(map); map = NULL;
      errorInCreate3D() ;
    }

    for(int j=0; j<N; ++j)
    {
      map[i][j] = (char *) malloc(sizeof(char) * N);
      if(!map[i][j])
      {
        for(int m=0; m<j; ++m)
        {
          free(map[i][m]); map[i][m] = NULL;
        }
        for(int n=0; n<i; ++n)
        {
          free(map[n]); map[n] = NULL;
        }
        free(map); map = NULL;
        errorInCreate3D() ;
      }
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

void printMap2D(char ** map2D)
{
  for(int i=0; i<N; ++i)
  {
    for(int j=0; j<N; ++j)
    {
       printf("%c ", map2D[i][j]);
    }
    printf("\n");
  }
  printf("\n");
}

char ** createMap2D()
{
  char ** map2D = (char **) malloc(sizeof(char *)*N);
  if(!map2D) errorInCreate2D();
  for(int i=0; i<N; ++i)
  {
    map2D[i] = (char *) malloc(sizeof(char)*N);
    if(!map2D[i])
    {
      for(int j=0; j<i; ++j)
      {
        free(map2D[j]); map2D[j] = NULL;
      }
      free(map2D);
      errorInCreate2D();
    }
  }
  return map2D;
}

void  initMap2D(char ** map2D, char *** map3D)
{
  // initialise par default
  for(int i=0; i<N; ++i)
  {
    for(int j=0; j<N; ++j)
    {
      map2D[i][j] = '0';
    }
  }

  for(int i=0; i<N; ++i)
  {
    for(int j=0; j<N; ++j)
    {
        for(int k=N-1; k>=0; --k)
        {
          if(map3D[i][j][k] != '0' && '0' == map2D[i][j])
          {
            map2D[i][j] = map3D[i][j][k];
            k = 0;
          }
        }
    }
  }
}

void freeMap2D(char ** map2D)
{
  if(map2D)
  {
    for(int i=0; i<N; ++i)
    {
      free(map2D[i]); map2D[i] = NULL;
    }
    free(map2D); map2D = NULL;
  }
}

int canMoove(char *** map, int posDeb, int posEnd)
{
  int x      = (posDeb - posDeb % N) / N;
  int y      = posDeb % N;
  int x2     = (posEnd - posEnd % N) / N;
  int y2     = posEnd % N;
  int count  = 0;
  int count2 = 0;
  for (int i = 0; i < N; i++)
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

int moove(char *** map, int posDeb, int posEnd)
{
  if (!canMoove(map, posDeb, posEnd))
    return 0;
  else
  {
    int x = (posDeb - posDeb % N) / N;
    int y = posDeb % N;
    int x2 = (posEnd - posEnd % N) / N;
    int y2 = posEnd % N;
    for (int i = N-1; i >= 0; i--)
    {
      if (map[x][y][i] != '0')
      {
        map[x2][y2][i] = map[x][y][i];
        map[x][y][i] = '0';
        return 1;
      }
    }
    perror("In moove() : in else end\n");
    return 0;
  }
}

int check_End_Game(char *** map)
{
  char ** map_Temporaire = createMap2D();
  initMap2D(map_Temporaire, map);
  int count_L  = 0;
  int count_C  = 0;
  int count_DD = 0;
  int count_DG = 0;


/* Vérification si il y a une ligne, colonne ou diagonale complété */
  for (int i = 0; i < N-1; i++)
  {
    for (int j = 0; j < N-1; j++)
    {
      if (map_Temporaire[i][j] == map_Temporaire[i][j+1])
        count_L++;
      if (map_Temporaire[j][i] == map_Temporaire[j+1][i])
        count_C++;
      if (map_Temporaire[i][j] == map_Temporaire[i+1][j+1])
        count_DD++;
      if (map_Temporaire[N-1-i][j] == map_Temporaire[N-1-(i+1)][j+1])
        count_DG++;
    }
    if (count_C == N-1 || count_L == N-1 || count_DD == N-1 || count_DG == N-1) /* partie terminée */
    {
      freeMap2D(map_Temporaire);
      return 1;
    }
    else
    {
      count_C = 0; count_L = 0; count_DD = 0; count_DG = 0;
    }
  }
  freeMap2D(map_Temporaire);
  return 0;                                                                     /* partie non-terminée */
}

void writeFile(char ** map2D)
{
  FILE * mapTXT = NULL;
  mapTXT = fopen("map.txt", "w+");
  if(!mapTXT) {
    perror("Opening Problem in writeFile()");
    exit(EXIT_FAILURE);
  }
  for(int i=0; i<N; ++i) {
    for(int j=0; j<N; ++j){
      fputc(map2D[i][j], mapTXT);
    }
    fputs("\n", mapTXT);
  }
  fclose(mapTXT);
}


/*Attention malloc ici, il faut libérer char **  */ 
char **  readFile(char  * nameFile)
{
  FILE * mapTXT = NULL;
  mapTXT = fopen(nameFile, "r");
  if (!mapTXT){
    perror("Opening Problem in readFile()");
    exit(EXIT_FAILURE);
  }

  char ** map2D = createMap2D();
  if (!map2D)
  {
    perror("Error Allocation Memory in readFile()");
    exit(EXIT_FAILURE);
  }
  int  charActu = ' ';
  int i = 0 ; int j = 0 ;
  while (charActu != EOF)
  {
    charActu = fgetc(mapTXT);
    if ('0' == charActu || 'b' == charActu ||  'n' == charActu)
    {
      map2D[i][j] = charActu;
      ++ j;
      if (N == j)
      {
	j = 0 ;
	++i   ;
      }
    }
  }
  fclose(mapTXT);
  return map2D;
}


void vider_buffer(void)
{
    int c; 
    do {
        c = getchar();
    } while(c != '\n' && c != EOF);
}


char checkGameOption(char input)
{
  while (input != '1' &&  input != '2')
  {
    printf("Je n'ai pas compris !  \n\nQue voulez-vous faire ? \n[1] Jouer un nouveau piont ? (de votre pile)  \n[2] Deplacer un piont se trouvant sur la map  \n");
    scanf(" %c",&input);
  }
  return input ;
}
void play()//char ** pileArray)
{
  char answer = ' ';
  printf("Que souhaitez-vous faire ? \n[1] Jouer un nouveau piont ? (de votre pile)  \n[2] Deplacer un piont se trouvant sur la map  \n");
  scanf("%c", &answer);
  answer = checkGameOption(answer);
  printf("%c \n", answer);
  
}

/*Fonctions d'erreur pour eviter la répétition :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void errorInCreate3D() 
{
    perror("ERROR ALLOCATION MEMORY in createMap\n");
    exit(EXIT_FAILURE);
}

void errorInCreate2D() 
{
    perror("ERROR ALLOCATION MEMORY in createMap2D\n");
    exit(EXIT_FAILURE);
}
