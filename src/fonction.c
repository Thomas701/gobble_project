/**
 * \file fonction.c
 * 
 * \brief Fichier contenant les fonctions "actives" liées aux mouvement des pions.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

/**
 * \fn void mooveSinceStack(char *** map, char ** stackArray, int numStack,int sizePiont ,int endPiont, char c)
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
 */
void mooveSinceStack(char *** map, char ** stackArray, int numStack,int sizePion ,int endPion, char c){ // c = 'b' or 'n'
  stackArray[numStack][sizePion] = '0';
  int x = (endPion - endPion % N) / N;  int y = endPion % N; // transformation en coordonnées pour écrire dans le tableau
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
 * \author DUPOIS Thomas & VILLEPREUX Thibault
 */ 
void gameOption(char ** stackArray, char *** map3D, char ** map2D, char c, int deplacement) { // c = 'b' or 'n' joueur qui choisie
  if (c == 'b')   printf("Joueur 1, c'est a vous!\n");
  else            printf("Joueur 2, c'est a vous!\n");
  int answer = 0;  int* p_answer = &answer;    //permet de savoir si il existe encore des pions dans la pile, si "non" alors on lui demande pas si il veut jouer un pion de la pile
  answer = (isStackFull(stackArray) || !existPionInMap(map2D, c)) ? 1 : 0;
  
  if (canPlayNewPiont(stackArray, map2D) && !isStackFull(stackArray) && existPionInMap(map2D, c) // verifie les options dispo
      && (deplacement == 0 || (canEffectDeplacementWithDistance(map3D, c) && deplacement == 1)))  // demande l'option jouer nouveau pion ou deplacer ancien pion 
         SGO_demandePileEtDeplacement(map3D, map2D, p_answer);
  
  if (answer == 2 || answer == 0 && (deplacement == 0 || canEffectDeplacementWithDistance(map3D, c))) {// cas ou il a choisi/obligé de prendre l'option de déplacer un pion déja jouer
    int debPiont = 0 ; int * p_debPiont = &debPiont ; 
    int endPiont = 0 ; int * p_endPiont = &endPiont ;
    SGO_demandeQuelPiontDeplacer(map3D, map2D, p_debPiont);  // demande le coup qu le joueur veut faire (coord pion avant / après)

    if(!deplacement) SGO_verifEtDeplacementCaseSansLimite(map3D, c, p_debPiont, p_endPiont); // vérifie si deplacement valide, modifie le poiteur si non valide
    else             SGO_verifEtDeplacementCaseAvecLimite(map3D, c, p_debPiont, p_endPiont); // vérifie si deplacement valide, modifie le poiteur si non valide
      
    moove(map3D, debPiont, endPiont); // deplace le pion jouer car valide
    initMap2D(map2D, map3D);          // récupère l'information et l'écris dans la map 2D
  }
  else // cas ou il joue un nouveau pion et il peut le jouer cad il existe une pile ou il peut mettre un piont sur le plateau
  {
    int numPion  ; int * p_numPion = &numPion;   // variables pour la demandes d'informations
    int numStack ; int * p_numStack = &numStack;
    int endPiont ; int * p_endPiont = &endPiont;

    SGO_demanderQuellePileJouer(map3D, map2D, stackArray, p_numStack);      // demande quelle pile il veut jouer
    SGO_demanderQuelPionJouer(map3D, stackArray, p_numStack, p_numPion);    // demande quel pion il veut jouer
    printMap2D(map2D); printMap3dDebug(map3D);                              // affichage pour le joueur
    SGO_demanderQuelleCaseJouerPion(map3D, p_numPion, p_endPiont);          // demande à quelle case ou il veut mettre son pion
    mooveSinceStack(map3D, stackArray, numStack, numPion, endPiont, c);     // deplace le pion (verifie dans la fonction si déplacement valide)
    initMap2D(map2D, map3D);                                                // récupère l'information et l'écris dans la map 2D
 }
}





/**
 * \fn void gameOptionGraphique(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint, SDL_Rect ** tableauCase, char ** pileJ1, char ** pileJ2, char *** map3D, char ** map2D, int * p_etats, SDL_Texture ** textureTableauPion, int distance)
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
 * \author DUPOIS Thomas & VILLEPREUX Thibault
 */ 
void gameOptionGraphique(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint, SDL_Rect ** tableauCase,  
                         char ** pileJ1, char ** pileJ2, char *** map3D, char ** map2D, int * p_etats, 
                         SDL_Texture ** textureTableauPion, int distance){ // c = 'b' or 'n' joueur qui choisie
  int selection = 0;
  int imageIndexP = -1; // indique l'indexe de l'image qui a été selectionnée
  int imageIndexS = -1; // indique l'indexe de l'image ou le pion a été placé
  char c = 'b';

  SDL_Event event;      // pour récupérer les évennements
  SDL_Point pointMouse; // pour récupérer la positions de la souris

  while(2 == *p_etats){ // boucle principale
    while(SDL_PollEvent(&event)){ // programme continue et un nouveau evenement dans la file
      switch(event.type){
        case SDL_MOUSEBUTTONDOWN:
        if (event.button.button == SDL_BUTTON_LEFT){ // bouton souris gauche
          SDL_GetMouseState(&pointMouse.x, &pointMouse.y); // recupere coord souris
          if (selection == 0) imageIndexP = canSelection(pointMouse, map3D, map2D, tableauCase, pileJ1, pileJ2, c, distance); //si aucune image sélectionné, vérifie au clique si on peut faire une action avec le pion
          else{
            if(c == 'b')      imageIndexS = canPlay(imageIndexP, pointMouse, tableauCase, map3D, pileJ1, distance);  // verifie si le joueur 1 peut faire quelque chose sur l'indexe ou il a posé le pion

            else              imageIndexS = canPlay(imageIndexP, pointMouse, tableauCase, map3D, pileJ2, distance);  // verifie si le joueur 2 peut faire quelque chose sur l'indexe ou il a posé le pion
          }
          if (selection == 1 && imageIndexS == -1)       selection = 0; 
          else if (selection == 0 && imageIndexP != -1)  selection = 1; 
          else if (selection == 1 && imageIndexS != -1) {
            if (imageIndexP > (N*N) - 1) {
              if(c == 'b') {
                for (int i = 0; i < N-1; i++) {
                  if (pileJ1[i][(N-1) - (imageIndexP % N)] != '0') {
                    mooveSinceStack(map3D, pileJ1, i, (N-1) - (imageIndexP % N), imageIndexS, c);
                    break;
                  }
                }
                initMap2D(map2D, map3D);    // mise a jour de la map2D car action a eu lieu
                c = (c == 'b') ? 'n' : 'b'; // changement de joueur
                selection = 0;
                if (count_pion(map2D, N, 'b') || count_pion(map2D, N, 'n')) // detecte un victoire donc changement etat (victoire)
                  *p_etats = 1;
              }
              else {
                for (int i = 0; i < N-1; i++) {
                  if (pileJ2[i][(N-1) - (imageIndexP % N)] != '0') {
                    mooveSinceStack(map3D, pileJ2, i, (N-1) - (imageIndexP % N), imageIndexS, c); // deplace le pion car deplacement valide
                    break;
                  }
                }
                initMap2D(map2D, map3D);    // mise a jour de la map2D car action a eu lieu
                c = (c == 'b') ? 'n' : 'b'; // changement de joueur
                selection = 0;
                if (count_pion(map2D, N, 'b') || count_pion(map2D, N, 'n')) // detecte un victoire donc changement etat (victoire)
                  *p_etats = 1;
              }
            }
            else
            {
              moove(map3D, imageIndexP, imageIndexS); 
              initMap2D(map2D, map3D);  // mise a jour de la map2D car action a eu lieu
              c = (c == 'b') ? 'n' : 'b';
              selection = 0;
              if (count_pion(map2D, N, 'b') || count_pion(map2D, N, 'n'))
                *p_etats = 1;
            }
            initMap2D(map2D, map3D);  // mise a jour de la map2D car action a eu lieu
            imageIndexP = -1;
          }
        }
      }
      SDL_RenderClear(renderer);
      if(c == 'b')       printMapEmptySDL(tableauTextureMapVide[1], renderer);      // affiche map couleur bleu
      else if (c == 'n') printMapEmptySDL(tableauTextureMapVide[2], renderer);      // affiche map couleur rouge
      affichePileSDL(renderer, textureTableauPion, tableauDePoint, pileJ1, pileJ2);  // affiche piles des 2 joeuurs
      affichePiontSurPlateau(renderer, textureTableauPion, tableauDePoint , map3D);  // affiche pion sur plateau
      if (imageIndexP != -1) affichePionSelect(renderer, tableauDePoint, textureTableauPion, map3D, imageIndexP); // si image sélectionner rajoute pion par dessus
      SDL_RenderPresent(renderer); // MAJ du renderer donc on l'affichage
    }
  }
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













int sizePiontMaxStack(char ** stackArray, int numStack) {
  int sizePiont = 0 ;
  for(int i = N-1 ; i >= 0 ; i--) {
    if (stackArray[numStack][i] != '0') {
      sizePiont = i; 
      i = -1;
    }
  }
  return sizePiont ;
}