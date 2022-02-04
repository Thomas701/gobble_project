#ifndef FONCTION_H_
#define FONCTION_H_

#define N 3 // taille de la map +  taille d'une pile

/*Fonctions essentielles map :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

char *** createMap();     		      // créer une map
void initMap(char *** );       	    // initialise la map, toutes les cases sont vides
void freeMap(char *** );		        // libere map
void printMapDebug(char *** );	    // affiche map detaillée avec toutes les pieces
int canMoove(char ***, int, int)    // Renvoie 1 ou 0 selon si le joueur a le droit de déplacer un pion d'une position A à une position B
int moove(char *** map, int posDep, int posEnd) // Déplace un pion sur la map
int check_End_Game(char *** map)    // Renvoie 1 ou 0 selon si la partie est terminé ou pas (à améliorer pour plus tard)

/*Fonctions d'erreur pour eviter la répétition :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
void errorInCreate3D(); // erreur allocation


#endif