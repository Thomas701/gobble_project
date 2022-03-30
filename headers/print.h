/**
 * \file print.h
 * 
 * \brief Fichier contenant les headers des fonctions permettant d'afficher dans le terminal le plateau et les piles.
 * 
 * \author VILLEPREUX Thibault
 */

#ifndef PRINT_H_
#define PRINT_H_

/**
 * \fn void printMap3dDebug(char *** map)
 * 
 * \brief Fonction qui affiche dans le terminal le plateau de jeu détaillé.
 * 
 * \param[in] char *** map : plateau de jeu détaillé à afficher.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void printMap3dDebug(char *** map);

/**
 * \fn void printMap2D(char ** map2D)
 * 
 * \brief Fonction qui affiche dans le terminal le plateau de jeu non détaillé.
 * 
 * \param[in] char ** map2D : plateau de jeu non détaillé à afficher.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void printMap2D(char ** map2D);

/**
 * \fn void printStacks(char ** stacksArray)
 * 
 * \brief Fonction qui affiche dans le terminal les piles du joueur.
 * 
 * \param[in] char ** map2D : piles du joueur à afficher.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void printStacks(char ** stacksArray);

#endif