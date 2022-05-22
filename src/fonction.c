/**
 * \file fonction.c
 * 
 * \brief Fichier contenant les code des fonctions "actives" liées aux mouvement des pions.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

/**
 * \fn void mooveSinceStack(char *** map, char ** stackArray, int numStack,int sizePion ,int endPion, char c)
 * \brief Permet de placer le pion sur la map. Il faut d'abord vérifier si le coup est valide.
 * 
 * \param[in] char *** map : plateau de jeu détaillé
 * \param[in] char ** stackArray : pile du joueur qui déplace
 * \param[in] int numStack : numéro de la pile du joueur (exemple si 3*3 seulement 2 piles donc numéro 0 ou 1)
 * \param[in] int sizePion : taille du pion à déplacer(permet de l'identifier au sein de la pile)
 * \param[in] int endPion  : position sur la map ou il faut mettre le pion (entre 0 et 8 si 3*3)
 * \param[in] char c       : lettre qu'il faut mettre sur la map, soit 'b' si joueur 1, sinon 'n'
 * 
 * \return Pas de retour (void).
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
void mooveSinceStack(char *** map, char ** stackArray, int numStack,int sizePion ,int endPion, char c){ // c = 'b' or 'n'
  stackArray[numStack][sizePion] = '0';
  int x = (endPion - endPion % N) / N;  
  int y = endPion % N; // transformation en coordonnées pour écrire dans le tableau
  map[x][y][sizePion] = c;
}

/**
 * \fn int moove(char *** map, int posDeb, int posEnd)
 * \brief Permet de déplacer un pion se trouvant sur la map.\n
 * 
 * Vérifi dans la fonction si déplacement valide grâce à canMoove().
 * 
 * \param[in] char *** map : plateau de jeu détaillé
 * \param[in] int posDeb   : position de départ du pion (entre 0 et 8 si 3*3)
 * \param[in] int posEnd   : position d'arriver du pion (entre 0 et 8 si 3*3)
 * 
 * \return 1 si on a réussi a mettre le pion sur la map
 * \retrun 0 si déplacement non valide (canMoove) ou si erreur lors de l'insertion (n'arrive jamais).
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */ 
int moove(char *** map, int posDeb, int posEnd) {
  if (!canMoove(map, posDeb, posEnd)) return 0; // si on ne peut pas placer le pion car déplacmeent incorrecte
  else {
    int x  = (posDeb - posDeb % N) / N;   int y  = posDeb % N;
    int x2 = (posEnd - posEnd % N) / N;   int y2 = posEnd % N;
    for (int i = N-1; i >= 0; i--){
      if (map[x] [y] [i] != '0') {
          map[x2][y2][i]  = map[x][y][i];
          map[x] [y] [i] = '0';
          return 1;                        // déplacement réussi
      }
    }
    perror("In moove() : in else end\n"); return 0; // erreur si on a pas réussi a placer le pion, n'arrive jamais
  }
}

/**
 * \fn gameOption(char ** stackArray, char *** map3D, char ** map2D, char c, int deplacement)
 * \brief Fonction principale qui demande à un joueur son action et qui l'éxécute sur la map.
 * 
 * \param[in] char ** stackArray :  tableau des piles des 2 joueurs
 * \param[in] char *** map3D     : plateau de jeu détaillé
 * \param[in] char **  map2D     : plateau de jeu non détaillé
 * \param[in] char c             : permet d'identifier le joueur qui doit jouer
 * \param[in] int deplacement    : Mode de jeu, pas de restriction de voisin deplacement = 0, sinon deplacement = 1
 * 
 * \return Pas de retour (void).
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */ 
void gameOption(char ** stackArray, char *** map3D, char ** map2D, char c, int deplacement) { // c = 'b' or 'n' joueur qui choisie
  if (c == 'b')   printf("Joueur 1, c'est a vous!\n");
  else            printf("Joueur 2, c'est a vous!\n");
  int answer = 0;  int* p_answer = &answer;    //permet de savoir si il existe encore des pions dans la pile, si "non" alors on lui demande pas si il veut jouer un pion de la pile
  answer = (isStackFull(stackArray) || !existPionInMap(map2D, c)) ? 1 : 0;
  
  if (canPlayNewPion(stackArray, map2D) && !isStackFull(stackArray) && existPionInMap(map2D, c) // verifie les options dispo
      && (deplacement == 0 || (canEffectDeplacementWithDistance(map3D, c) && deplacement == 1)))  // demande l'option jouer nouveau pion ou deplacer ancien pion 
         SGO_demandePileEtDeplacement(map3D, map2D, p_answer);
  
  if ((answer == 2 || answer == 0) && (deplacement == 0 || canEffectDeplacementWithDistance(map3D, c))) {// cas ou il a choisi/obligé de prendre l'option de déplacer un pion déja jouer
    int debPion = 0 ; int * p_debPion = &debPion ; 
    int endPion = 0 ; int * p_endPion = &endPion ;
    SGO_demandeQuelPionDeplacer(map3D, map2D, p_debPion);  // demande le coup qu le joueur veut faire (coord pion avant / après)

    if(!deplacement) SGO_verifEtDeplacementCaseSansLimite(map3D, c, p_debPion, p_endPion); // vérifie si deplacement valide, modifie le poiteur si non valide
    else             SGO_verifEtDeplacementCaseAvecLimite(map3D, c, p_debPion, p_endPion); // vérifie si deplacement valide, modifie le poiteur si non valide
      
    moove(map3D, debPion, endPion); // deplace le pion jouer car valide
    initMap2D(map2D, map3D);          // récupère l'information et l'écris dans la map 2D
  }
  else // cas ou il joue un nouveau pion et il peut le jouer cad il existe une pile ou il peut mettre un pion sur le plateau
  {
    int numPion  ; int * p_numPion = &numPion;   // variables pour la demandes d'informations
    int numStack ; int * p_numStack = &numStack;
    int endPion  ; int * p_endPion = &endPion;

    SGO_demanderQuellePileJouer(map3D, map2D, stackArray, p_numStack);      // demande quelle pile il veut jouer
    SGO_demanderQuelPionJouer(map3D, stackArray, p_numStack, p_numPion);    // demande quel pion il veut jouer
    printMap2D(map2D); printMap3dDebug(map3D);                              // affichage pour le joueur
    SGO_demanderQuelleCaseJouerPion(map3D, p_numPion, p_endPion);          // demande à quelle case ou il veut mettre son pion
    mooveSinceStack(map3D, stackArray, numStack, numPion, endPion, c);     // deplace le pion (verifie dans la fonction si déplacement valide)
    initMap2D(map2D, map3D);                                                // récupère l'information et l'écris dans la map 2D
 }
}


/**
 * \fn void gameOptionGraphique(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint, SDL_Rect ** tableauCase, char ** pileJ1, char ** pileJ2, char *** map3D, char ** map2D, int * p_etats, SDL_Texture ** textureTableauPion, int distance, int * ia)
 * \brief Fonction principale qui demande à un joueur son action et qui l'éxécute sur la map.
 * 
 * \param[in] SDL_Renderer * renderer : renderer principale, sur lequel ou on colle les images du plateau / pions...
 * \param[in] SDL_Texture ** tableauTextureMapVide : pour afficher la map vide avec couleur (couleur pour indiquer le tour du joueur)
 * \param[in] point ** tableauDePoint : contient les coordonnées des cases su plateau + pile
 * \param[in] SDL_Rect ** tableauCase : contient les surfaces des cases su plateau + pile
 * \param[in] char ** pileJ1 : contient les spiles du joueur 1
 * \param[in] char ** pileJ2 : contient les spiles du joueur 2
 * \param[in] char *** map3D : plateau de jeu detaillé
 * \param[in] char **  map2D : plateau de jeu non-detaillé
 * \param[in] int * p_etats  : état de la partie, victoire / menu / entrain de jouer
 * \param[in] SDL_Texture ** textureTableauPion : contient les images de pions
 * \param[in] int deplacement    : Mode de jeu, pas de restriction de voisin deplacement = 0, sinon deplacement = 1
 * 
 * \return Pas de retour (void).
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */ 
void gameOptionGraphique(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint,
 SDL_Rect ** tableauCase,  char ** pileJ1, char ** pileJ2, char *** map3D, char ** map2D, int * p_etats, int boolPlayMusic,
 SDL_Texture ** textureTableauOptionMenu, SDL_Texture ** textureTableauPion, int distance, char * c, int * ia)
 { 
  int selection = 0;
  int imageIndexP = -1; // indique l'indexe de l'image qui a été selectionnée
  int imageIndexS = -1; // indique l'indexe de l'image ou le pion a été placé
  int eatingPion;       // -1 si aucun pion n'est mange, ou = indexDansLeTableau du pion mange
  SDL_Event event;      // pour récupérer les évennements
  SDL_Point pointMouse; // pour récupérer la positions de la souris
  // IA EXPLICATION
  // = 0 -> PAS D'IA
  // = 1 -> IA MIN-MAX QUI NE COMMENCE PAS
  // = 2 -> IA MIN-MAX QUI COMMENCE
  // = 3 -> IA ALPHA-BETA QUI NE COMMENCE PAS
  // = 4 -> IA ALPHA-BETA QUI COMMENCE
  int prof = (*ia == 1 || *ia == 2) ? 2 : 4;
  int alphaBeta = (*ia == 1 || *ia == 2) ? 0 : 1;

  while(2 == *p_etats){ // boucle principale
    while(SDL_PollEvent(&event)){ // programme continue et un nouveau evenement dans la file
      if (((*ia == 2 || *ia == 4) && *c == 'b') || ((*ia == 1 || *ia == 3) && *c == 'n'))
      {
        //int * tabParam = generateTab(-7,1,3,0,5,0,-1,2,1,0);
        int * tabParam = generateTab(0,3,3,-2,4,1,3,-1,-2,-3,0,0,0,0,0,0,0,0,0,0,0); // INFERNAL CHAMPION
        //int * tabParam = generateTab(0,0,0,0,0,0,0,0,0,0);
        //                            0,1,2,3,4,5, 6,7,8,9
        //                            g   g     g    g
        SGOG_IA(map3D, map2D, c, pileJ1, pileJ2, alphaBeta, p_etats, prof, renderer, tableauTextureMapVide, textureTableauPion, tableauDePoint, tabParam);
      }

      switch(event.type){
        case SDL_QUIT : //quitter
          *p_etats = 0;
        break ;

        case SDL_KEYDOWN :
          switch(event.key.keysym.sym)
          { //switch touches
            case SDLK_ESCAPE : //si echap
              printf("Ouiii\n");
              *p_etats = 3;
              printf("Ouiii 2\n");
              break;
            default:
              break;
          }
        break;

        case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT){ // bouton souris gauche
          SDL_GetMouseState(&pointMouse.x, &pointMouse.y); // recupere coord souris
          if (selection == 0) 
            imageIndexP = canSelection(pointMouse, map3D, map2D, tableauCase, pileJ1, pileJ2, *c, distance); //si aucune image sélectionné, vérifie au clique si on peut faire une action avec le pion
          else{
            if(*c == 'b')
              imageIndexS = canPlay(imageIndexP, pointMouse, tableauCase, map3D, pileJ1, distance);  // verifie si le joueur 1 peut faire quelque chose sur l'indexe ou il a posé le pion
            else
              imageIndexS = canPlay(imageIndexP, pointMouse, tableauCase, map3D, pileJ2, distance);  // verifie si le joueur 2 peut faire quelque chose sur l'indexe ou il a posé le pion
          }
          if (selection == 1 && imageIndexS == -1)       selection = 0; 
          else if (selection == 0 && imageIndexP != -1)  selection = 1; 
          else if (selection == 1 && imageIndexS != -1) {
            if (imageIndexP > (N*N) - 1) 
            {
              SGOG_PILE(renderer, tableauTextureMapVide, textureTableauPion, tableauDePoint, pileJ1, pileJ2, map3D, map2D, imageIndexP, imageIndexS, eatingPion, c);
              selection = 0;
              if (count_pion(map2D, N, 'b') || count_pion(map2D, N, 'n')) // detecte un victoire donc changement etat (victoire)
                *p_etats = 1;
            }
            else
            {
              eatingPion = getIndexPionWhoAreEat(map3D, imageIndexS);
              moove(map3D, imageIndexP, imageIndexS); 
              initMap2D(map2D, map3D);  // mise a jour de la map2D car action a eu lieu
              transition(renderer, textureTableauPion, tableauDePoint, map3D, imageIndexP, imageIndexS, tableauTextureMapVide, *c, pileJ1, pileJ2, eatingPion);
              *c = (*c == 'b') ? 'n' : 'b';
              selection = 0;
              if (count_pion(map2D, N, 'b') || count_pion(map2D, N, 'n'))
                *p_etats = 1;
            }
            initMap2D(map2D, map3D);  // mise a jour de la map2D car action a eu lieu
            printMap2D(map2D);
            imageIndexP = -1;
          }
        }
      }
      SDL_RenderClear(renderer);
      if(*c == 'b')       printMapEmptySDL(tableauTextureMapVide[1], renderer);      // affiche map couleur bleu
      else if (*c == 'n') printMapEmptySDL(tableauTextureMapVide[2], renderer);      // affiche map couleur rouge
      affichePileSDL(renderer, textureTableauPion, tableauDePoint, pileJ1, pileJ2);  // affiche piles des 2 joeuurs
      affichePionSurPlateau(renderer, textureTableauPion, tableauDePoint , map3D, -1);  // affiche pion sur plateau
      if (imageIndexP != -1 && selection == 1) 
        affichePionSelect(renderer, tableauDePoint, textureTableauPion, map3D, imageIndexP); // si image sélectionner rajoute pion par dessus
      SDL_RenderPresent(renderer); // MAJ du renderer donc on l'affichage
    }
  }
}

/**
 * \fn void SGOG_PILE(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, SDL_Texture ** textureTableauPion, point ** tableauDePoint, char ** pileJ1, char ** pileJ2, char *** map3D, char ** map2D, int imageIndexP, int imageIndexS, int eatingPion, char * c)
 * \brief Fonction permettant de déplacer un pion depuis une pile
 * 
 * \param[in] SDL_Renderer * renderer : renderer principale, sur lequel ou on colle les images du plateau / pions...
 * \param[in] SDL_Texture ** tableauTextureMapVide : pour afficher la map vide avec couleur (couleur pour indiquer le tour du joueur)
 * \param[in] SDL_Texture ** textureTableauPion : contient les images de pions
 * \param[in] point ** tableauDePoint : contient les coordonnées des cases su plateau + pile
 * \param[in] char ** pileJ1 : contient les spiles du joueur 1
 * \param[in] char ** pileJ2 : contient les spiles du joueur 2
 * \param[in] char *** map3D : plateau de jeu detaillé
 * \param[in] char **  map2D : plateau de jeu non-detaillé
 * \param[in] int imageIndexP : index de la case de départ
 * \param[in] int imageIndexS : index de la case de d'arrivé
 * \param[in] int eatingPion : index du pion mangé (-1 si aucun pion mangé)
 * \param[in] char * c  : caractère représentant le joueur qui joue
 * 
 * \return Pas de retour (void).
 * 
 * \author DUPOIS Thomas
 */ 
void SGOG_PILE(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, SDL_Texture ** textureTableauPion, point ** tableauDePoint,
char ** pileJ1, char ** pileJ2, char *** map3D, char ** map2D, int imageIndexP, int imageIndexS, int eatingPion, char * c)
{
  char ** pile = (*c == 'b') ? pileJ1 : pileJ2;
  for (int i = 0; i < N-1; i++) 
  {
    if (pile[i][(N-1) - (imageIndexP % N)] != '0') 
    {
      eatingPion = getIndexPionWhoAreEat(map3D, imageIndexS);
      mooveSinceStack(map3D, pile, i, (N-1) - (imageIndexP % N), imageIndexS, *c);
      break;
    }
  }
  initMap2D(map2D, map3D);    // mise a jour de la map2D car action a eu lieu
  transition(renderer, textureTableauPion, tableauDePoint, map3D, imageIndexP, imageIndexS, tableauTextureMapVide, *c, pileJ1, pileJ2, eatingPion);
  *c = (*c == 'b') ? 'n' : 'b'; // changement de joueur
}


/**
 * \fn void SGOG_IA(char *** map3D, char ** map2D, char * c, char ** pileJ1, char ** pileJ2, int alphaBeta, int * p_etats, int prof, SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, SDL_Texture ** textureTableauPion, point ** tableauDePoint, int * tabParam )
 * \brief Fonction permettant à l'intelligence artificielle de jouer
 * 
 * \param[in] char *** map3D : plateau de jeu detaillé
 * \param[in] char **  map2D : plateau de jeu non-detaillé
 * \param[in] char *  c : caractère de l'ia qui joue
 * \param[in] char ** pileJ1 : contient les spiles du joueur 1
 * \param[in] char ** pileJ2 : contient les spiles du joueur 2
 * \param[in] int alphaBeta : boolean si le alphaBeta est utilisé
 * \param[in] int * p_etats  : état de la partie, victoire / menu / entrain de jouer
 * \param[in] int prof : la profondeur de recherche dans l'arbre
 * \param[in] SDL_Renderer * renderer : renderer principale, sur lequel ou on colle les images du plateau / pions...
 * \param[in] SDL_Texture ** tableauTextureMapVide : pour afficher la map vide avec couleur (couleur pour indiquer le tour du joueur)
 * \param[in] SDL_Texture ** textureTableauPion : contient les images de pions
 * \param[in] point ** tableauDePoint : contient les coordonnées des cases su plateau + pile
 * \param[in] int * tabParam : tableau de paramètres de l'ia
 * 
 * \return Pas de retour (void).
 * 
 * \author DUPOIS Thomas
 */ 
void SGOG_IA(char *** map3D, char ** map2D, char * c, char ** pileJ1, char ** pileJ2, int alphaBeta, int * p_etats, int prof,
 SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, SDL_Texture ** textureTableauPion, point ** tableauDePoint, int * tabParam)
{
  int * tab = play(map3D, map2D, pileJ1, pileJ2, *c, 1, prof, alphaBeta, tabParam);
  printf("New eatingPion = %d\n", tab[2]);
  initMap2D(map2D, map3D);
  transition(renderer, textureTableauPion, tableauDePoint, map3D, tab[0], tab[1], tableauTextureMapVide, *c, pileJ1, pileJ2, tab[2]);
  *c = (*c == 'b') ? 'n' : 'b';
  if (count_pion(map2D, N, 'b') || count_pion(map2D, N, 'n'))
    *p_etats = 1;
  free(tab);
  free(tabParam);
}

/**
 * \fn void IAGame(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint, SDL_Texture ** textureTableauWin, int * p_etatS, SDL_Rect ** tableauCase,  SDL_Texture ** textureTableauPion , char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, int distance, char * c, int * ia)
 * \brief Fonction qui lance la partie Homme VS Homme.
 * 
 * Elle entraine l'intelligence artificielle
 *  
 * \param[in] SDL_Renderer ** renderer : rendu ou l'on colle les images.
 * \param[in] SDL_Texture ** tableauTextureMapVide : tableau de texture d'images qui contient map vide bleau ou rouge selon le tour du joueur.
 * \param[in] point ** tableauDePoint :  tableau de point pour gérer l'affichage des pions.
 * \param[in] SDL_Texture ** textureTableauWin : tableau de texture, contient les images de victoires avec lignes gagnantes éclairées.
 * \param[in] int * p_etatS : pointeur permettant de connaître l'état du programme (en game, en pause)
 * \param[in] SDL_Rect ** tableauCase : tableau de case / surface pour gérer l'affichage des pions et leurs sélections.
 * \param[in] SDL_Texture ** textureTableauPion : tableau de texture, contient les images des pions sélectionnés et non selectionnés.
 * \param[in] char *** map3D : contient la map du jeu détaillé.
 * \param[in] char **  map2D : contient la map du jeu non détaillé.
 * \param[in] char ** pileJ1 : contient la pile du joueur 1.
 * \param[in] char ** pileJ2 : contient la pile du joueur 2.
 * \param[in] int deplacement : option de jeu avec deplacement restreins ou non .
 * \param[in] int * ia : pointeur sur l'ia
 *
 * \return void : Pas de valeur de retour.
 * 
 * \author DUPOIS Thomas
 */
void IAGame(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint, SDL_Texture ** textureTableauWin, int * p_etatS, int boolPlayMusic, SDL_Texture ** textureTableauOptionMenu, SDL_Rect ** tableauCase,  SDL_Texture ** textureTableauPion , char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, int distance, char * c, int * ia)
{
  int champion = 0; int gc = 0; int tgc =0;
  int nbreIA = 10; int min = -5; int max = 5; int bestIA;
  int * tabResult = (int*) malloc(sizeof(int)*nbreIA);
  for (int tour = 0; tour < 5000; tour++)
  {  
    printf("-------------------------------\n");
    printf("TOUR: %d\n", tour);
    int ** tabIA = (int**) malloc(sizeof(int*)*nbreIA);
    printf("TEST creation tabIA\n");
    if (nbreChampion("champion.txt") == 10 || nbreChampion("grandChampion.txt") == 10 || nbreChampion("tresGrandChampion.txt") == 10)
    {
      printf("DETECTION GAGNANT\n");
      for (int i = 0; i < nbreIA; i++)
      {
        int * tab = (int*) malloc(sizeof(int)*21);
        tabIA[i] = tab;
        tabResult[i] = 0;
      }
      printf("RESET TABLEAU EFFECTUE\n");
      if (nbreChampion("tresGrandChampion.txt") == 10)
      {
        printf("detection TGC \n");
        readChampion(tabIA, "tresGrandChampion.txt");
        printf("TGC good\n");
        tgc = 1;
        clearFile("tresGrandChampion.txt");
      }
      else if (nbreChampion("grandChampion.txt") == 10)
      {
        printf("detection GC \n");
        readChampion(tabIA, "grandChampion.txt");
        printf("GC good\n");
        gc = 1;
        clearFile("grandChampion.txt");
      }
      else if (nbreChampion("champion.txt") == 10)
      {
        printf("detection Champion \n");
        readChampion(tabIA, "champion.txt");
        printf("Champion good\n");
        champion = 1;
        clearFile("champion.txt");
      }
    }
    else
    {
      for (int i = 0; i < nbreIA; i++)
      {
        tabIA[i] = generateTab(rdm(min,max),rdm(min,max),rdm(min,max),rdm(min,max),rdm(min,max),rdm(min,max),rdm(min,max),rdm(min,max),
        rdm(min,max),rdm(min,max),rdm(min,max),rdm(min,max),rdm(min,max),rdm(min,max),rdm(min,max),rdm(min,max),rdm(min,max),rdm(min,max),
        rdm(min,max),rdm(min,max),rdm(min,max));
        tabResult[i] = 0;
      }
    }
    printIAParametre(tabIA);
    for (int i = 0; i < nbreIA-1; i ++)
    {
      for (int j = i+1; j < nbreIA; j++)
      {
        printf("IA : %d vs %d\n", i, j);
        trainingIA(renderer, tableauTextureMapVide, tableauDePoint, textureTableauPion, map3D, map2D, pileJ1, pileJ2, i, j, tabIA, tabResult);
      }
    }
    printIAResult(tabResult, nbreIA);
    bestIA = getMaxOnTable(tabResult, nbreIA);
    if (champion)
      writeChampion(tabIA[bestIA], "grandChampion.txt");
    else if (gc)
      writeChampion(tabIA[bestIA], "tresGrandChampion.txt");
    else if (tgc)
      writeChampion(tabIA[bestIA], "infernalChampion.txt");
    else
      writeChampion(tabIA[bestIA], "champion.txt");
    champion = 0;
    gc = 0;
    tgc = 0;
    freeTableIA(tabIA, nbreIA);
  }
  *p_etatS = 0;
  free(tabResult);
}

/**
 * \fn void trainingIA(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint,  SDL_Texture ** textureTableauPion , char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, int i, int j, int ** tabIA, int * tabResult)
 * \brief Fonction qui lance la partie IA VS IA
 * 
 * Elle entraine l'intelligence artificielle
 *  
 * \param[in] SDL_Renderer ** renderer : rendu ou l'on colle les images.
 * \param[in] SDL_Texture ** tableauTextureMapVide : tableau de texture d'images qui contient map vide bleau ou rouge selon le tour du joueur.
 * \param[in] point ** tableauDePoint :  tableau de point pour gérer l'affichage des pions.
 * \param[in] SDL_Texture ** textureTableauPion : tableau de texture, contient les images des pions sélectionnés et non selectionnés.
 * \param[in] char *** map3D : contient la map du jeu détaillé.
 * \param[in] char **  map2D : contient la map du jeu non détaillé.
 * \param[in] char ** pileJ1 : contient la pile du joueur 1.
 * \param[in] char ** pileJ2 : contient la pile du joueur 2.
 * \param[in] int i : ia1
 * \param[in] int j : ia2
 * \param[in] int ** tabIA : contient l'ensemble des ias (tableaux de paramètre)
 * \param[in] int * tabResult : contient les resultats
 *
 * \return void : Pas de valeur de retour.
 * 
 * \author DUPOIS Thomas
 */
void trainingIA(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint,  SDL_Texture ** textureTableauPion , char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, int i, int j, int ** tabIA, int * tabResult)
{
  char c = 'b';
  int testArret = 0; 
  int arretImminent = 0;
  for (int k = 0; k < 4; k++)
  {
    while (!count_pion(map2D, N, 'b') && !count_pion(map2D, N, 'n') && arretImminent == 0)
    {
      if(c == 'b')
      {
        int * tabASuppr = play(map3D, map2D, pileJ1, pileJ2, c, 1, 2, 1, tabIA[i]);
        free(tabASuppr);
      }
      else
      {
        int * tabASuppr = play(map3D, map2D, pileJ1, pileJ2, c, 1, 2, 1, tabIA[j]);
        free(tabASuppr);
      }
      c = (c == 'b') ? 'n' : 'b';
      initMap2D(map2D, map3D);
      testArret++;
      if (testArret > 150) // cas ou les deux IA déplace le même pion en boucle et la partie ne s'arrète jamais
      {
        printf("ARRET IMMINENET: IA STUPIDE!\n");
        arretImminent = 1;
      }  
    }
    testArret = 0;
    arretImminent = 0;
    if (count_pion(map2D, N, 'b') && count_pion(map2D, N, 'n'))
    {
      printf("Egalité entre IA\n");
    }
    else if (count_pion(map2D, N, 'b'))
    {
      tabResult[i] = tabResult[i] + 1;
    }
    else if (count_pion(map2D, N, 'n'))
    {
      tabResult[j] = tabResult[j] + 1;
    }

    // réinitialise pile et plateau pour prochaine game
    initMap(map3D);       initMap2D(map2D, map3D);
    initPile(pileJ1,'b'); initPile(pileJ2,'n');
  }
  printf("Score IA%d: %d\n", i, tabResult[i]);
  printf("Score IA%d: %d\n", j, tabResult[j]);
}




