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

void gameOptionGraphique(SDL_Renderer * renderer, SDL_Texture *  textureMapVide, point ** tableauDePoint, SDL_Rect ** tableauCase,  char ** pileJ1, char ** pileJ2, char *** map3D, char ** map2D, int * p_etats, int boolPlayMusic, SDL_Texture ** textureTableauOptionMenu, SDL_Texture ** textureTableauPiont) // c = 'b' or 'n' joueur qui choisie
{
  int selection = 0;
  int imageIndexP = -1; // indique l'indexe de l'image qui a été selectionnée
  int imageIndexS = -1;
  char c = 'b';
  SDL_Event event;
  SDL_Point pointMouse;
  int sizePiontMax ;

  while(2 == *p_etats) // boucle principale
  {
    if (check_End_Game(map3D))
      *p_etats = 1;
    while(SDL_PollEvent(&event)) // programme continue et un nouveau evenement dans la file
    {
      switch(event.type)
      {
        case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) // bouton souris gauche
        {
          SDL_GetMouseState(&pointMouse.x, &pointMouse.y); // recupere coord souris
          if (selection == 0)
          {
            imageIndexP = canSelection(pointMouse, map3D, map2D, tableauCase, pileJ1, pileJ2, c);
          }
          else
          {
            if(c == 'b')
            {
              imageIndexS = canPlay(imageIndexP, pointMouse, tableauCase, map3D, pileJ1);
            }
            else
              imageIndexS = canPlay(imageIndexP, pointMouse, tableauCase, map3D, pileJ2);
          }
          if (selection == 1 && imageIndexS == -1)
            selection = 0;
          else if (selection == 0 && imageIndexP != -1)
            selection = 1;
          else if (selection == 1 && imageIndexS != -1)
          {
            if (imageIndexP > 8)
            {
              int numStack = (imageIndexP == 9 || imageIndexP == 11) ? 0 : 1 ;
              if(c == 'b')
              {
                sizePiontMax = sizePiontMaxStack(pileJ1, numStack);
                mooveSinceStack(map3D, pileJ1, numStack, sizePiontMax, imageIndexS, c);
                c = (c == 'b') ? 'n' : 'b';
                selection = 0;
              }
              else
              {
                sizePiontMax = sizePiontMaxStack(pileJ2, numStack);
                mooveSinceStack(map3D, pileJ2, numStack, sizePiontMax, imageIndexS, c);
                c = (c == 'b') ? 'n' : 'b';
                selection = 0;
              }
            }
            else
            {
              moove(map3D, imageIndexP, imageIndexS);
              c = (c == 'b') ? 'n' : 'b';
              selection = 0;
            }
            initMap2D(map2D, map3D);
          }
        }
      }
      SDL_RenderClear(renderer);
      printMapEmptySDL(textureMapVide, renderer);
      affichePileSDL(renderer, textureTableauPiont, tableauDePoint, pileJ1, pileJ2);
      affichePiontSurPlateau(renderer, textureTableauPiont, tableauDePoint, map3D);
      SDL_RenderPresent(renderer);
    }
  }
}

void loadAndPlayMainMusic(Mix_Music ** mainMusic)
{
  // initialisation de la musique
  * mainMusic = Mix_LoadMUS("Music/mainMusic.mp3");
  Mix_VolumeMusic(MIX_MAX_VOLUME/8);
  if(!* mainMusic)
    fprintf(stderr, "Error for load mainMusic : %s \n",SDL_GetError());
  
  // play music
  if(0 != Mix_PlayMusic(* mainMusic, -1))
    fprintf(stderr, "Error in Mix_PlayMusic %s\n", SDL_GetError());
}

int getIndex(SDL_Point pointMouse, SDL_Rect ** tableauCase)
{
  for(int i = 0 ; i < 13 ; ++i)
  {
    if(isInRectangle(pointMouse, *tableauCase[i]))
      return i;
  }
  return -1;
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

SDL_bool isInRect(SDL_Point point, SDL_Point rectangleHautGauche, SDL_Point rectangleBasDroit) // pour favoir si le point est à l'interieur d'un rectangle
{
  if (point.x >= rectangleHautGauche.x && point.x <= rectangleBasDroit.x && point.y >= rectangleHautGauche.y && point.y <= rectangleBasDroit.y) // si le point est dans le rectangle
    return SDL_TRUE ;
  return SDL_FALSE;
}

SDL_bool isInRectangle(SDL_Point point, SDL_Rect rect)
{
  if(point.x >= rect.x && point.x <= (rect.x + rect.w) && point.y >= rect.y && point.y <= (rect.y + rect.h))
    return SDL_TRUE;
  return SDL_FALSE;
}

int canSelection(SDL_Point pointMouse, char *** map3D, char ** map2D, SDL_Rect ** tableauCase, char ** pileJ1, char ** pileJ2, char c)
{
  int index = getIndex(pointMouse, tableauCase);
  int sizePiont; int numStack;
  if (index > 8)
    numStack = (index == 9 || index == 11 )? 0: 1;
  if(index != -1)
  {
    // cas des piles
    if(c == 'b' && (9 == index || 10 == index)) 
    {
      if (isEmptyStack(pileJ1, numStack))
        return -1;
      sizePiont = sizePiontMaxStack(pileJ1, numStack) ;
      if(canPlayStack(sizePiont, map3D))
      {
        return index;
      }
      return -1;
    }
    else if(c == 'n' && (11 == index || 12 == index))
    {
      if (isEmptyStack(pileJ2, numStack))
        return -1;
      sizePiont = sizePiontMaxStack(pileJ2, numStack);
      if(canPlayStack(sizePiont, map3D))
      {
        return index;
      }
      return -1;
    }
    // cas des pionts sur la map
    else if (index >= 0 && index < 9)
    {
      if (canMooveThisPiont(map3D, map2D, index, c))
        return index;
      return -1;
    }
    else
      return -1; // cas ou il clique sur la pile adversaire
  }
  return -1; // cas index == -1
}


/*arrivée pas le droit de poser sur une pile*/
int canPlay(int imageIndexP, SDL_Point pointMouse, SDL_Rect ** tableauCase, char *** map3D, char ** pile)
{
  int index = getIndex(pointMouse, tableauCase);

  if (index == -1 || index > 8)
    return -1;
  else
  {
    if (imageIndexP > 8)
    {
      int numStack = (imageIndexP == 9 || imageIndexP == 11) ? 0 : 1 ;
      int sizePiontMax = sizePiontMaxStack(pile, numStack);
      if (canPutPiont(map3D, sizePiontMax, index))
        return index;
      else
        return -1;
    }
    else
    {
      if (canMoove(map3D, imageIndexP, index))
        return index;
      else
        return -1;
    }
  }
}

/*Fonctions création de maps, piles, images :
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

SDL_Texture * loadImage(const char * path, SDL_Renderer *renderer)
{
  SDL_Surface *tmp = NULL;
  SDL_Texture *texture = NULL;
  tmp = IMG_Load(path);

  if(!tmp) // probleme chargement image
  {
    fprintf(stderr, "Erreur SDL_Load : %s\n", SDL_GetError());
    return NULL;
  }
  texture = SDL_CreateTextureFromSurface(renderer, tmp);
  SDL_FreeSurface(tmp);

  if(!texture) // probleme transfo image en texture
  {
    fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
    return NULL;
  }
  return texture;
}

int createPoint(point *** pTableauDePoint)
{
  point ** tableauDePoint = (point ** ) malloc(sizeof(point *) * 13);
  for(int i = 0 ; i < 13 ; ++i)
  {
    tableauDePoint[i] = malloc(sizeof(point) * 1);
    if(!tableauDePoint[i])
    {
      perror("Error allocation memory in createPoint for tableauDePoint[i] \n");
      for(int j = 0 ; j < i ; ++j)
        free(tableauDePoint[j]);
      free(tableauDePoint);
      return -1;
    }
  }
  tableauDePoint[ 0]->x = 502 ;  tableauDePoint[ 0]->y = 404 ;
  tableauDePoint[ 1]->x = 658 ;  tableauDePoint[ 1]->y = 405 ;
  tableauDePoint[ 2]->x = 807 ;  tableauDePoint[ 2]->y = 406 ;
  tableauDePoint[ 3]->x = 486 ;  tableauDePoint[ 3]->y = 517 ;
  tableauDePoint[ 4]->x = 664 ;  tableauDePoint[ 4]->y = 519 ;
  tableauDePoint[ 5]->x = 828 ;  tableauDePoint[ 5]->y = 517 ;
  tableauDePoint[ 6]->x = 465 ;  tableauDePoint[ 6]->y = 655 ;
  tableauDePoint[ 7]->x = 664 ;  tableauDePoint[ 7]->y = 649 ;
  tableauDePoint[ 8]->x = 854 ;  tableauDePoint[ 8]->y = 652 ;
  tableauDePoint[ 9]->x = 267 ;  tableauDePoint[ 9]->y = 423 ;
  tableauDePoint[10]->x = 222 ;  tableauDePoint[10]->y = 610 ;
  tableauDePoint[11]->x = 1032;  tableauDePoint[11]->y = 424 ;
  tableauDePoint[12]->x = 1069;  tableauDePoint[12]->y = 618 ;
  * pTableauDePoint = tableauDePoint;
  return 0;
}

int createCase(SDL_Rect *** pTableauCase)
{
  SDL_Rect ** tableauCase = (SDL_Rect **) malloc(sizeof(SDL_Rect *)*13);
  for(int i = 0 ; i < 13 ; i++)
  {
    tableauCase[i] = malloc(sizeof(SDL_Rect *) * 1);
    if(!tableauCase[i])
    {
      perror("Error allocation memory in createCase for tableauCase[i] \n");
      for(int j = 0 ; j < i ; ++j)
        free(tableauCase[j]);
      free(tableauCase);
      return -1;
    }
  }
  tableauCase[ 0]->w = 152 ; tableauCase[ 0]->h = 89 ;
  tableauCase[ 0]->x = 419 ; tableauCase[ 0]->y = 359 ;
  tableauCase[ 1]->w = 141 ; tableauCase[ 1]->h = 89 ;
  tableauCase[ 1]->x = 585 ; tableauCase[ 1]->y = 358 ;
  tableauCase[ 2]->w = 134 ; tableauCase[ 2]->h = 89 ;
  tableauCase[ 2]->x = 738 ; tableauCase[ 2]->y = 358 ;
  tableauCase[ 3]->w = 171 ; tableauCase[ 3]->h = 106 ;
  tableauCase[ 3]->x = 392 ; tableauCase[ 3]->y = 462 ;
  tableauCase[ 4]->w = 159 ; tableauCase[ 4]->h = 2 ;  // 107
  tableauCase[ 4]->x = 579 ; tableauCase[ 4]->y = 461 ;
  tableauCase[ 5]->w = 152 ; tableauCase[ 5]->h = 107 ;
  tableauCase[ 5]->x = 751 ; tableauCase[ 5]->y = 461 ;
  tableauCase[ 6]->w = 195 ; tableauCase[ 6]->h = 129 ;
  tableauCase[ 6]->x = 358 ; tableauCase[ 6]->y = 587 ;
  tableauCase[ 7]->w = 182 ; tableauCase[ 7]->h = 130 ;
  tableauCase[ 7]->x = 571 ; tableauCase[ 7]->y = 586 ;
  tableauCase[ 8]->w = 174 ; tableauCase[ 8]->h = 129 ;
  tableauCase[ 8]->x = 765 ; tableauCase[ 8]->y = 586 ;
  tableauCase[ 9]->w = 182 ; tableauCase[ 9]->h = 156 ;   // pile bleu fond
  tableauCase[ 9]->x = 168 ; tableauCase[ 9]->y = 307 ;
  tableauCase[ 10]->w = 169 ; tableauCase[ 10]->h = 184 ;  // pile bleu devant
  tableauCase[ 10]->x = 139 ; tableauCase[ 10]->y = 497 ;
  tableauCase[ 11]->w = 179 ; tableauCase[ 11]->h = 157 ;  // pile rouge fond
  tableauCase[ 11]->x = 949 ; tableauCase[ 11]->y = 307 ;
  tableauCase[ 12]->w = 188 ; tableauCase[ 12]->h = 198 ;  // pile rouge devant
  tableauCase[ 12]->x = 982 ; tableauCase[ 12]->y = 497 ;
  * pTableauCase = tableauCase;
  return 0;
}

/*Fonctions initialisation  :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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

void initPile(char ** pile, char c)
{
  for (int i = 0; i < N-1; i++)
  {
    for (int j = 0; j < N; j++)
      pile[i][j] = c;
  }
}

int loadTextureOptionMenu(SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu)
{
  SDL_Texture ** textureTableauOptionMenu = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*5);
  if (! textureTableauOptionMenu)
  {
    fprintf(stderr, "Erreur allocation memory in textureTableauOptionMenu\n"); 
    return -1;
  }
  for (int i = 0; i < 5; i++)
  {
    char nom[30];
    sprintf(nom, "Frames/option%d.png", i+1);

    textureTableauOptionMenu[i] = loadImage(nom, * renderer);
    if(!textureTableauOptionMenu[i]) { 
      fprintf(stderr, "Error loadTextureOptionMenu for textureTableauOptionMenu : %s\n", SDL_GetError()); 
      return -1; 
    }
  }
  * ptextureTableauOptionMenu = textureTableauOptionMenu;
  return 0;
}

/* return -1 si erreur 0 sinon*/
int initialiseDebutProgramme(SDL_Window ** window, SDL_Texture *** textureBackground, SDL_Texture ** textureMapVide, SDL_Surface ** icones, SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu, SDL_Texture *** pTextureTableauPiont, SDL_Texture *** pTextureTableauWin, point *** pTableauDePoint, SDL_Rect *** pTableauCase)
{
  // initialise le systeme gestion de rendu, d'évenements , audio et temps + test
  if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_TIMER))
  {
    fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
    return -1;
  }
    
  // alloue la fenetre
  * window = SDL_CreateWindow("GOBBLE GAME - PREP'ISIMA 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN) ;
  if(!* window)
  {
    fprintf(stderr, "Erreur SDL_CreateWindow : %s\n", SDL_GetError());
    return -1 ;
  }

  // initialisation renderer
  * renderer = SDL_CreateRenderer(* window, -1, SDL_RENDERER_ACCELERATED);
  if(!*renderer)
  {
    fprintf(stderr, "Error SDL_CreateRenderer for mainRenderer: %s\n", SDL_GetError());
    return -1;
  }
  
  // chargement de l'icones
  * icones = IMG_Load("Frames/icones.png");
  if (!* icones)
    SDL_Log("Erreur chargement icones IMG_Load : %s\n", Mix_GetError());
  else
    SDL_SetWindowIcon(* window, * icones);

  // chargement carte son
  if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0) // création de la configuration de la carte son
  {
    SDL_Log("Erreur initialisation SDL_mixer : %s\n", Mix_GetError());
    return -1 ;
  }

  // init texture background
  if(loadBackgroundMenu(renderer, textureBackground) != 0)
  {
    fprintf(stderr, "Error loadImage for textureBackground : %s\n", SDL_GetError());
    return -1;
  }

  // init texture map vide
  * textureMapVide = loadImage("Frames/map.png", * renderer);
  if(!*textureMapVide)
  {
    fprintf(stderr, "Error loadImage for textureMenu : %s\n", SDL_GetError());
    return -1;
  }

  if (0 != loadTextureOptionMenu(renderer, ptextureTableauOptionMenu))
  {
    fprintf(stderr, "Error loadTextureOptionMenu for ptextureTableauOptionMenu : %s\n", SDL_GetError());
    return -1;
  }

  if (0 != loadPiont(renderer, pTextureTableauPiont))
  {
    fprintf(stderr, "Error in loadPiont : %s \n",SDL_GetError());
    return 1;
  }
  if(0 != createPoint(pTableauDePoint))
  {
    fprintf(stderr, "Error in createPoint : %s \n",SDL_GetError());
    return 1;
  }
  if(0 != createCase(pTableauCase))
  {
    fprintf(stderr, "Error in createCase : %s \n",SDL_GetError());
    return 1;
  }
  if(0 != loadTextureWin(renderer, pTextureTableauWin))
  {
    fprintf(stderr, "Error in loadTextureWin : %s \n",SDL_GetError());
    return 1;
  }
  return 0;
}

int loadPiont(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauPiont)/*return 0 si ok, -1 sinon*/
{
  SDL_Texture ** textureTableauPiont = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*6);

  if (!textureTableauPiont)
  {
    return -1;
  }
  textureTableauPiont[0] = loadImage("Frames/1B.png", * renderer);
  if(!textureTableauPiont[0])
  {
    fprintf(stderr, "Error loadPiont for texturePiont1B : %s\n", SDL_GetError());
    return -1;
  }
  textureTableauPiont[1] = loadImage("Frames/2B.png", * renderer);
  if(!textureTableauPiont[1])
  {
    fprintf(stderr, "Error loadPiont for texturePiont2B : %s\n", SDL_GetError());
    return -1;
  }
  textureTableauPiont[2] = loadImage("Frames/3B.png", * renderer);
  if(!textureTableauPiont[2])
  {
    fprintf(stderr, "Error loadPiont for texturePiont2B : %s\n", SDL_GetError());
    return -1;
  }
  textureTableauPiont[3] = loadImage("Frames/1R.png", * renderer);
  if(!textureTableauPiont[3])
  {
    fprintf(stderr, "Error loadPiont for texturePiont1R : %s\n", SDL_GetError());
    return -1;
  }
  textureTableauPiont[4]= loadImage("Frames/2R.png", * renderer);
  if(!textureTableauPiont[4])
  {
    fprintf(stderr, "Error loadPiont for texturePiont2R : %s\n", SDL_GetError());
    return -1;
  }
  textureTableauPiont[5] = loadImage("Frames/3R.png", * renderer);
  if(!textureTableauPiont[5])
  {
    fprintf(stderr, "Error loadPiont for texturePiont3R : %s\n", SDL_GetError());
    return -1;
  }
  * pTextureTableauPiont = textureTableauPiont;
  return 0;
}

int loadBackgroundMenu(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauBack)
{
  SDL_Texture ** textureTableauBack = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*400);

  if (! textureTableauBack) {fprintf(stderr, "Erreur allocation memory in loadBackgroundMenu\n"); return -1;}
  for (int i = 0; i < 400; i++)
  {
    char nom[30];
    sprintf(nom, "Frames/background2/p (%d).png", i+1);
    textureTableauBack[i] = loadImage(nom, * renderer);
    if(!textureTableauBack[i]) { fprintf(stderr, "Error loadPiont for loadBackgroundMenu : %s\n", SDL_GetError()); return -1; }
  }
  * pTextureTableauBack = textureTableauBack;
  return 0;
}

int loadTextureWin(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauWin)
{
  SDL_Texture ** TextureTableauWin = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*8);

  if (! TextureTableauWin) {fprintf(stderr, "Erreur allocation memory in loadTextureWin\n"); return -1;}
  for (int i = 0; i < 8; i++)
  {
    char nom[30];
    sprintf(nom, "Frames/win%d.png", i+1);
    TextureTableauWin[i] = loadImage(nom, * renderer);
    if(!TextureTableauWin[i]) { fprintf(stderr, "Error loadTextureWin for TextureTableauWin : %s\n", SDL_GetError()); return -1; }
  }
  * pTextureTableauWin = TextureTableauWin;
  return 0;
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

/* -1 si erreur , 0 sinon*/
int printMapEmptySDL(SDL_Texture * textureMapVide, SDL_Renderer * renderer)
{
  if (0 !=  SDL_RenderCopy(renderer, textureMapVide, NULL, NULL)) 
    { 
      fprintf(stderr, "Error SDL_RenderCopy in printMapEmptySDL : %s \n", SDL_GetError());
      return -1; 
    }
  return 0;
}

/*Fonctions free pour libérer la mémoire :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void vider_buffer(void)
{
  int c; 
  do 
  {
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

void writeFilePile(char ** pile1, char ** pile2)
{
  FILE * pileFile = NULL;
  pileFile = fopen("pile.txt", "w+");
  if(!pileFile) {
    perror("Opening Problem in writeFilePile()");
    exit(EXIT_FAILURE);
  }
  for(int i = 0; i < N-1; i++) {
    for(int j = 0; j < N; j++) {
        fputc(pile1[i][j], pileFile);
    }
    fputc('\n', pileFile);
  }
  fputc('\n', pileFile);

  for(int i = 0; i < N-1; i++) {
    for(int j = 0; j < N; j++) {
        fputc(pile2[i][j], pileFile);
    }
    fputc('\n', pileFile);
  }
  fclose(pileFile);
}

void readFilePile(char * nameFile, char ** pile1, char ** pile2)
{
  FILE * pileFile = NULL;
  pileFile = fopen(nameFile, "r");
  if (!pileFile)
  {
    perror("Opening Problem in readFilePile()");
    exit(EXIT_FAILURE);
  }
  char  charActu = ' ';
  int i = 0 ; int j = 0 ; int count = 0; int tour = 0;
  while (charActu != EOF)
  {
    charActu = fgetc(pileFile);
    if (charActu != '\n' && tour == 0)
    {
      printf("pile1, c=%c,i=%d, j=%d\n", charActu, i, j);
      pile1[i][j] = charActu;
      j++;
      count = 0;
    }
    else if (charActu != '\n' && tour == 1 && i < N-1)
    {
      printf("pile2, c=%c,i=%d, j=%d\n", charActu, i, j);
      pile2[i][j] = charActu;
      j++;
      count = 0;
    }
    else
    {
      count++;
      i++;
      j = 0;
    }
    if (count == 2)
    {
      i = 0;
      j = 0;
      tour++;
    }
  }
  fclose(pileFile);
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

/*Fonctions Graphique :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void intro_authors(SDL_Window ** window, SDL_Renderer ** renderer)
{
  SDL_Texture * texture_authors = NULL; // contient la texture qui va acceuilir l'image authors [texture]
  Mix_Music * music_intro = NULL;   // [musique]

  int r = rand() % 1;
  if (r == 0)
    texture_authors = loadImage("Frames/authors.png", *renderer);
  else
    texture_authors = loadImage("Frames/authors1.png", *renderer);

  if(!texture_authors)
  {
    fprintf(stderr, "Erreur loadImage : %s\n", SDL_GetError());
    perror("Impossible d'afficher la texture = NULL");
  }
  else
  {
    for (int i = 0 ; i < 130 ; ++i ) //boucle pour rendre l'image d'intro transparente
    {
      SDL_RenderClear(*renderer);
      if(0 != SDL_SetTextureAlphaMod(texture_authors, i))
        fprintf(stderr, "Erreur SDL_SetTextureAlphaMod: %s\n", SDL_GetError());
      else
      {
        SDL_RenderCopy(*renderer, texture_authors, NULL, NULL);
        SDL_RenderPresent(*renderer);
        SDL_Delay(15);
      }
    }
      
    music_intro = Mix_LoadMUS("Music/intro2.wav"); // alloue la musique de demarrage
    if (!music_intro)
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s\n", Mix_GetError());
    else 
    {
      Mix_VolumeMusic(MIX_MAX_VOLUME/6); // baisse volume musique
      Mix_PlayMusic(music_intro, 0);      // joue une seule fois
    }

    for (int i = 130 ; i < 255 ; ++i )
    {
      SDL_RenderClear(*renderer);
      if(0 != SDL_SetTextureAlphaMod(texture_authors, i))
      {
        fprintf(stderr, "Erreur SDL_SetTextureAlphaMod : %s\n", SDL_GetError());
      }
      else
      {
        SDL_RenderCopy(*renderer, texture_authors, NULL, NULL);
        SDL_RenderPresent(*renderer);
        SDL_Delay(15);
      }
    }
    for (int i = 255 ; i >= 0 ; --i)
    {
      SDL_RenderClear(*renderer);  // effacer image précédente
      if(0 != SDL_SetTextureAlphaMod(texture_authors, i))
      {
        fprintf(stderr, "Erreur SDL_SetTextureAlphaMod : %s\n", SDL_GetError());
      }
      else
      {
        SDL_RenderCopy(*renderer, texture_authors, NULL, NULL);
        SDL_RenderPresent(*renderer);
        SDL_Delay(15);
      }
    }
  }
  SDL_RenderClear(*renderer);
  if (texture_authors) SDL_DestroyTexture(texture_authors); // liberation texture
  if (music_intro) Mix_FreeMusic(music_intro); // libération de la musique, plus besoin
}

void lancementMenu(SDL_Renderer * renderer, SDL_Texture ** textureBackground, SDL_Texture ** textureTableauOptionMenu, int * p_etats, int boolPlayMusic)
{
  SDL_RenderClear(renderer);
  //boutons du menu
  SDL_Rect tableauRectOption[4];

  for(int i = 0; i < 3; i++)
  {
    SDL_QueryTexture(textureTableauOptionMenu[i], NULL, NULL, &tableauRectOption[i].w, &tableauRectOption[i].h);
    tableauRectOption[i].x = WIDTH /2 - tableauRectOption[i].w / 2; 
  }
  
  SDL_QueryTexture(textureTableauOptionMenu[3], NULL, NULL, &tableauRectOption[3].w, &tableauRectOption[3].h);
  tableauRectOption[3].x = WIDTH /2 - tableauRectOption[3].w / 2; 
  tableauRectOption[0].y = 318; tableauRectOption[1].y  = 488; tableauRectOption[2].y = 650; 
  tableauRectOption[3].x = WIDTH - tableauRectOption[3].w;     tableauRectOption[3].y = 0;

  SDL_Point pointMouse; //souris du menu pour evenement

  int incrImg = 0; // numero image menu (background)
  
  while(*p_etats == 1) // boucle principale
  {
    SDL_Event event;
    SDL_RenderClear(renderer);
    SDL_GetMouseState(&pointMouse.x, &pointMouse.y); // recupere coord souris

    if (0 != SDL_RenderCopy(renderer, textureBackground[incrImg%400], NULL, NULL)) {fprintf(stderr, "Error SDL_RenderCopy for textureBackground : %s, i = %d, et img = %p \n", SDL_GetError(), incrImg%400 , textureBackground[incrImg%400]);}
    
    for(int i=0; i<3; ++i)
    {
      if(isInRectangle(pointMouse, tableauRectOption[i]))
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[i], 255);
        if (0 != SDL_RenderCopy( renderer,  textureTableauOptionMenu[i], NULL, &tableauRectOption[i])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
      else
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[i], 150);
        if (0 != SDL_RenderCopy( renderer,  textureTableauOptionMenu[i], NULL, &tableauRectOption[i])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
    }
    if(isInRectangle(pointMouse, tableauRectOption[3]))
    {
      if(boolPlayMusic)
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[3], 255);
        if (0 != SDL_RenderCopy(renderer,  textureTableauOptionMenu[3], NULL, &tableauRectOption[3])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
      else
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[4], 255);
        if (0 != SDL_RenderCopy(renderer,  textureTableauOptionMenu[4], NULL, &tableauRectOption[3])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
    }
    else
    {
      if(boolPlayMusic)
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[3], 100);
        if (0 != SDL_RenderCopy(renderer,  textureTableauOptionMenu[3], NULL, &tableauRectOption[3])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
      else
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[4], 100);
        if (0 != SDL_RenderCopy(renderer,  textureTableauOptionMenu[4], NULL, &tableauRectOption[3])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
    }

    incrImg++;
    SDL_RenderPresent(renderer);
    SDL_Delay(50);
    while(SDL_PollEvent(&event)) // programme continue et un nouveau evenement dans la file
    {
      SDL_GetMouseState(&pointMouse.x, &pointMouse.y); // recupere coord souris
      switch(event.type)
      {
        case SDL_QUIT : //quitter
          *p_etats = 0;
          break ;

        case SDL_MOUSEBUTTONDOWN :  // bouton souris enfonce
          if (event.button.button == SDL_BUTTON_LEFT) // bouton souris gauche
          {
            if (isInRectangle(pointMouse , tableauRectOption[0])) // 2 joueurs en local
            {
              *p_etats = 2 ;
              SDL_RenderClear(renderer);
            }
            else if(isInRectangle(pointMouse , tableauRectOption[1])) // IA min max
            {
              *p_etats = 3 ;
              SDL_RenderClear(renderer);
              printf("Lancement jeu contre IA \n");
            }
            else if(isInRectangle(pointMouse , tableauRectOption[3])) // sond
            {
              if(boolPlayMusic == 0) 
              {
                boolPlayMusic = 1; 
                Mix_ResumeMusic();
              }
              else 
              {
                boolPlayMusic = 0; 
                Mix_PauseMusic();
              }
            }
            else if(isInRectangle(pointMouse , tableauRectOption[2])) // choix QUITTER
            {
              *p_etats = 0;
            }
          }
          break ;
        default :
          break ;
      } 
    }
  }
}

void lancementJeu(SDL_Renderer * renderer, SDL_Texture *  textureMapVide, point ** tableauDePoint, SDL_Texture ** textureTableauWin, int * p_etatS, int boolPlayMusic, SDL_Texture ** textureTableauOptionMenu, SDL_Rect ** tableauCase,  SDL_Texture ** textureTableauPiont , char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2)
{
    SDL_Delay(1);
    gameOptionGraphique(renderer, textureMapVide, tableauDePoint, tableauCase, pileJ1, pileJ2, map3D, map2D, p_etatS, boolPlayMusic, textureTableauOptionMenu, textureTableauPiont);
    if (count_pion(map3D, N, 'b')) 
      printf("Le joueur 1 a gagne!\n");
    else 
      printf("Le joueur 2 a gagne!\n");
    initMap(map3D);
    initMap2D(map2D, map3D);
    initPile(pileJ1,'b');
    initPile(pileJ2,'n');
}

/*return -1 if stack is empty else 0, 1 or 2*/
int sizePiontInStack(char ** stackArray, int numStack)
{
  int sizePiont = -1 ;
  for(int i = N-1 ; i >= 0 ; i--)
  {
    if (stackArray[numStack][i] != '0')
    {
      sizePiont = i; 
      i = -1; // sortie de boucle
    }
  }
  return sizePiont ;
}
/* return 0 if succes, -1 else */
int affichePileSDL(SDL_Renderer * renderer, SDL_Texture ** textureTableauPiont, point ** tableauDePoint,char ** stackArrayJ1, char ** stackArrayJ2) // texturemapVide pour connaitre la taille
{
  SDL_Rect positionPiontCurr;
  int sizePiontMaxPile1J1 = sizePiontInStack(stackArrayJ1, 0) ;
  int sizePiontMaxPile2J1 = sizePiontInStack(stackArrayJ1, 1) ;
  int sizePiontMaxPile1J2 = sizePiontInStack(stackArrayJ2, 0) + 3 ;
  int sizePiontMaxPile2J2 = sizePiontInStack(stackArrayJ2, 1) + 3 ;
  
  if (sizePiontMaxPile1J1 != -1)
  {
    if (0 != SDL_QueryTexture(textureTableauPiont[sizePiontMaxPile1J1], NULL, NULL, &positionPiontCurr.w, &positionPiontCurr.h))
    {
       fprintf(stderr, "Error SDL_QueryTexture in affichePileSDL 1: %s \n", SDL_GetError());
       return -1;
    }
    positionPiontCurr.x = tableauDePoint[9]->x - positionPiontCurr.w/2   ;
    positionPiontCurr.y = tableauDePoint[9]->y - 2*positionPiontCurr.h/3 ;

    positionPiontCurr.w *= 0.79;
    positionPiontCurr.h *= 0.79;

    if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[sizePiontMaxPile1J1], NULL, &positionPiontCurr))
    {
      fprintf(stderr, "Error SDL_RenderCopy in affichePileSDL 2: %s \n", SDL_GetError());
      return -1;
    }

  }
  if (sizePiontMaxPile2J1 != -1)
  {
    if (0 != SDL_QueryTexture(textureTableauPiont[sizePiontMaxPile2J1], NULL, NULL, &positionPiontCurr.w, &positionPiontCurr.h))
    {
      fprintf(stderr, "Error SDL_QueryTexture in affichePileSDL 3: %s \n", SDL_GetError());
      return -1;
    }
    positionPiontCurr.x = tableauDePoint[10]->x - positionPiontCurr.w/2   ;
    positionPiontCurr.y = tableauDePoint[10]->y - 2*positionPiontCurr.h/3 ;  
    if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[sizePiontMaxPile2J1], NULL, &positionPiontCurr))
    {
      fprintf(stderr, "Error SDL_RenderCopy in affichePileSDL 4: %s \n", SDL_GetError());
      return -1;
    }
  }
  if (sizePiontMaxPile1J2 > 2)
  {
    if (0 != SDL_QueryTexture(textureTableauPiont[sizePiontMaxPile1J2], NULL, NULL, &positionPiontCurr.w, &positionPiontCurr.h))
    {
      fprintf(stderr, "Error SDL_QueryTexture in affichePileSDL 5: %s \n", SDL_GetError());
      return -1;
    }

    positionPiontCurr.w *= 0.79;
    positionPiontCurr.h *= 0.79;
    positionPiontCurr.x = tableauDePoint[11]->x - positionPiontCurr.w/2   ;
    positionPiontCurr.y = tableauDePoint[11]->y - 2*positionPiontCurr.h/3 ;  
    if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[sizePiontMaxPile1J2], NULL, &positionPiontCurr))
    {
      fprintf(stderr, "Error SDL_RenderCopy in affichePileSDL 6: %s \n", SDL_GetError());
      return -1;
    }
  }
  if (sizePiontMaxPile2J2 > 2 )
  {
    if (0 != SDL_QueryTexture(textureTableauPiont[sizePiontMaxPile2J2], NULL, NULL, &positionPiontCurr.w, &positionPiontCurr.h))
    {
      fprintf(stderr, "Error SDL_QueryTexture in affichePileSDL 7: %s \n", SDL_GetError());
      return -1;
    }
    positionPiontCurr.x = tableauDePoint[12]->x - positionPiontCurr.w/2   ;
    positionPiontCurr.y = tableauDePoint[12]->y - 2*positionPiontCurr.h/3 ;  
    if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[sizePiontMaxPile2J2], NULL, &positionPiontCurr))
    {
      fprintf(stderr, "Error SDL_RenderCopy in affichePileSDL 8: %s \n", SDL_GetError());
      return -1;
    }
  }
  return 0;
}







/* return 0 if succes, -1 else *, la map contient des '1', '2', '3' & 'a', 'b', 'c' */
int affichePiontSurPlateau(SDL_Renderer * renderer, SDL_Texture ** textureTableauPiont, point ** tableauDePoint ,char ***  map3D)
{
  char map2D [N][N];
  int find = 0 ;
  for(int i = 0; i < N; i++) 
  {
    for(int j = 0; j < N; j++) 
    {
      find = 0;
      for(int k=N-1; k>=0; --k) 
      {
        if(!find && map3D[i][j][k] != '0') 
        {
          if(map3D[i][j][k] == 'b')
            map2D[i][j] = '1'+ k ;
          else
           map2D[i][j] = 'a'+ k ;
          find++;
        }
      }
      if (!find)
        map2D[i][j] = '0';
    }
  }

  SDL_Rect positionPiontCurrent ;
  int x , y;                // position de la case que l'on parcourt
  int indicePiont;          // contient l'indice du piont à placer
  
  for(int i = 0 ; i < N*N ; i++)
  {
    x = i / 3 ; y = i % 3 ;
    if(map2D[x][y] != '0')
    {
      switch(map2D[x][y]) 
      {
        case '1' :
          indicePiont = 0;
          break;
        case '2' :
          indicePiont = 1;
          break;
        case '3' :
          indicePiont = 2;
          break;
        case 'a' :
          indicePiont = 3;
          break;
        case 'b' :
          indicePiont = 4;
          break;
        case 'c' :
          indicePiont = 5;
          break;
        default :
          printf("error in affichePiontSurPlateau switch \n");
          break;
      }
      if (0 != SDL_QueryTexture(textureTableauPiont[indicePiont], NULL, NULL, &positionPiontCurrent.w, &positionPiontCurrent.h))
      {
	       fprintf(stderr, "Error SDL_QueryTexture in affichePiontSurPlateau 1 : %s \n", SDL_GetError());
	       return -1;
      }
      if(0 == x)
      {
        positionPiontCurrent.w *= 0.77;
        positionPiontCurrent.h *= 0.77;
      }
      else if(1 == x)
      {
        positionPiontCurrent.w *= 0.86;
        positionPiontCurrent.h *= 0.86;
      }
      positionPiontCurrent.x =  tableauDePoint[i]->x - positionPiontCurrent.w/2;
      if(indicePiont != 2 && indicePiont != 5)
        positionPiontCurrent.y =  tableauDePoint[i]->y - 2*positionPiontCurrent.h/3; // ou 3 test ?
      else
        positionPiontCurrent.y =  tableauDePoint[i]->y - 4.5*positionPiontCurrent.h/6;
      
      if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[indicePiont], NULL, &positionPiontCurrent))
      {
        fprintf(stderr, "Error SDL_RenderCopy in affichePiontSurPlateau 2 : %s \n", SDL_GetError());
	      return -1;
      }
    }
  }
  return 0;
}
