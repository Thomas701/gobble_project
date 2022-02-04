#include <stdio.h>
#include <stdlib.h>
#include "fonction.c"


/*

char 'b' pour joeur blanc ,
char 'n' pour joeur noir  ,
char ' ' pour case vide   ,

*/

int main(int argc, char ** argv)
{

  char *** map = createMap();
  initMap(map);
  printMapDebug(map);
  freeMap(map);

  return EXIT_SUCCESS;
}
