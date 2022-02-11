#ifndef FONCTION_H_
#define FONCTION_H_

#define N 3                                      // taille de la map +  taille d'une pile
/*Fonctions essentielles map :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

char *** createMap();     		                   // créer une map
void initMap(char *** );       	                 // initialise la map, toutes les cases sont vides
void freeMap(char *** );		                     // libere map
void printMapDebug(char *** );	                 // affiche map detaillée avec toutes les pieces

void printMap2D(char ** );                       // affiche map2D, vu des joueurs
char ** createMap2D();                           // créer   map2D, vu des joueurs
void  initMap2D(char ** , char *** );            // init map2D grace à 3D, arg d'abord une map2D puis 3D
void freeMap2D(char ** );                        // libere map2D


int canMoove(char ***, int, int);                // Renvoie 1 ou 0 selon si le joueur a le droit de déplacer un pion d'une position A à une position B
int moove(char ***, int posDep, int posEnd);     // Déplace un pion sur la map
int check_End_Game(char *** );                   // Renvoie 1 ou 0 selon si la partie est terminé ou pas (à améliorer pour plus tard)



/*Fonctions d'erreur pour eviter la répétition :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void errorInCreate3D();                           // erreur allocation + exit
void errorInCreate2D();                           // erreur allocation + exit


#endif