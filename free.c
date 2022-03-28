/**
 * \file free.c
 * 
 * \brief Fichier contenant les codes des fonctions permettant de free de nos structures de données commes les piles, plateaux, tableaux, textures.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

/**
 * \fn void vider_buffer(void) 
 * 
 * \brief Fonction permettant de vider le buffer afin d'éviter les bugs dans les scanf.
 * 
 * \param[in] void : Pas de paramètre.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author DUPOIS Thomas
 */
void vider_buffer(void) {
  int c; 
  do {
    c = getchar();
  } while(c != '\n' && c != EOF);
}

/**
 * \fn void freeTabCase(SDL_Rect ** tableauCase)
 * 
 * \brief Fonction permettant de free le tableau de case (cases = surfaces (x/y et weidth/height) des cases du plateau et des piles en 3*3).
 * 
 * \param[in] SDL_Rect ** tableauCase : le tableau à free.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void freeTabCase(SDL_Rect ** tableauCase) {
  for(int j = 0 ; j < N ; j++)
    free(tableauCase[j]);
  free(tableauCase);
}

/**
 * \fn void freeMap(char *** map)
 * 
 * \brief Fonction permettant de free le plateau de jeu détaillé.
 * 
 * \param[in] char *** map : plateau de jeu à free.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void freeMap(char *** map) {
  if(map) {
    for(int i = 0 ; i < N ; ++i) {
      if(map[i]) {
        for(int j = 0 ; j < N ; ++j) 
          free(map[i][j]);
        free(map[i]);
      }
    }
    free(map);
  }
}

/**
 * \fn void freeMap2D(char ** map2D)
 * 
 * \brief Fonction permettant de free le plateau de jeu non détaillé.
 * 
 * \param[in] char ** map2D : plateau de jeu non detaillé à free.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void freeMap2D(char ** map2D) {
  if(map2D) {
    for(int i = 0; i < N; i++) {
      if (map2D[i] != NULL) {
        free(map2D[i]); 
      }
    }
    free(map2D);
  }
}

/**
 * \fn void freeStack(char ** stackArray)
 * 
 * \brief Fonction permettant de free les piles d'un joueur.
 * 
 * \param[in] har ** stackArray : pile du joueur à free.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void freeStack(char ** stackArray) {
  if(stackArray) {
    for(int i = 0; i < N-1; i++)
      free(stackArray[i]) ;
    free(stackArray) ;
  }
}
/**
 * \fn void freeSDL(SDL_Window * window, SDL_Renderer * renderer, Mix_Music * mainMusic, SDL_Texture ** textureTableauPion, SDL_Texture **  tableauTextureMapVide, SDL_Texture ** textureTableauOptionMenu,SDL_Texture ** textureBackground, point ** tableauDePoint, SDL_Surface * icones, SDL_Rect ** tableauCase)
 * 
 * \brief Fonction permettant de free les textures, misiques, rendu, fenêtre de la SDL.
 * 
 * \param[in] SDL_Window * window : fenêtre principale à free.
 * \param[in] SDL_Renderer * renderer : rendu principal à free.
 * \param[in] Mix_Music * mainMusic : musique principale à free.
 * \param[in] SDL_Texture ** textureTableauPion : tableau de texture de pion à free.
 * \param[in] SDL_Texture **  tableauTextureMapVide : tableau de texture de map vide à free.
 * \param[in] SDL_Texture ** textureTableauOptionMenu : tableau de texture des options du menu principal à free.
 * \param[in] SDL_Texture ** textureBackground : tableau de texture des images de l'animation du menu principal à free.
 * \param[in] point ** tableauDePoint : tableau des points à free.
 * \param[in] SDL_Surface * icones : logo du programme à free.
 * \param[in] SDL_Rect ** tableauCase : tableau des cases à free.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void freeSDL(SDL_Window * window, SDL_Renderer * renderer, Mix_Music * mainMusic, SDL_Texture ** textureTableauPion, SDL_Texture **  tableauTextureMapVide, SDL_Texture ** textureTableauOptionMenu,SDL_Texture ** textureBackground, point ** tableauDePoint, SDL_Surface * icones, SDL_Rect ** tableauCase){
  if(mainMusic) Mix_FreeMusic(mainMusic); // free musique principale

  /************************** FREE TEXTURE **************************/
  if(textureTableauPion) {
    for(int i=0; i<(N*2)*2; ++i) // nombres d'images de pion
      SDL_DestroyTexture(textureTableauPion[i]);
    free(textureTableauPion);
  }
  if(tableauTextureMapVide) {
    for(int i=0; i<3; ++i) // free 3 map : 1 map vert, 1 map rouge quand joueur rouge joue et 1 map bleu quand joueur bleu joue
      SDL_DestroyTexture(tableauTextureMapVide[i]);
    free(tableauTextureMapVide);
  }
  if(textureBackground) {
    for(int i = 0; i < 400; i++)                // nombres d'images de pions généré grace à Blender par DUPOIS Thomas
      SDL_DestroyTexture(textureBackground[i]);
    free(textureBackground);
  }
  if(textureTableauOptionMenu) {
    for(int i = 0; i < 5; i++)                  // nombres options menus
      SDL_DestroyTexture(textureTableauOptionMenu[i]);
    free(textureTableauOptionMenu);
  }
  /************************** END TEXTURE **************************/

  if(tableauDePoint) {
    for(int i=0; i < ((N*N) + (N*2)); ++i)      // nombres d'images de pion
      free(tableauDePoint[i]);
    free(tableauDePoint);
  }
  if(tableauCase) {
    for(int i=0; i < ((N*N) + (N*2)); ++i) // nombres d'images de pion
      free(tableauCase[i]);
    free(tableauCase);
  }
  if (icones) SDL_FreeSurface(icones); //free le logo du logiciel
  if (renderer) SDL_DestroyRenderer(renderer);  // renderer
  if(window) SDL_DestroyWindow(window); // libere la fenetre
}

void freeBaseGame(char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2){
  freeMap(map3D); freeMap2D(map2D); freeStack(pileJ1); freeStack(pileJ2);
}