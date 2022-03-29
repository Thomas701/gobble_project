/**
 * \file error.h
 * 
 * \brief Fichier contenant les headers des fonctions d'erreurs (affiches messages et quitte le programme).
 * 
 * \author VILLEPREUX Thibault
 */

#ifndef ERROR_H_
#define ERROR_H_

/**
 * \fn void errorInCreatePile()
 * \brief Affiche erreur et quitte le programme (appeler si erreur lors de la création d'une pile).
 * 
 * \param[in] void : Ne prend aucun paramètre.
 * 
 * \return void: aucun retour.
 * 
 * \author VILLEPREUX Thibault
 */
void errorInCreatePile();

/**
 * \fn void errorInCreate3D()
 * \brief Affiche erreur et quitte le programme (appeler si erreur lors de la création du plateau de jeu detaillé).
 * 
 * \param[in] void : Ne prend aucun paramètre.
 * 
 * \return void: aucun retour.
 * 
 * \author VILLEPREUX Thibault
 */
void errorInCreate3D();

/**
 * \fn void errorInCreate2D() 
 * \brief Affiche erreur et quitte le programme (appeler si erreur lors de la création du plateau de jeu non detaillé).
 * 
 * \param[in] void : Ne prend aucun paramètre.
 * 
 * \return void: aucun retour.
 * 
 * \author VILLEPREUX Thibault
 */
void errorInCreate2D();

#endif