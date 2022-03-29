#ifndef FONCTION_H_
#define FONCTION_H_

#define N 3                               

struct point
{
  int x, y;
};
typedef struct point point;

/*Fonctions active :
  ~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

int sizePiontMaxStack(char ** stackArray, int numStack); // retourne la taille du pion le plus grand d'une pile
void mooveSinceStack(char *** map, char ** stackArray, int numStack,int sizePiont ,int endPiont, char c); //place un pion sur la map depuis une pile
int moove(char *** map, int posDeb, int posEnd); // déplace un pion présent sur la map
void gameOption(char ** stackArray, char *** map3D,char ** map2D, char c, int deplacement); // Fonction principale du jeu
void gameOptionGraphique(SDL_Renderer * renderer, SDL_Texture **  tableauTextureMapVide, point ** tableauDePoint, SDL_Rect ** tableauCase,  char ** pileJ1, char ** pileJ2, char *** map3D, char ** map2D, int * p_etats, int boolPlayMusic, SDL_Texture ** textureTableauOptionMenu, SDL_Texture ** textureTableauPiont, int distance, char * c); // c = 'b' or 'n' joueur qui choisie
void SGO_demandePileEtDeplacement(char *** map3D, char ** map2D, int * answer); //Demande à l'utilisateur s'il souhaite déplacer ou jouer un nouveau piont tout en exerçant les vérifications adéquates
void SGO_demandeQuelPiontDeplacer(char *** map3D, char ** map2D, int * debPiont); //Demande à l'utilisateur quel piont souhaite-t-il déplacer?
void SGO_verifEtDeplacementCaseSansLimite(char *** map3D, char c, int * debPiont, int * endPiont); // exerce les verification sur le piont selectionne + la case d'arriver sans restriction de distance
void SGO_verifEtDeplacementCaseAvecLimite(char *** map3D, char c, int * debPiont, int * endPiont); // exerce les verification sur le piont selectionne + la case d'arriver avec restriction de distance
void SGO_demanderQuellePileJouer(char *** map3D, char ** map2D, char ** stackArray, int * numStack); // demande à l'utilisateur quelle pile il souhaite jouer
void SGO_demanderQuelPionJouer(char *** map3D, char ** stackArray, int * numStack, int * numPion); // demande à l'utilisateur quel pion souhait-il jouer de puis la pile
void SGO_demanderQuelleCaseJouerPion(char *** map3D, int * numPion, int * endPiont); // demande à l'utilisateur sur quelle case il souhaite placer son pion depuis sa pile
void loadAndPlayMainMusic(Mix_Music ** mainMusic, SDL_Rect ** tableauCase);
int getIndex(SDL_Point pointMouse, SDL_Rect ** tableauCase);

#endif
