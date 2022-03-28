/**
 * \file get.c
 * 
 * \brief Fichier contenant les codes des fonctions permettant d'écrire et lire les maps et piles dans des fichiers. On ne les utilise pas.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

/**
 * \fn int getIndex(SDL_Point pointMouse, SDL_Rect ** tableauCase)
 * 
 * \brief Fonction qui regarde si il y a un clique sur une case plateau ou pile.
 * 
 * \param[in] SDL_Point pointMouse : point de la souris où l'utilisateur à cliquer.
 * \param[in] SDL_Rect ** tableauCase : tableau contenant les surfaces des cases.
 * 
 * \return int :retourne l'indice si pion.
 * 
 * \author VILLEPREUX Thibault
 */
int getIndex(SDL_Point pointMouse, SDL_Rect ** tableauCase) {
  for(int i = 0 ; i < (N * N + N*2) ; i++) {
    if(isInRectangle(pointMouse, *tableauCase[i])) return i;
  }
  return -1;
}

/**
 * \fn int sizePionMaxStack(char ** stackArray, int numStack)
 * 
 * \brief Fonction qui regarde la taille maximum d'un pion d'une pile.
 * 
 * \param[in] char ** stackArray : tableau des piles du joueur.
 * \param[in] int numStack : identifiant permettant de connaître la pile du joueur.
 * 
 * \return int :retourne la taille max du pion d'une pile.
 * 
 * \author VILLEPREUX Thibault
 */
int sizePionMaxStack(char ** stackArray, int numStack) {
  int sizePion = 0 ;
  for(int i = N-1 ; i >= 0 ; i--) {
    if (stackArray[numStack][i] != '0') {
      sizePion = i; 
      i = -1;
    }
  }
  return sizePion ;
}

/**
 * \fn int sizePionInStack(char ** stackArray, int numStack)
 * 
 * \brief Fonction qui regarde la taille d'un pion d'une pile.
 * 
 * \param[in] char ** stackArray : tableau des piles du joueur.
 * \param[in] int numStack : identifiant permettant de connaître la pile du joueur.
 * 
 * \return int : retourne -1 si stack est vide sinon 0, 1 ou 2 (taille du pion).
 * 
 * \author VILLEPREUX Thibault
 */
int sizePionInStack(char ** stackArray, int numStack) {
  int sizePion = -1 ;
  for(int i = N-1 ; i >= 0 ; i--) {
    if (stackArray[numStack][i] != '0') {
      sizePion = i; 
      i = -1; // sortie de boucle
    }
  }
  return sizePion ;
}