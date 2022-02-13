#ifndef FONCTION_H_
#define FONCTION_H_

#define N 3                                     

/*Fonctions active:
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int sizePiontMaxStack(char ** stackArray, int numStack); // retourne la taille du pion le plus grand d'une pile
int mooveSinceStack(char *** map, char ** stackArray, int numStack,int sizePiont ,int endPiont, char c); //place un pion sur la map depuis une pile
int moove(char *** map, int posDeb, int posEnd); // déplace un pion présent sur la map
void gameOption(char ** stackArray, char *** map3D,char ** map2D, char c); // Fonction principale du jeu

/*Fonctions Vérifications :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int isEmptyStack(char ** stack, int num); // La pile numero "num" est vide?
int isEmptyStacks(char ** stack); // toutes les piles sont vides?
int isEmptyCase(char ** map2D); // la map est vide?
int canMoove(char *** map, int posDeb, int posEnd); // Le pion peut-il bouger?
int canMooveThisPiont(char *** map, char ** map2D, int posDeb, char c); // Le pion a au moin une possibilité de bouger
int count_pion(char *** map, int nbre, char c); //Y'a t-il un alignement de nbre pion de type "c" sur la map?
int check_End_Game(char *** map); // vérifie la fin de partie
int sizeMaxPiont(char ** stackArray); // vérifie si il y a au moins un piont de taille > 1
int canPlayNewPiont(char **  stackArray, char ** map2D); // S'il peut jouer un nouveau piont dans sa pile
int canPlayStack(int sizePiont, char *** map); // vérifie si il y a au moins un coup possible selon l'index
int canPutPiont(char *** map, int sizePiont, int endPiont); // vérifie si tu peux poser le pion à l'endroit "que l'on a pris dans la pile"
int isStackFull(char ** pile1); //vérifie si la pile est pleine


/*Fonctions création de maps et piles :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

char ** createStack(char c);
char *** createMap();
char ** createMap2D();

/*Fonctions initialisation de maps :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void initMap(char *** map); // initialise la map 3D
void  initMap2D(char ** map2D, char *** map3D); // initialise la map 2D

/*Fonctions print pour afficher les maps & piles :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void printMap3dDebug(char *** map); // affiche la map 3D
void printMap2D(char ** map2D); // affiche la map 2D
void printStacks(char ** stacksArray); // affiche les piles

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

/*Fonctions d'erreur pour eviter la répétition :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void errorInCreatePile();
void errorInCreate3D();
void errorInCreate2D();

#endif
