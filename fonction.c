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
      sizePiont = i; 
      i = -1;
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

void gameOption(char ** stackArray, char *** map3D,char ** map2D, char c, int deplacement) // c = 'b' or 'n' joueur qui choisie
{
  if (c == 'b')
    printf("Joueur 1, c'est a vous!\n");
  else
    printf("Joueur 2, c'est a vous!\n");
  int answer = 0;
  answer = (isStackFull(stackArray) || !existPiontInMap(map2D, c)) ? 1 : 0;
  if (canPlayNewPiont(stackArray, map2D) && !isStackFull(stackArray) && existPiontInMap(map2D, c) && (deplacement == 0 || (canEffectDeplacementWithDistance(map3D, c) && deplacement == 1)))
  {
      printf("Print1\n");
      printMap2D(map2D);
      printMap3dDebug(map3D);
      printf("Que souhaitez-vous faire ? \n[1] Jouer un nouveau pion ? (de votre pile)  \n[2] Deplacer un pion se trouvant sur la map  \n");
      scanf(" %d", &answer);
      vider_buffer();
      printf("Selection: %d, deplacement: %d, fonction: %d", answer, deplacement, canEffectDeplacementWithDistance(map3D, c));
      while (answer != 1 &&  answer != 2)
      {
        printf("Je n'ai pas compris !  \n\nQue voulez-vous faire ? \n[1] Jouer un nouveau pion ? (de votre pile)  \n[2] Deplacer un pion se trouvant sur la map  \n");
        scanf(" %d",&answer);
        vider_buffer();
      }
  }
  if (answer == 2 || answer == 0 && (deplacement == 0 || canEffectDeplacementWithDistance(map3D, c))) // cas ou il a choisi l'option 2 ou cas ou il a seulement l'option 2 possible
  {
    int debPiont = 0 ;
    int endPiont = 0 ;

    printf("Print2\n");
    printMap2D(map2D);
    printMap3dDebug(map3D);
    printf("Quel pion voulez-vous deplacer ? \n");
    scanf(" %d", &debPiont);
    vider_buffer();

    if(!deplacement)
    {
      while(debPiont < 0 || debPiont > N*N-1 || !canMooveThisPiontD(map3D, debPiont, c))
      {
        printf("Index non valide ! \nQuel pion voulez vous deplacer ?\n");
        scanf(" %d", &debPiont);
        vider_buffer();
      }

      printf("Sur quel case voulez vous deplacer le piont %d ? \n", debPiont);
      scanf(" %d", &endPiont);
      vider_buffer();
      
      while(endPiont < 0 || endPiont > (N*N)-1 || endPiont == debPiont || !canMoove(map3D, debPiont, endPiont))
      {
        printf("Deplacement invalide, veuillez recommencer. \n");
        printf("Sur quelle case voulez vous deplacer le pion %d ? \n", debPiont);
        scanf(" %d", &endPiont);
        vider_buffer();
      }
      moove(map3D, debPiont, endPiont);
      initMap2D(map2D, map3D);
    }
    else
    {
      while(debPiont < 0 || debPiont > N*N-1 || !canMooveThisPiontDistance(map3D, debPiont, c))
      {
        printf("Index non valide ! \nQuel pion voulez vous deplacer ?\n");
        scanf(" %d", &debPiont);
        vider_buffer();
      }
      int x1 = (debPiont - debPiont % N) / N;
      int y1 = debPiont % N;
      printf("Sur quel case voulez vous deplacer le piont %d ? \n", debPiont);
      scanf(" %d", &endPiont);
      int x2 = (endPiont - endPiont % N) / N;
      int y2 = endPiont % N;
      while (endPiont < 0 || endPiont > (N*N)-1 || endPiont == debPiont || !canMoove(map3D, debPiont, endPiont) || maximum(abs(x1-x2), abs(y1-y2)) > 1)
      {
        printf("Case invalide (distance>1)\nSur quel case voulez vous deplacer le pion %d ? \n", debPiont);
        scanf(" %d", &endPiont);
        x2 = (endPiont - endPiont % N) / N;
        y2 = endPiont % N;
        //printf("x1:%d, x2:%d, y1:%d, y2:%d result:%d\n", x1, x2, y1, y2, maximum(abs(x1-x2), abs(y1-y2)));
        vider_buffer();
      }
      moove(map3D, debPiont, endPiont);
      initMap2D(map2D, map3D);
    }
  }
  else // cas ou il joue un nouveau piont et il peut le jouer cad il existe une pile ou il peut mettre un piont sur le plateau
  {
    printf("ELSE\n");
    int numPion ;
    int numStack ;
    int endPiont ;
    printf("Print3\n");
    printMap2D(map2D);
    printMap3dDebug(map3D);
    printf("Voici vos piles : \n");
    printStacks(stackArray);
    printf("Quelle pile voulez vous jouer ?\n");
    scanf(" %d",&numStack);
    while(numStack < 0 || numStack > N-2 || isEmptyStack(stackArray, numStack) || !canPlayStack(sizePiontMaxStack(stackArray , numStack), map3D))
    {
      printf("Vous ne pouvez rien faire avec cette pile ! \nVeuillez saisir un nouveau numero de pile.\n");
      scanf(" %d", &numStack);
      vider_buffer();
    }

    printf("Quel pion voulez vous jouer (0 <= pion <= %d) ?\n", N-1);
    scanf(" %d",&numPion);
    while(numPion < 0 || numPion > N-1 || !existPiontInStack(stackArray, numStack, numPion) || !canPlayStack(numPion, map3D))
    {
      //printf("f1: %d & f2: %d\n", !existPiontInStack(stackArray, numStack, numPion), !canPlayStack(numPion, map3D));
      printf("Vous ne pouvez rien faire avec ce pion! \nVeuillez saisir un nouveau pion dans cette pile.\n");
      scanf(" %d", &numPion);
      vider_buffer();
    }

    printf("Print4\n");
    printMap2D(map2D);
    printMap3dDebug(map3D);
    printf("A quelle place voulez vous jouez le pion numero %d ? \n", numPion);
    scanf(" %d", &endPiont);
    vider_buffer();
    while(endPiont < 0 || endPiont > (N*N)-1 || !canPutPiont(map3D, numPion,endPiont))
    {
      printf("Position d'arrivee invalide !\nVeuillez resaisir le numero de case où vous voulez jouer [%d] \n", canPutPiont(map3D, numPion, endPiont));
      scanf(" %d", &endPiont);
      vider_buffer();
    }
    mooveSinceStack(map3D, stackArray, numStack, numPion, endPiont, c);
    initMap2D(map2D, map3D);
 }
}

void gameOptionGraphique(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint, SDL_Rect ** tableauCase,  char ** pileJ1, char ** pileJ2, char *** map3D, char ** map2D, int * p_etats, int boolPlayMusic, SDL_Texture ** textureTableauOptionMenu, SDL_Texture ** textureTableauPiont, int distance) // c = 'b' or 'n' joueur qui choisie
{
  int selection = 0;
  int imageIndexP = -1; // indique l'indexe de l'image qui a été selectionnée
  int imageIndexS = -1;
  char c = 'b';
  SDL_Event event;
  SDL_Point pointMouse;

  printf("--->3\n");
  debugTab(tableauCase);

  while(2 == *p_etats) // boucle principale
  {
    while(SDL_PollEvent(&event)) // programme continue et un nouveau evenement dans la file
    {
      switch(event.type)
      {
        case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT) // bouton souris gauche
        {
          printf("JOUEUR: %c\n", c);
          SDL_GetMouseState(&pointMouse.x, &pointMouse.y); // recupere coord souris
          if (selection == 0)
          {
            printf("Select: 0\n");
            imageIndexP = canSelection(pointMouse, map3D, map2D, tableauCase, pileJ1, pileJ2, c, distance);
          }
          else
          {
            printf("Select: 1\n");
            if(c == 'b')
            {
              imageIndexS = canPlay(imageIndexP, pointMouse, tableauCase, map3D, pileJ1, distance);
              printf("point d'arrivé: %d\n", imageIndexS);
            }
            else
            {
              imageIndexS = canPlay(imageIndexP, pointMouse, tableauCase, map3D, pileJ2, distance);
              printf("point d'arrivé: %d\n", imageIndexS);
            }
          }
          printf("Selection: p:%d & s:%d & select:%d\n", imageIndexP, imageIndexS, selection);
          if (selection == 1 && imageIndexS == -1)
          {
            printf("Select good & preSelect not good, so select=0\n");
            selection = 0;
          }
          else if (selection == 0 && imageIndexP != -1)
          {
            printf("Select not good & preSelect good\n so select=1\n");
            selection = 1;
          }
          else if (selection == 1 && imageIndexS != -1)
          {
            printf("Select good & preSelect: good\n");
            if (imageIndexP > (N*N) - 1)
            {
              if(c == 'b')
              {
                for (int i = 0; i < N-1; i++)
                {
                  if (pileJ1[i][(N-1) - (imageIndexP % N)] != '0')
                  {
                    mooveSinceStack(map3D, pileJ1, i, (N-1) - (imageIndexP % N), imageIndexS, c);
                    break;
                  }
                }
                initMap2D(map2D, map3D);
                c = (c == 'b') ? 'n' : 'b';
                selection = 0;
                if (count_pion(map2D, N, 'b') || count_pion(map2D, N, 'n'))
                {
                  printf("fin partie: b:%d & n:%d\n", count_pion(map2D, N, 'b'), count_pion(map2D, N, 'n'));
                  *p_etats = 1;
                }
              }
              else
              {
                for (int i = 0; i < N-1; i++)
                {
                  if (pileJ2[i][(N-1) - (imageIndexP % N)] != '0')
                  {
                    mooveSinceStack(map3D, pileJ2, i, (N-1) - (imageIndexP % N), imageIndexS, c);
                    break;
                  }
                }
                initMap2D(map2D, map3D);
                c = (c == 'b') ? 'n' : 'b';
                selection = 0;
                if (count_pion(map2D, N, 'b') || count_pion(map2D, N, 'n'))
                {
                  printf("fin partie: b:%d & n:%d\n", count_pion(map2D, N, 'b'), count_pion(map2D, N, 'n'));
                  *p_etats = 1;
                }
              }
            }
            else
            {
              moove(map3D, imageIndexP, imageIndexS);
              initMap2D(map2D, map3D);
              c = (c == 'b') ? 'n' : 'b';
              selection = 0;
              if (count_pion(map2D, N, 'b') || count_pion(map2D, N, 'n'))
              {
                printf("fin partie: b:%d & n:%d\n", count_pion(map2D, N, 'b'), count_pion(map2D, N, 'n'));
                *p_etats = 1;
              }
            }
            printf("Pile J1:\n");
            printStacks(pileJ1);
            printf("Pile J2:\n");
            printStacks(pileJ2);
            printf("initialisation:\n");
            initMap2D(map2D, map3D);
            printf("affichage:\n");
            printMap2D(map2D);
          }
        }
      }
      SDL_RenderClear(renderer);

      if(c == 'b')
        printMapEmptySDL(tableauTextureMapVide[1], renderer);
      else if (c == 'n')
        printMapEmptySDL(tableauTextureMapVide[2], renderer);
      affichePileSDL(renderer, textureTableauPiont, tableauDePoint, pileJ1, pileJ2);
      affichePiontSurPlateau(renderer, textureTableauPiont, tableauDePoint, map3D);
      SDL_RenderPresent(renderer);
    }
  }
}

void loadAndPlayMainMusic(Mix_Music ** mainMusic, SDL_Rect ** tableauCase)
{
  printf("Musique--->1\n");
  debugTab(tableauCase);
  // initialisation de la musique
  * mainMusic = Mix_LoadMUS("Music/mainMusic.mp3");
  Mix_VolumeMusic(MIX_MAX_VOLUME/8);
  if(!* mainMusic)
    fprintf(stderr, "Error for load mainMusic : %s \n",SDL_GetError());

  printf("Musique--->2\n");
  debugTab(tableauCase);
  printf("Musique--->2.5\n");
  // play music
  if(0 != Mix_PlayMusic(* mainMusic, -1))
  {
    printf("Error in Mix_PlayMusic: %s\n", SDL_GetError());
  }
  
  printf("Musique--->3\n");
  debugTab(tableauCase);
}

int getIndex(SDL_Point pointMouse, SDL_Rect ** tableauCase)
{
  for(int i = 0 ; i < (N * N + N*2) ; i++)
  {
    if(isInRectangle(pointMouse, *tableauCase[i]))
    {
      printf("Index trouvé [%d]!\n", i);
      return i;
    }
    else
      printf("index non trouvé pour mouse: %d, %d & i=%d\n", pointMouse.x , pointMouse.y ,i);
  }
  printf("return -1\n");
  return -1;
}

/*Fonctions Vérifications :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

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
    //printf("COMPTE RENDU:\n i=%d, iEnd=%d, j=%d, jEnd= %d, x=%d, y=%d\n",i, iEnd, j, jEnd, x, y);
    for (int i = 0; i <= N; i++)
    {
      for (int j = 0; j <= N; j++)
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
      printf("Return [1]\n");
      return -1; // cas ou il clique sur la pile adversaire
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


/*Fonctions création de maps, piles, images :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

SDL_Rect ** mallocTab()
{
  SDL_Rect ** tableauCase = (SDL_Rect **) malloc(sizeof(SDL_Rect *)*((N*N) + (N*2)));

  for(int i = 0 ; i < ((N*N) + (N*2)) ; i++)
  {
    tableauCase[i] = malloc(sizeof(SDL_Rect *) * 1);
    if(!tableauCase[i])
    {
      perror("Error allocation memory in createCase for tableauCase[i] \n");
      freeTabCase(tableauCase);
      exit(-1);
    }
  }
  return tableauCase;
}

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
  if(map2D == NULL)
    errorInCreate2D();
  for(int i = 0; i < N; i++)
  {
    map2D[i] = (char *) malloc(sizeof(char)*N);
    if(map2D[i] == NULL)
    {
      for(int j = 0; j < i; j++)
      {
        free(map2D[j]); 
        map2D[j] = NULL;
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
  point ** tableauDePoint = (point ** ) malloc(sizeof(point *) * 15);
  for(int i = 0 ; i < 15 ; ++i)
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
  tableauDePoint[ 9]->x = 286 ;  tableauDePoint[ 9]->y = 388 ;
  tableauDePoint[10]->x = 239 ;  tableauDePoint[10]->y = 503 ;
  tableauDePoint[11]->x = 183 ;  tableauDePoint[11]->y = 641 ;
  tableauDePoint[12]->x = 985 ;  tableauDePoint[12]->y = 389 ;
  tableauDePoint[13]->x = 1044;  tableauDePoint[13]->y = 506 ;
  tableauDePoint[14]->x = 1107;  tableauDePoint[14]->y = 646 ;
  * pTableauDePoint = tableauDePoint;
  return 0;
}

int createCase(SDL_Rect *** pTableauCase)
{
  SDL_Rect ** tableauCase = (SDL_Rect **) malloc(sizeof(SDL_Rect *)*((N*N) + (N*2)));

  for(int i = 0 ; i < ((N*N) + (N*2)) ; i++)
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
  tableauCase[ 4]->w = 159 ; tableauCase[ 4]->h = 108 ;  // 107
  tableauCase[ 4]->x = 579 ; tableauCase[ 4]->y = 461 ;
  tableauCase[ 5]->w = 152 ; tableauCase[ 5]->h = 107 ;
  tableauCase[ 5]->x = 751 ; tableauCase[ 5]->y = 461 ;
  tableauCase[ 6]->w = 195 ; tableauCase[ 6]->h = 129 ;
  tableauCase[ 6]->x = 358 ; tableauCase[ 6]->y = 587 ;
  tableauCase[ 7]->w = 182 ; tableauCase[ 7]->h = 130 ;
  tableauCase[ 7]->x = 571 ; tableauCase[ 7]->y = 586 ;
  tableauCase[ 8]->w = 174 ; tableauCase[ 8]->h = 129 ;
  tableauCase[ 8]->x = 765 ; tableauCase[ 8]->y = 586 ;
  tableauCase[ 9]->w = 128 ; tableauCase[ 9]->h = 131 ;   //  bleu fond
  tableauCase[ 9]->x = 223 ; tableauCase[ 9]->y = 293 ;
  tableauCase[ 10]->w = 148 ; tableauCase[ 10]->h = 123 ;  //  bleu moyen
  tableauCase[ 10]->x = 167 ; tableauCase[ 10]->y = 431 ;
  tableauCase[ 11]->w = 143 ; tableauCase[ 11]->h = 110 ;  //  bleu devant
  tableauCase[ 11]->x = 112 ; tableauCase[ 11]->y = 579 ;
  tableauCase[ 12]->w = 119 ; tableauCase[ 12]->h = 129 ;  //  rouge fond
  tableauCase[ 12]->x = 927 ; tableauCase[ 12]->y = 294 ;
  tableauCase[ 13]->w = 117 ; tableauCase[ 13]->h = 116 ;  //  rouge moyen
  tableauCase[ 13]->x = 987 ; tableauCase[ 13]->y = 430 ;
  tableauCase[ 14]->w = 122 ; tableauCase[ 14]->h = 114 ;  //  rouge devant
  tableauCase[ 14]->x = 1050 ; tableauCase[ 14]->y = 579 ;
  
  debugTab(tableauCase);

  * pTableauCase = tableauCase;
  return 0;
}

void initTableauCase(SDL_Rect ** tableauCase)
{
  tableauCase[ 0]->w = 152 ; tableauCase[ 0]->h = 89 ;
  tableauCase[ 0]->x = 419 ; tableauCase[ 0]->y = 359 ;
  tableauCase[ 1]->w = 141 ; tableauCase[ 1]->h = 89 ;
  tableauCase[ 1]->x = 585 ; tableauCase[ 1]->y = 358 ;
  tableauCase[ 2]->w = 134 ; tableauCase[ 2]->h = 89 ;
  tableauCase[ 2]->x = 738 ; tableauCase[ 2]->y = 358 ;
  tableauCase[ 3]->w = 171 ; tableauCase[ 3]->h = 106 ;
  tableauCase[ 3]->x = 392 ; tableauCase[ 3]->y = 462 ;
  tableauCase[ 4]->w = 159 ; tableauCase[ 4]->h = 108 ;  // 107
  tableauCase[ 4]->x = 579 ; tableauCase[ 4]->y = 461 ;
  tableauCase[ 5]->w = 152 ; tableauCase[ 5]->h = 107 ;
  tableauCase[ 5]->x = 751 ; tableauCase[ 5]->y = 461 ;
  tableauCase[ 6]->w = 195 ; tableauCase[ 6]->h = 129 ;
  tableauCase[ 6]->x = 358 ; tableauCase[ 6]->y = 587 ;
  tableauCase[ 7]->w = 182 ; tableauCase[ 7]->h = 130 ;
  tableauCase[ 7]->x = 571 ; tableauCase[ 7]->y = 586 ;
  tableauCase[ 8]->w = 174 ; tableauCase[ 8]->h = 129 ;
  tableauCase[ 8]->x = 765 ; tableauCase[ 8]->y = 586 ;
  tableauCase[ 9]->w = 128 ; tableauCase[ 9]->h = 131 ;   //  bleu fond
  tableauCase[ 9]->x = 223 ; tableauCase[ 9]->y = 293 ;
  tableauCase[ 10]->w = 148 ; tableauCase[ 10]->h = 123 ;  //  bleu moyen
  tableauCase[ 10]->x = 167 ; tableauCase[ 10]->y = 431 ;
  tableauCase[ 11]->w = 143 ; tableauCase[ 11]->h = 110 ;  //  bleu devant
  tableauCase[ 11]->x = 112 ; tableauCase[ 11]->y = 579 ;
  tableauCase[ 12]->w = 119 ; tableauCase[ 12]->h = 129 ;  //  rouge fond
  tableauCase[ 12]->x = 927 ; tableauCase[ 12]->y = 294 ;
  tableauCase[ 13]->w = 117 ; tableauCase[ 13]->h = 116 ;  //  rouge moyen
  tableauCase[ 13]->x = 987 ; tableauCase[ 13]->y = 430 ;
  tableauCase[ 14]->w = 122 ; tableauCase[ 14]->h = 114 ;  //  rouge devant
  tableauCase[ 14]->x = 1050 ; tableauCase[ 14]->y = 579 ;
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

void initMap2D(char ** map2D, char *** map3D)
{
  for(int i = 0; i < N; i++)
  {
    for(int j = 0; j < N; j++)
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
int initialiseDebutProgramme(SDL_Window ** window, SDL_Texture *** textureBackground, SDL_Texture *** ptableauTextureMapVide, SDL_Surface ** icones, SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu, SDL_Texture *** pTextureTableauPiont, SDL_Texture *** pTextureTableauWin, point *** pTableauDePoint, SDL_Rect *** pTableauCase)
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
  if(0 != loadTextureTableauMap(renderer, ptableauTextureMapVide))
  {
    fprintf(stderr, "Error loadTextureTableauMap for ptableauTextureMapVide : %s\n", SDL_GetError());
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

int loadTextureTableauMap(SDL_Renderer ** renderer, SDL_Texture *** ptableauTextureMapVide)
{
  SDL_Texture ** tableauTextureMapVide = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*3); 
  // 0 map vert, 1 map bleau, 2 map rouge
  if(!tableauTextureMapVide) { fprintf(stderr, "Error malloc in loadTextureTableauMap for tableauTextureMapVide\n"); return -1; }

  for (int i = 0; i < 3; i++) // il n'y a que 3 images map a charger
  {
    char nom[30];
    sprintf(nom, "Frames/map%d.png", i+1);
    tableauTextureMapVide[i] = loadImage(nom, * renderer);
    if(!tableauTextureMapVide[i]) { fprintf(stderr, "Error loadTextureTableauMap for tableauTextureMapVide : %s\n", SDL_GetError()); return -1; }
  }
  * ptableauTextureMapVide = tableauTextureMapVide;
  return 0;
}

int loadPiont(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauPiont)/*return 0 si ok, -1 sinon*/
{
    SDL_Texture ** textureTableauPiont = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*6);
    if (!textureTableauPiont) {
        fprintf(stderr, "Erreur allocation memory in loadPion\n");
        return -1;
    }
    for (int i = 0; i < 6; i++)
    {
        char nom[30];
        sprintf(nom, "Frames/pion%d.png", i+1);

        textureTableauPiont[i] = loadImage(nom, * renderer);
        if(!textureTableauPiont[i]) { 
        fprintf(stderr, "Error loadTextureOptionMenu for textureTableauPiont : %s\n", SDL_GetError()); 
        return -1; 
        }
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
  printf("cherche crach:1\n");
  SDL_RenderClear(renderer);
  //boutons du menu
  SDL_Rect tableauRectOption[4];

  for(int i = 0; i < 3; i++)
  {
    SDL_QueryTexture(textureTableauOptionMenu[i], NULL, NULL, &tableauRectOption[i].w, &tableauRectOption[i].h);
    tableauRectOption[i].x = WIDTH /2 - tableauRectOption[i].w / 2; 
  }
  printf("cherche crach:2\n");
  SDL_QueryTexture(textureTableauOptionMenu[3], NULL, NULL, &tableauRectOption[3].w, &tableauRectOption[3].h);
  tableauRectOption[3].x = WIDTH /2 - tableauRectOption[3].w / 2; 
  tableauRectOption[0].y = 318; tableauRectOption[1].y  = 488; tableauRectOption[2].y = 650; 
  tableauRectOption[3].x = WIDTH - tableauRectOption[3].w;     tableauRectOption[3].y = 0;

  SDL_Point pointMouse; //souris du menu pour evenement

  int incrImg = 0; // numero image menu (background)
  printf("cherche crach:3\n");
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

void lancementJeu(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint, SDL_Texture ** textureTableauWin, int * p_etatS, int boolPlayMusic, SDL_Texture ** textureTableauOptionMenu, SDL_Rect ** tableauCase,  SDL_Texture ** textureTableauPiont , char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, int distance)
{
  printf("--->2\n");
  debugTab(tableauCase);
  
  gameOptionGraphique(renderer, tableauTextureMapVide, tableauDePoint, tableauCase, pileJ1, pileJ2, map3D, map2D, p_etatS, boolPlayMusic, textureTableauOptionMenu, textureTableauPiont, distance);
  if(count_pion(map2D, N, 'b') && count_pion(map2D, N, 'n'))
    printf("EGALITE");
  else if (count_pion(map2D, N, 'b')) 
    printf("Le joueur 1 a gagne!\n");
  else 
    printf("Le joueur 2 a gagne!\n");

  // affichage vainqueur
  SDL_RenderClear(renderer);
  printf("--------------- chack end game : %d\n",check_End_Game(map2D));
  printMapEmptySDL(textureTableauWin[check_End_Game(map2D)-1], renderer);
  affichePileSDL(renderer, textureTableauPiont, tableauDePoint, pileJ1, pileJ2);
  affichePiontSurPlateau(renderer, textureTableauPiont, tableauDePoint, map3D);
  SDL_RenderPresent(renderer);
  SDL_Delay(8000);

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


/* 0 if success, -1 else*/
int affichePileSDL(SDL_Renderer * renderer, SDL_Texture ** textureTableauPiont, point ** tableauDePoint,char ** stackArrayJ1, char ** stackArrayJ2) // texturemapVide pour connaitre la taille
{
  SDL_Rect positionPiontCurrent;
  int * arrayCountPionInStack = (int *) calloc(N*2, sizeof(int));
  if(!arrayCountPionInStack)
  {
    fprintf(stderr,"Error in affichePileSDL for arrayCountPionInStack\n");
    return -1;
  }
  for (int i = 0; i < N-1; i++)
  {
    for (int j = 0; j < N; j++)
    {
        if (j == 0 && stackArrayJ1[i][j] == 'b') {arrayCountPionInStack[2] ++;}
        if (j == 0 && stackArrayJ2[i][j] == 'n') {arrayCountPionInStack[5] ++;}
        if (j == 1 && stackArrayJ1[i][j] == 'b') {arrayCountPionInStack[1] ++;}
        if (j == 1 && stackArrayJ2[i][j] == 'n') {arrayCountPionInStack[4] ++;}
        if (j == 2 && stackArrayJ1[i][j] == 'b') {arrayCountPionInStack[0] ++;}
        if (j == 2 && stackArrayJ2[i][j] == 'n') {arrayCountPionInStack[3] ++;}
    }
  }
  for(int i=0; i<N*2; i++)
  {
    if(arrayCountPionInStack[i] > 0 )
    {
      if (0 != SDL_QueryTexture(textureTableauPiont[i], NULL, NULL, &positionPiontCurrent.w, &positionPiontCurrent.h))
      {
         fprintf(stderr, "Error SDL_QueryTexture in affichePileSDL : %s \n", SDL_GetError());
         return -1;
      }
      if(0 == i%3)      { positionPiontCurrent.w *= 0.77; positionPiontCurrent.h *= 0.77; } // dezoom car derniere ligne
      else if(1 == i%3) { positionPiontCurrent.w *= 0.86; positionPiontCurrent.h *= 0.86; } // dezoom car ligne 2/3
      
      positionPiontCurrent.x =  tableauDePoint[i+9]->x - positionPiontCurrent.w/2;
      
      if(i%3 != 0) // pas un gros piont
        positionPiontCurrent.y =  tableauDePoint[i+9]->y - 2*positionPiontCurrent.h/3; // ou 3 test ?
      else
        positionPiontCurrent.y =  tableauDePoint[i+9]->y - 4.5*positionPiontCurrent.h/6;
      
      if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[i], NULL, &positionPiontCurrent))
      {
        fprintf(stderr, "Error SDL_RenderCopy in affichePiontSurPlateau 2 : %s \n", SDL_GetError());
        return -1;
      }

    } 
  }
  return 0;
}

/* return 0 if succes, -1 else *, la map contient des '1', '2', '3' & 'a', 'b', 'c' */
int affichePiontSurPlateau(SDL_Renderer * renderer, SDL_Texture ** textureTableauPiont, point ** tableauDePoint ,char ***  map3D) {
  SDL_Rect positionPiontCurrent ;
  int indicePiont;          // contient l'indice du piont à placer
  int posCase ; // position en terme de case i%3 + j
  for (int i = 0  ; i < N ; ++i) {
    for(int j = 0 ; j < N ; j++) {
      for(int k=N-1; k >=0; --k) {
        if('0' != map3D[i][j][k]) {
          switch(map3D[i][j][k])  {
            case 'b' : indicePiont = N-1 - k ; break;
            case 'n' : indicePiont = 3 + N-1 - k; break;
            default : printf("error in affichePiontSurPlateau switch map3D[i][j][k] : %c\n", map3D[i][j][k]); break;
          }
          if (0 != SDL_QueryTexture(textureTableauPiont[indicePiont], NULL, NULL, &positionPiontCurrent.w, &positionPiontCurrent.h)) {
            fprintf(stderr, "Error SDL_QueryTexture in affichePiontSurPlateau 1 : %s \n", SDL_GetError());
            return -1;
          }
          if(0 == i) { // case du fond zoom
            positionPiontCurrent.w *= 0.77;
            positionPiontCurrent.h *= 0.77;
          }
          else if(1 == i) {  // case milieu zoom
            positionPiontCurrent.w *= 0.86;
            positionPiontCurrent.h *= 0.86;
          }
          posCase = (i * N) + j;
          // on centre si piont petit ou moyen
          positionPiontCurrent.x =  tableauDePoint[posCase]->x - positionPiontCurrent.w/2;
          // si gros oon ne centre pas
          if(k == N-1)
            positionPiontCurrent.y =  tableauDePoint[posCase]->y - 2*positionPiontCurrent.h/3;
          else
            positionPiontCurrent.y =  tableauDePoint[posCase]->y - 4.5*positionPiontCurrent.h/6;
          if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[indicePiont], NULL, &positionPiontCurrent) ){
            fprintf(stderr, "Error SDL_RenderCopy in affichePiontSurPlateau 2 : %s \n", SDL_GetError());
            return -1;
          }
          k = -1; // pour sortir de la boucle
        }
      }
    }
  }
  return 0;
}