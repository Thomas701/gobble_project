#include "fonction.h"

/*Fonctions Vérifications :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void debugTab(SDL_Rect ** tableauCase)
{
  for (int i = 0; i < (N*N) + (N*2); i++)
  {
    if (tableauCase[i]->x > 2000 || tableauCase[i]->x < 0 || tableauCase[i]->y > 2000 || tableauCase[i]->y < 0 
    || tableauCase[i]->w > 2000 || tableauCase[i]->w < 0 || tableauCase[i]->h > 2000 || tableauCase[i]->h < 0)
    {
      printf("ERROR INITIALISATION CASE:\n %d && %d && %d && %d\n", tableauCase[i]->x,tableauCase[i]->y, tableauCase[i]->w > 2000, tableauCase[i]->h + tableauCase[i]->y > 2000);
      free(tableauCase[i]);
      tableauCase[i] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
      initTableauCase(tableauCase);
    }
  }
}

int maximum(int i, int i2) { return (i > i2) ? i : i2; }

int minimum(int i, int i2) { return (i > i2) ? i2 : i; }

int existPiontInMap(char ** map2D, char c)
{
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < N; j++)
    {
      if (map2D[i][j] == c)
        return 1;
    }
  }
  return 0;
}

int existPiontInStack(char ** stack, int num, int i)
{
  if (stack[num][i] == '0')
    return 0;
  else
    return 1;
}

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

int canMooveThisPiont(char *** map, char ** map2D ,int posDeb, char c) // Le pion peut-il bouger?
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

int canMooveThisPiontD(char *** map, int posDeb, char c) // Le pion peut-il bouger?
{
  int x      = (posDeb - posDeb % N) / N;
  int y      = posDeb % N;
  int count  = -1;
  int max;
  char piont;
  //printf("AMAURY: 1\n");
  for (int i = 0; i < N; i++)
  {
    //printf("AMAURY: 2 + [%d]\n", i);
    if (map[x][y][i] != '0')
    {
      count = i;
      piont = map[x][y][i];
    }
  }
  //printf("AMAURY: 3\n");
  if (piont != c)
    return 0;
  else
  {
    //printf("AMAURY: 4\n");
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        max = -1; // gros nombre!
        for (int k = 0; k < N ; k++)
        {
          //printf("AMAURY 5: i=%d, j=%d, k=%d\n", i, j, k);
          if (map[i][j][k] != '0')
          {
            max = k;
            //printf("AMAURY IF ACTIVATE: i=%d, j=%d, k=%d\n", i, j, k);
            break; //Pour stopper la boucle
          }
        }
        if (max < count)
        {
          //printf("ALERTE MAX < COUNT\n");
          return 1;
        }
      }
    }
    //printf("NE RETOURNERA FINALEMENT RIEN\n");
    return 0;
  }
}

int canMooveThisPiontDistance(char *** map, int posDeb, char c) // Le pion peut-il bouger?
{
  int x      = (posDeb - posDeb % N) / N;
  int y      = posDeb % N;
  int i, j, iEnd, jEnd;
  int count  = -1;
  int max;
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
    i = maximum(0, x-1); iEnd = minimum(x+1, N-1);
    //printf("COMPTE RENDU:\n i=%d, iEnd=%d, j=%d, jEnd= %d, x=%d, y=%d\n",i, iEnd, j, jEnd, x, y);
    for (; i <= iEnd; i++)
    {
      j = maximum(0, y-1); jEnd = minimum(y+1, N-1);
      for (; j <= jEnd; j++)
      {
        max = -1; // gros nombre!
        for (int k = 0; k < N ; k++)
        {
          //printf("[2]k=%d, i= %d & j= %d & x= %d & y = %d ET %c\n", k, i, j, x, y, map[i][j][k]);
          if (map[i][j][k] != '0')
          {
            max = k;
            //printf("[2]i= %d & j= %d & k= %d & max= %d & count = %d\n", i, j, k,max, count);
            break; //Pour stopper la boucle
          }
        }
        if (max < count)
        {
          //printf("ALERTE MAX < COUNT\n");
          return 1;
        }
      }
    }
    //printf("NE RETOURNERA FINALEMENT RIEN\n");
    return 0;
  }
}

int count_pion(char ** map_Temporaire, int nbre, char c) //Y'a t-il un alignement de nbre pion de type "c" sur la map?
{
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
      return 1;
    }
    else
    {
      count_C = 0; count_L = 0; count_DD = 0; count_DG = 0;
    }
  }
  return 0;
}

int check_End_Game(char ** map_Temporaire)
{
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
      if (count_L == N-1)
        return (i == 0) ? 1 : (i == 1) ? 2 : 3;
      else if (count_C == N-1)
        return (i == 0) ? 4 : (i == 1) ? 5 : 6;
      else if (count_DD == N-1)
        return 7;
      else
        return 8;
    }
    else
    {
      count_C = 0; count_L = 0; count_DD = 0; count_DG = 0;
    }
  }
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
        return 1;
    }
  }
  return 0;
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
      return 1;
    else 
      return 0;
  }
}

int canPlayStack(int sizePiont, char *** map) //pardon petite fonction... <3
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
          break;
        }
      }
      if (1 == possible)
        return 1; 
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

SDL_bool isInRect(SDL_Point point, SDL_Point rectangleHautGauche, SDL_Point rectangleBasDroit) // pour favoir si le point est à l'interieur d'un rectangle
{
  if (point.x >= rectangleHautGauche.x && point.x <= rectangleBasDroit.x && point.y >= rectangleHautGauche.y && point.y <= rectangleBasDroit.y) // si le point est dans le rectangle
    return SDL_TRUE ;
  return SDL_FALSE;
}

SDL_bool isInRectangle(SDL_Point point, SDL_Rect rect)
{ 
  //printf("%d >= %d && %d <= %d && %d >= %d &&  %d <= %d ET MEME AVEC CA: %d\n", point.x, rect.x, point.x, (rect.x + rect.w), point.y, rect.y, point.y, (rect.y + rect.h));
  if(point.x >= rect.x && point.x <= (rect.x + rect.w) && point.y >= rect.y && point.y <= (rect.y + rect.h))
    return SDL_TRUE;
  return SDL_FALSE;
}

int canSelection(SDL_Point pointMouse, char *** map3D, char ** map2D, SDL_Rect ** tableauCase, char ** pileJ1, char ** pileJ2, char c, int distance)
{
  int index = getIndex(pointMouse, tableauCase);
  if(index != -1)
  {
    // cas des piles
    if(c == 'b' && index > (N*N)-1 && index < (N*N) + N)
    {
      for (int i = 0; i < N-1; i++)
      {
        if (pileJ1[i][(N-1)- index % N] != '0')
          return index;
      }
      return -1;
    }
    else if(c == 'n' && index > (N*N) + (N-1))
    {
      for (int i = 0; i < N-1; i++)
      {
        if (pileJ2[i][(N-1)- index % N] != '0')
          return index;
      }
      return -1;
    }
    // cas des pionts sur la map
    else if (index >= 0 && index < (N*N))
    {
      if (distance)
      {
        if (canMooveThisPiontDistance(map3D, index, c))
          return index;
        return -1;
      }
      else
      {
        if (canMooveThisPiontD(map3D, index, c))
          return index;
        return -1;
      } 
    }
    else
    {
      printf("Return [1]\n");
      return -1; // cas ou il clique sur la pile adversaire
    }
  }
  printf("Return [2]\n");
  return -1; // cas index == -1
}


/*arrivée pas le droit de poser sur une pile*/
int canPlay(int imageIndexP, SDL_Point pointMouse, SDL_Rect ** tableauCase, char *** map3D, char ** pile, int distance)
{
  int index = getIndex(pointMouse, tableauCase);
  int x1 = (imageIndexP - imageIndexP % N) / N;
  int y1 = imageIndexP % N;
  int x2 = (index - index % N) / N;
  int y2 = index % N;
  

  if (index == -1 || index > 8)
  {
    printf("return: 0\n");
    return -1;
  }
  else
  {
    if (imageIndexP > 8)
    {
      int sizePiontMax = (imageIndexP == 9 || imageIndexP == 12) ? 2 : (imageIndexP == 10 || imageIndexP == 13) ? 1 : 0 ;
      if (canPutPiont(map3D, sizePiontMax, index))
        return index;
      else
      {
        printf("return: 1\n");
        return -1;
      }
    }
    else
    {
      if (canMoove(map3D, imageIndexP, index) && (maximum(abs(x1-x2), abs(y1-y2)) <= 1 || distance == 0))
        return index;
      else
      {
        printf("return: 2\n");
        return -1;
      }
    }
  }
}

/*verifie si on peut deplacer un pion dans une map*/
int canEffectDeplacementWithDistance(char *** map3D, char c)
{
  int posDeb;
  for (int i = 0; i < N; i++)
  {
      for(int j = 0;j < N; j++)
      {
        posDeb = (i * N) + j;
        //printf("POSDEP: %d ET i=%d, j=%d, PAR CONSEQUENT AV COMPTE RENDU:\n", posDeb, i, j);
        if (canMooveThisPiontDistance(map3D, posDeb, c))
        {
          //printf("BOUGEABLE!\n");
          return 1;
        }
      }
  }
  return 0;
}

int getSizePionOnCase(char *** map3D, int i, int j)
{
  int size = -1;
  for (int k = N-1; k >= 0; k--)
  {
    if(map3D[i][j][k] != '0')
      size = k;
  }
  return size;
}

int getSizePionOnCase2(char *** map3D, int index)
{
  int i = (index - index % N) / N;
  int j = index % N;
  int size = -1;
  for (int k = N-1; k >= 0; k--)
  {
    if(map3D[i][j][k] != '0')
    {
      size = k;
      break;
    }
  }
  return size;
}

char getCaractereOnCase(char *** map3D, int index)
{
  int i = (index - index % N) / N;
  int j = index % N;
  for (int k = N-1; k >= 0; k--)
  {
    if(map3D[i][j][k] != '0')
      return map3D[i][j][k];
  }
  return '0';
}

int getIndexPionWhoAreEat(char *** map3D, int index)
{
  int size = getSizePionOnCase2(map3D, index);
  printf("SIZE = %d pour index = %d\n", size, index);
  if (size == -1)
    return -1;
  else
  {
    char c = getCaractereOnCase(map3D, index);
    return (c == 'b') ? (N-1) - size : ((N-1) - size) + N;
  }
}