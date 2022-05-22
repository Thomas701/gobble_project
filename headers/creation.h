/**
 * \file creation.h
 * 
 * \brief Fichier contenant les headers des fonctions permettant la créations des piles, plateau, tableau de cases et de coordonées des cases.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
#ifndef CREATION_H_
#define CREATION_H_

/**
 * \fn SDL_Rect ** mallocTab()
 * \brief Permet de créer dynamiquement le tableau de case pour l'interface graphique.
 * 
 * \param[in] void : Ne prend aucun paramètre.
 * 
 * \return SDL_RECT ** : Retourne un tableau de case, chaque case est un pointeur vers une surface.
 * 
 * \author VILLEPREUX Thibault
 */
SDL_Rect ** mallocTab();

/**
 * \fn char ** createStack(char c)
 * \brief Permet de créer dynamiquement les piles de départ d'un joueur avec le caractère c (initialisation + declaration).
 *  
 * \param[in] char c : Caractère que l'on mets dans la pile créer.
 * 
 * \return char ** : Retourne un tableau 2D de char, chaque case est un caractère permettant d'identifier un joueur pendant une partie.
 * \return NULL : **Impossible** car le programme se ferme avant (avec message d'erreur car indispensable pour jouer).
 * 
 * \author VILLEPREUX Thibault
 */
char ** createStack(char c);

/**
 * \fn char *** createMap()
 * \brief Permet de créer dynamiquement **le plateau de jeu détaillé**.
 *  
 * \param[in] void : Ne prend aucun paramètre.
 * 
 * \return char *** : Retourne un tableau 3D de char, chaque case sera un caractère du joueur.
 * \return NULL : **Impossible** car le programme se ferme avant (avec message d'erreur car indispensable pour jouer).
 * 
 * \author VILLEPREUX Thibault
 */
char *** createMap();

/**
 * \fn char ** createMap2D()
 * \brief Permet de créer dynamiquement **le plateau de jeu non détaillé**.
 *  
 * \param[in] void : Ne prend aucun paramètre.
 * 
 * \return char ** : Retourne un tableau 2D de char, chaque case sera un caractère du joueur.
 * \return NULL : **Impossible** car le programme se ferme avant (avec message d'erreur car indispensable pour jouer).
 * 
 * \author VILLEPREUX Thibault
 */
char ** createMap2D();

/**
 * \fn int createPoint(point *** pTableauDePoint)
 * \brief Permet de créer dynamiquement le tableau de point pour l'interface graphique. \n
 * 
 * Chaque case est un pointeur vers un point. Une structure de données créer avant la connaissance de SDL_Point.\n
 * 
 * \param[in] point *** pTableauDePoint : Prend un pointeur vers un tableau de point car va modifier les coordonées de ce dernier.
 * 
 * \return int : Retourne entier pour savoir si tout c'est bien passé. -1 si erreur, 0 sinon
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
int createPoint(point *** pTableauDePoint);

/**
 * \fn int createCase(SDL_Rect *** pTableauCase)
 * \brief Permet de créer dynamiquement le tableau de case pour l'interface graphique. \n
 * 
 * Chaque case du tableau est un pointeur vers un case de la map.\n
 * 
 * \param[in] SDL_Rect *** pTableauCase : Prend un pointeur vers un tableau de case car va modifier les coordonées de ce dernier.
 * 
 * \return int : Retourne entier pour savoir si tout c'est bien passé. -1 si erreur, 0 sinon
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
int createCase(SDL_Rect *** pTableauCase);

#endif