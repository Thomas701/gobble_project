/**
 * \file get.h
 * 
 * \brief Fichier contenant les codes des fonctions permettant d'écrire et lire les maps et piles dans des fichiers. On ne les utilise pas.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

#ifndef GET_H_
#define GET_H_

/**
 * \fn int getIndex(SDL_Point pointMouse, SDL_Rect ** tableauCase)
 * 
 * \brief Fonction qui regarde si il y a un clique sur une case plateau ou pile.
 * 
 * \param[in] SDL_Point pointMouse : point de la souris où l'utilisateur à cliquer.
 * \param[in] SDL_Rect ** tableauCase : tableau contenant les surfaces des cases.
 * 
 * \return int :retourne l'indice si pion.
 * 
 * \author DUPOIS Thomas
 */
int getIndex(SDL_Point pointMouse, SDL_Rect ** tableauCase);

/**
 * \fn int sizePionMaxStack(char ** stackArray, int numStack)
 * 
 * \brief Fonction qui regarde la taille maximum d'un pion d'une pile.
 * 
 * \param[in] char ** stackArray : tableau des piles du joueur.
 * \param[in] int numStack : identifiant permettant de connaître la pile du joueur.
 * 
 * \return int :retourne la taille max du pion d'une pile.
 * 
 * \author VILLEPREUX Thibault
 */
int sizePionMaxStack(char ** stackArray, int numStack);

/**
 * \fn int sizePionInStack(char ** stackArray, int numStack)
 * 
 * \brief Fonction qui regarde la taille d'un pion d'une pile.
 * 
 * \param[in] char ** stackArray : tableau des piles du joueur.
 * \param[in] int numStack : identifiant permettant de connaître la pile du joueur.
 * 
 * \return int : retourne -1 si stack est vide sinon 0, 1 ou 2 (taille du pion).
 * 
 * \author VILLEPREUX Thibault
 */
int sizePionInStack(char ** stackArray, int numStack) ;

/**
 * \fn int getSizePionOnCase(char *** map3D, int i, int j)
 * 
 * \brief Fonction qui renvoie la taille du pion sur la case demandé (-1) si pas de pion
 * 
 * \param[in] char ** map3D : map du jeu
 * \param[in] int i : coordonné x
 * \param[in] int j : coordonné y
 * 
 * \return int : renvoie la taille du pion sur la case demandé (-1) si pas de pion
 * 
 * \author DUPOIS Thomas
 */
int getSizePionOnCase(char *** map3D, int i, int j);

/**
 * \fn int getSizePionOnCase2(char *** map3D, int index)
 * 
 * \brief Fonction qui renvoie la taille du pion sur la case demandé (-1) si pas de pion
 * 
 * \param[in] char ** map3D : map du jeu
 * \param[in] int index : index de la map
 * 
 * \return int : renvoie la taille du pion sur la case demandé (-1) si pas de pion
 * 
 * \author DUPOIS Thomas
 */
int getSizePionOnCase2(char *** map3D, int index);

/**
 * \fn char getCaractereOnCase(char *** map3D, int index)
 * 
 * \brief Fonction qui renvoie le caractère du pion sur la case demandé ('0') si pas de pion
 * 
 * \param[in] char ** map3D : map du jeu
 * \param[in] int index : index de la map
 * 
 * \return char : renvoie le caractère du pion sur la case demandé ('0') si pas de pion
 * 
 * \author DUPOIS Thomas
 */
char getCaractereOnCase(char *** map3D, int index);

/**
 * \fn int getIndexPionWhoAreEat(char *** map3D, int index)
 * 
 * \brief Fonction qui renvoie la taille du pion mangé (-1) si aucun pion n'est mangé
 * 
 * \param[in] char ** map3D : map du jeu
 * \param[in] int index : index de la map
 * 
 * \return int : renvoie la taille du pion mangé (-1) si aucun pion n'est mangé
 * 
 * \author DUPOIS Thomas
 */
int getIndexPionWhoAreEat(char *** map3D, int index);

/**
 * \fn int getMaxOnTable(int * tab, int size)
 * 
 * \brief Fonction qui renvoie le nombre maximum dans le tableau
 * 
 * \param[in] char ** map3D : map du jeu
 * \param[in] int size : taille du tableau
 * 
 * \return int : renvoie le nombre maximum dans le tableau
 * 
 * \author DUPOIS Thomas
 */
int getMaxOnTable(int * tab, int size);

#endif