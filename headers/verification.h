/**
 * \file verification.h
 * 
 * \brief Fichier contenant les headers des fonctions permettant de vérifier si un déplacement / insertion de nouveau pion est valide.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

#ifndef VERIFICATION_H_
#define VERIFICATION_H_

/**
 * \fn int maximum(int i, int i2)
 * 
 * \brief Fonction qui retourne le maximum entre 2 entiers.
 * 
 * \param[in] int i  : premier  entier.
 * \param[in] int i2 : deuxième entier.
 * 
 * \return int : retourne l'entier le plus grand.
 * 
 * \author DUPOIS Thomas
 */
int maximum(int i, int i2) ;

/**
 * \fn int minimum(int i, int i2)
 * 
 * \brief Fonction qui retourne le minimum entre 2 entiers.
 * 
 * \param[in] int i  : premier  entier.
 * \param[in] int i2 : deuxième entier.
 * 
 * \return int : retourne l'entier le plus petit.
 * 
 * \author DUPOIS Thomas
 */
int minimum(int i, int i2);


/**
 * \fn int existPionInMap(char ** map2D, char c)
 * 
 * \brief Fonction qui regarde si il **existe un pion visible** sur le plateau.
 * 
 * \param[in] char ** map2D : map non detaillé, uniquement en 2D qui permet de voir uniquement les pions visibles.
 * \param[in] char c : identifiant du joueur ('b' ou 'n').
 * 
 * \return int : retourne 1 si il existe un pion visible c sinon 0.
 * 
 * \author DUPOIS Thomas
 */
int existPionInMap(char ** map2D, char c) ;

/**
 * \fn int existPionInStack(char ** stack, int num, int i)
 * 
 * \brief Fonction qui regarde si il existe un pion d'une certaine taille sur la pile d'un joueur.
 * 
 * \param[in] char ** stack : pile du joueur.
 * \param[in] int num : numéro de la pile du joueur.
 * \param[in] int i : taille du pion que l'on doit chercher.
 * 
 * \return int : retourne 1 si il existe un pion sinon 0.
 * 
 * \author VILLEPREUX Thibault
 */
int existPionInStack(char ** stack, int num, int i) ;

/**
 * \fn int existPionInStack(char ** stack, int num, int i)
 * 
 * \brief Fonction qui regarde si il existe un pion d'une certaine taille sur la pile d'un joueur.
 * 
 * \param[in] char ** stack : pile du joueur.
 * \param[in] int num : numéro de la pile du joueur.
 * \param[in] int i : taille du pion que l'on doit chercher.
 * 
 * \return int : retourne 1 si il existe un pion sinon 0.
 * 
 * \author VILLEPREUX Thibault
 */
int isEmptyStack(char ** stack, int num) ;

/**
 * \fn int int isEmptyStacks(char ** stack)
 * 
 * \brief Fonction qui regarde si la pile du joueur est vide.
 * 
 * \param[in] char ** stack : pile du joueur.
 * 
 * \return int : retourne 1 si elle est vide sinon 0.
 * 
 * \author VILLEPREUX Thibault
 */
int isEmptyStacks(char ** stack);

/**
 * \fn int int isEmptyCase(char ** map2D)
 * 
 * \brief Fonction qui regarde si il existe une case du plateau vide.
 * 
 * \param[in] char ** map2D : plateau de jeu non detaillé.
 * 
 * \return int : retourne 1 si il existe une case vide sinon 0.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
int isEmptyCase(char ** map2D) ;

/**
 * \fn int canMoove(char *** map, int posDeb, int posEnd)
 * 
 * \brief Fonction qui regarde si le pion d'une case du plateau de jeu peut se déplacer vers une autre case du plateau de jeu.
 * 
 * \param[in] char *** map : plateau de jeu detaillé.
 * \param[in] int posDeb : numéro de la case de depart.
 * \param[in] int posEnd : numéro de la case d'arriver.
 * 
 * \return int : retourne 1 si le déplacement est possible sinon 0.
 * 
 * \author DUPOIS Thomas
 */
int canMoove(char *** map, int posDeb, int posEnd) ;

/**
 * \fn int canMooveThisPion(char *** map, char ** map2D ,int posDeb, char c)
 * 
 * \brief Fonction qui regarde si le pion d'une case du plateau de jeu peut se deplacer ailleurs dans la map. Il existe une possibilité de déplacement.
 * 
 * \param[in] char *** map : plateau de jeu detaillé.
 * \param[in] char ** map2D : plateau de jeu non detaillé.
 * \param[in] int posDeb : numéro de la case de depart.
 * \param[in] char c : identifiant du joueur qui veut deplacer son pion.
 * 
 * \return int : retourne 1 si le déplacement est possible sinon 0.
 * 
 * \author DUPOIS Thomas
 */
int canMooveThisPion(char *** map, char ** map2D, int posDeb, char c) ;

/**
 * \fn int canMooveThisPionDistance(char *** map, int posDeb, char c)
 * 
 * \brief Fonction qui regarde si le pion d'une case du plateau de jeu peut se deplacer ailleurs dans la map **d'une distance de 1**. Il existe une possibilité de déplacement.
 * 
 * \param[in] char *** map : plateau de jeu detaillé.
 * \param[in] int posDeb : numéro de la case de depart.
 * \param[in] char c : identifiant du joueur qui veut deplacer son pion.
 * 
 * \return int : retourne 1 si le déplacement est possible sinon 0.
 * 
 * \author DUPOIS Thomas
 */
int canMooveThisPionDistance(char *** map, int posDeb, char c) ;

/**
 * \fn int canMooveThisPionD(char *** map, int posDeb, char c)
 * 
 * \brief Fonction qui regarde si le pion d'une case du plateau de jeu peut se deplacer ailleurs dans la map **d'une distance de 1**. Il existe une possibilité de déplacement.
 * 
 * \param[in] char *** map : plateau de jeu detaillé.
 * \param[in] char ** map2D : plateau de jeu non detaillé.
 * \param[in] int posDeb : numéro de la case de depart.
 * \param[in] char c : identifiant du joueur qui veut deplacer son pion.
 * 
 * \return int : retourne 1 si le déplacement est possible sinon 0.
 * 
 * \author DUPOIS Thomas
 */
int canMooveThisPionD(char *** map, int posDeb, char c) ;

/**
 * \fn int count_pion(char ** map, int nbre, char c)
 * 
 * \brief Fonction qui regarde si il y a un alignement de nombre (passé en paramètre) pions du joueur sur la map.
 * 
 * \param[in] char ** map : plateau de jeu non detaillé.
 * \param[in] int nbre : nombre de pion(s) à aligné(s).
 * \param[in] char c : identifiant du joueur.
 * 
 * \return int : retourne 1 si il existe un alignement de **nbre pion(s)** du joueur sinon 0.
 * 
 * \author DUPOIS Thomas
 */
int count_pion(char ** map, int nbre, char c) ;

/**
 * \fn void debugTab(SDL_Rect ** tableauCase)
 * 
 * \brief Fonction qui vérifie que les cases n'ont pas été modifié car bug sur WINDOWS.
 * 
 * \param[in] SDL_Rect ** tableauCase : tableau de cases.
 * 
 * \return void : pas de retour, fonction avec effet de bord.
 * 
 * \author DUPOIS Thomas
 */
void debugTab(SDL_Rect ** tableauCase) ;

/**
 * \fn int check_End_Game(char ** map)
 * 
 * \brief Fonction qui nous informe en cas de victoire du joueur et nous donne l'identifiant de la ligne correspondante.
 * 
 * \param[in] SDL_Rect ** tableauCase : tableau de cases
 * 
 * \return int : retourne 0 si pas de victoire sinon retourn un nombre >  0, qui représente un identifiant de la ligne afin de réaliser un affichage en SDL.
 * 
 * \author DUPOIS Thomas
 */
int check_End_Game(char ** map) ;
/**
 * \fn int sizeMaxPion(char ** stackArray)
 * 
 * \brief Fonction qui regarde si il y a un pion de taille > 1 dans la pile du joueur (patant de l'hypothèse que les piles sont non vide appelle dans canPlayNewPion).
 * 
 * \param[in] char ** stackArray : pile du joueur.
 * 
 * \return int : retourne 1 si on a au moins une pile ayant une taille max de pion de 1 ou plus sinon 0.
 * 
 * \author DUPOIS Thomas
 */
int sizeMaxPion(char ** stackArray);

/**
 * \fn int canPlayNewPion(char **  stackArray, char ** map2D)
 * 
 * \brief Fonction qui regarde si le joueur peut jouer un nouveau pion sur le plateau.\n
 * 
 * On peut jouer un nouveau pion si il existe une case vide sur le plateau, ou si on veut jouer un pion de taille > 1.
 * 
 * \param[in] char ** stackArray : pile du joueur.
 * \param[in] char ** map2D : plateau de jeu non detaillé.
 * 
 * \return int : retourne 1 si c'est possible et 0 sinon.
 * 
 * \author DUPOIS Thomas
 */
int canPlayNewPion(char **  stackArray, char ** map2D) ;

/**
 * \fn int canPlayStack(int sizePion, char *** map)
 * 
 * \brief Fonction qui regarde si le joueur peut jouer un nouveau pion (et on connais sa taille) sur le plateau.\n
 * 
 * On peut jouer un nouveau pion si il existe une case ou il n'y a pas de pion de même taille et de taille supérieur.
 * 
 * \param[in] int sizePion : taille du pion que l'on cherche à poser.
 * \param[in] char *** map : plateau de jeu detaillé.
 * 
 * \return int : retourne 1 si c'est possible et 0 sinon.
 * 
 * \author VILLEPREUX Thibault
 */
int canPlayStack(int sizePion, char *** map);

/**
 * \fn int canPutPion(char *** map, int sizePion, int endPion)
 * 
 * \brief Fonction qui regarde si on peut mettre un pion d'une taille donnée sur une case du plateau de jeu.
 * 
 * \param[in] char *** map : plateau de jeu detaillé.
 * \param[in] int sizePion : taille du pion que l'on cherche à poser.
 * \param[in] int endPion  : case ou l'on veut poser le pion.
 * 
 * \return int : retourne 1 si c'est possible et 0 sinon.
 * 
 * \author VILLEPREUX Thibault
 */
int canPutPion(char *** map, int sizePion, int endPion) ;

/**
 * \fn int isStackFull(char ** pile)
 * 
 * \brief Fonction qui regarde si la pile du joueur est pleine ou non.
 * 
 * \param[in] char ** pile : pile du joueur.
 * 
 * \return int : retourne 1 si la pile est pleine et 0 sinon.
 * 
 * \author DUPOIS Thomas
 */
int isStackFull(char ** pile) ;

/**
 * \fn SDL_bool isInRect(SDL_Point point, SDL_Point rectangleHautGauche, SDL_Point rectangleBasDroit)
 * 
 * \brief Fonction qui regarde si le point de la souris se trouve à l'intérieur de la surface. La surface est donné grâce à 2 points.\n
 * 
 * Différence avec isInRectangle() qui prend un SDL_Rect, cette dernière est bien plus utilisé.
 * 
 * \param[in] SDL_Point point : coordonnée de la souris.
 * \param[in] SDL_Point rectangleHautGauche : coordonnée du rectangle haut gauche. 
 * \param[in] SDL_Point rectangleBasDroit : coordonnée du rectangle bas droit.
 * 
 * \return SDL_bool : retourne SDL_TRUE si le point de la souris est dedans et SDL_FALSE sinon.
 * 
 * \author VILLEPREUX Thibault
 */
SDL_bool isInRect(SDL_Point point, SDL_Point rectangleHautGauche, SDL_Point rectangleBasDroit);

/**
 * \fn SDL_bool isInRectangle(SDL_Point point, SDL_Rect rect)
 * 
 * \brief Fonction qui regarde si le point de la souris se trouve à l'intérieur de la surface. La surface est donné grâce à SDL_Rect.\n
 * 
 * Différence avec isInRect() qui 2 points (un en haut à gauche et un en bas à droite), cette dernière n'est pas utilisé.
 * 
 * \param[in] SDL_Point point : coordonnée de la souris.
 * \param[in] SDL_Rect rect : surface du rectangle.
 * 
 * \return SDL_bool : retourne SDL_TRUE si le point de la souris est dedans le rectangle et SDL_FALSE sinon.
 * 
 * \author VILLEPREUX Thibault
 */
SDL_bool isInRectangle(SDL_Point point, SDL_Rect rect) ;

/**
 * \fn int canSelection(SDL_Point pointMouse, char *** map3D, char ** map2D, SDL_Rect ** tableauCase, char ** pileJ1, char ** pileJ2, char c, int distance)
 * 
 * \brief Fonction qui permet de savoir si on peut selectionner un pion, il vérifie qu'il y a un pion sur la case sélectionné ou qu'il peut récuperer un pion sur une pile (le pion existe et c'est la pile du joueur).
 * 
 * \param[in] SDL_Point pointMouse : coordonnée de la souris.
 * \param[in] char *** map3D : plateau de jeu detaillé.
 * \param[in] char **  map2D : plateau de jeu non detaillé.
 * \param[in] SDL_Rect ** tableauCase : tableau de case contenant les surfaces des cases des piles et des cases du plateau de jeu.
 * \param[in] char ** pileJ1 : pile du joueur 1.
 * \param[in] char ** pileJ2 : pile du joueur 2.
 * \param[in] char c : identifiant du joueur.
 * \param[in] int distance : mode de jeu.
 * 
 * \return int : retourne l'indice si valide et sinon -1.
 * 
 * \author VILLEPREUX Thibault
 */
int canSelection(SDL_Point pointMouse, char *** map3D, char ** map2D, SDL_Rect ** tableauCase, char ** pileJ1, char ** pileJ2, char c, int distance);

/**
 * \fn int canPlay(int imageIndexP, SDL_Point pointMouse, SDL_Rect ** tableauCase, char *** map3D, char ** pile, int distance)
 * 
 * \brief Fonction qui permet de savoir si on peut jouer un pion, il appelle d'autres fonctions pour vérifier la validiter du coup.\n
 * 
 * Cette fonction est appellée quand on a un pion selectionné et que le joueur utilise le clique de sa souris.
 * 
 * \param[in] int imageIndexP 
 * \param[in] SDL_Point pointMouse : coordonnée de la souris.
 * \param[in] SDL_Rect ** tableauCase : tableau de case contenant les surfaces des cases des piles et des cases du plateau de jeu.
 * \param[in] char *** map3D : plateau de jeu detaillé.
 * \param[in] char ** pile   : pile du joueur.
 * \param[in] int distance : mode de jeu.
 * 
 * \return int : retourne l'indice si valide et sinon -1.
 * 
 * \author DUPOIS Thomas
 */
int canPlay(int imageIndexP, SDL_Point pointMouse, SDL_Rect ** tableauCase, char *** map3D, char ** pile, int distance);

/**
 * \fn int canEffectDeplacementWithDistance(char *** map3D, char c)
 * 
 * \brief Fonction qui permet de savoir si il existe au moins un déplacement valide pour le joueur quand la distance est réduite de 1.
 * 
 * \param[in] char *** map3D : plateau de jeu detaillé.
 * \param[in] char c : identifiant du joueur.
 * 
 * \return int : retourne 1 si possible sinon 0.
 * 
 * \author DUPOIS Thomas
 */
int canEffectDeplacementWithDistance(char *** map3D, char c);

#endif