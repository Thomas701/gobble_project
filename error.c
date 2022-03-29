#include "fonction.h"

/*Fonctions d'erreur pour eviter la répétition  :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void errorInCreatePile() 
{
    perror("ERROR ALLOCATION MEMORY in createPile\n");
    exit(EXIT_FAILURE);
}

void errorInCreate3D() 
{
    perror("ERROR ALLOCATION MEMORY in createMap\n");
    exit(EXIT_FAILURE);
}

void errorInCreate2D() 
{
    perror("ERROR ALLOCATION MEMORY in createMap2D\n");
    exit(EXIT_FAILURE);
}