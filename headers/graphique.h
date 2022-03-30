/**
 * \file graphique.h
 * 
 * \brief Fichier contenant les headers des fonctions graphiques. Elles gèrent le chargement des images (initialisations) et leurs affichagent.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

#ifndef GRAPHIQUE_H_
#define GRAPHIQUE_H_

/**
 * \fn SDL_Texture * loadImage(const char * path, SDL_Renderer *renderer)
 * \brief Fonction qui va permmetre de transformer une image (n'importe quel format valide) en texture.
 *  
 * \param[in] const char * path : prend le chemin de l'image à charger.
 * \param[in] SDL_Renderer *renderer : associe la texture créer à un renderer.
 * 
 * \return SDL_Texture * : Retourne un pointeur vers la texture à manipuler.
 * \return NULL : Si chemin d'accès invalide ou erreur allocation texture à cause de SDL_CreateTextureFromSurface (message d'erreur qui prévient)
 * 
 * \author VILLEPREUX Thibault
 */
SDL_Texture * loadImage(const char * path, SDL_Renderer *renderer);

/**
 * \fn void intro_authors(SDL_Renderer ** renderer)
 * \brief Fonction lance l'animation de début avec le nom des participants et le logo ISIMA avec fondu transparent.
 *  
 * \param[in] SDL_Renderer ** renderer : Rendu ou l'on colle l'image d'animation.
 * 
 * \return void : Pas de valeur de retour.
 * 
 * \author VILLEPREUX Thibault
 */
void intro_authors(SDL_Renderer ** renderer);

/**
 * \fn void lancementMenu(SDL_Renderer * renderer, SDL_Texture ** textureBackground, SDL_Texture ** textureTableauOptionMenu, int * p_etats, int boolPlayMusic)
 * \brief Fonction qui gère lorsque le joueur se trouve dans le menu principale.\n
 * 
 * Il peut lancer une partie 1VS1, 1VSIA, quitter le jeu (autre que par la croix rouge) ou couper et rejouer le son.
 *  
 * \param[in] SDL_Renderer ** renderer : rendu ou l'on colle les images.
 * \param[in] SDL_Texture ** textureBackground : Tableau de texture d'images qui va contenir les 400 images d'animations.
 * \param[in] SDL_Texture ** textureTableauOptionMenu :  Tableau de texture des images des options menu (1VS1, 1VSIA, SOUN , QUIT GAME)
 * \param[in] int * p_etats : pointeur permettant de connaître l'état du programme (en game, en pause)
 * \param[in] int boolPlayMusic : permet de savoir si on joue de la musique ou pas.
 * 
 * \return void : Pas de valeur de retour.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
void lancementMenu(SDL_Renderer * renderer, SDL_Texture ** textureBackground, SDL_Texture ** textureTableauOptionMenu, int * p_etats, int boolPlayMusic);

/**
 * \fn void lancementJeu1VS1(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint, SDL_Texture ** textureTableauWin, int * p_etatS, SDL_Rect ** tableauCase,  SDL_Texture ** textureTableauPion , char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, int distance)
 * \brief Fonction qui lance la partie Homme VS Homme.
 * 
 * Elle appelle gameOptionGraphique qui joue la partie et ensuite elle affiche le vainquer et réinitialise plateau et pile pour prochaine partie.
 *  
 * \param[in] SDL_Renderer ** renderer : rendu ou l'on colle les images.
 * \param[in] SDL_Texture ** tableauTextureMapVide : tableau de texture d'images qui contient map vide bleau ou rouge selon le tour du joueur.
 * \param[in] point ** tableauDePoint :  tableau de point pour gérer l'affichage des pions.
 * \param[in] SDL_Texture ** textureTableauWin : tableau de texture, contient les images de victoires avec lignes gagnantes éclairées.
 * \param[in] int * p_etatS : pointeur permettant de connaître l'état du programme (en game, en pause)
 * \param[in] SDL_Rect ** tableauCase : tableau de case / surface pour gérer l'affichage des pions et leurs sélections.
 * \param[in] SDL_Texture ** textureTableauPion : tableau de texture, contient les images des pions sélectionnés et non selectionnés.
 * \param[in] char *** map3D : contient la map du jeu détaillé.
 * \param[in] char **  map2D : contient la map du jeu non détaillé.
 * \param[in] char ** pileJ1 : contient la pile du joueur 1.
 * \param[in] char ** pileJ2 : contient la pile du joueur 2.
 * \param[in] int deplacement : option de jeu avec deplacement restreins ou non .
 *
 * \return void : Pas de valeur de retour.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
void lancementJeu1VS1(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint, SDL_Texture ** textureTableauWin, int * p_etatS, int boolPlayMusic, SDL_Texture ** textureTableauOptionMenu, SDL_Rect ** tableauCase,  SDL_Texture ** textureTableauPion , char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, int distance, char * c);

/**
 * \fn int affichePileSDL(SDL_Renderer * renderer, SDL_Texture ** textureTableauPion, point ** tableauDePoint,char ** stackArrayJ1, char ** stackArrayJ2)
 * \brief Fonction qui affiche les piles des joueurs en interface graphique.
 * 
 * \param[in] SDL_Renderer ** renderer : rendu ou l'on colle les images.
 * \param[in] SDL_Texture ** textureTableauPion : tableau de texture, contient les images des pions sélectionnés et non selectionnés.
 * \param[in] point ** tableauDePoint :  tableau de point pour gérer l'affichage des pions.
 * \param[in] char ** stackArrayJ1 : contient la pile du joueur 1.
 * \param[in] char ** stackArrayJ2 : contient la pile du joueur 2.
 *
 * \return int : Retourne 0 si succès et sinon -1.
 * 
 * \author VILLEPREUX Thibault
 */
int affichePileSDL(SDL_Renderer * renderer, SDL_Texture ** textureTableauPion, point ** tableauDePoint,char ** stackArrayJ1, char ** stackArrayJ2);

/**
 * \fn int affichePionSurPlateau(SDL_Renderer * renderer, SDL_Texture ** textureTableauPion, point ** tableauDePoint ,char ***  map3D)
 * \brief Fonction qui affiche les pions sur la map en interface graphique.
 * 
 * \param[in] SDL_Renderer ** renderer : rendu ou l'on colle les images.
 * \param[in] SDL_Texture ** textureTableauPion : tableau de texture, contient les images des pions sélectionnés et non selectionnés.
 * \param[in] point ** tableauDePoint :  tableau de point pour gérer l'affichage des pions.
 * \param[in] char *** map3D : map detaillé du plateau de jeu.
 *
 * \return int : Retourne 0 si succès et sinon -1.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
int affichePionSurPlateau(SDL_Renderer * renderer, SDL_Texture ** textureTableauPion, point ** tableauDePoint ,char ***  map3D, int index);

/**
 * \fn int affichePionSelect(SDL_Renderer * renderer, point ** tableauDePoint, SDL_Texture ** textureTableauPion, char *** map3D,int index)
 * \brief Fonction qui affiche le pion sélectionné sur la map en interface graphique.
 * 
 * \param[in] SDL_Renderer ** renderer : rendu ou l'on colle les images.
 * \param[in] point ** tableauDePoint :  tableau de point pour gérer l'affichage des pions.
 * \param[in] SDL_Texture ** textureTableauPion : tableau de texture, contient les images des pions sélectionnés et non selectionnés.
 * \param[in] char *** map3D : map detaillé du plateau de jeu.
 * \param[in] int index : contient l'identifiant de la case du pion qui a été selectionné.
 * 
 * \return int : Retourne 0 si succès et sinon -1.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
int affichePionSelect(SDL_Renderer * renderer, point ** tableauDePoint, SDL_Texture ** textureTableauPion, char *** map3D,int index);

/**
 * \fn int printMapEmptySDL(SDL_Texture * textureMapVide, SDL_Renderer * renderer)
 * 
 * \brief Fonction qui affiche en interface graphique la map sans pion.
 * 
 * \param[in] SDL_Texture * textureMapVide : map graphique à afficher.
 * \param[in] SDL_Renderer * renderer : rendu ou l'on mets l'image que l'on charge.
 * 
 * \return int : retourne 0 si succès sinon -1.
 * 
 * \author VILLEPREUX Thibault
 */
int printMapEmptySDL(SDL_Texture * textureMapVide, SDL_Renderer * renderer);

int transition(SDL_Renderer * renderer,  SDL_Texture ** textureTableauPiont, point ** tableauDePoint, char *** map3D, int dep, int end, SDL_Texture ** tableauTextureMapVide, char c, char ** pileJ1, char ** pileJ2, int indicePionWhoEat);
int affichePionOnCase(SDL_Renderer * renderer,  SDL_Texture ** textureTableauPiont, point ** tableauDePoint, int index, int indicePion);
void pause(SDL_Renderer * renderer, SDL_Texture ** textureTableauOptionMenu, int * p_etats, int boolPlayMusic, SDL_Texture ** tableauTextureMapVide, SDL_Texture ** textureTableauPion, point ** tableauDePoint ,char ***  map3D);

#endif