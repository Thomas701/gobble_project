
/*Fonctions Graphique :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void intro_authors(SDL_Window ** window, SDL_Renderer ** renderer) {
  SDL_Texture * texture_authors = NULL; // contient la texture qui va acceuilir l'image authors [texture]
  Mix_Music * music_intro = NULL;      // [musique] 

  texture_authors = loadImage("Frames/authors1.png", *renderer);

  if(!texture_authors) {
    fprintf(stderr, "Erreur loadImage : %s\n", SDL_GetError());
    perror("Impossible d'afficher la texture = NULL");
  }
  else
  {
    for (int i = 0 ; i < 130 ; ++i ) //boucle pour rendre l'image d'intro transparente
    {
      SDL_RenderClear(*renderer);
      if(0 != SDL_SetTextureAlphaMod(texture_authors, i))
        fprintf(stderr, "Erreur SDL_SetTextureAlphaMod: %s\n", SDL_GetError());
      else
      {
        SDL_RenderCopy(*renderer, texture_authors, NULL, NULL);
        SDL_RenderPresent(*renderer);
        SDL_Delay(15);
      }
    }
      
    music_intro = Mix_LoadMUS("Music/intro2.wav"); // alloue la musique de demarrage
    if (!music_intro)
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Erreur chargement de la musique : %s\n", Mix_GetError());
    else 
    {
      Mix_VolumeMusic(MIX_MAX_VOLUME/6); // baisse volume musique
      Mix_PlayMusic(music_intro, 0);      // joue une seule fois
    }

    for (int i = 130 ; i < 255 ; ++i )
    {
      SDL_RenderClear(*renderer);
      if(0 != SDL_SetTextureAlphaMod(texture_authors, i))
      {
        fprintf(stderr, "Erreur SDL_SetTextureAlphaMod : %s\n", SDL_GetError());
      }
      else
      {
        SDL_RenderCopy(*renderer, texture_authors, NULL, NULL);
        SDL_RenderPresent(*renderer);
        SDL_Delay(15);
      }
    }
    for (int i = 255 ; i >= 0 ; --i)
    {
      SDL_RenderClear(*renderer);  // effacer image précédente
      if(0 != SDL_SetTextureAlphaMod(texture_authors, i))
      {
        fprintf(stderr, "Erreur SDL_SetTextureAlphaMod : %s\n", SDL_GetError());
      }
      else
      {
        SDL_RenderCopy(*renderer, texture_authors, NULL, NULL);
        SDL_RenderPresent(*renderer);
        SDL_Delay(15);
      }
    }
  }
  SDL_RenderClear(*renderer);
  if (texture_authors) SDL_DestroyTexture(texture_authors); // liberation texture
  if (music_intro) Mix_FreeMusic(music_intro); // libération de la musique, plus besoin
}

void lancementMenu(SDL_Renderer * renderer, SDL_Texture ** textureBackground, SDL_Texture ** textureTableauOptionMenu, int * p_etats, int boolPlayMusic)
{
  printf("cherche crach:1\n");
  SDL_RenderClear(renderer);
  //boutons du menu
  SDL_Rect tableauRectOption[4];

  for(int i = 0; i < 3; i++)
  {
    SDL_QueryTexture(textureTableauOptionMenu[i], NULL, NULL, &tableauRectOption[i].w, &tableauRectOption[i].h);
    tableauRectOption[i].x = WIDTH /2 - tableauRectOption[i].w / 2; 
  }
  printf("cherche crach:2\n");
  SDL_QueryTexture(textureTableauOptionMenu[3], NULL, NULL, &tableauRectOption[3].w, &tableauRectOption[3].h);
  tableauRectOption[3].x = WIDTH /2 - tableauRectOption[3].w / 2; 
  tableauRectOption[0].y = 318; tableauRectOption[1].y  = 488; tableauRectOption[2].y = 650; 
  tableauRectOption[3].x = WIDTH - tableauRectOption[3].w;     tableauRectOption[3].y = 0;

  SDL_Point pointMouse; //souris du menu pour evenement

  int incrImg = 0; // numero image menu (background)
  printf("cherche crach:3\n");
  while(*p_etats == 1) // boucle principale
  {
    SDL_Event event;
    SDL_RenderClear(renderer);
    SDL_GetMouseState(&pointMouse.x, &pointMouse.y); // recupere coord souris

    if (0 != SDL_RenderCopy(renderer, textureBackground[incrImg%400], NULL, NULL)) {fprintf(stderr, "Error SDL_RenderCopy for textureBackground : %s, i = %d, et img = %p \n", SDL_GetError(), incrImg%400 , textureBackground[incrImg%400]);}
    
    for(int i=0; i<3; ++i)
    {
      if(isInRectangle(pointMouse, tableauRectOption[i]))
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[i], 255);
        if (0 != SDL_RenderCopy( renderer,  textureTableauOptionMenu[i], NULL, &tableauRectOption[i])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
      else
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[i], 150);
        if (0 != SDL_RenderCopy( renderer,  textureTableauOptionMenu[i], NULL, &tableauRectOption[i])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
    }
    if(isInRectangle(pointMouse, tableauRectOption[3]))
    {
      if(boolPlayMusic)
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[3], 255);
        if (0 != SDL_RenderCopy(renderer,  textureTableauOptionMenu[3], NULL, &tableauRectOption[3])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
      else
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[4], 255);
        if (0 != SDL_RenderCopy(renderer,  textureTableauOptionMenu[4], NULL, &tableauRectOption[3])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
    }
    else
    {
      if(boolPlayMusic)
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[3], 100);
        if (0 != SDL_RenderCopy(renderer,  textureTableauOptionMenu[3], NULL, &tableauRectOption[3])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
      else
      {
        SDL_SetTextureAlphaMod(textureTableauOptionMenu[4], 100);
        if (0 != SDL_RenderCopy(renderer,  textureTableauOptionMenu[4], NULL, &tableauRectOption[3])) fprintf(stderr, "Error SDL_RenderCopy for textureMenu : %s\n", SDL_GetError());
      }
    }

    incrImg++;
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
            if (isInRectangle(pointMouse , tableauRectOption[0])) // 2 joueurs en local
            {
              *p_etats = 2 ;
              SDL_RenderClear(renderer);
            }
            else if(isInRectangle(pointMouse , tableauRectOption[1])) // IA min max
            {
              *p_etats = 3 ;
              SDL_RenderClear(renderer);
              printf("Lancement jeu contre IA \n");
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
            else if(isInRectangle(pointMouse , tableauRectOption[2])) // choix QUITTER
            {
              *p_etats = 0;
            }
          }
          break ;
        default :
          break ;
      } 
    }
  }
}

void lancementJeu(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint, SDL_Texture ** textureTableauWin, int * p_etatS, SDL_Rect ** tableauCase,  SDL_Texture ** textureTableauPion , char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, int distance)
{
  printf("--->2\n");
  debugTab(tableauCase);
  
  gameOptionGraphique(renderer, tableauTextureMapVide, tableauDePoint, tableauCase, pileJ1, pileJ2, map3D, map2D, p_etatS, textureTableauPion, distance);
  if(count_pion(map2D, N, 'b') && count_pion(map2D, N, 'n'))
    printf("EGALITE");
  else if (count_pion(map2D, N, 'b')) 
    printf("Le joueur 1 a gagne!\n");
  else 
    printf("Le joueur 2 a gagne!\n");

  // affichage vainqueur
  SDL_RenderClear(renderer);
  printf("--------------- chack end game : %d\n",check_End_Game(map2D));
  printMapEmptySDL(textureTableauWin[check_End_Game(map2D)-1], renderer);
  affichePileSDL(renderer, textureTableauPion, tableauDePoint, pileJ1, pileJ2);
  affichePiontSurPlateau(renderer, textureTableauPion, tableauDePoint, map3D);
  SDL_RenderPresent(renderer);
  SDL_Delay(8000);

  initMap(map3D);
  initMap2D(map2D, map3D);
  initPile(pileJ1,'b');
  initPile(pileJ2,'n');
}

/*return -1 if stack is empty else 0, 1 or 2*/
int sizePiontInStack(char ** stackArray, int numStack)
{
  int sizePiont = -1 ;
  for(int i = N-1 ; i >= 0 ; i--)
  {
    if (stackArray[numStack][i] != '0')
    {
      sizePiont = i; 
      i = -1; // sortie de boucle
    }
  }
  return sizePiont ;
}


/* 0 if success, -1 else*/
int affichePileSDL(SDL_Renderer * renderer, SDL_Texture ** textureTableauPiont, point ** tableauDePoint,char ** stackArrayJ1, char ** stackArrayJ2) // texturemapVide pour connaitre la taille
{
  SDL_Rect positionPiontCurrent;
  int * arrayCountPionInStack = (int *) calloc(N*2, sizeof(int));
  if(!arrayCountPionInStack)
  {
    fprintf(stderr,"Error in affichePileSDL for arrayCountPionInStack\n");
    return -1;
  }
  for (int i = 0; i < N-1; i++)
  {
    for (int j = 0; j < N; j++)
    {
        if (j == 0 && stackArrayJ1[i][j] == 'b') {arrayCountPionInStack[2] ++;}
        if (j == 0 && stackArrayJ2[i][j] == 'n') {arrayCountPionInStack[5] ++;}
        if (j == 1 && stackArrayJ1[i][j] == 'b') {arrayCountPionInStack[1] ++;}
        if (j == 1 && stackArrayJ2[i][j] == 'n') {arrayCountPionInStack[4] ++;}
        if (j == 2 && stackArrayJ1[i][j] == 'b') {arrayCountPionInStack[0] ++;}
        if (j == 2 && stackArrayJ2[i][j] == 'n') {arrayCountPionInStack[3] ++;}
    }
  }
  for(int i=0; i<N*2; i++)
  {
    if(arrayCountPionInStack[i] > 0 )
    {
      if (0 != SDL_QueryTexture(textureTableauPiont[i], NULL, NULL, &positionPiontCurrent.w, &positionPiontCurrent.h))
      {
         fprintf(stderr, "Error SDL_QueryTexture in affichePileSDL : %s \n", SDL_GetError());
         free(arrayCountPionInStack);
         return -1;
      }
      if(0 == i%3)      { positionPiontCurrent.w *= 0.77; positionPiontCurrent.h *= 0.77; } // dezoom car derniere ligne
      else if(1 == i%3) { positionPiontCurrent.w *= 0.86; positionPiontCurrent.h *= 0.86; } // dezoom car ligne 2/3
      
      positionPiontCurrent.x =  tableauDePoint[i+9]->x - positionPiontCurrent.w/2;
      
      if(i%3 != 0) // pas un gros piont
        positionPiontCurrent.y =  tableauDePoint[i+9]->y - 2*positionPiontCurrent.h/3; // ou 3 test ?
      else
        positionPiontCurrent.y =  tableauDePoint[i+9]->y - 4.5*positionPiontCurrent.h/6;
      
      if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[i], NULL, &positionPiontCurrent))
      {
        fprintf(stderr, "Error SDL_RenderCopy in affichePiontSurPlateau 2 : %s \n", SDL_GetError());
        free(arrayCountPionInStack);
        return -1;
      }
    } 
  }
  free(arrayCountPionInStack);
  return 0;
}

/* return 0 if succes, -1 else *, la map contient des '1', '2', '3' & 'a', 'b', 'c' */
int affichePiontSurPlateau(SDL_Renderer * renderer, SDL_Texture ** textureTableauPiont, point ** tableauDePoint ,char ***  map3D) {
  SDL_Rect positionPiontCurrent ;
  int indicePiont;          // contient l'indice du piont à placer
  int posCase ; // position en terme de case i%3 + j
  for (int i = 0  ; i < N ; ++i) {
    for(int j = 0 ; j < N ; j++) {
      for(int k=N-1; k >=0; --k) {
        if('0' != map3D[i][j][k]) {
          switch(map3D[i][j][k])  {
            case 'b' : indicePiont = N-1 - k ; break;
            case 'n' : indicePiont = 3 + N-1 - k; break;
            default : printf("error in affichePiontSurPlateau switch map3D[i][j][k] : %c\n", map3D[i][j][k]); break;
          }
          if (0 != SDL_QueryTexture(textureTableauPiont[indicePiont], NULL, NULL, &positionPiontCurrent.w, &positionPiontCurrent.h)) {
            fprintf(stderr, "Error SDL_QueryTexture in affichePiontSurPlateau 1 : %s \n", SDL_GetError());
            return -1;
          }
          if(0 == i) { // case du fond zoom
            positionPiontCurrent.w *= 0.77;
            positionPiontCurrent.h *= 0.77;
          }
          else if(1 == i) {  // case milieu zoom
            positionPiontCurrent.w *= 0.86;
            positionPiontCurrent.h *= 0.86;
          }
          posCase = (i * N) + j;
          // on centre si piont petit ou moyen
          positionPiontCurrent.x =  tableauDePoint[posCase]->x - positionPiontCurrent.w/2;
          // si gros oon ne centre pas
          if(k == N-1)
            positionPiontCurrent.y =  tableauDePoint[posCase]->y - 2*positionPiontCurrent.h/3;
          else
            positionPiontCurrent.y =  tableauDePoint[posCase]->y - 4.5*positionPiontCurrent.h/6;
          if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[indicePiont], NULL, &positionPiontCurrent) ){
            fprintf(stderr, "Error SDL_RenderCopy in affichePiontSurPlateau 2 : %s \n", SDL_GetError());
            return -1;
          }
          k = -1; // pour sortir de la boucle
        }
      }
    }
  }
  return 0;
}

int affichePionSelect(SDL_Renderer * renderer, point ** tableauDePoint, SDL_Texture ** textureTableauPiont, char *** map3D,int index)
{
  SDL_Rect positionPiontCurrent;
  if (index > 8)
  {
    if (0 != SDL_QueryTexture(textureTableauPiont[index-3], NULL, NULL, &positionPiontCurrent.w, &positionPiontCurrent.h)) // index-2 car par exemple l'index = 10 necessite de charger la texture 8 du tableau
    {
      fprintf(stderr, "Error SDL_QueryTexture in affichePionSelect 1 : %s \n", SDL_GetError());
      return -1;
    }
    if(0 == index%3)      { positionPiontCurrent.w *= 0.77; positionPiontCurrent.h *= 0.77; } // dezoom car derniere ligne
    else if(1 == index%3) { positionPiontCurrent.w *= 0.86; positionPiontCurrent.h *= 0.86; } // dezoom car ligne 2/3
    
    positionPiontCurrent.x =  tableauDePoint[index]->x - positionPiontCurrent.w/2;
    
    if(index%3 != 0) // pas un gros piont
      positionPiontCurrent.y =  tableauDePoint[index]->y - 2*positionPiontCurrent.h/3; // ou 3 test ?
    else
      positionPiontCurrent.y =  tableauDePoint[index]->y - 4.5*positionPiontCurrent.h/6;
    
    if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[index-3], NULL, &positionPiontCurrent))
    {
      fprintf(stderr, "Error SDL_RenderCopy in affichePionSelect 2: %s \n", SDL_GetError());
      return -1;
    }
    return 0;
  }
  else
  {
    int i = (index - index % N) / N;
    int j = index % N;
    int indicePiont;          // contient l'indice du piont à placer
    for(int k=N-1; k >=0; --k) 
    {
      if('0' != map3D[i][j][k]) 
      {
        switch(map3D[i][j][k])  {
          case 'b' : indicePiont = (N-1 - k) + (N*2) ; break;
          case 'n' : indicePiont = (3 + N-1 - k) + (N*2); break;
          default : printf("error in affichePionSelect switch map3D[%d][%d][%d] : %c\n", i, j, k, map3D[i][j][k]); break;
        }
        if (0 != SDL_QueryTexture(textureTableauPiont[indicePiont], NULL, NULL, &positionPiontCurrent.w, &positionPiontCurrent.h)) {
          fprintf(stderr, "Error SDL_QueryTexture in affichePionSelect 3: %s \n", SDL_GetError());
          return -1;
        }
        if(0 == i) { // case du fond zoom
          positionPiontCurrent.w *= 0.77;
          positionPiontCurrent.h *= 0.77;
        }
        else if(1 == i) {  // case milieu zoom
          positionPiontCurrent.w *= 0.86;
          positionPiontCurrent.h *= 0.86;
        }
        // on centre si piont petit ou moyen
        positionPiontCurrent.x =  tableauDePoint[index]->x - positionPiontCurrent.w/2;
        // si gros oon ne centre pas
        if(k == N-1)
          positionPiontCurrent.y =  tableauDePoint[index]->y - 2*positionPiontCurrent.h/3;
        else
          positionPiontCurrent.y =  tableauDePoint[index]->y - 4.5*positionPiontCurrent.h/6;
        if (0 !=  SDL_RenderCopy(renderer, textureTableauPiont[indicePiont], NULL, &positionPiontCurrent) ){
          fprintf(stderr, "Error SDL_RenderCopy in affichePiontSurPlateau 2 : %s \n", SDL_GetError());
          return -1;
        }
        k = -1; // pour sortir de la boucle
      }
    }
    return 0;
  }
}