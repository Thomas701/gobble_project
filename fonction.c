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

SDL_bool isInRect(SDL_Point point, SDL_Point rectangleHautGauche, SDL_Point rectangleBasDroit) // pour favoir si le point est à l'interieur d'un rectangle
{
  if (point.x >= rectangleHautGauche.x && point.x <= rectangleBasDroit.x && point.y >= rectangleHautGauche.y && point.y <= rectangleBasDroit.y) // si le point est dans le rectangle
    return SDL_TRUE ;
  return SDL_FALSE;
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

int createPiont(point *** pTableauDePoint)
{
  point ** tableauDePoint = (point ** ) malloc(sizeof(point *) * 13);
  for(int i = 0 ; i < 13 ; ++i)
  {
    tableauDePoint[i] = malloc(sizeof(point) * 1);
    if(!tableauDePoint[i])
    {
      perror("Error allocation memory in createPiont for tableauDePoint[i] \n");
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

/* return -1 si erreur 0 sinon*/
int initialiseDebutProgramme(SDL_Window ** window, SDL_Texture ** textureMenu, SDL_Texture *** textureBackground, SDL_Texture ** textureMapVideB, SDL_Texture ** textureMapVideR ,SDL_Surface ** icones, SDL_Renderer ** renderer)
{
  // initialise le systeme gestion de rendu, d'évenements , audio et temps + test
  if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_TIMER))
  {
    fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
    return -1;
  }
    
  // alloue la fenetre
  * window = SDL_CreateWindow("GOOBLE PROJECT - PREP'ISIMA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN) ;
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

  // init texture menu
  * textureMenu = loadImage("Frames/menu.jpg", * renderer);
  if(!* textureMenu)
  {
    fprintf(stderr, "Error loadImage for textureMenu : %s\n", SDL_GetError());
    return -1;
  }

  // init texture map vide
  * textureMapVideB = loadImage("Frames/map.png", * renderer);
  if(!* textureMapVideB)
  {
    fprintf(stderr, "Error loadImage for textureMenu : %s\n", SDL_GetError());
    return -1;
  }

  * textureMapVideR = loadImage("Frames/map.png", * renderer); // attention modifier pour plus tard
  if(!* textureMapVideR)
  {
    fprintf(stderr, "Error loadImage for textureMenu : %s\n", SDL_GetError());
    return -1;
  }
  return 0;
}

int loadPiont(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauPiont)/*return 0 si ok, -1 sinon*/
{
  SDL_Texture ** textureTableauPiont = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*6);

  if (!* textureTableauPiont)
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

  int r = rand() % 10;
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


void lancementMenu(SDL_Renderer * renderer, SDL_Texture ** textureBackground, SDL_Texture * textureMenu, int * p_etats, int boolPlayMusic)
{
  SDL_RenderClear(renderer);

  //boutons du menu
  SDL_Point pointChoice1VS1_HG =  {160, 240};   SDL_Point pointChoiceIA_HG = {170, 430};
  SDL_Point pointChoice1VS1_BD =  {990, 355};  SDL_Point pointChoiceIA_BD = {975, 550};
  SDL_Point pointQuitter_HG  =    {170, 650};    SDL_Point pointSound_HG =  {1120, 0};
  SDL_Point pointQuitter_BD  =    {1000, 780};   SDL_Point pointSound_BD =  {1280, 185};
  SDL_Point pointMouse = {0 , 0}; //souris du menu pour evenement

  int incrImg = 0; // numero image menu (background)
  
  while(*p_etats == 1) // boucle principale
  {
    SDL_Event event;
    SDL_RenderClear(renderer);
    if (0 != SDL_RenderCopy(renderer, textureBackground[incrImg%400], NULL, NULL)) {fprintf(stderr, "Error SDL_RenderCopy for textureBackground : %s, i = %d, et img = %p \n", SDL_GetError(), incrImg%400 , textureBackground[incrImg%400]);}
    if (0 != SDL_SetTextureBlendMode( textureMenu, SDL_BLENDMODE_MOD)) {fprintf(stderr, "transparence textureMenu impossible : %s\n", SDL_GetError());}
    if (0 != SDL_RenderCopy( renderer,  textureMenu, NULL, NULL)) { fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());}
    incrImg++;
    SDL_RenderPresent(renderer);
    SDL_Delay(50);
    while(SDL_PollEvent(&event)) // programme continue et un nouveau evenement dans la file
    {
      switch(event.type)
      {
        case SDL_QUIT : //quitter
          *p_etats = 0;
          break ;

        case SDL_MOUSEBUTTONDOWN :  // bouton souris enfonce
          if (event.button.button == SDL_BUTTON_LEFT) // bouton souris gauche
          {
            SDL_GetMouseState(&pointMouse.x, &pointMouse.y); // recupere coord souris
            if (isInRect(pointMouse , pointChoice1VS1_HG, pointChoice1VS1_BD)) // 2 joueurs en local
            {
              *p_etats = 2 ;
              SDL_RenderClear(renderer);
              printf("Lancement jeu 1VS1 \n");
            }
            else if(isInRect(pointMouse , pointChoiceIA_HG, pointChoiceIA_BD)) // IA min max
            {
              *p_etats = 2 ;
              SDL_RenderClear(renderer);
              printf("Lancement jeu contre IA \n");
            }
            else if(isInRect(pointMouse , pointSound_HG, pointSound_BD)) // choix contre IA renfocement
            {
              if(boolPlayMusic == 0) {boolPlayMusic = 1; Mix_ResumeMusic();}
              else {boolPlayMusic = 0; Mix_PauseMusic();}
              printf("Changement de music \n");
            }
            else if(isInRect(pointMouse , pointQuitter_HG, pointQuitter_BD)) // choix QUITTER
            {
              *p_etats = 0;
              printf("Quitter \n");
            }
          }
          break ;
        default :
          break ;
      }  
    }
  }
}


/* return 0 if succes, -1 else */
int affichePileSDL(SDL_Renderer * renderer, SDL_Texture * textureMapVide, SDL_Texture ** textureTableauPiont, point ** tableauDePoint,char ** stackArrayJ1, char ** stackArrayJ2) // texturemapVide pour connaitre la taille
{
  SDL_Rect positionPiontCurr;
  int sizePiontMaxPile1J1 = sizePiontMaxStack(stackArrayJ1, 0) ;
  int sizePiontMaxPile2J1 = sizePiontMaxStack(stackArrayJ1, 1) ;
  
  int sizePiontMaxPile1J2 = sizePiontMaxStack(stackArrayJ2, 0) + 3;
  int sizePiontMaxPile2J2 = sizePiontMaxStack(stackArrayJ2, 1) + 3; // -1 car commence Ã  1 , + 3 dans textureTableauPiont
  if (sizePiontMaxPile1J1 > 0)
  {
    if (0 != SDL_QueryTexture(textureTableauPiont[sizePiontMaxPile1J1], NULL, NULL, &positionPiontCurr.w, &positionPiontCurr.h))
    {
       fprintf(stderr, "Error SDL_QueryTexture in affichePileSDL : %s \n", SDL_GetError());
       return -1;
    }
    positionPiontCurr.x = tableauDePoint[9]->x - positionPiontCurr.w/2   ;
    positionPiontCurr.y = tableauDePoint[9]->y - 2*positionPiontCurr.h/3 ;

    positionPiontCurr.w *= 0.79;
    positionPiontCurr.h *= 0.79;

    if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[sizePiontMaxPile1J1], NULL, &positionPiontCurr))
    {
      fprintf(stderr, "Error SDL_RenderCopy in affichePileSDL : %s \n", SDL_GetError());
      return -1;
    }

  }
  if (sizePiontMaxPile2J1 != -1)
  {
    if (0 != SDL_QueryTexture(textureTableauPiont[sizePiontMaxPile2J1], NULL, NULL, &positionPiontCurr.w, &positionPiontCurr.h))
    {
      fprintf(stderr, "Error SDL_QueryTexture in affichePileSDL : %s \n", SDL_GetError());
      return -1;
    }
    positionPiontCurr.x = tableauDePoint[10]->x - positionPiontCurr.w/2   ;
    positionPiontCurr.y = tableauDePoint[10]->y - 2*positionPiontCurr.h/3 ;  
    if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[sizePiontMaxPile2J1], NULL, &positionPiontCurr))
    {
      fprintf(stderr, "Error SDL_RenderCopy in affichePileSDL : %s \n", SDL_GetError());
      return -1;
    }
  }
  if (sizePiontMaxPile1J2 > 2)
  {
    if (0 != SDL_QueryTexture(textureTableauPiont[sizePiontMaxPile1J2], NULL, NULL, &positionPiontCurr.w, &positionPiontCurr.h))
    {
      fprintf(stderr, "Error SDL_QueryTexture in affichePileSDL : %s \n", SDL_GetError());
      return -1;
    }

    positionPiontCurr.w *= 0.79;
    positionPiontCurr.h *= 0.79;
    positionPiontCurr.x = tableauDePoint[11]->x - positionPiontCurr.w/2   ;
    positionPiontCurr.y = tableauDePoint[1]->y - 2*positionPiontCurr.h/3 ;  
    if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[sizePiontMaxPile1J2], NULL, &positionPiontCurr))
    {
      fprintf(stderr, "Error SDL_RenderCopy in affichePileSDL : %s \n", SDL_GetError());
      return -1;
    }
  }
  if (sizePiontMaxPile2J2 > 2 )
  {
    if (0 != SDL_QueryTexture(textureTableauPiont[sizePiontMaxPile2J2], NULL, NULL, &positionPiontCurr.w, &positionPiontCurr.h))
    {
      fprintf(stderr, "Error SDL_QueryTexture in affichePileSDL : %s \n", SDL_GetError());
      return -1;
    }
    positionPiontCurr.x = tableauDePoint[12]->x - positionPiontCurr.w/2   ;
    positionPiontCurr.y = tableauDePoint[12]->y - 2*positionPiontCurr.h/3 ;  
    if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[sizePiontMaxPile2J2], NULL, &positionPiontCurr))
    {
      fprintf(stderr, "Error SDL_RenderCopy in affichePileSDL : %s \n", SDL_GetError());
      return -1;
    }
  }
  return 0;
}

/* return 0 if succes, -1 else *, la map contient des '1', '2', '3' & 'a', 'b', 'c' */
int affichePiontSurPlateau(SDL_Renderer * renderer, SDL_Texture * textureMapVide, SDL_Texture ** textureTableauPiont, point ** tableauDePoint ,char **  map2D)
{
  SDL_Rect positionPiontCurrent ;
  int x , y;                // position de la case que l'on parcourt
  int indicePiont;          // contient l'indice du piont à placer


  for(int i = 0 ; i < N*N ; i++)
  {
    x = i / 3 ; y = i % 3 ;
    if(map2D[x][y] != '0')
    {
      if(map2D[x][y] >= '1' && map2D[x][y] <= '3') // cas piont
        indicePiont = map2D[x][y] - 48 - 1 ; // -1 car tableauTexture
      else
	       indicePiont = map2D[x][y] - 96 - 1 + 3; // si a alors 1 , b alors 2 + 2 pour le tableau de texture
      if (0 != SDL_QueryTexture(textureTableauPiont[indicePiont], NULL, NULL, &positionPiontCurrent.w, &positionPiontCurrent.h))
      {
	       fprintf(stderr, "Error SDL_QueryTexture in affichePileSDL : %s \n", SDL_GetError());
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
        fprintf(stderr, "Error SDL_RenderCopy in affichePileSDL : %s \n", SDL_GetError());
	      return -1;
      }
    }
  }
  return 0;
}
