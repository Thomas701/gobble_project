/**
 * \file init.c
 * 
 * \brief Fichier contenant les codes des fonctions permettant l'initialisation de nos structures de données commes les piles, plateaux, tableaux, textures.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

/**
 * \fn void initMap(char *** map)
 * 
 * \brief Fonction qui initialise le plateau de jeu detaillé (3D) avec que des cases vides ('0').
 * 
 * \param[in] char *** map : Contient le plateau de jeu que l'on va modifier.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
void initMap(char *** map) {
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      for(int k = 0; k < N; k++)
        map[i][j][k] = '0';
    }
  }
}

/**
 * \fn void initMap2D(char ** map2D, char *** map3D)
 * 
 * \brief Fonction qui initialise le plateau de jeu non detaillé (2D) avec les case de la map3D.\n
 * 
 * Elle effectue un premier parcours pour mettre toutes les cases à '0' puis parcours la map3D et si pion rencontré, elle l'écrit dans la map 2D.
 * 
 * \param[in] char **  map2D : Contient le plateau de jeu non detaillé ou l'on va mettre les valeurs de map3D.
 * \param[in] char *** map3D : Contient le plateau de jeu detaillé que l'on va copier.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
void initMap2D(char ** map2D, char *** map3D) {
  for(int i = 0; i < N; i++) { // initialise toute la map2D à '0'
    for(int j = 0; j < N; j++)
      map2D[i][j] = '0';
  }
  for(int i=0; i < N; i++) { // mets les pions dans la map2D
    for(int j = 0; j < N; j++) {
      for(int k = (N-1); k >= 0; k--) {
        if(map3D[i][j][k] != '0') {
          map2D[i][j] = map3D[i][j][k];
          k = -1;
        }
      }
    }
  }
}

/**
 * \fn void initPile(char ** pile, char c)
 * 
 * \brief Fonction qui initialise les piles du joueur à son caractère identifiant (b ou n). 
 * 
 * \param[in] char **  pile : contient les piles du joueur.
 * \param[in] char c : identifiant du joueur.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
void initPile(char ** pile, char c) {
  for (int i = 0; i < N-1; i++) {
    for (int j = 0; j < N; j++)
      pile[i][j] = c;
  }
}

/**
 * \fn int loadTextureOptionMenu(SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu)
 * 
 * \brief Fonction qui charge les images des options menu.
 * 
 * \param[in] SDL_Renderer ** renderer : Rendu principale du jeu.
 * \param[in] SDL_Texture *** ptextureTableauOptionMenu : pointeur sur tableau qui va contenir les images des options.
 * 
 * \return int : Retourne -1 si erreur, sinon 0
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
int loadTextureOptionMenu(SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu) {
  SDL_Texture ** textureTableauOptionMenu = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*12); // alloue le tableau de texture
  if (! textureTableauOptionMenu) { // si erreur return -1 (permet par la suite de quitter le programme)
    fprintf(stderr, "Erreur allocation memory in textureTableauOptionMenu\n"); 
    return -1;
  }
  for (int i = 0; i < 12; i++) { // seulement 12 options dans le menu principal
    char nom[30];
    sprintf(nom, "Frames/option%d.png", i+1); // sinon on charge les images dans le tableau
    textureTableauOptionMenu[i] = loadImage(nom, * renderer);
    if(!textureTableauOptionMenu[i]) {
      fprintf(stderr, "Error loadTextureOptionMenu for textureTableauOptionMenu : %s\n", SDL_GetError()); 
      return -1; 
    }
  }
  * ptextureTableauOptionMenu = textureTableauOptionMenu; // alloue le pointeur sur le nouveau tableau
  return 0;
}

/**
 * \fn int initialiseDebutProgramme(SDL_Window ** window, SDL_Texture *** textureBackground, SDL_Texture *** ptableauTextureMapVide, SDL_Surface ** icones, SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu, SDL_Texture *** pTextureTableauPion, SDL_Texture *** pTextureTableauWin, point *** pTableauDePoint, SDL_Rect *** pTableauCase)
 * 
 * \brief Fonction qui initialise toutes la partie SDL images + audio. Et qui initialise les tableaux de texture (pions, maps) et le tableau de point et de case. 
 * 
 * \param[in] SDL_Window ** window : fenêtre principale de notre jeu
 * \param[in] SDL_Texture *** textureBackground : contient les images d'animations du menu (celle des 400 images).
 * \param[in] SDL_Texture *** ptableauTextureMapVide : contient les images des maps vide (vert / bleu / rouge).
 * \param[in] SDL_Surface ** icones : contient l'image de l'icone du programme.
 * \param[in] SDL_Renderer ** renderer : rendu principale du jeu.
 * \param[in] SDL_Texture *** ptextureTableauOptionMenu : contient les textures des options du menu principale .
 * \param[in] SDL_Texture *** pTextureTableauPion : contient les textures des pions normals et sélectionnés.
 * \param[in] SDL_Texture *** pTextureTableauWin : contient les textures des map où les lignes sont colorés (en cas de victoire où égalité).
 * \param[in] point *** pTableauDePoint : contient les points des cases du plateau et piles.
 * \param[in] SDL_Rect *** pTableauCase : contient les surfaces des cases du plateau et piles.
 * 
 * \return int : Retourne 0 si bien passé, sinon -1. La gestion pour quitter le programme ne se fait pas ici car il faut libérer proprement la mémoire.
 * 
 * \author VILLEPREUX Thibault
 */
int initialiseDebutProgramme(SDL_Window ** window, SDL_Texture *** textureBackground, SDL_Texture *** ptableauTextureMapVide, SDL_Surface ** icones, SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu, SDL_Texture *** pTextureTableauPion, SDL_Texture *** pTextureTableauWin, point *** pTableauDePoint, SDL_Rect *** pTableauCase) {
  // initialise le systeme gestion de rendu, d'évenements , audio et temps + test
  if (0 != SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_AUDIO | SDL_INIT_TIMER)) { fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError()); return -1; }
  // alloue la fenetre
  * window = SDL_CreateWindow("GOBBLE GAME - PREP'ISIMA 2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN) ;
  if(!* window) { fprintf(stderr, "Erreur SDL_CreateWindow : %s\n", SDL_GetError()); return -1 ; }
  // initialisation renderer
  * renderer = SDL_CreateRenderer(* window, -1, SDL_RENDERER_ACCELERATED);
  if(!*renderer) { fprintf(stderr, "Error SDL_CreateRenderer for mainRenderer: %s\n", SDL_GetError()); return -1; }
  // chargement de l'icones
  * icones = IMG_Load("Frames/icones.png");
  if (!* icones) SDL_Log("Erreur chargement icones IMG_Load : %s\n", Mix_GetError());
  else SDL_SetWindowIcon(* window, * icones);
  // chargement carte son avec création de la configuration de la carte son
  if (Mix_OpenAudio(96000, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) < 0)  { SDL_Log("Erreur initialisation SDL_mixer : %s\n", Mix_GetError()); return -1 ; }
  // init texture background
  if(loadBackgroundMenu(renderer, textureBackground) != 0) { fprintf(stderr, "Error loadImage for textureBackground : %s\n", SDL_GetError()); return -1; }
  // init texture map vide
  if(0 != loadTextureTableauMap(renderer, ptableauTextureMapVide)) { fprintf(stderr, "Error loadTextureTableauMap for ptableauTextureMapVide : %s\n", SDL_GetError()); return -1; }
  // init texture option menu
  if (0 != loadTextureOptionMenu(renderer, ptextureTableauOptionMenu)) { fprintf(stderr, "Error loadTextureOptionMenu for ptextureTableauOptionMenu : %s\n", SDL_GetError()); return -1; }
  // init tableau de pion
  if (0 != loadPion(renderer, pTextureTableauPion)) { fprintf(stderr, "Error in loadPion : %s \n",SDL_GetError()); return -1; }
  // init tableau de point
  if(0 != createPoint(pTableauDePoint)) { fprintf(stderr, "Error in createPoint : %s \n",SDL_GetError()); return -1; }
  // init tableau de case
  if(0 != createCase(pTableauCase)) { fprintf(stderr, "Error in createCase : %s \n",SDL_GetError()); return -1; }
  // init map lors des victoires
  if(0 != loadTextureWin(renderer, pTextureTableauWin)) { fprintf(stderr, "Error in loadTextureWin : %s \n",SDL_GetError()); return -1; }
  return 0;
}

/**
 * \fn int loadTextureTableauMap(SDL_Renderer ** renderer, SDL_Texture *** ptableauTextureMapVide)
 * 
 * \bref Fonction qui charge les images des map vides (vert/rouge/bleu).
 * 
 * \param[in] SDL_Renderer ** renderer : Rendu principale du jeu.
 * \param[in] SDL_Texture *** ptableauTextureMapVide : pointeur sur tableau qui va contenir les images des map vides (vert/rouge/bleu).
 * 
 * \return int : Retourne -1 si erreur, sinon 0
 * 
 * \author VILLEPREUX Thibault
 */
int loadTextureTableauMap(SDL_Renderer ** renderer, SDL_Texture *** ptableauTextureMapVide) {
  SDL_Texture ** tableauTextureMapVide = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*3); 
  // 0 map vert, 1 map bleau, 2 map rouge
  if(!tableauTextureMapVide) { fprintf(stderr, "Error malloc in loadTextureTableauMap for tableauTextureMapVide\n"); return -1; }

  for (int i = 0; i < 3; i++){ // il n'y a que 3 images de map a charger
    char nom[30];
    sprintf(nom, "Frames/map%d.png", i+1);
    tableauTextureMapVide[i] = loadImage(nom, * renderer);
    if(!tableauTextureMapVide[i]) { fprintf(stderr, "Error loadTextureTableauMap for tableauTextureMapVide : %s\n", SDL_GetError()); return -1; }
  }
  * ptableauTextureMapVide = tableauTextureMapVide;
  return 0;
}

/**
 * \fn int loadPion(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauPion)
 * 
 * \bref Fonction qui charge les images des pions normals et sélectionnés.
 * 
 * \param[in] SDL_Renderer ** renderer : Rendu principale du jeu.
 * \param[in] SDL_Texture *** pTextureTableauPion : pointeur sur tableau qui va contenir les images des pions normals et sélectionnés.
 * 
 * \return int : Retourne -1 si erreur, sinon 0
 * 
 * \author VILLEPREUX Thibault
 */
int loadPion(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauPion)/*return 0 si ok, -1 sinon*/
{
    SDL_Texture ** textureTableauPion = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*(N*2)*2); // créer tableau de texture
    if (!textureTableauPion) {
        fprintf(stderr, "Erreur allocation memory in loadPion\n");
        return -1;
    }
    for (int i = 0; i < (N*2)*2; i++) { // remplie le tableau
        char nom[30];
        sprintf(nom, "Frames/pion%d.png", i+1);
        textureTableauPion[i] = loadImage(nom, * renderer);
        if(!textureTableauPion[i]) { 
        fprintf(stderr, "Error loadTextureOptionMenu for textureTableauPion[i] : %s\n", SDL_GetError()); 
        return -1; 
      }
    }
    * pTextureTableauPion = textureTableauPion; // mets le tableau dans le pointeur car aucun retour de tableau
    return 0;
}

/**
 * \fn int loadBackgroundMenu(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauBack)
 * 
 * \bref Fonction qui charge les 400 images de l'animation du menu.
 * 
 * \param[in] SDL_Renderer ** renderer : Rendu principale du jeu.
 * \param[in] SDL_Texture *** pTextureTableauBack : pointeur sur tableau qui va contenir les 400 images de l'animation du menu.
 * 
 * \return int : Retourne -1 si erreur, sinon 0
 * 
 * \author DUPOIS Thomas
 */
int loadBackgroundMenu(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauBack) {
  SDL_Texture ** textureTableauBack = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*400); // alloue le tableau
  if (! textureTableauBack) {fprintf(stderr, "Erreur allocation memory in loadBackgroundMenu\n"); return -1;}
  for (int i = 0; i < 400; i++) { // charge le tableau
    char nom[30];
    sprintf(nom, "Frames/background2/p (%d).png", i+1);
    textureTableauBack[i] = loadImage(nom, * renderer);
    if(!textureTableauBack[i]) { fprintf(stderr, "Error loadPion for loadBackgroundMenu : %s\n", SDL_GetError()); return -1; }
  }
  * pTextureTableauBack = textureTableauBack; // mets le tableau dans le pointeur car aucun retour de tableau
  return 0;
}

/**
 * \fn int loadTextureWin(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauWin)
 * 
 * \brief Fonction qui charge les images des lignes coloré (en cas de victoire ou égalité).
 * 
 * \param[in] SDL_Renderer ** renderer : Rendu principale du jeu.
 * \param[in] SDL_Texture *** pTextureTableauWin : pointeur sur tableau qui va contenir les images des lignes coloré (en cas de victoire ou égalité).
 * 
 * \return int : Retourne -1 si erreur, sinon 0
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibaul
 */
int loadTextureWin(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauWin) {
  SDL_Texture ** TextureTableauWin = (SDL_Texture **) malloc(sizeof(SDL_Texture *)*8);

  if (! TextureTableauWin) {fprintf(stderr, "Erreur allocation memory in loadTextureWin\n"); return -1;}
  for (int i = 0; i < 8; i++)
  {
    char nom[30];
    sprintf(nom, "Frames/win%d.png", i+1);
    TextureTableauWin[i] = loadImage(nom, * renderer);
    if(!TextureTableauWin[i]) { fprintf(stderr, "Error loadTextureWin for TextureTableauWin : %s\n", SDL_GetError()); return -1; }
  }
  * pTextureTableauWin = TextureTableauWin;
  return 0;
}

/**
 * \fn void loadAndPlayMainMusic(Mix_Music ** mainMusic)
 * 
 * \brief Fonction qui charge et joue la musique principale.
 * 
 * \param[in] Mix_Music ** mainMusic : contient la musique principale du jeu.
 * 
 * \return void : Pas de type de retour.
 * 
 * \author VILLEPREUX Thibault
 */
void loadAndPlayMainMusic(Mix_Music ** mainMusic) {
  // initialisation de la musique
  * mainMusic = Mix_LoadMUS("Music/mainMusic.mp3");
  Mix_VolumeMusic(MIX_MAX_VOLUME/8);
  if(!* mainMusic) fprintf(stderr, "Error for load mainMusic : %s \n", SDL_GetError());
  // play music
  if(0 != Mix_PlayMusic(* mainMusic, -1)) { printf("Error in Mix_PlayMusic: %s\n", SDL_GetError());
  }
}

/**
 * \fn void initTableauCase(SDL_Rect ** tableauCase)
 * 
 * \brief Fonction qui initialise (attention ne créée pas) toutes les cases/surfaces en 3*3.
 * 
 * \param[in] SDL_Rect ** tableauCase : contient les surfaces (x/y et weidth/height) des cases du plateau et des piles en 3*3.
 * 
 * \return void : Pas de type de retour.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault 
 */
void initTableauCase(SDL_Rect ** tableauCase) {
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
  tableauCase[ 9]->w = 128 ; tableauCase[ 9]->h = 131 ;  // bleu fond
  tableauCase[ 9]->x = 223 ; tableauCase[ 9]->y = 293 ;
  tableauCase[10]->w = 148 ; tableauCase[10]->h = 123 ;  // bleu moyen
  tableauCase[10]->x = 167 ; tableauCase[10]->y = 431 ;
  tableauCase[11]->w = 143 ; tableauCase[11]->h = 110 ;  // bleu devant
  tableauCase[11]->x = 112 ; tableauCase[11]->y = 579 ;
  tableauCase[12]->w = 119 ; tableauCase[12]->h = 129 ;  // rouge fond
  tableauCase[12]->x = 927 ; tableauCase[12]->y = 294 ;
  tableauCase[13]->w = 117 ; tableauCase[13]->h = 116 ;  // rouge moyen
  tableauCase[13]->x = 987 ; tableauCase[13]->y = 430 ;
  tableauCase[14]->w = 122 ; tableauCase[14]->h = 114 ;  // rouge devant
  tableauCase[14]->x = 1050; tableauCase[14]->y = 579 ;
}