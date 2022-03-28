/**
 * \file free.h
 * 
 * \brief Fichier contenant les headers des fonctions permettant de free de nos structures de données commes les piles, plateaux, tableaux, textures.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

#ifndef FREE_H_
#define FREE_H_

/**
 * \fn void vider_buffer(void) 
 * 
 * \brief Fonction permettant de vider le buffer afin d'éviter les bugs dans les scanf.
 * 
 * \param[in] void : Pas de paramètre.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author DUPOIS Thomas
 */
void vider_buffer(void);

/**
 * \fn void freeTabCase(SDL_Rect ** tableauCase)
 * 
 * \brief Fonction permettant de free le tableau de case (cases = surfaces (x/y et weidth/height) des cases du plateau et des piles en 3*3).
 * 
 * \param[in] SDL_Rect ** tableauCase : le tableau à free.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void freeTabCase(SDL_Rect ** tableauCase);

/**
 * \fn void freeMap(char *** map)
 * 
 * \brief Fonction permettant de free le plateau de jeu détaillé.
 * 
 * \param[in] char *** map : plateau de jeu à free.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void freeMap(char *** map);

/**
 * \fn void freeMap2D(char ** map2D)
 * 
 * \brief Fonction permettant de free le plateau de jeu non détaillé.
 * 
 * \param[in] char ** map2D : plateau de jeu non detaillé à free.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void freeMap2D(char ** map2D);

/**
 * \fn void freeStack(char ** stackArray)
 * 
 * \brief Fonction permettant de free les piles d'un joueur.
 * 
 * \param[in] har ** stackArray : pile du joueur à free.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void freeStack(char ** stackArray);

/**
 * \fn void freeSDL(SDL_Window * window, SDL_Renderer * renderer, Mix_Music * mainMusic, SDL_Texture ** textureTableauPion, SDL_Texture **  tableauTextureMapVide, SDL_Texture ** textureTableauOptionMenu,SDL_Texture ** textureBackground, point ** tableauDePoint, SDL_Surface * icones, SDL_Rect ** tableauCase)
 * 
 * \brief Fonction permettant de free les textures, misiques, rendu, fenêtre de la SDL.
 * 
 * \param[in] SDL_Window * window : fenêtre principale à free.
 * \param[in] SDL_Renderer * renderer : rendu principal à free.
 * \param[in] Mix_Music * mainMusic : musique principale à free.
 * \param[in] SDL_Texture ** textureTableauPion : tableau de texture de pion à free.
 * \param[in] SDL_Texture **  tableauTextureMapVide : tableau de texture de map vide à free.
 * \param[in] SDL_Texture ** textureTableauOptionMenu : tableau de texture des options du menu principal à free.
 * \param[in] SDL_Texture ** textureBackground : tableau de texture des images de l'animation du menu principal à free.
 * \param[in] point ** tableauDePoint : tableau des points à free.
 * \param[in] SDL_Surface * icones : logo du programme à free.
 * \param[in] SDL_Rect ** tableauCase : tableau des cases à free.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void freeSDL(SDL_Window * window, SDL_Renderer * renderer, Mix_Music * mainMusic, SDL_Texture ** textureTableauPion, SDL_Texture **  tableauTextureMapVide, SDL_Texture ** textureTableauOptionMenu,SDL_Texture ** textureBackground, point ** tableauDePoint, SDL_Surface * icones, SDL_Rect ** tableauCase);
#endif