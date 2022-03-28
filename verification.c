/**
 * \file verification.c
 * 
 * \brief Fichier contenant les codes des fonctions permettant de vérifier si un déplacement / insertion de nouveau pion est valide.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */


/**
 * \fn int maximum(int i, int i2)
 * 
 * \brief Fonction qui retourne le maximum entre 2 entiers.
 * 
 * \param[in] int i  : premier  entier.
 * \param[in] int i2 : deuxième entier.
 * 
 * \return int : retourne l'entier le plus grand.
 * 
 * \author DUPOIS Thomas
 */
int maximum(int i, int i2) { return (i > i2) ? i : i2; }

/**
 * \fn int minimum(int i, int i2)
 * 
 * \brief Fonction qui retourne le minimum entre 2 entiers.
 * 
 * \param[in] int i  : premier  entier.
 * \param[in] int i2 : deuxième entier.
 * 
 * \return int : retourne l'entier le plus petit.
 * 
 * \author DUPOIS Thomas
 */
int minimum(int i, int i2) { return (i > i2) ? i2 : i; }


/**
 * \fn int existPionInMap(char ** map2D, char c)
 * 
 * \brief Fonction qui regarde si il **existe un pion visible** sur le plateau.
 * 
 * \param[in] char ** map2D : map non detaillé, uniquement en 2D qui permet de voir uniquement les pions visibles.
 * \param[in] char c : identifiant du joueur ('b' ou 'n').
 * 
 * \return int : retourne 1 si il existe un pion visible c sinon 0.
 * 
 * \author VILLEPREUX Thibault
 */
int existPionInMap(char ** map2D, char c) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (map2D[i][j] == c)
        return 1;
    }
  }
  return 0;
}

/**
 * \fn int existPionInStack(char ** stack, int num, int i)
 * 
 * \brief Fonction qui regarde si il existe un pion d'une certaine taille sur la pile d'un joueur.
 * 
 * \param[in] char ** stack : pile du joueur.
 * \param[in] int num : numéro de la pile du joueur.
 * \param[in] int i : taille du pion que l'on doit chercher.
 * 
 * \return int : retourne 1 si il existe un pion sinon 0.
 * 
 * \author VILLEPREUX Thibault
 */
int existPionInStack(char ** stack, int num, int i) {
  if (stack[num][i] == '0') return 0;
  else return 1;
}

/**
 * \fn int existPionInStack(char ** stack, int num, int i)
 * 
 * \brief Fonction qui regarde si il existe un pion d'une certaine taille sur la pile d'un joueur.
 * 
 * \param[in] char ** stack : pile du joueur.
 * \param[in] int num : numéro de la pile du joueur.
 * \param[in] int i : taille du pion que l'on doit chercher.
 * 
 * \return int : retourne 1 si il existe un pion sinon 0.
 * 
 * \author VILLEPREUX Thibault
 */
int isEmptyStack(char ** stack, int num) {
  for (int i = 0; i < N; i++) {
    if (stack[num][i] != '0') return 0;
  }
  return 1;
}

/**
 * \fn int int isEmptyStacks(char ** stack)
 * 
 * \brief Fonction qui regarde si la pile du joueur est vide.
 * 
 * \param[in] char ** stack : pile du joueur.
 * 
 * \return int : retourne 0 si elle est vide sinon 1.
 * 
 * \author VILLEPREUX Thibault
 */
int isEmptyStacks(char ** stack){
  for(int i = 0; i < N-1; i++)  {
    for(int j = 0; j < N; j++)  {   // ascendant pour opti
      if (stack[i][j] != '0') return 0;
    }
  }
  return 1;
}

/**
 * \fn int int isEmptyStacks(char ** stack)
 * 
 * \brief Fonction qui regarde si il existe une case du plateau vide.
 * 
 * \param[in] char ** map2D : plateau de jeu non detaillé.
 * 
 * \return int : retourne 1 si il existe une case vide sinon 0.
 * 
 * \author VILLEPREUX Thibault
 */
int isEmptyCase(char ** map2D) {
   for(int i = 0; i < N; i++) {
     for(int j = 0 ; j < N ; j++) {
       if('0' == map2D[i][j]) return 1;
     }
   }
   return 0;
 }

/**
 * \fn int canMoove(char *** map, int posDeb, int posEnd)
 * 
 * \brief Fonction qui regarde si le pion d'une case du plateau de jeu peut se déplacer vers une autre case du plateau de jeu.
 * 
 * \param[in] char *** map : plateau de jeu detaillé.
 * \param[in] int posDeb : numéro de la case de depart.
 * \param[in] int posEnd : numéro de la case d'arriver.
 * 
 * \return int : retourne 1 si le déplacement est possible sinon 0.
 * 
 * \author DUPOIS Thomas
 */
int canMoove(char *** map, int posDeb, int posEnd) {
  int x  = (posDeb - posDeb % N) / N;  int y  = posDeb % N; // transforme le numéro de la case de depart en coordonnée.
  int x2 = (posEnd - posEnd % N) / N;  int y2 = posEnd % N; // transforme le numéro de la case d'arriver en coordonnée.
  int count  = 0; int count2 = 0;
  
  for (int i = 0; i < N; i++) {
    if (map[x ][y ][i] != '0') count  = i+1; // compte le nombre de pion sur la case de depart
    if (map[x2][y2][i] != '0') count2 = i+1; // compte le nombre de pion sur la case de d'arriver
  }
  if (count > count2) return 1; // si il y a plus de pion sur la case de depart alors deplacement valide
  else return 0;                // sinon invalide ?
}

/**
 * \fn int canMooveThisPion(char *** map, char ** map2D ,int posDeb, char c)
 * 
 * \brief Fonction qui regarde si le pion d'une case du plateau de jeu peut se deplacer ailleurs dans la map. Il existe une possibilité de déplacement.
 * 
 * \param[in] char *** map : plateau de jeu detaillé.
 * \param[in] char ** map2D : plateau de jeu non detaillé.
 * \param[in] int posDeb : numéro de la case de depart.
 * \param[in] char c : identifiant du joueur qui veut deplacer son pion.
 * 
 * \return int : retourne 1 si le déplacement est possible sinon 0.
 * 
 * \author VILLEPREUX Thibault
 */
int canMooveThisPion(char *** map, char ** map2D, int posDeb, char c) {
  int x = (posDeb - posDeb % N) / N; int y = posDeb % N; // transforme le numéro de la case en indice.
  int count  = -1;
  char pion;
  for (int i = 0; i < N; i++) { // compte le nombre de pion sur la case du plateau donné en paramètre 
    if (map[x][y][i] != '0') {
      count = i;
      pion = map[x][y][i]; // dernier pion sur la map, enregistre le joueur qui le possède
    }
  }
  if (pion != c) return 0; // si le dernier pion n'est pas de notre couleur impossible (on ne peut pas déplacer un pion qui n'est pas le notre)
  else { // sinon le pion que l'on veut déplacer est le notre
    if(isEmptyCase(map2D)) return 1; // si la map est vide alors on peut
    else { // on cherche une case qui possède des pions pas plus grande que notre pion
      int max;
      for (int i = 0; i < N; i++)  {
        for (int j = 0; j < N; j++){
          max = N-1;
          for (int k = N-1; k >= 0; k--) {
            if (map[x][y][k] != '0') {
              max = k;
              k = -1; // si on trouve on sort de la boucle et on retourn 1
            }
          }
          if (max < count) return 1;
        }
      }
      return 0; // pas trouver
    }
  }
}

/**
 * \fn int canMooveThisPionDistance(char *** map, int posDeb, char c)
 * 
 * \brief Fonction qui regarde si le pion d'une case du plateau de jeu peut se deplacer ailleurs dans la map **d'une distance de 1**. Il existe une possibilité de déplacement.
 * 
 * \param[in] char *** map : plateau de jeu detaillé.
 * \param[in] int posDeb : numéro de la case de depart.
 * \param[in] char c : identifiant du joueur qui veut deplacer son pion.
 * 
 * \return int : retourne 1 si le déplacement est possible sinon 0.
 * 
 * \author DUPOIS Thomas
 */
int canMooveThisPionDistance(char *** map, int posDeb, char c) {
  int x = (posDeb - posDeb % N) / N; int y = posDeb % N;  // transforme le numéro de la case en indice
  int i, j, iEnd, jEnd;
  int count  = -1;
  int max;
  char pion;
  for (int i = 0; i < N; i++) {
    if (map[x][y][i] != '0')  {
      count = i;
      pion = map[x][y][i];
    }
  }
  if (pion != c) return 0;
  else {
    i = maximum(0, x-1); iEnd = minimum(x+1, N-1);
    for (; i <= iEnd; i++) {
      j = maximum(0, y-1); jEnd = minimum(y+1, N-1);
      for (; j <= jEnd; j++) {
        max = -1; // gros nombre!
        for (int k = 0; k < N ; k++) {
          if (map[i][j][k] != '0') {
            max = k;
            break; //Pour stopper la boucle
          }
        }
        if (max < count) return 1;
      }
    }
    return 0;
  }
}

/**
 * \fn int canMooveThisPionD(char *** map, int posDeb, char c)
 * 
 * \brief Fonction qui regarde si le pion d'une case du plateau de jeu peut se deplacer ailleurs dans la map **d'une distance de 1**. Il existe une possibilité de déplacement.
 * 
 * \param[in] char *** map : plateau de jeu detaillé.
 * \param[in] char ** map2D : plateau de jeu non detaillé.
 * \param[in] int posDeb : numéro de la case de depart.
 * \param[in] char c : identifiant du joueur qui veut deplacer son pion.
 * 
 * \return int : retourne 1 si le déplacement est possible sinon 0.
 * 
 * \author DUPOIS Thomas
 */
int canMooveThisPionD(char *** map, int posDeb, char c) // Le pion peut-il bouger?
{
  int x = (posDeb - posDeb % N) / N; int y = posDeb % N; // transforme le numéro de la case en indice.
  int count  = -1;
  int max;
  char pion;
  for (int i = 0; i < N; i++) { // compte le nombre de pion sur la case du plateau donné en paramètre 
    if (map[x][y][i] != '0')  {
      count = i;
      pion = map[x][y][i];      // dernier pion sur la map, enregistre le joueur qui le possède
    }
  }
  if (pion != c) return 0; // si le dernier pion n'est pas de notre couleur impossible (on ne peut pas déplacer un pion qui n'est pas le notre)
  else { // sinon le pion que l'on veut déplacer est le notre
    for (int i = 0; i < N; i++)  { // on cherche une case d'une distance de 1 qui possède des pions pas plus grande que notre pion
      for (int j = 0; j < N; j++){
        max = -1; // gros nombre!
        for (int k = 0; k < N ; k++) { 
          if (map[i][j][k] != '0') {
            max = k;
            break; //Pour stopper la boucle
          }
        }
        if (max < count)  return 1;
      }
    }
    return 0;
  }
}

/**
 * \fn int count_pion(char ** map, int nbre, char c)
 * 
 * \brief Fonction qui regarde si il y a un alignement de nombre (passé en paramètre) pions du joueur sur la map.
 * 
 * \param[in] char ** map : plateau de jeu non detaillé.
 * \param[in] int nbre : nombre de pion(s) à aligné(s).
 * \param[in] char c : identifiant du joueur.
 * 
 * \return int : retourne 1 si il existe un alignement de **nbre pion(s)** du joueur sinon 0.
 * 
 * \author DUPOIS Thomas
 */
int count_pion(char ** map, int nbre, char c) {
  int count_L  = 0; int count_C  = 0; //compteur mis a 0 au debut
  int count_DD = 0; int count_DG = 0; //compteur mis a 0 au debut

/* Vérification si il y a une ligne, colonne ou diagonale complété */
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) { // compte dans toutes les directions
      count_L += (map[i][j] == c) ? 1 : 0; 
      count_C += (map[j][i] == c) ? 1 : 0;
      count_DD += (map[j][j] == c) ? 1 : 0;
      count_DG += (map[N-1-j][j] == c) ? 1 : 0;
    }
    if (count_C == nbre || count_L == nbre || count_DD == nbre || count_DG == nbre) return 1; // victoire du joueur
    else {
      count_C = 0; count_L = 0; count_DD = 0; count_DG = 0;
    }
  }
  return 0;
}

/**
 * \fn void debugTab(SDL_Rect ** tableauCase)
 * 
 * \brief Fonction qui vérifie que les cases n'ont pas été modifié car bug sur WINDOWS.
 * 
 * \param[in] SDL_Rect ** tableauCase : tableau de cases.
 * 
 * \return void : pas de retour, fonction avec effet de bord.
 * 
 * \author DUPOIS Thomas
 */
void debugTab(SDL_Rect ** tableauCase) {
  for (int i = 0; i < (N*N) + (N*2); i++) {
    if (tableauCase[i]->x > 2000 || tableauCase[i]->x < 0 || tableauCase[i]->y > 2000 || tableauCase[i]->y < 0 
     || tableauCase[i]->w > 2000 || tableauCase[i]->w < 0 || tableauCase[i]->h > 2000 || tableauCase[i]->h < 0) {
      free(tableauCase[i]);
      tableauCase[i] = (SDL_Rect *) malloc(sizeof(SDL_Rect));
      initTableauCase(tableauCase);
    }
  }
}

/**
 * \fn int check_End_Game(char ** map)
 * 
 * \brief Fonction qui nous informe en cas de victoire du joueur et nous donne l'identifiant de la ligne correspondante.
 * 
 * \param[in] SDL_Rect ** tableauCase : tableau de cases
 * 
 * \return int : retourne 1 si pas de victoire sinon retourn un nombre >  0, qui représente un identifiant de la ligne afin de réaliser un affichage en SDL.
 * 
 * \author DUPOIS Thomas
 */
int check_End_Game(char ** map) {
  int count_L  = 0; int count_C  = 0; //compteur mis a 0 au debut
  int count_DD = 0; int count_DG = 0; //compteur mis a 0 au debut

  //Vérification si il y a une ligne, colonne ou diagonale complété
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N-1; j++) {
      if (map[i][j] == map[i][j+1] && map[i][j] != '0') count_L++; // compte dans toutes les directions
      if (map[j][i] == map[j+1][i] && map[j][i] != '0') count_C++;
      if (map[j][j] == map[j+1][j+1] && map[j][j] != '0') count_DD++;
      if (map[N-1-j][j] == map[N-1-(j+1)][j+1] && map[N-1-j][j] != '0') count_DG++;
    } // si un compteur a atteint le bon nombre on retorun l'id de la ligne
    if (count_C == N-1 || count_L == N-1 || count_DD == N-1 || count_DG == N-1){ //partie terminée, retourne le bon numéro pour afficher la bonne ligne après
      if (count_L == N-1) return (i == 0) ? 1 : (i == 1) ? 2 : 3;
      else if (count_C == N-1) return (i == 0) ? 4 : (i == 1) ? 5 : 6;
      else if (count_DD == N-1) return 7;
      else return 8;
    }
    else { //sinon on mets à 0 et on recommence
      count_C = 0; count_L = 0; count_DD = 0; count_DG = 0;
    }
  }
  return 0; // pas de victoire
}


/**
 * \fn int sizeMaxPion(char ** stackArray)
 * 
 * \brief Fonction qui regarde si il y a un pion de taille > 1 dans la pile du joueur (patant de l'hypothèse que les piles sont non vide appelle dans canPlayNewPion).
 * 
 * \param[in] char ** stackArray : pile du joueur.
 * 
 * \return int : retourne 1 si on a au moins une pile ayant une taille max de pion de 1 ou plus sinon 0.
 * 
 * \author VILLEPREUX Thibault
 */
int sizeMaxPion(char ** stackArray) {
  for(int i = 0 ; i < N-1 ; i++)    {
    for(int j = N-1 ; j >= 1 ; j--) {
      if('0' != stackArray[i][j]) return 1;
    }
  }
  return 0;
}

/**
 * \fn int canPlayNewPion(char **  stackArray, char ** map2D)
 * 
 * \brief Fonction qui regarde si le joueur peut jouer un nouveau pion sur le plateau.\n
 * 
 * On peut jouer un nouveau pion si il existe une case vide sur le plateau, ou si on veut jouer un pion de taille > 1.
 * 
 * \param[in] char ** stackArray : pile du joueur.
 * \param[in] char ** map2D : plateau de jeu non detaillé.
 * 
 * \return int : retourne 1 si c'est possible et 0 sinon.
 * 
 * \author VILLEPREUX Thibault
 */
int canPlayNewPion(char **  stackArray, char ** map2D) {
  if(isEmptyCase(map2D)) {
    if(isEmptyStacks(stackArray)) return 0;
    else return 1;
  }
  else {
    if(sizeMaxPion(stackArray)) return 1;
    else return 0;
  }
}

/**
 * \fn int canPlayStack(int sizePion, char *** map)
 * 
 * \brief Fonction qui regarde si le joueur peut jouer un nouveau pion (et on connais sa taille) sur le plateau.\n
 * 
 * On peut jouer un nouveau pion si il existe une case ou il n'y a pas de pion de même taille et de taille supérieur.
 * 
 * \param[in] int sizePion : taille du pion que l'on cherche à poser.
 * \param[in] char *** map : plateau de jeu detaillé.
 * 
 * \return int : retourne 1 si c'est possible et 0 sinon.
 * 
 * \author VILLEPREUX Thibault
 */
int canPlayStack(int sizePion, char *** map){
  int possible;
  for(int i = 0 ; i < N ; i++) {
    for(int j = 0 ; j < N ; j++) {
      possible = 1 ;
      for(int k = N-1 ; k >= sizePion; k--) {
        if (map[i][j][k] != '0') {
          possible = 0 ; // si il y a 
          break;
        }
      }
      if (1 == possible) return 1; 
    }
  }
  return 0;
}

/**
 * \fn int canPutPion(char *** map, int sizePion, int endPion)
 * 
 * \brief Fonction qui regarde si on peut mettre un pion d'une taille donnée sur une case du plateau de jeu.
 * 
 * \param[in] char *** map : plateau de jeu detaillé.
 * \param[in] int sizePion : taille du pion que l'on cherche à poser.
 * \param[in] int endPion  : case ou l'on veut poser le pion.
 * 
 * \return int : retourne 1 si c'est possible et 0 sinon.
 * 
 * \author VILLEPREUX Thibault
 */
int canPutPion(char *** map, int sizePion, int endPion) {
  int x = (endPion - endPion % N) / N; int y = endPion % N; // transforme le numéro de la case d'arriver en coordonnée
  for(int i = N-1; i >= sizePion ; i--) { // on regarde si il y a un pion de même taille ou de taille supérieur
    if(map[x][y][i] != '0')
      return 0;
  }
  return 1;
}

/**
 * \fn int isStackFull(char ** pile)
 * 
 * \brief Fonction qui regarde si la pile du joueur est pleine ou non.
 * 
 * \param[in] char ** pile : pile du joueur.
 * 
 * \return int : retourne 1 si la pile est pleine et 0 sinon.
 * 
 * \author VILLEPREUX Thibault
 */
int isStackFull(char ** pile) {
  for (int i = 0; i < N-1; i++) {
    for (int j = 0; j < N; j++) {
      if (pile[i][j] == '0') return 0; // si on trouve un '0' alors pile non pleine
    }
  }
  return 1;
}

/**
 * \fn SDL_bool isInRect(SDL_Point point, SDL_Point rectangleHautGauche, SDL_Point rectangleBasDroit)
 * 
 * \brief Fonction qui regarde si le point de la souris se trouve à l'intérieur de la surface. La surface est donné grâce à 2 points.\n
 * 
 * Différence avec isInRectangle() qui prend un SDL_Rect, cette dernière est bien plus utilisé.
 * 
 * \param[in] SDL_Point point : coordonnée de la souris.
 * \param[in] SDL_Point rectangleHautGauche : coordonnée du rectangle haut gauche. 
 * \param[in] SDL_Point rectangleBasDroit : coordonnée du rectangle bas droit.
 * 
 * \return SDL_bool : retourne SDL_TRUE si le point de la souris est dedans et SDL_FALSE sinon.
 * 
 * \author VILLEPREUX Thibault
 */
SDL_bool isInRect(SDL_Point point, SDL_Point rectangleHautGauche, SDL_Point rectangleBasDroit) {
  if (point.x >= rectangleHautGauche.x && point.x <= rectangleBasDroit.x && point.y >= rectangleHautGauche.y && point.y <= rectangleBasDroit.y) // si le point est dans le rectangle
    return SDL_TRUE ;
  return SDL_FALSE;
}

/**
 * \fn SDL_bool isInRectangle(SDL_Point point, SDL_Rect rect)
 * 
 * \brief Fonction qui regarde si le point de la souris se trouve à l'intérieur de la surface. La surface est donné grâce à SDL_Rect.\n
 * 
 * Différence avec isInRect() qui 2 points (un en haut à gauche et un en bas à droite), cette dernière n'est pas utilisé.
 * 
 * \param[in] SDL_Point point : coordonnée de la souris.
 * \param[in] SDL_Rect rect : surface du rectangle.
 * 
 * \return SDL_bool : retourne SDL_TRUE si le point de la souris est dedans le rectangle et SDL_FALSE sinon.
 * 
 * \author VILLEPREUX Thibault
 */
SDL_bool isInRectangle(SDL_Point point, SDL_Rect rect) { 
  if(point.x >= rect.x && point.x <= (rect.x + rect.w) && point.y >= rect.y && point.y <= (rect.y + rect.h))
    return SDL_TRUE;
  return SDL_FALSE;
}

/**
 * \fn int canSelection(SDL_Point pointMouse, char *** map3D, char ** map2D, SDL_Rect ** tableauCase, char ** pileJ1, char ** pileJ2, char c, int distance)
 * 
 * \brief Fonction qui permet de savoir si on peut selectionner un pion, il vérifie qu'il y a un pion sur la case sélectionné ou qu'il peut récuperer un pion sur une pile (le pion existe et c'est la pile du joueur).
 * 
 * \param[in] SDL_Point pointMouse : coordonnée de la souris.
 * \param[in] char *** map3D : plateau de jeu detaillé.
 * \param[in] char **  map2D : plateau de jeu non detaillé.
 * \param[in] SDL_Rect ** tableauCase : tableau de case contenant les surfaces des cases des piles et des cases du plateau de jeu.
 * \param[in] char ** pileJ1 : pile du joueur 1.
 * \param[in] char ** pileJ2 : pile du joueur 2.
 * \param[in] char c : identifiant du joueur.
 * \param[in] int distance : mode de jeu.
 * 
 * \return int : retourne l'indice si valide et sinon -1.
 * 
 * \author DUPOIS Thomas
 */
int canSelection(SDL_Point pointMouse, char *** map3D, char ** map2D, SDL_Rect ** tableauCase, char ** pileJ1, char ** pileJ2, char c, int distance) {
  int index = getIndex(pointMouse, tableauCase);
  if(index != -1) {
    // cas des piles
    if(c == 'b' && index > (N*N)-1 && index < (N*N) + N) {
      for (int i = 0; i < N-1; i++) {
        if (pileJ1[i][(N-1)- index % N] != '0') return index;
      }
      return -1;
    }
    else if(c == 'n' && index > (N*N) + (N-1)) {
      for (int i = 0; i < N-1; i++) {
        if (pileJ2[i][(N-1)- index % N] != '0') return index;
      }
      return -1;
    }
    // cas des pions sur la map
    else if (index >= 0 && index < (N*N)) {
      if (distance) {
        if (canMooveThisPionDistance(map3D, index, c)) return index;
        return -1;
      }
      else
      {
        if (canMooveThisPionD(map3D, index, c)) return index;
        return -1;
      } 
    }
    else return -1; // cas ou il clique sur la pile adversaire
  }
  return -1; // cas index == -1
}


/**
 * \fn int canPlay(int imageIndexP, SDL_Point pointMouse, SDL_Rect ** tableauCase, char *** map3D, char ** pile, int distance)
 * 
 * \brief Fonction qui permet de savoir si on peut jouer un pion, il appelle d'autres fonctions pour vérifier la validiter du coup.\n
 * 
 * Cette fonction est appellée quand on a un pion selectionné et que le joueur utilise le clique de sa souris.
 * 
 * \param[in] int imageIndexP 
 * \param[in] SDL_Point pointMouse : coordonnée de la souris.
 * \param[in] SDL_Rect ** tableauCase : tableau de case contenant les surfaces des cases des piles et des cases du plateau de jeu.
 * \param[in] char *** map3D : plateau de jeu detaillé.
 * \param[in] char ** pile   : pile du joueur.
 * \param[in] int distance : mode de jeu.
 * 
 * \return int : retourne l'indice si valide et sinon -1.
 * 
 * \author DUPOIS Thomas
 */
int canPlay(int imageIndexP, SDL_Point pointMouse, SDL_Rect ** tableauCase, char *** map3D, char ** pile, int distance) {
  int index = getIndex(pointMouse, tableauCase); // recupère la case ou le clique a été fait, -1 si la case n'existe pas

  int x1 = (imageIndexP - imageIndexP % N) / N; int y1 = imageIndexP % N; // coordonnée du pion de départ
  int x2 = (index - index % N) / N;             int y2 = index % N;       // coordonnée du pion d'arriver
  

  if (index == -1 || index > 8) return -1; // pas le droit de poser son pion sur une pile ou sur autre qu'une case
  else {
    if (imageIndexP > 8) { // cas où le pion de départ appartient à la pile 
      int sizePionMax = (imageIndexP == 9 || imageIndexP == 12) ? 2 : (imageIndexP == 10 || imageIndexP == 13) ? 1 : 0 ;  // recupère la taille du pion
      if (canPutPion(map3D, sizePionMax, index)) return index; // si on peut jouer ce pion, on retourne l'indice de la case
      else return -1; // sinon -1
    }
    else { // si le pion de départ appartient au plateau de jeu
      if (canMoove(map3D, imageIndexP, index) && (maximum(abs(x1-x2), abs(y1-y2)) <= 1 || distance == 0)) return index; // on regarde si on peut le jouer et si oui on retourne l'indice
      else return -1;
    }
  }
}

/**
 * \fn int canEffectDeplacementWithDistance(char *** map3D, char c)
 * 
 * \brief Fonction qui permet de savoir si il existe au moins un déplacement valide pour le joueur quand la distance est réduite de 1.
 * 
 * \param[in] char *** map3D : plateau de jeu detaillé.
 * \param[in] char c : identifiant du joueur.
 * 
 * \return int : retourne 1 si possible sinon 0.
 * 
 * \author DUPOIS Thomas
 */
int canEffectDeplacementWithDistance(char *** map3D, char c) {
  int posDeb;
  for (int i = 0; i < N; i++) {
    for(int j = 0;j < N; j++) {
      posDeb = (i * N) + j;
      if (canMooveThisPionDistance(map3D, posDeb, c)) return 1;
    }
  }
  return 0;
}