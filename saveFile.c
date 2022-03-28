/**
 * \file saveFile.c
 * 
 * \brief Fichier contenant les codes des fonctions permettant d'écrire et lire les maps et piles dans des fichiers. On ne les utilise pas.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

/**
 * \fn void writeFile(char *** map3D)
 * 
 * \brief Fonction qui écrit le plateau de jeu détaillé dans un fichier "map.txt".
 * 
 * \param[in] char *** map : plateau de jeu détaillé à ecrire dans le fichier.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void writeFile(char *** map3D) {
  FILE * mapTXT = NULL;
  mapTXT = fopen("map.txt", "w+");
  if(!mapTXT) {
    perror("Opening Problem in writeFile()");
    exit(EXIT_FAILURE);
  }
  int find = 0 ;
  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      find = 0;
      for(int k=N-1; k>=0; --k) {
           if(!find && map3D[i][j][k] != '0') {
             if(map3D[i][j][k] == 'b')  fputc('1'+k, mapTXT);
             else fputc('a'+ k, mapTXT);
             find++;
           }
       }
        if (!find) fputc('0', mapTXT);
    }
    fputs("\n", mapTXT);
  }
  fclose(mapTXT);
}

/**
 * \fn char ***  readFile3D(char  * nameFile)
 * 
 * \brief Fonction qui lit le plateau de jeu détaillé dans un fichier.
 * 
 * \param[in] char  * nameFile) : nom du fichier où lire.
 * 
 * \return char *** : retourne la map3D detaillé. Attention il y a un malloc dans cette fonction donc libérer le tableau si utilisation.
 * 
 * \author VILLEPREUX Thibault
 */
char ***  readFile3D(char  * nameFile) {
  FILE * mapTXT = NULL;
  mapTXT = fopen(nameFile, "r");
  if (!mapTXT){
    perror("Opening Problem in readFile()");
    exit(EXIT_FAILURE);
  }

  char *** map3D = createMap();
  if (!map3D) {
    perror("Error Allocation Memory in readFile()");
    exit(EXIT_FAILURE);
  }
  initMap(map3D);
  char  charActu = ' ';
  int i = 0 ; int j = 0 ; int k ;
  while (charActu != EOF) {
    charActu = fgetc(mapTXT);
    if ('0' == charActu ||
      (charActu >= '1' && charActu <= '3' )||
      (charActu >= 'a' && charActu <= 'c')) {
      if ('0' == charActu) k = 0 ;
      else if (charActu >= '1' && charActu <= '3' ) k = charActu - '1';
      else k =  charActu - 'a' ;

      if (charActu >= 'a') {charActu = 'n';}
      else if (charActu >= '1') {charActu = 'b';}
  
      map3D[i][j][k] = charActu;
      j++;
      if (N == j) {
        j = 0 ; i++ ;
      }
    }
  }
  fclose(mapTXT);
  return map3D;
}

/**
 * \fn char **  readFile3D(char  * nameFile)
 * 
 * \brief Fonction qui lit le plateau de jeu non détaillé dans un fichier.
 * 
 * \param[in] char  * nameFile : nom du fichier où lire.
 * 
 * \return char ** : retourne la map2D non detaillé. Attention il y a un malloc dans cette fonction donc libérer le tableau si utilisation.
 * 
 * \author VILLEPREUX Thibault
 */
char **  readFile2D(char  * nameFile) {
  FILE * mapTXT = NULL;
  mapTXT = fopen(nameFile, "r");
  if (!mapTXT) {
    perror("Opening Problem in readFile()");
    exit(EXIT_FAILURE);
  }

  char ** map2D = createMap2D();
  if (!map2D) {
    perror("Error Allocation Memory in readFile()");
    exit(EXIT_FAILURE);
  }
  int  charActu = ' ';
  int i = 0 ; int j = 0 ;
  while (charActu != EOF) {
    charActu = fgetc(mapTXT);
    if ('0' == charActu ||
      (charActu >= '1' && charActu <= '3' )||
      (charActu >= 'a' && charActu <= 'c')) {
      if (charActu >= 'a')  {charActu = 'n';}
      else if (charActu >= '1') {charActu = 'b';}
      
      map2D[i][j] = charActu;
      j++;
      if (N == j) {
        j = 0 ;
        i++ ;
      }
    }
  }
  fclose(mapTXT);
  return map2D;
}

/**
 * \fn void writeFilePile(char ** pile1, char ** pile2)
 * 
 * \brief Fonction qui écrit les piles des joueurs dans un fichier "pile.txt".
 * 
 * \param[in] char  * nameFile : nom du fichier où lire.
 * \param[in] char ** pile1 : pile du joueur1 que l'on doit écrire dans le fichier.
 * \param[in] char ** pile2 : pile du joueur2 que l'on doit écrire dans le fichier.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author DUPOIS Thomas
 */
void writeFilePile(char ** pile1, char ** pile2) {
  FILE * pileFile = NULL;
  pileFile = fopen("pile.txt", "w+");
  if(!pileFile) {
    perror("Opening Problem in writeFilePile()");
    exit(EXIT_FAILURE);
  }
  for(int i = 0; i < N-1; i++) {
    for(int j = 0; j < N; j++) {
        fputc(pile1[i][j], pileFile);
    }
    fputc('\n', pileFile);
  }
  fputc('\n', pileFile);

  for(int i = 0; i < N-1; i++) {
    for(int j = 0; j < N; j++) {
        fputc(pile2[i][j], pileFile);
    }
    fputc('\n', pileFile);
  }
  fclose(pileFile);
}

/**
 * \fn void readFilePile(char * nameFile, char ** pile1, char ** pile2)
 * 
 * \brief Fonction qui lit les piles des joueurs dans un fichier.
 * 
 * \param[in] char ** pile1 : pile du joueur1 que l'on doit lire dans le fichier.
 * \param[in] char ** pile2 : pile du joueur2 que l'on doit lire dans le fichier.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author DUPOIS Thomas
 */
void readFilePile(char * nameFile, char ** pile1, char ** pile2) {
  FILE * pileFile = NULL;
  pileFile = fopen(nameFile, "r");
  if (!pileFile) {
    perror("Opening Problem in readFilePile()");
    exit(EXIT_FAILURE);
  }
  char  charActu = ' ';
  int i = 0 ; int j = 0 ; int count = 0; int tour = 0;
  while (charActu != EOF) {
    charActu = fgetc(pileFile);
    if (charActu != '\n' && tour == 0) {
      printf("pile1, c=%c,i=%d, j=%d\n", charActu, i, j);
      pile1[i][j] = charActu;
      j++;
      count = 0;
    }
    else if (charActu != '\n' && tour == 1 && i < N-1) {
      printf("pile2, c=%c,i=%d, j=%d\n", charActu, i, j);
      pile2[i][j] = charActu;
      j++;
      count = 0;
    }
    else {
      count++;
      i++;
      j = 0;
    }
    if (count == 2) {
      i = 0;
      j = 0;
      tour++;
    }
  }
  fclose(pileFile);
}
