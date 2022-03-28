/**
 * \file saveFile.h
 * 
 * \brief Fichier contenant les headers des fonctions permettant d'écrire et lire les maps et piles dans des fichiers. On ne les utilise pas.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

#ifndef SAVEFILE_H_
#define SAVEFILE_H_

/**
 * \fn void writeFile(char *** map3D)
 * 
 * \brief Fonction qui écrit le plateau de jeu détaillé dans un fichier "map.txt".
 * 
 * \param[in] char *** map : plateau de jeu détaillé à ecrire dans le fichier.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author VILLEPREUX Thibault
 */
void writeFile(char *** map3D);

/**
 * \fn char ***  readFile3D(char  * nameFile)
 * 
 * \brief Fonction qui lit le plateau de jeu détaillé dans un fichier.
 * 
 * \param[in] char  * nameFile) : nom du fichier où lire.
 * 
 * \return char *** : retourne la map3D detaillé. Attention il y a un malloc dans cette fonction donc libérer le tableau si utilisation.
 * 
 * \author VILLEPREUX Thibault
 */
char ***  readFile3D(char  * nameFile);

/**
 * \fn char **  readFile3D(char  * nameFile)
 * 
 * \brief Fonction qui lit le plateau de jeu non détaillé dans un fichier.
 * 
 * \param[in] char  * nameFile : nom du fichier où lire.
 * 
 * \return char ** : retourne la map2D non detaillé. Attention il y a un malloc dans cette fonction donc libérer le tableau si utilisation.
 * 
 * \author VILLEPREUX Thibault
 */
char **  readFile2D(char  * nameFile);

/**
 * \fn void writeFilePile(char ** pile1, char ** pile2)
 * 
 * \brief Fonction qui écrit les piles des joueurs dans un fichier "pile.txt".
 * 
 * \param[in] char  * nameFile : nom du fichier où lire.
 * \param[in] char ** pile1 : pile du joueur1 que l'on doit écrire dans le fichier.
 * \param[in] char ** pile2 : pile du joueur2 que l'on doit écrire dans le fichier.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author DUPOIS Thomas
 */
void writeFilePile(char ** pile1, char ** pile2);

/**
 * \fn void readFilePile(char * nameFile, char ** pile1, char ** pile2)
 * 
 * \brief Fonction qui lit les piles des joueurs dans un fichier.
 * 
 * \param[in] char ** pile1 : pile du joueur1 que l'on doit lire dans le fichier.
 * \param[in] char ** pile2 : pile du joueur2 que l'on doit lire dans le fichier.
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author DUPOIS Thomas
 */
void readFilePile(char * nameFile, char ** pile1, char ** pile2) ;

#endif