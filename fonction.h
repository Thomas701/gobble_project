#ifndef FONCTION_H_
#define FONCTION_H_

#define N 3 // taille de la map +  taille d'une pile

/*Fonctions essentielles map :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

char *** createMap();     		// créer une map
void initMap(char *** );       	// initialise la map, toutes les cases sont vides
void freeMap(char *** );		// libere map
void printMapDebug(char *** );	// affiche map detaillé avec toutes les pieces




/*Fonctions d'erreur pour eviter la répétition :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void errorInCreate3D(); // erreur allocation


#endif