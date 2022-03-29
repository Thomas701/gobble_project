#ifndef SAVEFILE_H_
#define SAVEFILE_H_

/*Fonctions lecture/ecriture fichiers  :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*--[ATTENTION AU MALLOC BORDEL!!!]--*/ /* return map2D Attention malloc ici, il faut libérer char ** */ 
void writeFile(char *** map3D); //ecrit la map dans un fichier
char ***  readFile3D(char  * nameFile); // lit le fichier map 3D
char **  readFile2D(char  * nameFile); // lit le fichier map 2D
void writeFilePile(char ** pile1, char ** pile2); // ecrit l'etat des piles dans un fichier
void readFilePile(char * nameFile, char ** pile1, char ** pile2); // lit l'etat des piles dans un fichier

#endif