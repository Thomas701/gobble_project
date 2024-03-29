/**
 * \file graphique.c
 * 
 * \brief Fichier contenant les codes des fonctions graphiques. Elles gèrent le chargement des images (initialisations) et leurs affichagent.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */



/**
 * \fn SDL_Texture * loadImage(const char * path, SDL_Renderer *renderer)
 * \brief Fonction qui va permmetre de transformer une image (n'importe quel format valide) en texture.
 *  
 * \param[in] const char * path : prend le chemin de l'image à charger.
 * \param[in] SDL_Renderer *renderer : associe la texture créer à un renderer.
 * 
 * \return SDL_Texture * : Retourne un pointeur vers la texture à manipuler.
 * \return NULL : Si chemin d'accès invalide ou erreur allocation texture à cause de SDL_CreateTextureFromSurface (message d'erreur qui prévient)
 * 
 * \author VILLEPREUX Thibault
 */
SDL_Texture * loadImage(const char * path, SDL_Renderer *renderer) {
  SDL_Surface *tmp = NULL; SDL_Texture *texture = NULL;
  tmp = IMG_Load(path); // chargement de l'image 

  if(!tmp){ // probleme chargement image donc affiche message d'erreur + return NULL
    fprintf(stderr, "Erreur SDL_Load : %s\n", SDL_GetError());
    return NULL;
  }

  texture = SDL_CreateTextureFromSurface(renderer, tmp); // si pas d'erreur on créer la texture
  SDL_FreeSurface(tmp); // on libère la mémoire de l'image

  if(!texture){ // probleme transfo image en texture , message + return NULL
    fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s\n", SDL_GetError());
    return NULL;
  }
  return texture; // tout c'est bien passé !
}

/**
 * \fn void intro_authors(SDL_Renderer ** renderer)
 * \brief Fonction lance l'animation de début avec le nom des participants et le logo ISIMA avec fondu transparent.
 *  
 * \param[in] SDL_Renderer ** renderer : Rendu ou l'on colle l'image d'animation.
 * 
 * \return void : Pas de valeur de retour.
 * 
 * \author VILLEPREUX Thibault
 */
void intro_authors(SDL_Renderer ** renderer) {
  SDL_Texture * texture_authors = NULL; // contient la texture qui va acceuilir l'image authors [texture]
  Mix_Music * music_intro = NULL;      // [musique] 
  texture_authors = loadImage("Frames/authors1.png", *renderer); // chargement de l'image
  if(!texture_authors) { // si probleme de chargement on affiche message + quitte fonction, pas programme car ce n'est pas grave
    fprintf(stderr, "Erreur loadImage : %s\n", SDL_GetError());
    perror("Impossible d'afficher la texture = NULL"); return; 
  }
  // boucle sur i pour gérer la transparence
  for (int i = 0 ; i < 130 ; ++i ) {//boucle pour rendre l'image d'intro transparente
    SDL_RenderClear(*renderer);
    if(0 != SDL_SetTextureAlphaMod(texture_authors, i)) fprintf(stderr, "Erreur SDL_SetTextureAlphaMod: %s\n", SDL_GetError()); // probleme transparence
    else { // affiche l'image
      SDL_RenderCopy(*renderer, texture_authors, NULL, NULL);
      SDL_RenderPresent(*renderer);
      SDL_Delay(15);
    }
  }
  
  // lance la musique
  music_intro = Mix_LoadMUS("Music/intro.wav"); // alloue la musique de l'intro
  if (!music_intro) SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s\n", Mix_GetError()); // probleme chargement musique affiche image
  else {
    Mix_VolumeMusic(MIX_MAX_VOLUME/6); // baisse volume musique
    Mix_PlayMusic(music_intro, 0);      // joue une seule fois
  }

  // renlance l'animation
  for (int i = 130 ; i < 255 ; ++i ) { 
    SDL_RenderClear(*renderer);
    if(0 != SDL_SetTextureAlphaMod(texture_authors, i)) fprintf(stderr, "Erreur SDL_SetTextureAlphaMod : %s\n", SDL_GetError());

    else { // affiche image
      SDL_RenderCopy(*renderer, texture_authors, NULL, NULL);
      SDL_RenderPresent(*renderer);
      SDL_Delay(15);
    }
  }
  for (int i = 255 ; i >= 0 ; --i) { // transparence augmente pour créer fondu
    SDL_RenderClear(*renderer);  // effacer image précédente
    if(0 != SDL_SetTextureAlphaMod(texture_authors, i)) fprintf(stderr, "Erreur SDL_SetTextureAlphaMod : %s\n", SDL_GetError());
    else { // colle l'image
    SDL_RenderCopy(*renderer, texture_authors, NULL, NULL);
    SDL_RenderPresent(*renderer);
    SDL_Delay(15);
    }
  }
  SDL_RenderClear(*renderer); // nettoie le rendu
  if (texture_authors) SDL_DestroyTexture(texture_authors); // liberation texture car plus besoin
  if (music_intro) Mix_FreeMusic(music_intro); // libération de la musique, plus besoin
}


/**
 * \fn void lancementMenu(SDL_Renderer * renderer, SDL_Texture ** textureBackground, SDL_Texture ** textureTableauOptionMenu, int * p_etats, int boolPlayMusic, int * ia)
 * \brief Fonction qui gère lorsque le joueur se trouve dans le menu principale.\n
 * 
 * Il peut lancer une partie 1VS1, 1VSIA, quitter le jeu (autre que par la croix rouge) ou couper et rejouer le son.
 *  
 * \param[in] SDL_Renderer ** renderer : rendu ou l'on colle les images.
 * \param[in] SDL_Texture ** textureBackground : Tableau de texture d'images qui va contenir les 400 images d'animations.
 * \param[in] SDL_Texture ** textureTableauOptionMenu :  Tableau de texture des images des options menu (1VS1, 1VSIA, SOUN , QUIT GAME)
 * \param[in] int * p_etats : pointeur permettant de connaître l'état du programme (en game, en pause)
 * \param[in] int boolPlayMusic : permet de savoir si on joue de la musique ou pas.
 * \param[in] int * ia : pointeur sur l'ia (permet de définir s'il y'aura une ia ou pas)
 * 
 * \return void : Pas de valeur de retour.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
void lancementMenu(SDL_Renderer * renderer, SDL_Texture ** textureBackground, SDL_Texture ** textureTableauOptionMenu, int * p_etats, int boolPlayMusic, int * ia){
  SDL_RenderClear(renderer);
  SDL_Rect tableauRectOption[9]; //boutons du menu

  for(int i = 0; i < 3; i++) { // initialise les coord des options du menu
    SDL_QueryTexture(textureTableauOptionMenu[i], NULL, NULL, &tableauRectOption[i].w, &tableauRectOption[i].h);
    tableauRectOption[i].x = WIDTH /2 - tableauRectOption[i].w / 2;
  }
  for(int i = 4; i < 9; i++) { // initialise les coord des options du menu
    SDL_QueryTexture(textureTableauOptionMenu[i+3], NULL, NULL, &tableauRectOption[i].w, &tableauRectOption[i].h);
    tableauRectOption[i].x = WIDTH /2 - tableauRectOption[i].w / 2; 
  }
  // cas particulier pour l'image du sond, ne dépend pas des 3 centraux donc pas alignés avec eux
  SDL_QueryTexture(textureTableauOptionMenu[3], NULL, NULL, &tableauRectOption[3].w, &tableauRectOption[3].h);
  //tableauRectOption[3].x = WIDTH /2 - tableauRectOption[3].w / 2; 

  tableauRectOption[0].y = 318; tableauRectOption[1].y  = 488; tableauRectOption[2].y = 650;  // jouer 1 vs 1, jouer 1 vs ia, quitter
  tableauRectOption[4].y = 318; tableauRectOption[5].y  = 488; tableauRectOption[6].y = 318; tableauRectOption[7].y = 488; // min-max, alpha beta, i start, ia start
  tableauRectOption[8].y = 148; // IA training
  tableauRectOption[3].x = WIDTH - tableauRectOption[3].w;     tableauRectOption[3].y = 0;    // bouton de sond

  SDL_Point pointMouse; //souris du menu pour evenement
  int incrImg = 0; // numero image menu (background)
  int menu = 0; // correspond à l'étape du menu ([0]ia -> [1]min-max -> [2]qui commence?)
  while(*p_etats == 1) { // boucle principale
    SDL_Event event; SDL_RenderClear(renderer);
    SDL_GetMouseState(&pointMouse.x, &pointMouse.y); // recupere coord souris

    // charge la prochaine image de background, animation
    if (0 != SDL_RenderCopy(renderer, textureBackground[incrImg%400], NULL, NULL)) {fprintf(stderr, "Error SDL_RenderCopy for textureBackground : %s, i = %d, et img = %p \n", SDL_GetError(), incrImg%400 , textureBackground[incrImg%400]);}
    if (menu == 0)
    {
      for(int i=0; i < 2; ++i) 
      { // affiche les option menu centraux en trasparent si souris dessus
        if(isInRectangle(pointMouse, tableauRectOption[i])) {
          SDL_SetTextureAlphaMod(textureTableauOptionMenu[i], 255);
          if (0 != SDL_RenderCopy( renderer,  textureTableauOptionMenu[i], NULL, &tableauRectOption[i])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
        }
        else { // affiche les option menu centraux en non trasparent si souris pas dessus
          SDL_SetTextureAlphaMod(textureTableauOptionMenu[i], 150);
          if (0 != SDL_RenderCopy( renderer,  textureTableauOptionMenu[i], NULL, &tableauRectOption[i])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
        }
      }
    }
    /* BOUTON QUITTER */
    if(isInRectangle(pointMouse, tableauRectOption[2])) {
      SDL_SetTextureAlphaMod(textureTableauOptionMenu[2], 255);
      if (0 != SDL_RenderCopy( renderer,  textureTableauOptionMenu[2], NULL, &tableauRectOption[2])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
    }
    else { // affiche les option menu centraux en non trasparent si souris pas dessus
      SDL_SetTextureAlphaMod(textureTableauOptionMenu[2], 150);
      if (0 != SDL_RenderCopy( renderer,  textureTableauOptionMenu[2], NULL, &tableauRectOption[2])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
    }
    if (menu == 1)
    {
      for(int i = 4; i < 6; i++) 
      { // affiche les option menu centraux en trasparent si souris dessus
        if(isInRectangle(pointMouse, tableauRectOption[i])) {
          SDL_SetTextureAlphaMod(textureTableauOptionMenu[i+3], 255);
          if (0 != SDL_RenderCopy( renderer,  textureTableauOptionMenu[i+3], NULL, &tableauRectOption[i])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
        }
        else { // affiche les option menu centraux en non trasparent si souris pas dessus
          SDL_SetTextureAlphaMod(textureTableauOptionMenu[i+3], 150);
          if (0 != SDL_RenderCopy( renderer,  textureTableauOptionMenu[i+3], NULL, &tableauRectOption[i])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
        }
      }     
      if(isInRectangle(pointMouse, tableauRectOption[8])) {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[11], 255);
        if (0 != SDL_RenderCopy( renderer,  textureTableauOptionMenu[11], NULL, &tableauRectOption[8])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
      else { // affiche les option menu centraux en non trasparent si souris pas dessus
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[11], 150);
        if (0 != SDL_RenderCopy( renderer,  textureTableauOptionMenu[11], NULL, &tableauRectOption[8])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
    }
    if (menu == 2)
    {
      for(int i = 6; i < 8; i++) 
      { // affiche les option menu centraux en trasparent si souris dessus
        if(isInRectangle(pointMouse, tableauRectOption[i])) {
          SDL_SetTextureAlphaMod(textureTableauOptionMenu[i+3], 255);
          if (0 != SDL_RenderCopy( renderer,  textureTableauOptionMenu[i+3], NULL, &tableauRectOption[i])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
        }
        else { // affiche les option menu centraux en non trasparent si souris pas dessus
          SDL_SetTextureAlphaMod(textureTableauOptionMenu[i+3], 150);
          if (0 != SDL_RenderCopy( renderer,  textureTableauOptionMenu[i+3], NULL, &tableauRectOption[i])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
        }
      }
    }
    if(isInRectangle(pointMouse, tableauRectOption[3])) { // gere le cas de l'affichage bouton sond (transparence)
      if(boolPlayMusic) {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[3], 255);
        if (0 != SDL_RenderCopy(renderer,  textureTableauOptionMenu[3], NULL, &tableauRectOption[3])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
      else {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[4], 255);
        if (0 != SDL_RenderCopy(renderer,  textureTableauOptionMenu[4], NULL, &tableauRectOption[3])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
    }
    else {
      if(boolPlayMusic) {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[3], 100);
        if (0 != SDL_RenderCopy(renderer,  textureTableauOptionMenu[3], NULL, &tableauRectOption[3])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
      else {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[4], 100);
        if (0 != SDL_RenderCopy(renderer,  textureTableauOptionMenu[4], NULL, &tableauRectOption[3])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
    }
    incrImg++;
    SDL_RenderPresent(renderer);
    SDL_Delay(50);

    // programme qui gère les cliques (déclenches les évenements)
    while(SDL_PollEvent(&event)) { // programme continue et un nouveau evenement dans la file
      SDL_GetMouseState(&pointMouse.x, &pointMouse.y); // recupere coord souris
      switch(event.type) {
        case SDL_QUIT : //quitter
          *p_etats = 0;
          break ;

        case SDL_MOUSEBUTTONDOWN :  // bouton souris enfonce
          if (event.button.button == SDL_BUTTON_LEFT) { // bouton souris gauche
            if (isInRectangle(pointMouse , tableauRectOption[0])) {// 2 joueurs en local
              if (menu == 0)
              {
                printf("Pas d'ia");
                *ia = 0;
                *p_etats = 2 ;
              }
              if (menu == 1)
              {
                printf("ia = 1");
                *ia = 1;
              }
              if (menu == 2)
              {
                *p_etats = 2;
              } 
              menu = (menu == 0) ? 1 : 2;
              SDL_RenderClear(renderer);
            }
            else if(isInRectangle(pointMouse , tableauRectOption[8])) {
              if(menu == 1)
              {
                *p_etats = 4;
              }
            }
            else if(isInRectangle(pointMouse , tableauRectOption[1])) {// IA min max
              if (menu == 1)
              {
                printf("ia = 3");
                *ia = 3;
              }
              if (menu == 2)
              {
                if (*ia == 3)
                {
                  printf("ia = 4");
                  *ia = 4;
                }
                else if (*ia == 1)
                {
                  printf("ia = 2");
                  *ia = 2; 
                }
                *p_etats = 2 ;
              }
              menu = (menu == 0) ? 1 : 2;
              SDL_RenderClear(renderer);
              printf("Lancement jeu contre IA \n");
            }
            else if(isInRectangle(pointMouse , tableauRectOption[3])) { // sond
              if(boolPlayMusic == 0) {
                boolPlayMusic = 1; 
                Mix_ResumeMusic();
              }
              else  {
                boolPlayMusic = 0; 
                Mix_PauseMusic();
              }
            }
            else if(isInRectangle(pointMouse , tableauRectOption[2])) { // choix QUITTER
              if (menu == 0)
                *p_etats = 0;
              menu = (menu == 2) ? 1 : 0;
            }
          }
          break ;
        default :
          break ;
      } 
    }
  }
}

/**
 * \fn void lancementJeu1VS1(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint, SDL_Texture ** textureTableauWin, int * p_etatS, SDL_Rect ** tableauCase,  SDL_Texture ** textureTableauPion , char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, int distance, char * c, int * ia)
 * \brief Fonction qui lance la partie Homme VS Homme.
 * 
 * Elle appelle gameOptionGraphique qui joue la partie et ensuite elle affiche le vainquer et réinitialise plateau et pile pour prochaine partie.
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
 * \author VILLEPREUX Thibault
 */
void lancementJeu1VS1(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint, SDL_Texture ** textureTableauWin, int * p_etatS, SDL_Rect ** tableauCase,  SDL_Texture ** textureTableauPion , char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, int distance, char * c, int * ia)
{
  // fonction qui lance partie et quitte quand partie finie
  gameOptionGraphique(renderer, tableauTextureMapVide, tableauDePoint, tableauCase, pileJ1, pileJ2, map3D, map2D, p_etatS, textureTableauPion, distance, c, ia);
  
  if(count_pion(map2D, N, 'b') && count_pion(map2D, N, 'n'))
  {
    printf("EGALITE");
    *c = 'b';
  }
  else if (count_pion(map2D, N, 'b'))
  {
    printf("Le joueur 1 a gagne!\n");
    *c = 'b';
  }
  else if (count_pion(map2D, N, 'n'))
  {
    printf("Le joueur 2 a gagne!\n");
    *c = 'b';
  }
  else
    printf("La partie a été interrompu\n");

  // affichage vainqueur
  SDL_RenderClear(renderer);
  if (check_End_Game(map2D) != 0)
    printMapEmptySDL(textureTableauWin[check_End_Game(map2D)-1], renderer);
  else
    return ;
  printMapEmptySDL(textureTableauWin[check_End_Game(map2D)-1], renderer);
  affichePileSDL(renderer, textureTableauPion, tableauDePoint, pileJ1, pileJ2);
  affichePionSurPlateau(renderer, textureTableauPion, tableauDePoint, map3D, -1);
  SDL_RenderPresent(renderer);
  SDL_Delay(2000);

  // réinitialise pile et plateau pour prochaine game
  initMap(map3D);       initMap2D(map2D, map3D);
  initPile(pileJ1,'b'); initPile(pileJ2,'n');
}



/**
 * \fn int affichePileSDL(SDL_Renderer * renderer, SDL_Texture ** textureTableauPion, point ** tableauDePoint,char ** stackArrayJ1, char ** stackArrayJ2)
 * \brief Fonction qui affiche les piles des joueurs en interface graphique.
 * 
 * \param[in] SDL_Renderer ** renderer : rendu ou l'on colle les images.
 * \param[in] SDL_Texture ** textureTableauPion : tableau de texture, contient les images des pions sélectionnés et non selectionnés.
 * \param[in] point ** tableauDePoint :  tableau de point pour gérer l'affichage des pions.
 * \param[in] char ** stackArrayJ1 : contient la pile du joueur 1.
 * \param[in] char ** stackArrayJ2 : contient la pile du joueur 2.
 *
 * \return int : Retourne 0 si succès et sinon -1.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
int affichePileSDL(SDL_Renderer * renderer, SDL_Texture ** textureTableauPion, point ** tableauDePoint,char ** stackArrayJ1, char ** stackArrayJ2) {
  SDL_Rect positionPionCurrent;
  int * arrayCountPionInStack = (int *) calloc(N*2, sizeof(int));  // tableau temporaire qui permet d'enregistrer si il y a des pions sur les  piles
  if(!arrayCountPionInStack) {
    fprintf(stderr,"Error in affichePileSDL for arrayCountPionInStack\n");
    return -1;
  }
  for (int i = 0; i < N-1; i++) { // compte le nombre de pion dans chaque pile
    for (int j = 0; j < N; j++) {
        if (j == 0 && stackArrayJ1[i][j] == 'b') {arrayCountPionInStack[2] ++;}
        if (j == 0 && stackArrayJ2[i][j] == 'n') {arrayCountPionInStack[5] ++;}
        if (j == 1 && stackArrayJ1[i][j] == 'b') {arrayCountPionInStack[1] ++;}
        if (j == 1 && stackArrayJ2[i][j] == 'n') {arrayCountPionInStack[4] ++;}
        if (j == 2 && stackArrayJ1[i][j] == 'b') {arrayCountPionInStack[0] ++;}
        if (j == 2 && stackArrayJ2[i][j] == 'n') {arrayCountPionInStack[3] ++;}
    }
  }
  for(int i=0; i<N*2; i++) { // parcours le tableau où l'on a compté les pions et si > 0 alors il y a un pion à afficher
    if(arrayCountPionInStack[i] > 0 ) {  // interroge texture pour avoir la dimmension 
      if (0 != SDL_QueryTexture(textureTableauPion[i], NULL, NULL, &positionPionCurrent.w, &positionPionCurrent.h)) {
         fprintf(stderr, "Error SDL_QueryTexture in affichePileSDL : %s \n", SDL_GetError());
         free(arrayCountPionInStack);
         return -1;
      }
      if(0 == i%3)      { positionPionCurrent.w *= Z3; positionPionCurrent.h *= Z3; } // dezoom car derniere ligne
      else if(1 == i%3) { positionPionCurrent.w *= Z2; positionPionCurrent.h *= Z2; } // dezoom car ligne 2/3
      
      positionPionCurrent.x =  tableauDePoint[i+9]->x - positionPionCurrent.w/2;
      
      if(i%3 != 0) positionPionCurrent.y =  tableauDePoint[i+9]->y - 2*positionPionCurrent.h/3; // ce n'est pas un gros pion
      else positionPionCurrent.y =  tableauDePoint[i+9]->y - 4.5*positionPionCurrent.h/6;       // c'est un gros pion
      
      if (0 !=  SDL_RenderCopy(renderer, textureTableauPion[i], NULL, &positionPionCurrent)) { // colle l'image
        fprintf(stderr, "Error SDL_RenderCopy in affichePionSurPlateau 2 : %s \n", SDL_GetError());
        free(arrayCountPionInStack);
        return -1;
      }
    } 
  }
  free(arrayCountPionInStack); return 0;
}

/**
 * \fn int affichePionSurPlateau(SDL_Renderer * renderer, SDL_Texture ** textureTableauPion, point ** tableauDePoint ,char ***  map3D)
 * \brief Fonction qui affiche les pions sur la map en interface graphique.
 * 
 * \param[in] SDL_Renderer ** renderer : rendu ou l'on colle les images.
 * \param[in] SDL_Texture ** textureTableauPion : tableau de texture, contient les images des pions sélectionnés et non selectionnés.
 * \param[in] point ** tableauDePoint :  tableau de point pour gérer l'affichage des pions.
 * \param[in] char *** map3D : map detaillé du plateau de jeu.
 *
 * \return int : Retourne 0 si succès et sinon -1.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
int affichePionSurPlateau(SDL_Renderer * renderer, SDL_Texture ** textureTableauPion, point ** tableauDePoint ,char ***  map3D, int index) {
  SDL_Rect positionPionCurrent ;
  int x = (index - index % N) / N;
  int y = index % N;
  int indicePion;          // contient l'indice du pion à placer
  int posCase ;            // position en terme de case (i%3 + j)
  for (int i = 0  ; i < N ; ++i) {
    for(int j = 0 ; j < N ; j++) {
      for(int k=N-1; k >=0; --k) {
        if (index != -1 && x == i && y == j)
          continue;
        if('0' != map3D[i][j][k]) { // si on a trouver un pion sur le plateau
          switch(map3D[i][j][k])  { // on regarde a qui il appartient
            case 'b' : indicePion = N-1 - k ; break;
            case 'n' : indicePion = 3 + N-1 - k; break;
            default : printf("error in affichePionSurPlateau switch map3D[i][j][k] : %c\n", map3D[i][j][k]); break;
          }
          if (0 != SDL_QueryTexture(textureTableauPion[indicePion], NULL, NULL, &positionPionCurrent.w, &positionPionCurrent.h)) { // on récupère sa dimmension
            fprintf(stderr, "Error SDL_QueryTexture in affichePionSurPlateau 1 : %s \n", SDL_GetError());
            return -1;
          }
          if(0 == i) { // case du fond dézoom
            positionPionCurrent.w *= Z3; positionPionCurrent.h *= Z3;
          }
          else if(1 == i) {  // case milieu dézoom
            positionPionCurrent.w *= Z2; positionPionCurrent.h *= Z2;
          }
          posCase = (i * N) + j;
          
          positionPionCurrent.x =  tableauDePoint[posCase]->x - positionPionCurrent.w/2; // on centre si pion petit ou moyen
          
          if(k == N-1) positionPionCurrent.y =  tableauDePoint[posCase]->y - 2*positionPionCurrent.h/3; // si gros on ne centre pas
          else         positionPionCurrent.y =  tableauDePoint[posCase]->y - 4.5*positionPionCurrent.h/6;
          if (0 !=  SDL_RenderCopy(renderer, textureTableauPion[indicePion], NULL, &positionPionCurrent) ){ // on le colle sur le renerer
            fprintf(stderr, "Error SDL_RenderCopy in affichePionSurPlateau 2 : %s \n", SDL_GetError()); return -1;
          }
          k = -1; // pour sortir de la boucle car pas la peine d'afficher les pions en dessous
        }
      }
    }
  }
  return 0;
}

/**
 * \fn int affichePionSelect(SDL_Renderer * renderer, point ** tableauDePoint, SDL_Texture ** textureTableauPion, char *** map3D,int index)
 * \brief Fonction qui affiche le pion sélectionné sur la map en interface graphique.
 * 
 * \param[in] SDL_Renderer ** renderer : rendu ou l'on colle les images.
 * \param[in] point ** tableauDePoint :  tableau de point pour gérer l'affichage des pions.
 * \param[in] SDL_Texture ** textureTableauPion : tableau de texture, contient les images des pions sélectionnés et non selectionnés.
 * \param[in] char *** map3D : map detaillé du plateau de jeu.
 * \param[in] int index : contient l'identifiant de la case du pion qui a été selectionné.
 * 
 * \return int : Retourne 0 si succès et sinon -1.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
int affichePionSelect(SDL_Renderer * renderer, point ** tableauDePoint, SDL_Texture ** textureTableauPion, char *** map3D,int index) {
  SDL_Rect positionPionCurrent;
  if (index > 8) { // cas si pion sélectionné est un pion de la pile
    if (0 != SDL_QueryTexture(textureTableauPion[index-3], NULL, NULL, &positionPionCurrent.w, &positionPionCurrent.h)) { // index-2 car par exemple l'index = 10 necessite de charger la texture 8 du tableau
      fprintf(stderr, "Error SDL_QueryTexture in affichePionSelect 1 : %s \n", SDL_GetError());
      return -1;
    }
    if(0 == index%3)      { positionPionCurrent.w *= Z3; positionPionCurrent.h *= Z3; } // dezoom car derniere ligne
    else if(1 == index%3) { positionPionCurrent.w *= Z2; positionPionCurrent.h *= Z2; } // dezoom car ligne 2/3
    positionPionCurrent.x =  tableauDePoint[index]->x - positionPionCurrent.w/2;
    if(index%3 != 0)  positionPionCurrent.y =  tableauDePoint[index]->y - 2*positionPionCurrent.h/3; // pas un gros pion
    else positionPionCurrent.y =  tableauDePoint[index]->y - 4.5*positionPionCurrent.h/6;
    
    if (0 !=  SDL_RenderCopy(renderer, textureTableauPion[index-3], NULL, &positionPionCurrent)) { // on colle l'image du pion sur le rendu
      fprintf(stderr, "Error SDL_RenderCopy in affichePionSelect 2: %s \n", SDL_GetError());
      return -1;
    }
    return 0;
  }
  else { // sinon si pion selectionné es tun pion du plateau
    int i = (index - index % N) / N; int j = index % N;
    int indicePion;          // contient l'indice du pion à placer
    for(int k=N-1; k >=0; --k)  {
      if('0' != map3D[i][j][k])  {
        switch(map3D[i][j][k])  {
          case 'b' : indicePion = (N-1 - k) + (N*2) ; break;
          case 'n' : indicePion = (3 + N-1 - k) + (N*2); break;
          default : printf("error in affichePionSelect switch map3D[%d][%d][%d] : %c\n", i, j, k, map3D[i][j][k]); break;
        }
        if (0 != SDL_QueryTexture(textureTableauPion[indicePion], NULL, NULL, &positionPionCurrent.w, &positionPionCurrent.h)) {
          fprintf(stderr, "Error SDL_QueryTexture in affichePionSelect 3: %s \n", SDL_GetError());
          return -1;
        }
        if(0 == i) { // case du fond zoom
          positionPionCurrent.w *= Z3; positionPionCurrent.h *= Z3;
        }
        else if(1 == i) {  // case milieu zoom
          positionPionCurrent.w *= Z2; positionPionCurrent.h *= Z2;
        }
        positionPionCurrent.x =  tableauDePoint[index]->x - positionPionCurrent.w/2;  // on centre si pion petit ou moyen
        if(k == N-1) positionPionCurrent.y =  tableauDePoint[index]->y - 2*positionPionCurrent.h/3; // si gros on ne centre pas
        else positionPionCurrent.y =  tableauDePoint[index]->y - 4.5*positionPionCurrent.h/6;
        if (0 !=  SDL_RenderCopy(renderer, textureTableauPion[indicePion], NULL, &positionPionCurrent) ){ // on colle l'image du pion sur le rendu
          fprintf(stderr, "Error SDL_RenderCopy in affichePionSurPlateau 4 : %s \n", SDL_GetError());
          return -1;
        }
        k = -1; // pour sortir de la boucle
      }
    }
    return 0;
  }
}

/**
 * \fn int printMapEmptySDL(SDL_Texture * textureMapVide, SDL_Renderer * renderer)
 * 
 * \brief Fonction qui affiche en interface graphique la map sans pion.
 * 
 * \param[in] SDL_Texture * textureMapVide : map graphique à afficher.
 * \param[in] SDL_Renderer * renderer : rendu ou l'on mets l'image que l'on charge.
 * 
 * \return int : retourne 0 si succès sinon -1.
 * 
 * \author VILLEPREUX Thibault
 */
int printMapEmptySDL(SDL_Texture * textureMapVide, SDL_Renderer * renderer) {
  if (0 !=  SDL_RenderCopy(renderer, textureMapVide, NULL, NULL))  { 
      fprintf(stderr, "Error SDL_RenderCopy in printMapEmptySDL : %s \n", SDL_GetError());
      return -1; 
    }
  return 0;
}

int transition(SDL_Renderer * renderer,  SDL_Texture ** textureTableauPiont, point ** tableauDePoint, char *** map3D, int dep, int end, SDL_Texture ** tableauTextureMapVide, char c, char ** pileJ1, char ** pileJ2, int indicePionWhoEat)
{
  SDL_Rect positionPiontCurrent;
  int x1 =  tableauDePoint[dep]->x; int y1 = tableauDePoint[dep]->y;
  int x2 =  tableauDePoint[end]->x; int y2 = tableauDePoint[end]->y;
  int xDelta = (int) ((x2 - x1) / 20);
  int yDelta = (int) ((y2 - y1) / 20);
  int i = (end - end % N) / N;
  int j = end % N;
  printf("i=%d car %d et j=%d car %d et dep=%d\n", i, (dep - dep % N) / N, j, dep % N, dep);
  //printf("->dep:%d, i=%d, j=%d\n", dep, i, j);
  int indicePiont;          // contient l'indice du piont à placer
  if (dep < 9)
  {
    for(int k = N-1; k >=0; k--) 
    {
      printf("k = %d, i= %d, j= %d\n", k, i, j);
      if('0' != map3D[i][j][k]) 
      {

        switch(map3D[i][j][k])  {
          case 'b' : indicePiont = (N-1) - k ; printf("INDICE PION1: %d\n", indicePiont); break;
          case 'n' : indicePiont = (N-1) - k + N; printf("INDICE PION2: %d\n", indicePiont); break;
          default : printf("error in transition switch map3D[%d][%d][%d] : %c\n", i, j, k, map3D[i][j][k]); break;
        }
        break;
      }
    }
  }
  else
  {
    indicePiont = dep-9;
  }
  printf("INDICE PION: %d\n", indicePiont);
  if (0 != SDL_QueryTexture(textureTableauPiont[indicePiont], NULL, NULL, &positionPiontCurrent.w, &positionPiontCurrent.h)) {
    fprintf(stderr, "Error SDL_QueryTexture in transition 3: %s \n", SDL_GetError());
    return -1;
  }
  //printf("x1=%d, y1=%d, x2=%d, y2=%d, delX=%d, delY=%d\n", x1, y1, x2, y2, xDelta, yDelta);
  //printf("x-> %d & y-> %d\n", abs(x1 - x2), abs(y1 - y2));
  while(abs(x1 - x2) > 20 || abs(y1 - y2) > 20)
  {
    //printf("x-> %d & y-> %d\n", abs(x1 - x2), abs(y1 - y2));
    positionPiontCurrent.x =  x1 - positionPiontCurrent.w/2;
    positionPiontCurrent.y =  y1 - 4.5*positionPiontCurrent.h/6;
    if(c == 'b')
      printMapEmptySDL(tableauTextureMapVide[1], renderer);
    else if (c == 'n')
      printMapEmptySDL(tableauTextureMapVide[2], renderer);
    affichePileSDL(renderer, textureTableauPiont, tableauDePoint, pileJ1, pileJ2);
    affichePionSurPlateau(renderer, textureTableauPiont, tableauDePoint, map3D, end);
    if (indicePionWhoEat != -1)
      affichePionOnCase(renderer, textureTableauPiont, tableauDePoint, end, indicePionWhoEat);
    if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[indicePiont], NULL, &positionPiontCurrent) ){
    fprintf(stderr, "Error SDL_RenderCopy in transition 2 : %s \n", SDL_GetError());
    return -1;
    }
    SDL_RenderPresent(renderer);
    x1 += xDelta;
    y1 += yDelta;
    SDL_Delay(10);
  }
  return 1;
}

int affichePionOnCase(SDL_Renderer * renderer,  SDL_Texture ** textureTableauPiont, point ** tableauDePoint, int index, int indicePion)
{
  SDL_Rect positionPiontCurrent;

  if (0 != SDL_QueryTexture(textureTableauPiont[indicePion], NULL, NULL, &positionPiontCurrent.w, &positionPiontCurrent.h)) 
  {
    fprintf(stderr, "Error SDL_QueryTexture in affichePionOnCase: %s \n", SDL_GetError());
    return -1;
  }

  /* zoom */
  if(index >= 0 && index < 3) 
  {
    //printf("Petit zoom\n");
    positionPiontCurrent.w *= 0.77;
    positionPiontCurrent.h *= 0.77;
  }
  else if(index > 2 && index < 6)
  { 
    //printf("Moyen zoom\n");
    positionPiontCurrent.w *= 0.86; 
    positionPiontCurrent.h *= 0.86;
    }

  positionPiontCurrent.x =  tableauDePoint[index]->x - positionPiontCurrent.w/2;
  if(indicePion % N == 0) //si c'est un gros pion
    positionPiontCurrent.y =  tableauDePoint[index]->y - 2*positionPiontCurrent.h/3;
  else
    positionPiontCurrent.y =  tableauDePoint[index]->y - 4.5*positionPiontCurrent.h/6;

  if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[indicePion], NULL, &positionPiontCurrent) )
  {
    fprintf(stderr, "Error SDL_RenderCopy in affichePionOnCase: %s \n", SDL_GetError());
    return -1;
  }
  return 0;
}

void pause(SDL_Renderer * renderer, SDL_Texture ** textureTableauOptionMenu, int * p_etats, int boolPlayMusic, SDL_Texture ** tableauTextureMapVide, SDL_Texture ** textureTableauPion, point ** tableauDePoint ,char ***  map3D)
{
  SDL_RenderClear(renderer);
  SDL_Rect tableauRectOption[6];

  for(int i = 0; i < 6; i++)
  {
    SDL_QueryTexture(textureTableauOptionMenu[i], NULL, NULL, &tableauRectOption[i].w, &tableauRectOption[i].h);
    tableauRectOption[i].x = WIDTH /2 - tableauRectOption[i].w / 2; 
  }
  printf("1\n");
  SDL_QueryTexture(textureTableauOptionMenu[3], NULL, NULL, &tableauRectOption[3].w, &tableauRectOption[3].h);
  tableauRectOption[5].y = 318; tableauRectOption[2].y  = 488; //button resume and quite
  tableauRectOption[3].x = WIDTH - tableauRectOption[3].w; tableauRectOption[3].y = 0; //button sound

  SDL_Point pointMouse; //souris du menu pour evenement
  while(*p_etats == 3) // boucle principale
  {
    SDL_Event event;
    SDL_RenderClear(renderer);
    SDL_GetMouseState(&pointMouse.x, &pointMouse.y); // recupere coord souris
    printMapEmptySDL(tableauTextureMapVide[0], renderer);
    affichePionSurPlateau(renderer, textureTableauPion, tableauDePoint, map3D, -1);
    if (0 !=  SDL_RenderCopy(renderer, textureTableauOptionMenu[6], NULL, NULL)) 
    { 
      fprintf(stderr, "Error SDL_RenderCopy in pause : %s \n", SDL_GetError());
    }
    for(int i = 2; i < 6; i = i+3) // boucle sur "resume" and "quit"
    {
      if(isInRectangle(pointMouse, tableauRectOption[i]))
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[i], 255);
        if (0 != SDL_RenderCopy( renderer,  textureTableauOptionMenu[i], NULL, &tableauRectOption[i])) fprintf(stderr, "Error SDL_RenderCopy for pause : %s\n", SDL_GetError());
      }
      else
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[i], 150);
        if (0 != SDL_RenderCopy( renderer,  textureTableauOptionMenu[i], NULL, &tableauRectOption[i])) fprintf(stderr, "Error SDL_RenderCopy for pause: %s\n", SDL_GetError());
      }
    }
    if(isInRectangle(pointMouse, tableauRectOption[3]))
    {
      if(boolPlayMusic)
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[3], 255);
        if (0 != SDL_RenderCopy(renderer,  textureTableauOptionMenu[3], NULL, &tableauRectOption[3])) fprintf(stderr, "Error SDL_RenderCopy for pause : %s\n", SDL_GetError());
      }
      else
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[4], 255);
        if (0 != SDL_RenderCopy(renderer,  textureTableauOptionMenu[4], NULL, &tableauRectOption[3])) fprintf(stderr, "Error SDL_RenderCopy for pause : %s\n", SDL_GetError());
      }
    }
    else
    {
      if(boolPlayMusic)
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[3], 100);
        if (0 != SDL_RenderCopy(renderer,  textureTableauOptionMenu[3], NULL, &tableauRectOption[3])) fprintf(stderr, "Error SDL_RenderCopy for pause : %s\n", SDL_GetError());
      }
      else
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[4], 100);
        if (0 != SDL_RenderCopy(renderer,  textureTableauOptionMenu[4], NULL, &tableauRectOption[3])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
    }

    SDL_RenderPresent(renderer);
    SDL_Delay(50);
    while(SDL_PollEvent(&event)) // programme continue et un nouveau evenement dans la file
    {
      SDL_GetMouseState(&pointMouse.x, &pointMouse.y); // recupere coord souris
      switch(event.type)
      {
        case SDL_QUIT : //quitter
          *p_etats = 0;
          break ;

        case SDL_MOUSEBUTTONDOWN :  // bouton souris enfonce
          if (event.button.button == SDL_BUTTON_LEFT) // bouton souris gauche
          {
            if (isInRectangle(pointMouse , tableauRectOption[5])) // resume
            {
              *p_etats = 2 ;
              SDL_RenderClear(renderer);
            }
            else if(isInRectangle(pointMouse , tableauRectOption[2])) // quite
            {
              *p_etats = 1;
            }
            else if(isInRectangle(pointMouse , tableauRectOption[3])) // sond
            {
              if(boolPlayMusic == 0) 
              {
                boolPlayMusic = 1; 
                Mix_ResumeMusic();
              }
              else 
              {
                boolPlayMusic = 0; 
                Mix_PauseMusic();
              }
            }
          }
          break ;
        default :
          break ;
      } 
    }
  }
}