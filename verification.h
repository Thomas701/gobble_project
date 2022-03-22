#ifndef VERIFICATION_H_
#define VERIFICATION_H_

/*Fonctions Vérifications :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void debugTab(SDL_Rect ** tableauCase); // sauve moi la vie!
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
int canMooveThisPiontD(char *** map, int posDeb, char c); // ??? a changer? canMooveThisPiont v=2.0 
int count_pion(char ** map2D, int nbre, char c); //Y'a t-il un alignement de nbre pion de type "c" sur la map?
int check_End_Game(char ** map2D); // vérifie la fin de partie et renvoie la ligne correspondante
int sizeMaxPiont(char ** stackArray); // vérifie si il y a au moins un piont de taille > 1
int canPlayNewPiont(char **  stackArray, char ** map2D); // S'il peut jouer un nouveau piont dans sa pile
int canPlayStack(int sizePiont, char *** map); // vérifie si il y a au moins un coup possible selon l'index
int canPutPiont(char *** map, int sizePiont, int endPiont); // vérifie si tu peux poser le pion à l'endroit "que l'on a pris dans la pile"
int isStackFull(char ** pile1); //vérifie si la pile est pleine
SDL_bool isInRect(SDL_Point point, SDL_Point rectangleHautGauche, SDL_Point rectangleBasDroit); // pour favoir si le point est à l'interieur d'un rectangle
SDL_bool isInRectangle(SDL_Point point, SDL_Rect rect);
int canSelection(SDL_Point pointMouse, char *** map3D, char ** map2D, SDL_Rect ** tableauCase, char ** pileJ1, char ** pileJ2, char c, int distance);
int canPlay(int imageIndexP, SDL_Point pointMouse, SDL_Rect ** tableauCase, char *** map3D, char ** pile, int distance); //vérifie si étant donné un index de départ, le joueur peut jouer sur l'index d'arrivé sélectionné
int canEffectDeplacementWithDistance(char *** map3D, char c); //verifie si on peut deplacer un pion dans une map

#endif