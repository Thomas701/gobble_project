#include "fonction.h"

/*Fonctions active:
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*return la taille du piont le plus grand d'une pile*/
int sizePiontMaxStack(char ** stackArray, int numStack)
{
  int sizePiont = 0 ;
  for(int i = N-1 ; i >= 0 ; i--)
  {
    if (stackArray[numStack][i] != '0')
    {
      sizePiont = i; i = -1;
    }
  }
  return sizePiont ;
}

/*return 1 si réussi à déplacer, 0 sinon */
void mooveSinceStack(char *** map, char ** stackArray, int numStack,int sizePiont ,int endPiont, char c) // c = 'b' or 'n'
{
  stackArray[numStack][sizePiont] = '0';
  int x = (endPiont - endPiont % N) / N;
  int y = endPiont % N;
  map[x][y][sizePiont] = c;
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

void gameOption(char ** stackArray, char *** map3D,char ** map2D, char c) // c = 'b' or 'n' joueur qui choisie
{
  if (c == 'b')
    printf("Joueur 1, c'est a vous!\n");
  else
    printf("Joueur 2, c'est a vous!\n");
  int answer = 0;
  answer = (isStackFull(stackArray)) ? 1 : 0;
  if (canPlayNewPiont(stackArray, map2D) && !isStackFull(stackArray))
  {
      printMap2D(map2D);
      printMap3dDebug(map3D);
      printf("Que souhaitez-vous faire ? \n[1] Jouer un nouveau piont ? (de votre pile)  \n[2] Deplacer un piont se trouvant sur la map  \n");
      scanf(" %d", &answer);
      vider_buffer();
      while (answer != 1 &&  answer != 2)
      {
        printf("Je n'ai pas compris !  \n\nQue voulez-vous faire ? \n[1] Jouer un nouveau piont ? (de votre pile)  \n[2] Deplacer un piont se trouvant sur la map  \n");
        scanf(" %d",&answer);
        vider_buffer();
      }
  }
  
  if (answer == 2 || answer == 0) // cas ou il a choisi l'option 2 ou cas ou il a seulement l'option 2 possible
  {
    int debPiont = 0 ;
    int endPiont = 0 ;

    printMap2D(map2D);
    printMap3dDebug(map3D);
    printf("Quel piont voulez-vous déplacer ? \n");
    scanf(" %d", &debPiont);
    vider_buffer();

    while(debPiont < 0 || debPiont > N*N-1 || !canMooveThisPiont(map3D, map2D, debPiont, c))
    {
      printf("Index non valide ! \nQuel piont voulez vous déplacer ?\n");
      scanf(" %d", &debPiont);
      vider_buffer();
    }

    printf("Sur quel case voulez vous déplacer le piont %d ? \n", debPiont);
    scanf(" %d", &endPiont);
    vider_buffer();

    while(endPiont < 0 || endPiont > (N*N)-1 || endPiont == debPiont || !canMoove(map3D, debPiont, endPiont))
    {
      printf("Deplacement invalide, veuillez recommencer. \n");
      printf("Sur quelle case voulez vous déplacer le piont %d ? \n", debPiont);
      scanf(" %d", &endPiont);
      vider_buffer();
    }
    moove(map3D, debPiont, endPiont);
    initMap2D(map2D, map3D);
  }
  
  else // cas ou il joue un nouveau piont et il peut le jouer cad il existe une pile ou il peut mettre un piont sur le plateau
  {
    int numStack ;
    int endPiont ;
    printMap2D(map2D);
    printMap3dDebug(map3D);
    printf("Voici vos piles : \n");
    printStacks(stackArray);
    printf("Quelle pile voulez vous jouer ?\n");
    scanf(" %d",&numStack);
    while(numStack < 0 || numStack > N-2 || isEmptyStack(stackArray, numStack) || !canPlayStack(sizePiontMaxStack(stackArray , numStack), map3D))
    {
      printf("Vous ne pouvez rien faire avec cette pile ! \nVeuillez saisir un nouveau numéro de pile.\n");
      scanf(" %d", &numStack);
      vider_buffer();
    }
    int sizePiontMax = sizePiontMaxStack(stackArray, numStack);
    printMap2D(map2D);
    printMap3dDebug(map3D);
    printf("A quelle place voulez vous jouez le piont numéro %d ? \n", sizePiontMax);
    scanf(" %d", &endPiont);
    vider_buffer();
    while(endPiont < 0 || endPiont > (N*N)-1 || !canPutPiont(map3D, sizePiontMax,endPiont))
    {
      printf("Position arrivé invalide !\nVeuillez resaisir le numéro de case où vous voulez jouer [%d] \n", canPutPiont(map3D, sizePiontMax,endPiont));
      scanf(" %d", &endPiont);
      vider_buffer();
    }
    mooveSinceStack(map3D, stackArray, numStack, sizePiontMax, endPiont, c);
    initMap2D(map2D, map3D);
 }
}

/*Fonctions Vérifications :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int isEmptyStack(char ** stack, int num) // La pile est vide?
{
  for (int i = 0; i < N; i++)
  {
    if (stack[num][i] != '0')
      return 0;
  }
  return 1;
}

int isEmptyStacks(char ** stack)
{
  for(int i = 0; i < N-1; i++) 
  {
    for(int j = 0; j < N; j++) 
    { // ascendant pour opti
      if (stack[i][j] != '0')
      {
        return 0;
      }
    }
  }
  return 1;
}

int isEmptyCase(char ** map2D)
 {
   for(int i = 0; i < N; i++)
   {
     for(int j = 0 ; j < N ; j++)
     {
       if('0' == map2D[i][j])
        return 1;
     }
   }
   return 0;
 }

int canMoove(char *** map, int posDeb, int posEnd) // Le pion peut-il bouger?
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
      count = i+1;
    if (map[x2][y2][i] != '0')
      count2 = i+1;
  }
  if (count > count2)
    return 1;
  else
    return 0;
}

int canMooveThisPiont(char *** map, char ** map2D, int posDeb, char c) // Le pion peut-il bouger?
{
  int x      = (posDeb - posDeb % N) / N;
  int y      = posDeb % N;
  int count  = -1;
  char piont;
  for (int i = 0; i < N; i++)
  {
    if (map[x][y][i] != '0')
    {
      count = i;
      piont = map[x][y][i];
    }
  }
  if (piont != c)
    return 0;
  else
  {
    if(isEmptyCase(map2D))
      return 1;
    else
    {
      int max;
      for (int i = 0; i < N; i++)
      {
        for (int j = 0; j < N; j++)
        {
          max = N-1;
          for (int k = N-1; k >= 0; k--)
          {
            if (map[x][y][k] != '0')
            {
              max = k;
              k = -1;
            }
          }
          if (max < count)
            return 1;
        }
      }
      return 0;
    }
  }
}

int count_pion(char *** map, int nbre, char c) //Y'a t-il un alignement de nbre pion de type "c" sur la map?
{
  char ** map_Temporaire = createMap2D();
  initMap2D(map_Temporaire, map);
  int count_L  = 0; int count_C  = 0; 
  int count_DD = 0; int count_DG = 0; 

/* Vérification si il y a une ligne, colonne ou diagonale complété */
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      count_L += (map_Temporaire[i][j] == c) ? 1 : 0;
      count_C += (map_Temporaire[j][i] == c) ? 1 : 0;
      count_DD += (map_Temporaire[j][j] == c) ? 1 : 0;
      count_DG += (map_Temporaire[N-1-j][j] == c) ? 1 : 0;
    }
    if (count_C == nbre || count_L == nbre || count_DD == nbre || count_DG == nbre) /* partie terminée */
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
  return 0; /* partie non-terminée */
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
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N-1; j++)
    {
      if (map_Temporaire[i][j] == map_Temporaire[i][j+1] && map_Temporaire[i][j] != '0') {count_L++;}
      if (map_Temporaire[j][i] == map_Temporaire[j+1][i] && map_Temporaire[j][i] != '0') {count_C++;}
      if (map_Temporaire[j][j] == map_Temporaire[j+1][j+1] && map_Temporaire[j][j] != '0') {count_DD++;}
      if (map_Temporaire[N-1-j][j] == map_Temporaire[N-1-(j+1)][j+1] && map_Temporaire[N-1-j][j] != '0') {count_DG++;}
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


/*return 1 si on a au moins une pile ayant une taille max de piont de 1
  patant de l'hypothèse que les piles sont non vide appelle dans canPlayNewPiont
*/
int sizeMaxPiont(char ** stackArray)
{
  for(int i = 0 ; i < N-1 ; i++)
  {
    for(int j = N-1 ; j >= 1 ; j--)
    {
      if('0' != stackArray[i][j]) 
        return 0;
    }
  }
  return 1;
}

int canPlayNewPiont(char **  stackArray, char ** map2D)
{
  if(isEmptyCase(map2D))
  {
    if(isEmptyStacks(stackArray)) 
      return 0;

    else 
      return 1;
  }
  else
  {
    if(sizeMaxPiont(stackArray)) 
      return 0;

    else 
      return 1;
  }
}

int canPlayStack(int sizePiont, char *** map)
{
  int possible;
  for(int i = 0 ; i < N ; i++)
  {
    for(int j = 0 ; j < N ; j++)
    {
      possible = 1 ;
      for(int k = N-1 ; k >= sizePiont; k--)
      {
	if (map[i][j][k] != '0')
        {
	  possible = 0 ;
	  k = -1;
	}
      }
      if(1 == possible) return 1; 
    }
  }
  return 0;
}

int canPutPiont(char *** map, int sizePiont, int endPiont)
{
  int x = (endPiont - endPiont % N) / N;
  int y = endPiont % N;
  for(int i = N-1; i >= sizePiont ; i--)
  {
    if(map[x][y][i] != '0')
      return 0;
  }
  return 1;
}

int isStackFull(char ** pile1)
{
  for (int i = 0; i < N-1; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if (pile1[i][j] == '0')
        return 0;
    }
  }
  return 1;
}

/*Fonctions création de maps et piles :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

char ** createStack(char c)
{
  char ** pile = (char **) malloc(sizeof(char *)*(N-1));
  if(!pile) 
    errorInCreatePile();

  for(int i = 0; i < N-1; i++)
  {
    pile[i] = (char*) malloc(sizeof(char)*N);
    if(!pile[i])
    {
      for(int l = 0; l < i; l++) { free(pile[l]); pile[l] = NULL; }
      free(pile); pile = NULL;
      errorInCreatePile() ;
    }
  }

  for (int i = 0; i < N-1; i++)
  {
    for (int j = 0; j < N; j++)
      pile[i][j] = c;
  }
  return pile;
}

char *** createMap() 
{
  char *** map;

  map = (char ***) malloc(sizeof(char **)*N);
  if(!map) errorInCreate3D() ; // map == NULL

  for(int i = 0 ; i < N; i++) 
  {
    map[i] = (char **) malloc(sizeof(char *)*N);
    if(!map[i])
    {
      for(int l = 0; l < i; l++) { free(map[l]); map[l] = NULL; }
      free(map); map = NULL;
      errorInCreate3D() ;
    }

    for(int j = 0; j<N; j++)
    {
      map[i][j] = (char *) malloc(sizeof(char) * N);
      if(!map[i][j])
      {
        for(int m = 0; m < j; m++) { free(map[i][m]); map[i][m] = NULL; }
        for(int n = 0; n < i; n++) { free(map[n]); map[n] = NULL; }
        free(map); map = NULL;
        errorInCreate3D() ;
      }
    }
  }
  return map ;
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

/*Fonctions initialisation de maps :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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

void  initMap2D(char ** map2D, char *** map3D)
{
  for(int i=0; i < N; i++)
  {
    for(int j=0; j < N; j++)
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

/*Fonctions print pour afficher les maps & piles :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void printMap3dDebug(char *** map)
{
  for(int i = 0 ; i < N ; ++i)
  {
    for(int j = 0 ; j < N ; ++j)
    {
      printf("[%d][ ", j+i*N);
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
       printf("%c ", map2D[i][j]);
    printf("\n");
  }
  printf("\n");
}

void printStacks(char ** stacksArray)
{
  for(int i = 0; i < N-1 ; i++)
  {
    printf("pile numéro %d : |", i);
    for(int j=0; j < N ; j++)
      printf(" %c |", stacksArray[i][j]);
    printf("\n");
  }
}

/*Fonctions free pour libérer la mémoire :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void vider_buffer(void)
{
    int c; 
    do {
        c = getchar();
    } while(c != '\n' && c != EOF);
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
  if(map2D)
  {
    for(int i=0; i<N; i++)
    {
      free(map2D[i]); map2D[i] = NULL;
    }
    free(map2D); map2D = NULL;
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

/*Fonctions lecture/ecriture fichiers :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/* blanc : 1, 2, 3 | noir : a, b, c */
void writeFile(char *** map3D)
{
  FILE * mapTXT = NULL;
  mapTXT = fopen("map.txt", "w+");
  if(!mapTXT) {
    perror("Opening Problem in writeFile()");
    exit(EXIT_FAILURE);
  }
  int find = 0 ;
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      find = 0;
      for(int k=N-1; k>=0; --k) {
	       if(!find && map3D[i][j][k] != '0') {
	         if(map3D[i][j][k] == 'b')
	           fputc('1'+k, mapTXT);
	         else
	           fputc('a'+ k, mapTXT);
	         find++;
	       }
       }
        if (!find)
          fputc('0', mapTXT);
    }
    fputs("\n", mapTXT);
  }
  fclose(mapTXT);
}

/* retourne char *** Attention malloc ici, il faut libérer char *** */ 
char ***  readFile3D(char  * nameFile)
{
  FILE * mapTXT = NULL;
  mapTXT = fopen(nameFile, "r");
  if (!mapTXT){
    perror("Opening Problem in readFile()");
    exit(EXIT_FAILURE);
  }

  char *** map3D = createMap();
  if (!map3D)
  {
    perror("Error Allocation Memory in readFile()");
    exit(EXIT_FAILURE);
  }
  initMap(map3D);
  char  charActu = ' ';
  int i = 0 ; int j = 0 ; int k ;
  while (charActu != EOF)
  {
    charActu = fgetc(mapTXT);
    if ('0' == charActu ||
	  (charActu >= '1' && charActu <= '3' )||
	  (charActu >= 'a' && charActu <= 'c'))
    {
      if ('0' == charActu) k = 0 ;
      else if (charActu >= '1' && charActu <= '3' ) k = charActu - '1';
      else k =  charActu - 'a' ;

      if (charActu >= 'a') {charActu = 'n';}
      else if (charActu >= '1') {charActu = 'b';}
  
      map3D[i][j][k] = charActu;
      j++;
      if (N == j)
      {
        j = 0 ;
        i++ ;
      }
    }
  }
  fclose(mapTXT);
  return map3D;
}

/* return map2D Attention malloc ici, il faut libérer char ** */ 
char **  readFile2D(char  * nameFile)
{
  FILE * mapTXT = NULL;
  mapTXT = fopen(nameFile, "r");
  if (!mapTXT)
  {
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
    if ('0' == charActu ||
	  (charActu >= '1' && charActu <= '3' )||
	  (charActu >= 'a' && charActu <= 'c'))
    {
      if (charActu >= 'a')  {charActu = 'n';}
      else if (charActu >= '1') {charActu = 'b';}
      
      map2D[i][j] = charActu;
      j++;
      if (N == j)
      {
        j = 0 ;
        i++ ;
      }
    }
  }
  fclose(mapTXT);
  return map2D;
}


/*Fonctions d'erreur pour eviter la répétition :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void errorInCreatePile() 
{
    perror("ERROR ALLOCATION MEMORY in createPile\n");
    exit(EXIT_FAILURE);
}

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

