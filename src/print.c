/**
 * \file print.c
 * 
 * \brief Fichier contenant les codes des fonctions permettant d'afficher dans le terminal le plateau et les piles.
 * 
 * \author VILLEPREUX Thibault
 */

/**
 * \fn void printMap3dDebug(char *** map)
 * 
 * \brief Fonction qui affiche dans le terminal le plateau de jeu détaillé.
 * 
 * \param[in] char *** map : plateau de jeu détaillé à afficher.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void printMap3dDebug(char *** map) {
  for(int i = 0 ; i < N ; ++i) {
    for(int j = 0 ; j < N ; ++j) {
      printf("[%d][ ", j+i*N);
      for(int k = 0; k < N; ++k)
        printf("'%c' ", map[i][j][k]);
      printf("]    ");
    }
    printf("\n\n");
  }
  printf("\n");
}

/**
 * \fn void printMap2D(char ** map2D)
 * 
 * \brief Fonction qui affiche dans le terminal le plateau de jeu non détaillé.
 * 
 * \param[in] char ** map2D : plateau de jeu non détaillé à afficher.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void printMap2D(char ** map2D) {
  for(int i=0; i<N; ++i) {
    for(int j=0; j<N; ++j)
       printf("%c ", map2D[i][j]);
    printf("\n");
  }
  printf("\n");
}

/**
 * \fn void printStacks(char ** stacksArray)
 * 
 * \brief Fonction qui affiche dans le terminal les piles du joueur.
 * 
 * \param[in] char ** map2D : piles du joueur à afficher.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void printStacks(char ** stacksArray) {
  for(int i = 0; i < N-1 ; i++) {
    printf("pile numéro %d : |", i);
    for(int j=0; j < N ; j++)
      printf(" %c |", stacksArray[i][j]);
    printf("\n");
  }
}

/**
 * \fn void printIAParametre(int ** tab)
 * 
 * \brief Fonction qui affiche dans le terminal le tableau de paramètre de l'IA
 * 
 * \param[in] int ** tab : tableau de paramètre
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author DUPOIS Thomas
 */
void printIAParametre(int ** tab) 
{
  for(int i = 0; i < 10; i++) {
    for(int j = 0; j < 10; j++)
       printf("%d ", tab[i][j]);
    printf("\n");
  }
  printf("\n");
}

/**
 * \fn void printIAResult(int * tab, int nbreIA) 
 * 
 * \brief Fonction qui affiche les resultats des IA
 * 
 * \param[in] int ** tab : tableau de resultat d'ia
 * \param[in] int nbreIA : Le nombre d'IA
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author DUPOIS Thomas
 */
void printIAResult(int * tab, int nbreIA) 
{
  for(int i = 0; i < nbreIA; i++)
    printf("%d ", tab[i]);
  printf("\n");
}