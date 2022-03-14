#ifndef FONCTION_H_
#define FONCTION_H_

#define N 3                               

struct point
{
  int x, y;
};
typedef struct point point;

/*Fonctions active:
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int sizePiontMaxStack(char ** stackArray, int numStack); // retourne la taille du pion le plus grand d'une pile
void mooveSinceStack(char *** map, char ** stackArray, int numStack,int sizePiont ,int endPiont, char c); //place un pion sur la map depuis une pile
int moove(char *** map, int posDeb, int posEnd); // déplace un pion présent sur la map
void gameOption(char ** stackArray, char *** map3D,char ** map2D, char c, int deplacement); // Fonction principale du jeu
void gameOptionGraphique(SDL_Renderer * renderer, SDL_Texture **  tableauTextureMapVide, point ** tableauDePoint, const SDL_Rect ** tableauCase,  char ** pileJ1, char ** pileJ2, char *** map3D, char ** map2D, int * p_etats, int boolPlayMusic, SDL_Texture ** textureTableauOptionMenu, SDL_Texture ** textureTableauPiont, int distance); // c = 'b' or 'n' joueur qui choisie
void loadAndPlayMainMusic(Mix_Music ** mainMusic);
int getIndex(SDL_Point pointMouse, const SDL_Rect ** tableauCase);

/*Fonctions Vérifications :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int maximum(int i, int i2);
int minimum(int i, int i2);
int existPiontInMap(char ** map2D, char c); // Vérifie si le joueur possède au moins un piont dans la map qu'il peut déplacer
int existPiontInStack(char ** stack, int num, int i); //Vérifie si il existe un piont de taille i dans la pile numéro "num"
int isEmptyStack(char ** stack, int num); // La pile numero "num" est vide?
int isEmptyStacks(char ** stack); // toutes les piles sont vides?
int isEmptyCase(char ** map2D); // la map contient au moins une case vide?
int canMoove(char *** map, int posDeb, int posEnd); // Le pion peut-il bouger?
int canMooveThisPiont(char *** map, char ** map2D, int posDeb, char c); // Le pion a au moin une possibilité de bouger
int canMooveThisPiontDistance(char *** map, int posDeb, char c); // Le pion peut-il bouger sur une distance de 1?
int count_pion(char ** map2D, int nbre, char c); //Y'a t-il un alignement de nbre pion de type "c" sur la map?
int check_End_Game(char ** map2D); // vérifie la fin de partie et renvoie la ligne correspondante
int sizeMaxPiont(char ** stackArray); // vérifie si il y a au moins un piont de taille > 1
int canPlayNewPiont(char **  stackArray, char ** map2D); // S'il peut jouer un nouveau piont dans sa pile
int canPlayStack(int sizePiont, char *** map); // vérifie si il y a au moins un coup possible selon l'index
int canPutPiont(char *** map, int sizePiont, int endPiont); // vérifie si tu peux poser le pion à l'endroit "que l'on a pris dans la pile"
int isStackFull(char ** pile1); //vérifie si la pile est pleine
SDL_bool isInRect(SDL_Point point, SDL_Point rectangleHautGauche, SDL_Point rectangleBasDroit); // pour favoir si le point est à l'interieur d'un rectangle
SDL_bool isInRectangle(SDL_Point point, const SDL_Rect rect);
int canSelection(SDL_Point pointMouse, char *** map3D, char ** map2D, const SDL_Rect ** tableauCase, char ** pileJ1, char ** pileJ2, char c);
int canPlay(int imageIndexP, SDL_Point pointMouse, const SDL_Rect ** tableauCase, char *** map3D, char ** pile, int distance); //vérifie si étant donné un index de départ, le joueur peut jouer sur l'index d'arrivé sélectionné
int canEffectDeplacementWithDistance(char *** map3D, char c); //verifie si on peut deplacer un pion dans une map

/*Fonctions création de maps et piles :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

char ** createStack(char c);
char *** createMap();
char ** createMap2D();
SDL_Texture * loadImage(const char * path, SDL_Renderer *renderer);
int createPoint(point *** pTableauDePoint);
int createCase(SDL_Rect *** pTableauCase);

/*Fonctions initialisation de maps :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void initMap(char *** map); // initialise la map 3D
void initMap2D(char ** map2D, char *** map3D); // initialise la map 2D
void initPile(char ** pile, char c); // remplie une pile
int loadTextureOptionMenu(SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu);
int initialiseDebutProgramme(SDL_Window ** window, SDL_Texture *** textureBackground, SDL_Texture *** ptableauTextureMapVide, SDL_Surface ** icones, SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu, SDL_Texture *** pTextureTableauPiont, SDL_Texture *** pTextureTableauWin, point *** pTableauDePoint);
int loadPiont(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauPiont); //charge les pionts dans un tableau de pionts
int loadBackgroundMenu(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauBack); //charge les images background du menu dans un tableau
int loadTextureWin(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauWin);
int loadTextureTableauMap(SDL_Renderer ** renderer, SDL_Texture *** ptableauTextureMapVide); // 0 mapVerte, 1mapBleu, 2 mapRouge

/*Fonctions print pour afficher les maps & piles :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void printMap3dDebug(char *** map); // affiche la map 3D
void printMap2D(char ** map2D); // affiche la map 2D
void printStacks(char ** stacksArray); // affiche les piles
int printMapEmptySDL(SDL_Texture * textureMapVide, SDL_Renderer * renderer); // affiche la map vide

/*Fonctions free pour libérer la mémoire :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void vider_buffer(void); // vide le buffer
void freeMap(char *** map); // libere la mémoire de la map 3D
void freeMap2D(char ** map2D); // libere la memoire de la map 2D
void freeStack(char ** stackArray); // libere la memoire de la pile

/*Fonctions lecture/ecriture fichiers :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/


/*--[ATTENTION AU MALLOC BORDEL!!!]--*/ /* return map2D Attention malloc ici, il faut libérer char ** */ 
void writeFile(char *** map3D); //ecrit la map dans un fichier
char ***  readFile3D(char  * nameFile); // lit le fichier map 3D
char **  readFile2D(char  * nameFile); // lit le fichier map 2D
void writeFilePile(char ** pile1, char ** pile2); // ecrit l'etat des piles dans un fichier
void readFilePile(char * nameFile, char ** pile1, char ** pile2); // lit l'etat des piles dans un fichier

/*Fonctions d'erreur pour eviter la répétition :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void errorInCreatePile();
void errorInCreate3D();
void errorInCreate2D();

/*Fonctions graphique :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void intro_authors(SDL_Window ** window, SDL_Renderer ** renderer); //creer le fondu initial
void lancementMenu(SDL_Renderer * renderer, SDL_Texture ** textureBackground, SDL_Texture ** textureTableauOptionMenu, int * p_etats, int boolPlayMusic); //lance le menu principale du jeu
void lancementJeu(SDL_Renderer * renderer, SDL_Texture **  tableauTextureMapVide, point ** tableauDePoint, SDL_Texture ** textureTableauWin, int * p_etatS, int boolPlayMusic, SDL_Texture ** textureTableauOptionMenu, const SDL_Rect ** tableauCase,  SDL_Texture ** textureTableauPiont , char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, int distance);
int affichePileSDL(SDL_Renderer * renderer, SDL_Texture ** textureTableauPiont, point ** tableauDePoint,char ** stackArrayJ1, char ** stackArrayJ2); // texturemapVide pour connaitre la taille
int affichePiontSurPlateau(SDL_Renderer * renderer, SDL_Texture ** textureTableauPiont, point ** tableauDePoint ,char ***  map3D); //affiche les pion sur le plateau de jeu
#endif
