/**
 * \file fonction.h
 * 
 * \brief Fichier contenant les headers des fonctions "actives" liées aux mouvement des pions.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

#ifndef FONCTION_H_
#define FONCTION_H_

/**
 * \struct point
 * \brief Objet représentant un point (x,y).\n
 * 
 * La structures a été créée avant la découverte de SDL_Point, donc certaines fonctions l'utilisent.\n
 * Elle est composée de 2 champs, un entier pour la cooredonnée x et un autre int pour la coordonnée y.
 */
typedef struct point {
  int x, y;
} point;

/*Fonctions active:
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/**
 * \fn void mooveSinceStack(char *** map, char ** stackArray, int numStack,int sizePion ,int endPion, char c)
 * \brief Permet de placer le pion sur la map. Il faut d'abord vérifier si le coup est valide.
 * 
 * \param[in] char *** map : plateau de jeu détaillé
 * \param[in] char ** stackArray : pile du joueur qui déplace
 * \param[in] int numStack : numéro de la pile du joueur (exemple si 3*3 seulement 2 piles donc numéro 0 ou 1)
 * \param[in] int sizePion : taille du pion à déplacer(permet de l'identifier au sein de la pile)
 * \param[in] int endPion  : position sur la map ou il faut mettre le pion (entre 0 et 8 si 3*3)
 * \param[in] char c       : lettre qu'il faut mettre sur la map, soit 'b' si joueur 1, sinon 'n'
 * 
 * \return Pas de retour (void).
 * 
 * \author DUPOIS Thomas & VILLEPREUX Thibault
 */ 
void mooveSinceStack(char *** map, char ** stackArray, int numStack, int sizePion ,int endPion, char c);


/**
 * \fn int moove(char *** map, int posDeb, int posEnd)
 * \brief Permet de déplacer un pion se trouvant sur la map.\n
 * 
 * Il faut vérifié avant si le déplacement est valide, mais sur-vérification grâce à canMoove().
 * 
 * \param[in] char *** map : plateau de jeu détaillé
 * \param[in] int posDeb   : position de départ du pion (entre 0 et 8 si 3*3)
 * \param[in] int posEnd   : position d'arriver du pion (entre 0 et 8 si 3*3)
 * 
 * \return 1 si on a réussi a mettre le pion sur la map
 * \retrun 0 si déplacement non valide (canMoove) ou si erreur lors de l'insertion (n'arrive jamais).
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */ 
int moove(char *** map, int posDeb, int posEnd); // déplace un pion présent sur la map

/**
 * \fn gameOption(char ** stackArray, char *** map3D, char ** map2D, char c, int deplacement)
 * \brief Fonction principale qui demande à un joueur son action et qui l'éxécute sur la map.
 * 
 * \param[in] char ** stackArray :  tableau des piles des 2 joueurs
 * \param[in] char *** map3D     : plateau de jeu détaillé
 * \param[in] char **  map2D     : plateau de jeu non détaillé
 * \param[in] char c             : permet d'identifier le joueur qui doit jouer
 * \param[in] int deplacement    : Mode de jeu, pas de restriction de voisin deplacement = 0, sinon deplacement = 1
 * 
 * \return Pas de retour (void).
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */ 
void gameOption(char ** stackArray, char *** map3D, char ** map2D, char c, int deplacement); // Fonction principale du jeu


/**
 * \fn void gameOptionGraphique(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint, SDL_Rect ** tableauCase, char ** pileJ1, char ** pileJ2, char *** map3D, char ** map2D, int * p_etats, SDL_Texture ** textureTableauPion, int distance)
 * \brief Fonction principale qui demande à un joueur son action et qui l'éxécute sur la map.
 * 
 * \param[in] SDL_Renderer * renderer : renderer principale, sur lequel ou on colle les images du plateau / pions...
 * \param[in] SDL_Texture ** tableauTextureMapVide : pour afficher la map vide avec couleur (couleur pour indiquer le tour du joueur)
 * \param[in] point ** tableauDePoint : contient les coordonnées des cases su plateau + pile
 * \param[in] SDL_Rect ** tableauCase : contient les surfaces des cases su plateau + pile
 * \param[in] char ** pileJ1 : contient les spiles du joueur 1
 * \param[in] char ** pileJ2 : contient les spiles du joueur 2
 * \param[in] char *** map3D : plateau de jeu detaillé
 * \param[in] char **  map2D : plateau de jeu non-detaillé
 * \param[in] int * p_etats  : état de la partie, victoire / menu / entrain de jouer
 * \param[in] SDL_Texture ** textureTableauPion : contient les images de pions
 * \param[in] int deplacement    : Mode de jeu, pas de restriction de voisin deplacement = 0, sinon deplacement = 1
 * 
 * \return Pas de retour (void).
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */ 
void gameOptionGraphique(SDL_Renderer * renderer, SDL_Texture **  tableauTextureMapVide, point ** tableauDePoint, SDL_Rect ** tableauCase,  char ** pileJ1, char ** pileJ2, char *** map3D, char ** map2D, int * p_etats, SDL_Texture ** textureTableauPion, int distance);
#endif