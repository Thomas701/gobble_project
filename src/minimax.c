#define INF 99999


void initScore(ScoreMap * scoreMap) {
	scoreMap->P3_0    = INF;
	scoreMap->P3_1p   =	40 ;
	scoreMap->P3_1m   = 50 ;
	scoreMap->P3_2p   = 10 ;
	scoreMap->P3_2m   = 20 ;
	scoreMap->P3_1p1m = 15 ;

	/****  2 pions ****/
	scoreMap->P2_0    = 35 ;
	scoreMap->P2_1p   =  5 ;
	scoreMap->P2_1m   = 10 ;
}


SDL_Point bestCoup(char *** map3D, int depth, char player, char ** pileJ1, char ** pileJ2) {
	BoardGame ** tableauListeCoup = NULL;
	int numberValideLocation = ((player == 'b')) ? getNextMap(&tableauListeCoup, map3D, pileJ1, player) : getNextMap(&tableauListeCoup, map3D, pileJ2, player);
	int value = - INF; SDL_Point coupF = {0,0}; int tmp;

	ScoreMap * critereScoreMap = malloc(sizeof(critereScoreMap));
	if(!critereScoreMap) {
		fprintf(stderr, "Erreur allocation memory in bestCoup for critereScoreMap... EXIT GAME\n");
		exit(EXIT_FAILURE);
	}
	initScore(critereScoreMap);

	for(int i = 0 ; i < numberValideLocation; ++i) {
		tmp = (player == 'b') ? max(value, minimax(tableauListeCoup[i]->map, depth-1, 0, player, tableauListeCoup[i]->pile, pileJ2, critereScoreMap)): 
								max(value, minimax(tableauListeCoup[i]->map, depth-1, 0, player, pileJ1, tableauListeCoup[i]->pile, critereScoreMap));
		if(tmp > value) {
			value = tmp; 
			coupF.x = tableauListeCoup[i]->coup.x;
		}
	}
	// free tableauListeCoup
	return coupF;
}

int minimax(char *** map3D, int depth, int maximizingPlayer, char player, char ** pileJ1, char ** pileJ2, ScoreMap * critereScoreMap) {
	if(depth == 0 || isLeaf(map3D)) {
		return evaluateScoreMap(map3D, player, critereScoreMap);
	}

	BoardGame ** tableauListeCoup = NULL;
	
	int numberValideLocation = ((player == 'b')) ? getNextMap(&tableauListeCoup, map3D, pileJ1, player) : getNextMap(&tableauListeCoup, map3D, pileJ2, player);

	player = (player == 'b') ? 'n' : 'b' ; 

	if(maximizingPlayer) {
		int value = -INF ;
		for(int i = 0 ; i < numberValideLocation; ++i) {
			value = (player == 'b') ? max(value, minimax(tableauListeCoup[i]->map, depth-1, 0, player, tableauListeCoup[i]->pile, pileJ2, critereScoreMap)) : 
									  max(value, minimax(tableauListeCoup[i]->map, depth-1, 0, player, pileJ1, tableauListeCoup[i]->pile, critereScoreMap));
		}
		// il faut free tableauListeCoup !? mais proprement car on a besoin de la case [i]
		return value;
	}
	else { // minimizingPlayer
		int value = INF;
		for(int i = 0 ; i < numberValideLocation; ++i) {
			value = (player == 'b') ? min(value, minimax(tableauListeCoup[i]->map, depth-1, 1, player, tableauListeCoup[i]->pile, pileJ2, critereScoreMap)) : 
									  min(value, minimax(tableauListeCoup[i]->map, depth-1, 1, player, pileJ1, tableauListeCoup[i]->pile, critereScoreMap));
		}
		// il faut free tableauListeCoup !? mais proprement car on a besoin de la case [i]
		return value;
	}
}

int max (int a, int b) {
	if (a>b) {
		return a;
	}
	return b;
}

int min(int a, int b){
	if (a<b) {
		return a;
	}
	return b;
}

int isLeaf(char *** map3D) {
	char ** map2D = createMap2D();
	initMap2D(map2D, map3D);
	if(check_End_Game(map2D) != 0) { // il y a un victoire d'un ou plusieurs joueurs
		freeMap2D(map2D);
		return 1;
	}
	return 0;
}

int getNextMap(BoardGame *** ptableauListeCoup, char ***  map3D, char ** pile, char player) {
	int numberMove = numberMovePossible(map3D, pile); // il faut d'abord compter le nombre de coup possible avant de pouvoir allouer dynamiquement 
	
	BoardGame ** tableauListeCoup = malloc(sizeof(BoardGame *)*numberMove);
	int tmp = 0;

	/*on traite d'abord les insertions de nouveaux pions*/
	for(int sizePion = 0 ; sizePion < N ; ++sizePion) { // parcour les pions de la pile
		if(havePawnSizeInPile(sizePion, pile)) { // si il y a un pion de la taille sizePion dans la pile alors on 
			for(int numCase = 0 ; numCase < N*N ; ++numCase) { // parcour la map
				if(canPutPion(map3D, sizePion, numCase)) { // plus petit pion = 0 et on regarde si le pion peut être poser
					tableauListeCoup[tmp] = malloc(sizeof(BoardGame));
					tableauListeCoup[tmp]->map = createMap(); copyMap3D(map3D, tableauListeCoup[tmp]->map);

					tableauListeCoup[tmp]->pile = createStack('0'); // 0 car après copie donc on s'en moque
					copyPile(pile, tableauListeCoup[tmp]->pile);
					if(tableauListeCoup[tmp]->pile[0][sizePion] != '0')
						 mooveSinceStack(tableauListeCoup[tmp]->map, tableauListeCoup[tmp]->pile, 0 , sizePion, numCase, player);
					else mooveSinceStack(tableauListeCoup[tmp]->map, tableauListeCoup[tmp]->pile, 1 , sizePion, numCase, player);

					if (player == 'b') {
						SDL_Point tmpCoup = {sizePion + N * N , numCase};
						tableauListeCoup[tmp]->coup = tmpCoup;
					} 
					else {
						SDL_Point tmpCoup = {sizePion + N * N - 1 + N, numCase};
						tableauListeCoup[tmp]->coup = tmpCoup;
					}
					++ tmp ;
				}
			}
		}
	}
	for(int i = 0 ; i < tmp ; ++i) {
		printf("\n");
		printMap3dDebug(tableauListeCoup[i]->map);
	}

	/*on traite le déplacement des pions existants*/
		// on test tous les coups de déplacement
	for(int numCase = 0 ; numCase < N*N ; ++numCase) {
		if(!caseIsEmpty(map3D, numCase)) {

			int y = (numCase - numCase % N) / N;
			int x = numCase % N;
			
			/**** 4 direction de bases*****/
			int sizePion = getSizePionInCase(map3D, numCase);
			if(x + 1 < N  && canPutPion(map3D, sizePion, numCase + 1)) {  // cas droite
				tableauListeCoup[tmp] = malloc(sizeof(BoardGame));
					
				tableauListeCoup[tmp]->map = createMap(); copyMap3D(map3D, tableauListeCoup[tmp]->map);
				moove(tableauListeCoup[tmp]->map, numCase, numCase +1);
					
				tableauListeCoup[tmp]->pile = createStack('0'); // 0 car après copie donc on s'en moque
				copyPile(pile, tableauListeCoup[tmp]->pile);
				SDL_Point tmpCoup1 = {numCase, numCase + 1};
				tableauListeCoup[tmp]->coup = tmpCoup1;
				++ tmp;
			}
			if(x - 1 >= 0 && canPutPion(map3D, sizePion, numCase - 1)) { // cas gauche
				tableauListeCoup[tmp] = malloc(sizeof(BoardGame));
					
				tableauListeCoup[tmp]->map = createMap(); copyMap3D(map3D, tableauListeCoup[tmp]->map);
				moove(tableauListeCoup[tmp]->map, numCase, numCase -1);
					
				tableauListeCoup[tmp]->pile = createStack('0'); // 0 car après copie donc on s'en moque
				copyPile(pile, tableauListeCoup[tmp]->pile);
				SDL_Point tmpCoup2 = {numCase, numCase - 1};
				tableauListeCoup[tmp]->coup = tmpCoup2;
				++ tmp;
			} 
			if(y + 1 < N  && canPutPion(map3D, sizePion, numCase + N)) { // cas bas
				tableauListeCoup[tmp] = malloc(sizeof(BoardGame));
					
				tableauListeCoup[tmp]->map = createMap(); copyMap3D(map3D, tableauListeCoup[tmp]->map);
				moove(tableauListeCoup[tmp]->map, numCase, numCase + N);
					
				tableauListeCoup[tmp]->pile = createStack('0'); // 0 car après copie donc on s'en moque
				copyPile(pile, tableauListeCoup[tmp]->pile);
				SDL_Point tmpCoup3 = {numCase, numCase + N};
				tableauListeCoup[tmp]->coup = tmpCoup3;
				++ tmp;
			} 
			if(y - 1 >= 0 && canPutPion(map3D, sizePion, numCase - N)) {  // cas haut
				tableauListeCoup[tmp] = malloc(sizeof(BoardGame));
					
				tableauListeCoup[tmp]->map = createMap(); copyMap3D(map3D, tableauListeCoup[tmp]->map);
				moove(tableauListeCoup[tmp]->map, numCase, numCase - N);
					
				tableauListeCoup[tmp]->pile = createStack('0'); // 0 car après copie donc on s'en moque
				copyPile(pile, tableauListeCoup[tmp]->pile);
				SDL_Point tmpCoup4 = {numCase, numCase - N};
				tableauListeCoup[tmp]->coup = tmpCoup4;
				++ tmp;
			}

			/***** 4 diagonales ****/
			printf("pp y : %d x : %d\n", y, x);
			if(x + 1 < N && y - 1 >= 0 && canPutPion(map3D, sizePion, numCase + 1 - N)) { // cas haut droite
				tableauListeCoup[tmp] = malloc(sizeof(BoardGame));
				printf("11111111111\n");
					
				tableauListeCoup[tmp]->map = createMap(); copyMap3D(map3D, tableauListeCoup[tmp]->map);
				printf("7777777\n");
				printMap3dDebug(tableauListeCoup[tmp]->map);
				printf("--- %d %d \n", numCase, numCase + 1 - N);
				moove(tableauListeCoup[tmp]->map, numCase, numCase + 1 - N);
				printf("666666\n");
				tableauListeCoup[tmp]->pile = createStack('0'); // 0 car après copie donc on s'en moque
				copyPile(pile, tableauListeCoup[tmp]->pile);
				SDL_Point tmpCoup5 = {numCase, numCase + 1 - N};
				tableauListeCoup[tmp]->coup = tmpCoup5;
				++ tmp;
				printf("5555555555\n");
			} 
			printf("44444444444\n");
			if(x - 1 >= 0 && y - 1 >= 0 && canPutPion(map3D, sizePion, numCase - 1 - N)) { // cas haut gauche
				
				tableauListeCoup[tmp] = malloc(sizeof(BoardGame));
					
				tableauListeCoup[tmp]->map = createMap(); copyMap3D(map3D, tableauListeCoup[tmp]->map);
				moove(tableauListeCoup[tmp]->map, numCase, numCase - 1 - N);
				printf("111\n");
				tableauListeCoup[tmp]->pile = createStack('0'); // 0 car après copie donc on s'en moque
				copyPile(pile, tableauListeCoup[tmp]->pile);
				SDL_Point tmpCoup6 = {numCase, numCase - 1 - N};
				tableauListeCoup[tmp]->coup = tmpCoup6;
				++ tmp;
				printf("2222222222\n");
					
			} 
			if(x + 1 < N  && y + 1 < N  && canPutPion(map3D, sizePion, numCase + 1 + N)) { // cas bas droite
				tableauListeCoup[tmp] = malloc(sizeof(BoardGame));
					
				tableauListeCoup[tmp]->map = createMap(); copyMap3D(map3D, tableauListeCoup[tmp]->map);
				moove(tableauListeCoup[tmp]->map, numCase, numCase + 1 + N);
					
				tableauListeCoup[tmp]->pile = createStack('0'); // 0 car après copie donc on s'en moque
				copyPile(pile, tableauListeCoup[tmp]->pile);
				SDL_Point tmpCoup7 = {numCase, numCase + 1 + N};
				tableauListeCoup[tmp]->coup = tmpCoup7;
				++tmp;
			}
			if(x - 1 >= 0 && y + 1 < N  && canPutPion(map3D, sizePion, numCase - 1 + N)) { // cas bas gauche
				tableauListeCoup[tmp] = malloc(sizeof(BoardGame));
					
				tableauListeCoup[tmp]->map = createMap(); copyMap3D(map3D, tableauListeCoup[tmp]->map);
				moove(tableauListeCoup[tmp]->map, numCase, numCase - 1 + N);
					
				tableauListeCoup[tmp]->pile = createStack('0'); // 0 car après copie donc on s'en moque
				copyPile(pile, tableauListeCoup[tmp]->pile);
				SDL_Point tmpCoup8 = {numCase, numCase - 1 + N};
				tableauListeCoup[tmp]->coup = tmpCoup8;
				++ tmp;
			}

		}
	}
	return numberMove ;
}



int numberMovePossible(char *** map3D, char ** pile) {
	int numberMove = 0 ;
	// on test tous les coups depuis une pile
	for(int sizePion = 0 ; sizePion < N ; ++sizePion) { // parcour les pions de la pile
		if(havePawnSizeInPile(sizePion, pile)) { // si il y a un pion de la taille sizePion dans la pile alors on 
			for(int numCase = 0 ; numCase < N*N ; ++numCase) { // parcour la map
				if(canPutPion(map3D, sizePion, numCase)) { // plus petit pion = 0 et on regarde si le pion peut être poser
					++ numberMove;
				}
			}
		}
	}
	// on test tous les coups de déplacement
	for(int numCase = 0 ; numCase < N*N ; ++numCase) {
		if( ! caseIsEmpty(map3D, numCase) ) {
			int size = getSizePionInCase( map3D, numCase) ;
			numberMove += numberMovePionDistance(map3D, size, numCase);
		}
	}
	return numberMove;
}

int caseIsEmpty(char *** map3D, int numCase) {
	int x = (numCase - numCase % N) / N;
	int y = numCase % N;
	for(int i = 0 ; i < N ; ++i) {
		if (map3D[x][y][i] != '0') {
			return 0;
		}
	}
	return 1;
}

int numberMovePionDistance(char *** map3D, int sizePion, int numCase) {
	int numberMove = 0;
	int x = (numCase - numCase % N) / N;
	int y = numCase % N;
	
	/**** 4 direction de bases*****/
	if(x + 1 < N  && canPutPion(map3D, sizePion, numCase + 1)) ++ numberMove; // cas droite
	if(x - 1 >= 0 && canPutPion(map3D, sizePion, numCase - 1)) ++ numberMove; // cas gauche
	if(y + 1 < N  && canPutPion(map3D, sizePion, numCase + N)) ++ numberMove; // cas bas
	if(y - 1 >= 0 && canPutPion(map3D, sizePion, numCase - N)) ++ numberMove; // cas haut

	/***** 4 diagonales ****/
	if(x + 1 < N  && y - 1 >= 0 && canPutPion(map3D, sizePion, numCase + 1 - N)) ++ numberMove;  // cas haut droite
	if(x - 1 >= 0 && y - 1 >= 0 && canPutPion(map3D, sizePion, numCase - 1 - N)) ++ numberMove;  // cas haut gauche

	if(x + 1 < N  && y + 1 < N  && canPutPion(map3D, sizePion, numCase + 1 + N)) ++ numberMove;  // cas bas droite
	if(x - 1 >= 0 && y + 1 < N  && canPutPion(map3D, sizePion, numCase - 1 + N)) ++ numberMove;  // cas bas gauche

	return numberMove;
}
int evaluateScoreMap(char *** map3D, char player, ScoreMap * scoreMap) {
	int value = 0;
	return value;
}

/* return 1 si il existe 0 sinon*/
int havePawnSizeInPile(int size, char ** pile) {
	for(int i = 0 ; i < N-1 ; ++i) {
		if(pile[i][size] != '0') {
			return 1;
		}
	}
	return 0;
}

void copyMap3D(char *** map3D_S, char *** map3D_D) {
	for(int i = 0 ; i < N ; ++i) {
		for(int j = 0 ; j < N ; ++j ) {
			for(int k = 0 ; k < N ; ++k) {
				map3D_D[i][j][k] = map3D_S[i][j][k];
			}
		}
	}
}

void copyPile(char ** pile_S, char ** pile_D) {
	for(int i = 0 ; i < N - 1 ; ++i) {
		for(int j = 0 ; j < N ; ++j) {
			pile_D[i][j] = pile_S[i][j];
		}
	}
}

void freeArrayNextMap(int numberValideLocation, char **** arrayNextMap3D) {
	return ;
}

int getSizePionInCase(char *** map3D, int numCase) {
	int x = (numCase - numCase % N) / N;
	int y = numCase % N;
	for(int i = N-1 ; i >=0 ; ++i) {
		if(map3D[x][y][i] != '0') {
			return i;
		}
	}
	return -1;
}