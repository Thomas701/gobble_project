#include <stdio.h>
#include <stdlib.h>
#include "fonction.c"


/*

char 'b' pour joeur blanc ,
char 'n' pour joeur noir  ,
char '0' pour case vide   ,

*/


int main(int argc, char ** argv)
{

  char *** map3D = createMap();
  initMap(map3D);

  map3D[0][0][0] = 'b';
  map3D[0][0][1] = 'n';
  map3D[1][0][0] = 'b';
  map3D[1][1][0] = 'n';
  printMapDebug(map3D);


  char ** map2D = createMap2D();
  initMap2D(map2D, map3D);
  printMap2D(map2D);


  writeFile(map2D);

  char ** map2DBIS = readFile("map.txt");
    printMap2D(map2DBIS);

    play();
    
  freeMap2D(map2D);
  freeMap2D(map2DBIS);
  freeMap(map3D);


  return EXIT_SUCCESS;
}
