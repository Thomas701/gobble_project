/**
 * \file creation.c
 * 
 * \brief Fichier contenant les codes des fonctions permettant la créations des piles, plateau, tableau de cases et de coordonées des cases.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */


/**
 * \fn SDL_Rect ** mallocTab()
 * \brief Permet de créer dynamiquement le tableau de case pour l'interface graphique.
 * 
 * \param[in] void : Ne prend aucun paramètre.
 * 
 * \return SDL_RECT ** : Retourne un tableau de case, chaque case est un pointeur vers une surface.
 * 
 * \author VILLEPREUX Thibault
 */
SDL_Rect ** mallocTab(){
  SDL_Rect ** tableauCase = (SDL_Rect **) malloc(sizeof(SDL_Rect *)*((N*N) + (N*2))); // declare le tableau principale
  for(int i = 0 ; i < ((N*N) + (N*2)) ; i++) {
    tableauCase[i] = malloc(sizeof(SDL_Rect *)); // declare à chaque fois un pointeur
    if(!tableauCase[i]) {                        // si NULL alors pas d'allocation de mémoire
      perror("Error allocation memory in createCase for tableauCase[i] \n");
      freeTabCase(tableauCase);  exit(-1);       // free les cases existantes et arrête le programme avec un message d'erreur 
    }
  }
  return tableauCase;
}

/**
 * \fn char ** createStack(char c)
 * \brief Permet de créer dynamiquement les piles de départ d'un joueur avec le caractère c (initialisation + declaration).
 *  
 * \param[in] char c : Caractère que l'on mets dans la pile créer.
 * 
 * \return char ** : Retourne un tableau 2D de char, chaque case est un caractère permettant d'identifier un joueur pendant une partie.
 * \return NULL : **Impossible** car le programme se ferme avant (avec message d'erreur car indispensable pour jouer).
 * 
 * \author VILLEPREUX Thibault
 */
char ** createStack(char c) {
  char ** pile = (char **) malloc(sizeof(char *)*(N-1));   // alloue les piles
  if(!pile)  errorInCreatePile();                          // si erreur appelle fonction erreur qui va envoyer un message + quitter programme

  for(int i = 0; i < N-1; i++) {                           // sinon chaque ligne du tableau va correspondre à une pile
    pile[i] = (char*) malloc(sizeof(char)*N);
    if(!pile[i]) {                                         // si erreur lors de l'allocation on free + on quiite avec fonction (qui va faire message + exit prog)
      for(int l = 0; l < i; l++) { free(pile[l]); pile[l] = NULL; }
      free(pile); pile = NULL; errorInCreatePile() ;
    }
  }

  for (int i = 0; i < N-1; i++) {                         // remplie la pile du caractère du joueur
    for (int j = 0; j < N; j++)
      pile[i][j] = c;
  }
  return pile;
}

/**
 * \fn char *** createMap()
 * \brief Permet de créer dynamiquement **le plateau de jeu détaillé**.
 *  
 * \param[in] void : Ne prend aucun paramètre.
 * 
 * \return char *** : Retourne un tableau 3D de char, chaque case sera un caractère du joueur.
 * \return NULL : **Impossible** car le programme se ferme avant (avec message d'erreur car indispensable pour jouer).
 * 
 * \author VILLEPREUX Thibault
 */
char *** createMap()  {
  char *** map;

  map = (char ***) malloc(sizeof(char **)*N);
  if(!map) errorInCreate3D() ; // map == NULL alors erreur allocation donc appelle fonction (message + exit prog)

  for(int i = 0 ; i < N; i++){
    map[i] = (char **) malloc(sizeof(char *)*N);
    if(!map[i]) {               // si erreur allocation en cours dans la map free proprement + quit prog
      for(int l = 0; l < i; l++) { free(map[l]); map[l] = NULL; }
      free(map); map = NULL;
      errorInCreate3D() ;
    }

    for(int j = 0; j<N; j++) {
      map[i][j] = (char *) malloc(sizeof(char) * N);
      if(!map[i][j]) {   // si erreur allocation en cours dans la map free proprement + quit prog
        for(int m = 0; m < j; m++) { free(map[i][m]); map[i][m] = NULL; }
        for(int n = 0; n < i; n++) { free(map[n]); map[n] = NULL; }
        free(map); map = NULL;
        errorInCreate3D() ;
      }
    }
  }
  return map ; // return la map
}

/**
 * \fn char ** createMap2D()
 * \brief Permet de créer dynamiquement **le plateau de jeu non détaillé**.
 *  
 * \param[in] void : Ne prend aucun paramètre.
 * 
 * \return char ** : Retourne un tableau 2D de char, chaque case sera un caractère du joueur.
 * \return NULL : **Impossible** car le programme se ferme avant (avec message d'erreur car indispensable pour jouer).
 * 
 * \author VILLEPREUX Thibault
 */
char ** createMap2D() {
  char ** map2D = (char **) malloc(sizeof(char *)*N); // alloue le tableau 1D
  if(map2D == NULL) errorInCreate2D();                // appelle fonction qui envoie message + quit prog si NULL (malloc impossible)
  for(int i = 0; i < N; i++) {
    map2D[i] = (char *) malloc(sizeof(char)*N);       // alloue le tab2D
    if(map2D[i] == NULL) {                            // free proprement + appelle fonction qui envoie message + quit prog si NULL (malloc impossible)
      for(int j = 0; j < i; j++) {
        free(map2D[j]); 
        map2D[j] = NULL;
      }
      free(map2D);
      errorInCreate2D();
    }
  }
  return map2D;
}

/**
 * \fn int createPoint(point *** pTableauDePoint)
 * \brief Permet de créer dynamiquement le tableau de point pour l'interface graphique. \n
 * 
 * Chaque case est un pointeur vers un point. Une structure de données créer avant la connaissance de SDL_Point.\n
 * 
 * \param[in] point *** pTableauDePoint : Prend un pointeur vers un tableau de point car va modifier les coordonées de ce dernier.
 * 
 * \return int : Retourne entier pour savoir si tout c'est bien passé. -1 si erreur, 0 sinon
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
int createPoint(point *** pTableauDePoint) {
  point ** tableauDePoint = (point ** ) malloc(sizeof(point *) * 15); // 15 point en 3*3 (8 pour cases jeu + 2*3 pour pile joueur)
  if(!tableauDePoint) { perror("Error allocation memory in createPoint for tableauDePoint\n"); return -1;} // si erreur malloc affiche erreur + return -1 pour signaler erreur
  for(int i = 0 ; i < 15 ; ++i) { // on a 15 point en 3*3
    tableauDePoint[i] = malloc(sizeof(point) * 1);
    if(!tableauDePoint[i]) {      // si erreur on free proprement + affiche erreur + return -1
      perror("Error allocation memory in createPoint for tableauDePoint[i] \n");
      for(int j = 0 ; j < i ; ++j)
        free(tableauDePoint[j]);
      free(tableauDePoint);
      return -1;
    }
  } // création en dur, problème de génération des cases sur blender pas "droites, de même taille alors que même profondeur" donc pas de formules pour les trouver.
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
  * pTableauDePoint = tableauDePoint; // associe la nouveau tableau au pointeur passé en paramètre
  return 0; // si arrivé ici tout c'est bien passé
}


/**
 * \fn int createCase(SDL_Rect *** pTableauCase)
 * \brief Permet de créer dynamiquement le tableau de case pour l'interface graphique. \n
 * 
 * Chaque case du tableau est un pointeur vers un case de la map.\n
 * 
 * \param[in] SDL_Rect *** pTableauCase : Prend un pointeur vers un tableau de case car va modifier les coordonées de ce dernier.
 * 
 * \return int : Retourne entier pour savoir si tout c'est bien passé. -1 si erreur, 0 sinon
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
int createCase(SDL_Rect *** pTableauCase) {
  SDL_Rect ** tableauCase = (SDL_Rect **) malloc(sizeof(SDL_Rect *)*((N*N) + (N*2))); // malloc pour créer cas plateau
  if(!tableauCase) { // erreur malloc envoie message + return -1
    perror("Error allocation memory in createCase for tableauCase\n"); return -1 ;
  }
  for(int i = 0 ; i < ((N*N) + (N*2)) ; i++) {
    tableauCase[i] = malloc(sizeof(SDL_Rect));
    if(!tableauCase[i]) { // erreur malloc free + envoie message + return -1
      perror("Error allocation memory in createCase for tableauCase[i]\n");
      for(int j = 0 ; j < i ; ++j)
        free(tableauCase[j]);
      free(tableauCase);
      return -1;
    }
  }
  tableauCase[ 0]->w = 152 ; tableauCase[ 0]->h = 89  ;
  tableauCase[ 0]->x = 419 ; tableauCase[ 0]->y = 359 ;
  tableauCase[ 1]->w = 141 ; tableauCase[ 1]->h = 89  ;
  tableauCase[ 1]->x = 585 ; tableauCase[ 1]->y = 358 ;
  tableauCase[ 2]->w = 134 ; tableauCase[ 2]->h = 89  ;
  tableauCase[ 2]->x = 738 ; tableauCase[ 2]->y = 358 ;
  tableauCase[ 3]->w = 171 ; tableauCase[ 3]->h = 106 ;
  tableauCase[ 3]->x = 392 ; tableauCase[ 3]->y = 462 ;
  tableauCase[ 4]->w = 159 ; tableauCase[ 4]->h = 108 ;
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
  tableauCase[ 14]->x = 1050; tableauCase[ 14]->y = 579 ;
  * pTableauCase = tableauCase;
  return 0;
}

