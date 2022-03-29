#ifndef GRAPHIQUE_H_
#define GRAPHIQUE_H_

/*Fonctions graphique :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

void intro_authors(SDL_Window ** window, SDL_Renderer ** renderer); //creer le fondu initial
void lancementMenu(SDL_Renderer * renderer, SDL_Texture ** textureBackground, SDL_Texture ** textureTableauOptionMenu, int * p_etats, int boolPlayMusic); //lance le menu principale du jeu
void lancementJeu(SDL_Renderer * renderer, SDL_Texture ** tableauTextureMapVide, point ** tableauDePoint, SDL_Texture ** textureTableauWin, int * p_etatS, int boolPlayMusic, SDL_Texture ** textureTableauOptionMenu, SDL_Rect ** tableauCase,  SDL_Texture ** textureTableauPiont , char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, int distance, char * c);
int affichePileSDL(SDL_Renderer * renderer, SDL_Texture ** textureTableauPiont, point ** tableauDePoint,char ** stackArrayJ1, char ** stackArrayJ2); // texturemapVide pour connaitre la taille
int affichePiontSurPlateau(SDL_Renderer * renderer, SDL_Texture ** textureTableauPiont, point ** tableauDePoint ,char ***  map3D, int index); //affiche les pion sur le plateau de jeu
int affichePionSelect(SDL_Renderer * renderer, point ** tableauDePoint, SDL_Texture ** textureTableauPiont, char *** map3D,int index); // affiche le pion sélectionné par le joueur
int transition(SDL_Renderer * renderer,  SDL_Texture ** textureTableauPiont, point ** tableauDePoint, char *** map3D, int dep, int end, SDL_Texture ** tableauTextureMapVide, char c, char ** pileJ1, char ** pileJ2, int indicePionWhoEat);
int affichePionOnCase(SDL_Renderer * renderer,  SDL_Texture ** textureTableauPiont, point ** tableauDePoint, int index, int indicePion);
void pause(SDL_Renderer * renderer, SDL_Texture ** textureTableauOptionMenu, int * p_etats, int boolPlayMusic, SDL_Texture ** tableauTextureMapVide, SDL_Texture ** textureTableauPion, point ** tableauDePoint ,char ***  map3D);

#endif