#ifndef GRAPHIQUE_H_
#define GRAPHIQUE_H_

/*Fonctions graphique :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

void intro_authors(SDL_Window ** window, SDL_Renderer ** renderer); //creer le fondu initial
void lancementMenu(SDL_Renderer * renderer, SDL_Texture ** textureBackground, SDL_Texture ** textureTableauOptionMenu, int * p_etats, int boolPlayMusic); //lance le menu principale du jeu
void lancementJeu(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint, SDL_Texture ** textureTableauWin, int * p_etatS, SDL_Rect ** tableauCase,  SDL_Texture ** textureTableauPion, char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, int distance);
int affichePileSDL(SDL_Renderer * renderer, SDL_Texture ** textureTableauPiont, point ** tableauDePoint,char ** stackArrayJ1, char ** stackArrayJ2); // texturemapVide pour connaitre la taille
int affichePiontSurPlateau(SDL_Renderer * renderer, SDL_Texture ** textureTableauPiont, point ** tableauDePoint ,char ***  map3D); //affiche les pion sur le plateau de jeu
int affichePionSelect(SDL_Renderer * renderer, point ** tableauDePoint, SDL_Texture ** textureTableauPiont, char *** map3D,int index); // affiche le pion sélectionné par le joueur

#endif