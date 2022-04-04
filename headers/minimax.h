#define INF 99999

struct BoardGame{
	char *** map;
	char ** pile;
	SDL_Point coup; // x contient le numero de la case de depart, y d'arriver
};
typedef struct BoardGame BoardGame;

struct ScoreMap {
	/****  3 pions ****/
	int P3_0   ;  // 3 pions alignés dont 0 caché (donc victoire)
	int P3_1p  ;  // 3 pions alignés dont 1 petit caché
	int P3_1m  ;  // 3 pions alignés dont 1 moyen caché
	int P3_2m  ;  // 3 pions alignés dont 2 moyen cachés
	int P3_2p  ;  // 3 pions alignés dont 2 petit cachés
	int P3_1p1m;  // 3 pions alignés dont 1 petit caché et 1 moyen caché

	/****  2 pions ****/
	int P2_0 ;    // 2 pions alignés
	int P2_1p;    // 2 pions alignés dont 1 petit caché
	int P2_1m;    // 2 pions alignés dont 1 moyen caché
};
typedef struct ScoreMap ScoreMap;


void initScore(ScoreMap * scoreMap) ;

SDL_Point bestCoup(char *** map3D, int depth, char player, char ** pileJ1, char ** pileJ2);

int minimax(char *** map3D, int depth, int maximizingPlayer, char player, char ** pileJ1, char ** pileJ2, ScoreMap * critereScoreMap) ;

int max (int a, int b) ;

int min(int a, int b);

int isLeaf(char *** map3D) ;

int getSizePionInCase(char *** map3D, int numCase);



int getNextMap(BoardGame *** ptableauListeCoup, char ***  map3D, char ** pile, char player) ;


int numberMovePossible(char *** map3D, char ** pile) ;

int caseIsEmpty(char *** map3D, int numCase) ;

int numberMovePionDistance(char *** map3D, int sizePion, int numCase);
int evaluateScoreMap(char *** map3D, char player, ScoreMap * scoreMap) ;

/* return 1 si il existe 0 sinon*/
int havePawnSizeInPile(int size, char ** pile) ;

void copyMap3D(char *** map3D_S, char *** ma3D_D) ;

void copyPile(char ** pile_S, char ** pile_D) ;


void freeArrayNextMap(int numberValideLocation, char **** arrayNextMap3D);