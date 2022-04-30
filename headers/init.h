/**
 * \file init.h
 * 
 * \brief Fichier contenant les headers des fonctions permettant l'initialisation de nos structures de données commes les piles, plateaux, tableaux, textures.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

#ifndef INIT_H_
#define INIT_H_

/**
 * \fn void initMap(char *** map)
 * 
 * \brief Fonction qui initialise le plateau de jeu detaillé (3D) avec que des cases vides ('0').
 * 
 * \param[in] char *** map : Contient le plateau de jeu que l'on va modifier.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void initMap(char *** map);

/**
 * \fn void initMap2D(char ** map2D, char *** map3D)
 * 
 * \brief Fonction qui initialise le plateau de jeu non detaillé (2D) avec les case de la map3D.\n
 * 
 * Elle effectue un premier parcours pour mettre toutes les cases à '0' puis parcours la map3D et si pion rencontré, elle l'écrit dans la map 2D.
 * 
 * \param[in] char **  map2D : Contient le plateau de jeu non detaillé ou l'on va mettre les valeurs de map3D.
 * \param[in] char *** map3D : Contient le plateau de jeu detaillé que l'on va copier.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void initMap2D(char ** map2D, char *** map3D);

/**
 * \fn void initPile(char ** pile, char c)
 * 
 * \brief Fonction qui initialise les piles du joueur à son caractère identifiant (b ou n). 
 * 
 * \param[in] char **  pile : contient les piles du joueur.
 * \param[in] char c : identifiant du joueur.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void initPile(char ** pile, char c);

/**
 * \fn int loadTextureOptionMenu(SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu)
 * 
 * \brief Fonction qui charge les images des options menu.
 * 
 * \param[in] SDL_Renderer ** renderer : Rendu principale du jeu.
 * \param[in] SDL_Texture *** ptextureTableauOptionMenu : pointeur sur tableau qui va contenir les images des options.
 * 
 * \return int : Retourne -1 si erreur, sinon 0
 * 
 * \author VILLEPREUX Thibault
 */
int loadTextureOptionMenu(SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu);

/**
 * \fn int initialiseDebutProgramme(SDL_Window ** window, SDL_Texture *** textureBackground, SDL_Texture *** ptableauTextureMapVide, SDL_Surface ** icones, SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu, SDL_Texture *** pTextureTableauPion, SDL_Texture *** pTextureTableauWin, point *** pTableauDePoint, SDL_Rect *** pTableauCase)
 * 
 * \brief Fonction qui initialise toutes la partie SDL images + audio. Et qui initialise les tableaux de texture (pions, maps) et le tableau de point et de case. 
 * 
 * \param[in] SDL_Window ** window : fenêtre principale de notre jeu
 * \param[in] SDL_Texture *** textureBackground : contient les images d'animations du menu (celle des 400 images).
 * \param[in] SDL_Texture *** ptableauTextureMapVide : contient les images des maps vide (vert / bleu / rouge).
 * \param[in] SDL_Surface ** icones : contient l'image de l'icone du programme.
 * \param[in] SDL_Renderer ** renderer : rendu principale du jeu.
 * \param[in] SDL_Texture *** ptextureTableauOptionMenu : contient les textures des options du menu principale .
 * \param[in] SDL_Texture *** pTextureTableauPion : contient les textures des pions normals et sélectionnés.
 * \param[in] SDL_Texture *** pTextureTableauWin : contient les textures des map où les lignes sont colorés (en cas de victoire où égalité).
 * \param[in] point *** pTableauDePoint : contient les points des cases du plateau et piles.
 * \param[in] SDL_Rect *** pTableauCase : contient les surfaces des cases du plateau et piles.
 * 
 * \return int : Retourne 0 si bien passé, sinon -1. La gestion pour quitter le programme ne se fait pas ici car il faut libérer proprement la mémoire.
 * 
 * \author VILLEPREUX Thibault
 */
int initialiseDebutProgramme(SDL_Window ** window, SDL_Texture *** textureBackground, SDL_Texture *** ptableauTextureMapVide, SDL_Surface ** icones, SDL_Renderer ** renderer, SDL_Texture *** ptextureTableauOptionMenu, SDL_Texture *** pTextureTableauPion, SDL_Texture *** pTextureTableauWin, point *** pTableauDePoint, SDL_Rect *** pTableauCase);

/**
 * \fn int loadTextureTableauMap(SDL_Renderer ** renderer, SDL_Texture *** ptableauTextureMapVide)
 * 
 * \bref Fonction qui charge les images des map vides (vert/rouge/bleu).
 * 
 * \param[in] SDL_Renderer ** renderer : Rendu principale du jeu.
 * \param[in] SDL_Texture *** ptableauTextureMapVide : pointeur sur tableau qui va contenir les images des map vides (vert/rouge/bleu).
 * 
 * \return int : Retourne -1 si erreur, sinon 0
 * 
 * \author VILLEPREUX Thibault
 */
int loadTextureTableauMap(SDL_Renderer ** renderer, SDL_Texture *** ptableauTextureMapVide);

/**
 * \fn int loadPion(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauPion)
 * 
 * \bref Fonction qui charge les images des pions normals et sélectionnés.
 * 
 * \param[in] SDL_Renderer ** renderer : Rendu principale du jeu.
 * \param[in] SDL_Texture *** pTextureTableauPion : pointeur sur tableau qui va contenir les images des pions normals et sélectionnés.
 * 
 * \return int : Retourne -1 si erreur, sinon 0
 * 
 * \author VILLEPREUX Thibault
 */
int loadPion(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauPion);

/**
 * \fn int loadBackgroundMenu(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauBack)
 * 
 * \bref Fonction qui charge les 400 images de l'animation du menu.
 * 
 * \param[in] SDL_Renderer ** renderer : Rendu principale du jeu.
 * \param[in] SDL_Texture *** pTextureTableauBack : pointeur sur tableau qui va contenir les 400 images de l'animation du menu.
 * 
 * \return int : Retourne -1 si erreur, sinon 0
 * 
 * \author DUPOIS Thomas
 */
int loadBackgroundMenu(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauBack);

/**
 * \fn int loadTextureWin(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauWin)
 * 
 * \brief Fonction qui charge les images des lignes coloré (en cas de victoire ou égalité).
 * 
 * \param[in] SDL_Renderer ** renderer : Rendu principale du jeu.
 * \param[in] SDL_Texture *** pTextureTableauWin : pointeur sur tableau qui va contenir les images des lignes coloré (en cas de victoire ou égalité).
 * 
 * \return int : Retourne -1 si erreur, sinon 0
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
int loadTextureWin(SDL_Renderer ** renderer, SDL_Texture *** pTextureTableauWin);

/**
 * \fn void loadAndPlayMainMusic(Mix_Music ** mainMusic)
 * 
 * \brief Fonction qui charge et joue la musique principale.
 * 
 * \param[in] Mix_Music ** mainMusic : contient la musique principale du jeu.
 * 
 * \return void : Pas de type de retour.
 * 
 * \author VILLEPREUX Thibault
 */
void loadAndPlayMainMusic(Mix_Music ** mainMusic);

/**
 * \fn void initTableauCase(SDL_Rect ** tableauCase)
 * 
 * \brief Fonction qui initialise (attention ne créée pas) toutes les cases/surfaces en 3*3.
 * 
 * \param[in] SDL_Rect ** tableauCase : contient les surfaces (x/y et weidth/height) des cases du plateau et des piles en 3*3.
 * 
 * \return void : Pas de type de retour.
 * 
 * \author VILLEPREUX Thibault
 */
void initTableauCase(SDL_Rect ** tableauCase);
#endif