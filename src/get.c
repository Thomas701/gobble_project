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

/**
 * \fn int getSizePionOnCase(char *** map3D, int i, int j)
 * 
 * \brief Fonction qui renvoie la taille du pion sur la case demandé (-1) si pas de pion
 * 
 * \param[in] char ** map3D : map du jeu
 * \param[in] int i : coordonné x
 * \param[in] int j : coordonné y
 * 
 * \return int : renvoie la taille du pion sur la case demandé (-1) si pas de pion
 * 
 * \author DUPOIS Thomas
 */
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

/**
 * \fn int getSizePionOnCase2(char *** map3D, int index)
 * 
 * \brief Fonction qui renvoie la taille du pion sur la case demandé (-1) si pas de pion
 * 
 * \param[in] char ** map3D : map du jeu
 * \param[in] int index : index de la map
 * 
 * \return int : renvoie la taille du pion sur la case demandé (-1) si pas de pion
 * 
 * \author DUPOIS Thomas
 */
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

/**
 * \fn char getCaractereOnCase(char *** map3D, int index)
 * 
 * \brief Fonction qui renvoie le caractère du pion sur la case demandé ('0') si pas de pion
 * 
 * \param[in] char ** map3D : map du jeu
 * \param[in] int index : index de la map
 * 
 * \return char : renvoie le caractère du pion sur la case demandé ('0') si pas de pion
 * 
 * \author DUPOIS Thomas
 */
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

/**
 * \fn int getIndexPionWhoAreEat(char *** map3D, int index)
 * 
 * \brief Fonction qui renvoie la taille du pion mangé (-1) si aucun pion n'est mangé
 * 
 * \param[in] char ** map3D : map du jeu
 * \param[in] int index : index de la map
 * 
 * \return int : renvoie la taille du pion mangé (-1) si aucun pion n'est mangé
 * 
 * \author DUPOIS Thomas
 */
int getIndexPionWhoAreEat(char *** map3D, int index)
{
  int size = getSizePionOnCase2(map3D, index);
  //printf("SIZE = %d pour index = %d\n", size, index);
  if (size == -1)
    return -1;
  else
  {
    char c = getCaractereOnCase(map3D, index);
    return (c == 'b') ? (N-1) - size : ((N-1) - size) + N;
  }
}

/**
 * \fn int getMaxOnTable(int * tab, int size)
 * 
 * \brief Fonction qui renvoie le nombre maximum dans le tableau
 * 
 * \param[in] char ** map3D : map du jeu
 * \param[in] int size : taille du tableau
 * 
 * \return int : renvoie le nombre maximum dans le tableau
 * 
 * \author DUPOIS Thomas
 */
int getMaxOnTable(int * tab, int size)
{
  int max = tab[0];
  int index = 0;
  for (int i = 0; i < size; i++)
  {
    if (max < tab[i])
    {
      index = i;
      max = tab[i];
    }
  }
  return index;
}