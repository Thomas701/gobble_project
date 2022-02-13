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
  char ** pileJ1 = createStack('b');
  char ** pileJ2 = createStack('n');
  char *** map3D = createMap();
  char ** map2D = createMap2D();
  initMap(map3D);
  initMap2D(map2D, map3D);
  int tour = 0;
  char c;
  
  while (!check_End_Game(map3D))
  {
    c = (tour % 2 == 0) ? 'b' : 'n';
    if (c == 'b')
      gameOption(pileJ1, map3D, map2D, c);
    else
      gameOption(pileJ2, map3D, map2D, c);
    tour++;
  }
  if (count_pion(map3D, N, 'b'))
    printf("Le joueur 1 a gagne!\n");
  else
    printf("Le joueur 2 a gagne!\n");

  freeMap(map3D);
  freeMap2D(map2D);
  freeStack(pileJ1);
  freeStack(pileJ2);

  char ** map2D1 = createMap2D();
  char ** map2D2 = createMap2D();
  char ** map2D3 = createMap2D();
  char ** map2D4 = createMap2D();
  char ** map2D5 = createMap2D();
  char ** map2D6 = createMap2D();
  freeMap2D(map2D1);
  freeMap2D(map2D2);
  freeMap2D(map2D3);
  freeMap2D(map2D4);
  freeMap2D(map2D5);
  freeMap2D(map2D6);
  
  return EXIT_SUCCESS;
}
