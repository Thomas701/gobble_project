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
  while(*numPion < 0 || *numPion > N-1 || !existPionInStack(stackArray, *numStack, *numPion) || !canPlayStack(*numPion, map3D))
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

int SF_demandeDeplacement(){
  int deplacement = -1; // deplacement à -1 evite do while car on n'aime pas

  printf("Voulez-vous restreindre les déplacements à une distance de 1?\n[0] Non\n[1] Oui\n");
  scanf(" %d", &deplacement);

  while (deplacement != 0 && deplacement != 1) {
    printf("Resultat invalide");
    printf("Voulez-vous restreindre les déplacements à une distance de 1?\n[0] Non\n[1] Oui\n");
    scanf(" %d", &deplacement);
    vider_buffer();
  }
  return deplacement;
}
