/**
 * \file error.c
 * 
 * \brief Fichier contenant les codes des fonctions d'erreurs (affiches messages et quitte le programme).
 * 
 * \author VILLEPREUX Thibault
 */

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
void errorInCreatePile() {
    perror("ERROR ALLOCATION MEMORY in createPile\n");
    exit(EXIT_FAILURE);
}

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
void errorInCreate3D() {
    perror("ERROR ALLOCATION MEMORY in createMap\n");
    exit(EXIT_FAILURE);
}

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
void errorInCreate2D() {
    perror("ERROR ALLOCATION MEMORY in createMap2D\n");
    exit(EXIT_FAILURE);
}