/**
 * \file ia.h
 * 
 * \brier Fichier contenant les code des fonctions concernant l'intelligence artificielle
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

#ifndef IA_H
#define IA_H

/**
 * \fn int ** createTabOfCoups()
 * \brief Permet de créer dynamiquement le tableau contenant les coups pouvants être joué par l'IA
 *  
 * \param[in] void : Ne prend aucun paramètre
 * 
 * \return int ** : Retourne un tableau 2D de int, chaque case est un index permettant d'identifier la case de départ et d'arrivé
 * 
 * \author DUPOIS Thomas
 */
int ** createTabOfCoups();

/**
 * \fn void afficheTabOfCoups()
 * \brief Permet d'afficher le tableau contenant les coups pouvants être joué par l'IA
 *  
 * \param[in] int ** tab : tableau de coups possible que l'on doit afficher
 * 
 * \return void : Ne Retourne rien, il s'agit seulement d'un affichage console
 * 
 * \author DUPOIS Thomas
 */
void afficheTabOfCoups(int ** tab);

/**
 * \fn void initTabOfCoups(int ** tab)
 * \brief Permet d'initialiser l'ensemble des cases du tableau à -1
 *  
 * \param[in] int ** tab : tableau de coups possible que l'on doit initialiser
 * 
 * \return void : Ne Retourne rien, il s'agit seulement de remplir un tableau
 * 
 * \author DUPOIS Thomas
 */
void initTabOfCoups(int ** tab);

/**
 * \fn void listTabOfCoups(char *** map3D, char ** stacks, int ** tabOfCoups, char c)
 * \brief Permet de trouver la liste des coups possibles que peux jouer l'IA
 *  
 * \param[in] char *** map3D : map3D représentant la grille du jeu
 * \param[in] char ** stacks : pile du joueur en question
 * \param[in] int ** tabOfCoups : tableau de coups possible 
 * \param[in] char c : correspond au joueur qui joue
 * 
 * \return void : Ne Retourne rien, il s'agit de remplir le tableau
 * 
 * \author DUPOIS Thomas
 */

/**
 * \fn char *** copyMap3D(char *** map3D)
 * \brief Permet de copier la map 3D
 *  
 * \param[in] char *** map3D : map3D a copier
 * 
 * \return void : Retourne la nouvelle map3D copiée
 * 
 * \author DUPOIS Thomas
 */
char *** copyMap3D(char *** map3D);

/**
 * \fn char ** copyMap2D(char ** map2D)
 * \brief Permet de copier la map 2D
 *  
 * \param[in] char ** map2D : map2D a copier
 * 
 * \return void : retourne la nouvelle map2D copiée
 * 
 * \author DUPOIS Thomas
 */
char ** copyMap2D(char ** map2D);

/**
 * \fn char ** copyStack(char ** pile)
 * \brief Permet de copier une pile
 *  
 * \param[in] char ** pile : pile à copié
 * 
 * \return void : retourne la nouvelle pile copiée
 * 
 * \author DUPOIS Thomas
 */
char ** copyStack(char ** pile);

/**
 * \fn void listTabOfCoups(char *** map3D, char ** stacks, int ** tabOfCoups, char c)
 * \brief Permet de trouver la liste des coups possibles que peux jouer l'IA
 *  
 * \param[in] char *** map3D : map3D représentant la grille du jeu
 * \param[in] char ** stacks : pile du joueur en question
 * \param[in] int ** tabOfCoups : tableau de coups possible 
 * \param[in] char c : correspond au joueur qui joue
 * 
 * \return void : Ne Retourne rien, il s'agit de remplir le tableau
 * 
 * \author DUPOIS Thomas
 */
void listTabOfCoups(char *** map3D, char ** stacks, int ** tabOfCoups, char c);

/**
 * \fn void placePionByIa(int ** tab, int bestCoup, char *** map3D, char ** stacks, char c)
 * \brief Place un piont
 *  
 * \param[in] int ** tab : tableau de coups
 * \param[in] int bestCoup : index du coup à jouer
 * \param[in] char *** map3D : map3D représentant la grille du jeu
 * \param[in] char ** stacks : pile du joueur
 * \param[in] char c : correspond au joueur qui joue
 * 
 * \return void : Ne Retourne rien, place un pion
 * 
 * \author DUPOIS Thomas
 */
void placePionByIa(int ** tab, int bestCoup, char *** map3D, char ** stacks, char c);

/**
 * \fn int * play(char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, char c, int ia, int prof, int alphaBeta, int * tableauParam)
 * \brief Fait jouer l'IA
 *  
 * \param[in] char *** map3D : map3D représentant la grille du jeu
 * \param[in] char ** map2D : map2D représentant la grille du jeu en 2D
 * \param[in] char ** pileJ1 : pile du joueur 1
 * \param[in] char ** pileJ2 : pile du joueur 2
 * \param[in] char c : correspond au joueur qui joue
 * \param[in] int ia : = 1 si c'est l'ia qui joue, = 0 si ce n'est pas le cas (agit comme un boolean)
 * \param[in] int prof : correspond à la profondeur de recherche
 * \param[in] int alphaBeta : si on utilise le alpha Beta ou pas
 * \param[in] int * tableauParam : tableau de paramètre de l'IA
 * 
 * \return void : Ne Retourne rien, modifie la map3D et 2D
 * 
 * \author DUPOIS Thomas
 */
int * play(char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, char c, int ia, int prof, int alphaBeta, int * tableauParam);

/**
 * \fn void allFree(char *** map3D, char ** map2D, char ** stacks, char ** stacksOp, int ** tab, liste * l)
 * \brief free l'ensemble des éléments
 *  
 * \param[in] char *** map3D : map3D représentant la grille du jeu
 * \param[in] char ** map2D : map2D représentant la grille du jeu en 2D
 * \param[in] char ** stacks : pile du joueur 1
 * \param[in] char ** stacksOp : pile du joueur 2
 * \param[in] int ** tab : correspond au tableau de coups
 * \param[in] liste * l : correspond à la liste
 * 
 * \return void : Ne Retourne rien, cela free
 * 
 * \author DUPOIS Thomas
 */
void allFree(char *** map3D, char ** map2D, char ** stacks, char ** stacksOp, int ** tab, liste * l);

/**
 * \fn int prediction(int prof, char *** map3D, char ** pileJ1, char ** pileJ2, int ** tabOfCoups, int index, int ia, char c, int alphaBeta, int alpha, int beta, int * tableauParam)
 * \brief Prediction de la meilleur case pour jouer
 *  
 * \param[in] int prof : correspond à la profondeur de recherche dans l'arbre des possibilités
 * \param[in] char *** map3D : map3D représentant la grille du jeu
 * \param[in] char ** map2D : map2D représentant la grille du jeu
 * \param[in] char ** pileJ1 : pile du joueur 1
 * \param[in] char ** pileJ2 : pile du joueur 2
 * \param[in] int ** tablOfCoups : correspond au tableau qui contient les coups possibles
 * \param[in] int index : correspond à l'index choisi à la fonction précédente 
 * \param[in] int ia : = 1 si c'est l'ia qui joue, = 0 si ce n'est pas le cas (agit comme un boolean)
 * \param[in] char c : = 'b' ou 'n' en fonction du joueur qui joue
 * \param[in] int alphaBeta : = savoir si la fonction utilise le alphaBeta ou pas
 * \param[in] int alpha : = le alpha Pere
 * \param[in] int beta : = le beta Pere
 * \param[in] int * tableauParam : tableau paramètre de l'IA
 * 
 * \return void : Ne Retourne rien, modifie la map3D et 2D
 * 
 * \author DUPOIS Thomas
 */
int prediction(int prof, char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, int ** tabOfCoups, int index, int ia, char c, int alphaBeta, int alpha, int beta, int * tableauParam);

/**
 * \fn int evaluation(int * tabParam, char *** map3D, char ** map2D, int ** tabOfCoups, int index, char c, char ** stacks)
 * \brief évalue la grille et ajoute la note des paramètres
 *  
 * \param[in] int * tabParam : tableau contenant les paramètre
 * \param[in] char *** map3D : map3D représentant la grille du jeu
 * \param[in] char ** map2D : map2D représentant la grille du jeu en 2D
 * \param[in] int ** tabOfCoups : tableau des coups
 * \param[in] int index : index d'ou on doit jouer
 * \param[in] char c : caractère du joueur qui joue
 * 
 * \return int : Retourne la note finale
 * 
 * \author DUPOIS Thomas
 */
int evaluation(int * tabParam, char *** map3D, char ** map2D, int ** tabOfCoups, int index, char c, char ** stacks, int ia);

/**
 * \fn int number_pion_gobe(char *** map3D, char c)
 * \brief compte le nombre de pions gobés par le joueur
 *  
 * \param[in] char *** map3D : map 3D
 * \param[in] char c : piont du joueur
 * 
 * \return int : retourne le nombre de pions gobés par le joueur
 * 
 * \author DUPOIS Thomas
 */
int number_pion_gobe(char *** map3D, char c);

/**
 * \fn int countDiff(char ** map2D, char c)
 * \brief compte la différence entre le nombre de pion du joueur et le nombre de pion de l'adversaire posé sur la grille
 *  
 * \param[in] char ** map2D : map 2D
 * \param[in] char c : piont du joueur
 * 
 * \return int : retourne la différence
 * 
 * \author DUPOIS Thomas
 */
int countDiff(char ** map2D, char c);

/**
 * \fn int rdm (int i, int j)
 * \brief renvoie un nombre random entre i et j inclu
 *  
 * \param[in] int i : min
 * \param[in] int j : max
 * 
 * \return int : retourne le chiffre aléatoire entre i et j.
 * 
 * \author DUPOIS Thomas
 */
int rdm (int i, int j);

/**
 * \fn int *generateTab(int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10, int i11, int i12, int i13, int i14, int i15, int i16, int i17, int i18, int i19, int i20, int i21)
 * \brief retourne un tableau contenant les notes des paramètres de l'IA.
 *  
 * \param[in] int i1 : paramètre ia: deplacer un pion
 * \param[in] int i2 : paramètre ia: placer un pion
 * \param[in] int i3 : paramètre ia: manger un pion (difference = 1)
 * \param[in] int i4 : paramètre ia: manger un pion (difference = 2)
 * \param[in] int i5 : paramètre ia: case d'arrivé au centre
 * \param[in] int i6 : paramètre ia: case d'arrivé coin
 * \param[in] int i7 : paramètre ia: case d'arrivé middle
 * \param[in] int i8 : paramètre ia: jouer un gros
 * \param[in] int i9 : paramètre ia: jouer un moyen
 * \param[in] int i10 : paramètre ia: jouer un petit
 * \param[in] int i11 : paramètre ia: case depart centre
 * \param[in] int i12 : paramètre ia: case depart coin
 * \param[in] int i13 : paramètre ia: case depart middle
 * \param[in] int i14 : paramètre ia: manger moyen
 * \param[in] int i15 : paramètre ia: manger petit
 * \param[in] int i16 : paramètre ia: nbre pion > nbre pion adverse
 * \param[in] int i17 : paramètre ia: nbre pion = nbre pion adverse
 * \param[in] int i18 : paramètre ia: nbre pion < nbre pion advser
 * \param[in] int i19 : paramètre ia: nbre pion gobé > nbre pion gobé adverse
 * \param[in] int i20 : paramètre ia: nbre pion gobé < nbre pion gobé adverse
 * \param[in] int i21 : paramètre ia: alignement 2 pions
 * 
 * \return int : retourne le tableau contenant les paramètre de l'ia
 * 
 * \author DUPOIS Thomas
 */
int *generateTab(int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, 
int i10, int i11, int i12, int i13, int i14, int i15, int i16, int i17, int i18, int i19, int i20, int i21);

/**
 * \fn void writeChampion(int * tabParam, char nom[20])
 * 
 * \brief Fonction qui écrit les paramètre de l'ia gagnante du tournois
 * 
 * \param[in] int * tabParam : tableau de paramètre
 * \param[in] char nom[20] : nom du fichier
 * 
 * \return void : Pas de retour pour la fonction.
 * 
 * \author DUPOIS Thomas
 */
void writeChampion(int * tabParam, char nom[20]);

/**
 * \fn int nbreChampion(char nom[20])
 * 
 * \brief Fonction qui renvoie le nombre d'ia stockées dans le fichier
 * 
 * \param[in] char nom[20] : nom du fichier
 * 
 * \return int : renvoie le nombre d'ia stockées dans le fichier
 * 
 * \author DUPOIS Thomas
 */
int nbreChampion(char nom[20]);

/**
 * \fn void readChampion(int ** tabIA, char nom[20])
 * 
 * \brief Fonction qui stocke les 10 champion dans le tableau d'IA
 * 
 * \param[in] int ** tabIA : tableau d'IA
 * \param[in] char nom[20]: nom du fichier
 * 
 * \return void : ne renvoie rien
 * 
 * \author DUPOIS Thomas
 */
void readChampion(int ** tabIA, char nom[20]);

/**
 * \fn void readTheChampion(int ** tabIA, char nom[20])
 * 
 * \brief Fonction qui récupère la meilleur IA, créer 10 clone d'elle modifié génétiquement
 * 
 * \param[in] int ** tabIA : tableau d'IA
 * \param[in] char nom[20]: nom du fichier
 * 
 * \return void : ne renvoie rien
 * 
 * \author DUPOIS Thomas
 */
void readTheChampion(int ** tabIA, char nom[20]);

/**
 * \fn void clearFile(char nom[20])
 * 
 * \brief Fonction qui vide le contenu d'un fichier
 * 
 * \param[in] char nom[20]: nom du fichier
 * 
 * \return void : ne renvoie rien
 * 
 * \author DUPOIS Thomas
 */
void clearFile(char nom[20]);

/**
 * \fn int lectureDetection(char nameFile[35], char firstAvert[35], char secondAvert[35], int ** tabIA, int * champ)
 * 
 * \brief Fonction qui effectue la detection des champions (vérifie s'il y a 10 champions dans un fichier)
 * 
 * \param[in] char nameFile[20] : nom du fichier
 * \param[in] char firstAvert[35] : 1er avertissement
 * \param[in] char secondAvert[35] : 2eme avertissement
 * \param[in] int ** tabIA : tableau d'IA
 * \param[in] int * champ : boolean du champion en question
 * 
 * \return int : renvoie 1 ou 0 selon la detection
 * 
 * \author DUPOIS Thomas
 */
int lectureDetection(char nameFile[35], char firstAvert[35], char secondAvert[35], int ** tabIA, int * champ);

#endif
