#include "fonction.h"
#include "verification.h"
#include "graphique.h"
#include "creation.h"
#include "print.h"
#include "free.h"
#include "init.h"
#include "saveFile.h"
#include "error.h"

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
  int* p_answer = &answer;
  answer = (isStackFull(stackArray) || !existPiontInMap(map2D, c)) ? 1 : 0;
  if (canPlayNewPiont(stackArray, map2D) && !isStackFull(stackArray) && existPiontInMap(map2D, c) && (deplacement == 0 || (canEffectDeplacementWithDistance(map3D, c) && deplacement == 1)))
  {
    SGO_demandePileEtDeplacement(map3D, map2D, p_answer);
  }
  if (answer == 2 || answer == 0 && (deplacement == 0 || canEffectDeplacementWithDistance(map3D, c))) // cas ou il a choisi l'option 2 ou cas ou il a seulement l'option 2 possible
  {
    int debPiont = 0 ; int * p_debPiont = &debPiont ;
    int endPiont = 0 ; int * p_endPiont = &endPiont ;
    SGO_demandeQuelPiontDeplacer(map3D, map2D, p_debPiont);

    if(!deplacement)
      SGO_verifEtDeplacementCaseSansLimite(map3D, c, p_debPiont, p_endPiont);
    else
      SGO_verifEtDeplacementCaseAvecLimite(map3D, c, p_debPiont, p_endPiont);
      
    moove(map3D, debPiont, endPiont);
    initMap2D(map2D, map3D);
  }
  else // cas ou il joue un nouveau piont et il peut le jouer cad il existe une pile ou il peut mettre un piont sur le plateau
  {
    int numPion ; int * p_numPion = &numPion;
    int numStack ; int * p_numStack = &numStack;
    int endPiont ; int * p_endPiont = &endPiont;

    SGO_demanderQuellePileJouer(map3D, map2D, stackArray, p_numStack);
    SGO_demanderQuelPionJouer(map3D, stackArray, p_numStack, p_numPion);
    printMap2D(map2D);
    printMap3dDebug(map3D);
    SGO_demanderQuelleCaseJouerPion(map3D, p_numPion, p_endPiont);
    mooveSinceStack(map3D, stackArray, numStack, numPion, endPiont, c);
    initMap2D(map2D, map3D);
 }
}

void SGO_demandePileEtDeplacement(char *** map3D, char ** map2D, int * answer)
{
  printf("Print1\n");
  printMap2D(map2D);
  printMap3dDebug(map3D);
  printf("Que souhaitez-vous faire ? \n[1] Jouer un nouveau pion ? (de votre pile)  \n[2] Deplacer un pion se trouvant sur la map  \n");
  scanf(" %d", answer);
  vider_buffer();
  //printf("Selection: %d, deplacement: %d, fonction: %d", answer, deplacement, canEffectDeplacementWithDistance(map3D, c));
  while (*answer != 1 &&  *answer != 2)
  {
    printf("Je n'ai pas compris !  \n\nQue voulez-vous faire ? \n[1] Jouer un nouveau pion ? (de votre pile)  \n[2] Deplacer un pion se trouvant sur la map  \n");
    scanf(" %d", answer);
    vider_buffer();
  }
}

void SGO_demandeQuelPiontDeplacer(char *** map3D, char ** map2D, int * debPiont)
{
  printMap2D(map2D);
  printMap3dDebug(map3D);
  printf("Quel pion voulez-vous deplacer ? \n");
  scanf(" %d", debPiont);
  vider_buffer();
}

void SGO_verifEtDeplacementCaseSansLimite(char *** map3D, char c, int * debPiont, int * endPiont)
{
  while(*debPiont < 0 || *debPiont > N*N-1 || !canMooveThisPiontD(map3D, *debPiont, c))
  {
    printf("Index non valide ! \nQuel pion voulez vous deplacer ?\n");
    scanf(" %d", debPiont);
    vider_buffer();
  }

  printf("Sur quel case voulez vous deplacer le piont %d ? \n", *debPiont);
  scanf(" %d", endPiont);
  vider_buffer();
  
  while(*endPiont < 0 || *endPiont > (N*N)-1 || *endPiont == *debPiont || !canMoove(map3D, *debPiont, *endPiont))
  {
    printf("Deplacement invalide, veuillez recommencer. \n");
    printf("Sur quelle case voulez vous deplacer le pion %d ? \n", *debPiont);
    scanf(" %d", endPiont);
    vider_buffer();
  }
}

void SGO_verifEtDeplacementCaseAvecLimite(char *** map3D, char c, int * debPiont, int * endPiont)
{
  while(*debPiont < 0 || *debPiont > N*N-1 || !canMooveThisPiontDistance(map3D, *debPiont, c))
  {
    printf("Index non valide ! \nQuel pion voulez vous deplacer ?\n");
    scanf(" %d", debPiont);
    vider_buffer();
  }
  int x1 = (*debPiont - *debPiont % N) / N;
  int y1 = *debPiont % N;
  printf("Sur quel case voulez vous deplacer le piont %d ? \n", *debPiont);
  scanf(" %d", endPiont);
  int x2 = (*endPiont - *endPiont % N) / N;
  int y2 = *endPiont % N;
  while (*endPiont < 0 || *endPiont > (N*N)-1 || *endPiont == *debPiont || !canMoove(map3D, *debPiont, *endPiont) || maximum(abs(x1-x2), abs(y1-y2)) > 1)
  {
    printf("Case invalide (distance>1)\nSur quel case voulez vous deplacer le pion %d ? \n", *debPiont);
    scanf(" %d", endPiont);
    x2 = (*endPiont - *endPiont % N) / N;
    y2 = *endPiont % N;
    //printf("x1:%d, x2:%d, y1:%d, y2:%d result:%d\n", x1, x2, y1, y2, maximum(abs(x1-x2), abs(y1-y2)));
    vider_buffer();
  }
}

void SGO_demanderQuellePileJouer(char *** map3D, char ** map2D, char ** stackArray, int * numStack)
{
  printMap2D(map2D);
  printMap3dDebug(map3D);
  printf("Voici vos piles : \n");
  printStacks(stackArray);
  printf("Quelle pile voulez vous jouer ?\n");
  scanf(" %d", numStack);
  while(*numStack < 0 || *numStack > N-2 || isEmptyStack(stackArray, *numStack) || !canPlayStack(sizePiontMaxStack(stackArray , *numStack), map3D))
  {
    printf("Vous ne pouvez rien faire avec cette pile ! \nVeuillez saisir un nouveau numero de pile.\n");
    scanf(" %d", numStack);
    vider_buffer();
  }
}

void SGO_demanderQuelPionJouer(char *** map3D, char ** stackArray, int * numStack, int * numPion)
{
  printf("Quel pion voulez vous jouer (0 <= pion <= %d) ?\n", N-1);
  scanf(" %d", numPion);
  while(*numPion < 0 || *numPion > N-1 || !existPiontInStack(stackArray, *numStack, *numPion) || !canPlayStack(*numPion, map3D))
  {
    //printf("f1: %d & f2: %d\n", !existPiontInStack(stackArray, numStack, numPion), !canPlayStack(numPion, map3D));
    printf("Vous ne pouvez rien faire avec ce pion! \nVeuillez saisir un nouveau pion dans cette pile.\n");
    scanf(" %d", numPion);
    vider_buffer();
  }
}

void SGO_demanderQuelleCaseJouerPion(char *** map3D, int * numPion, int * endPiont)
{
  printf("A quelle place voulez vous jouez le pion numero %d ? \n", *numPion);
  scanf(" %d", endPiont);
  vider_buffer();
  while(*endPiont < 0 || *endPiont > (N*N)-1 || !canPutPiont(map3D, *numPion, *endPiont))
  {
    printf("Position d'arrivee invalide !\nVeuillez resaisir le numero de case où vous voulez jouer [%d] \n", canPutPiont(map3D, *numPion, *endPiont));
    scanf(" %d", endPiont);
    vider_buffer();
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
            imageIndexP = -1;
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
      if (imageIndexP != -1)
        affichePionSelect(renderer, tableauDePoint, textureTableauPiont, map3D, imageIndexP);
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