/**
 * \file demande.h
 * 
 * \brief Fichier contenant les headers des fonctions où l'on demande à l'utilisateurs ces choix d'action au clavier. Avec vérification.\n
 * 
 * SGO : sous game option car appelé dans game option. Elles sont appelées lors du lancement du jeu en console. 
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

#ifndef DEMANDE_H_
#define DEMANDE_H_

/**
 * \fn void SGO_demandePileEtDeplacement(char *** map3D, char ** map2D, int * answer)
 * \brief Fonction qui demande l'action que veut effectuer le joueur. Soit jouer un nouveau pion ou deplacer un ancien pion.\n
 * 
 * Vérification : option valide (saisie 1 ou 2, **ne vérifie pas si on peut faire cette action**).
 *  
 * \param[in] char *** map3D : plateau de jeu détaillé.
 * \param[in] char **  map2D : plateau de jeu non détaillé.
 * \param[in] int *  answer  : contient la réponse de l'utilisateur.
 * 
 * \return void : Pas de retour pour la fonction car réponse enregistré dans **answer**.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
void SGO_demandePileEtDeplacement(char *** map3D, char ** map2D, int * answer);

/**
 * \fn void SGO_demandeQuelPionDeplacer(char *** map3D, char ** map2D, int * debPion)
 * \brief Fonction qui demande le pion que veut deplacer le joueur. **Sans vérification.**
 *
 *  
 * \param[in] char *** map3D : plateau de jeu détaillé.
 * \param[in] char **  map2D : plateau de jeu non détaillé.
 * \param[in] int * debPion  : contient la réponse de l'utilisateur.
 * 
 * \return void : Pas de retour pour la fonction car réponse enregistré dans **debPion**.
 * 
 * \author DUPOIS Thomas
 */
void SGO_demandeQuelPionDeplacer(char *** map3D, char ** map2D, int * debPion);

/**
 * \fn void SGO_demanderQuellePileJouer(char *** map3D, char ** map2D, char ** stackArray, int * numStack)
 * \brief Fonction qui demande le pion que veut deplacer le joueur. **Avec vérification.**\n
 *
 * Vérification : indice invalide, la pile demandé ne contient aucun pion, on ne peut pas jouer de pion de cette pile sur le plateau
 *  
 * \param[in] char *** map3D : plateau de jeu détaillé.
 * \param[in] char **  map2D : plateau de jeu non détaillé.
 * \param[in] char **  stackArray : contient les piles du joueur.
 * \param[in] int * numStack : contient la réponse de l'utilisateur.
 * 
 * \return void : Pas de retour pour la fonction car réponse enregistré dans **numStack**.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
void SGO_demanderQuellePileJouer(char *** map3D, char ** map2D, char ** stackArray, int * numStack);

/**
 * \fn void SGO_demanderQuelPionJouer(char *** map3D, char ** stackArray, int * numStack, int * numPion)
 * \brief Fonction qui demande le pion que veut jouer le joueur dans sa pile. **Avec vérification.**\n
 *
 * Vérification : indice invalide, le pion existe et on peut le déplacer.
 *  
 * \param[in] char *** map3D : plateau de jeu détaillé.
 * \param[in] char **  stackArray : contient les piles du joueur.
 * \param[in] char *  numStack : contient le numéro de pile du joueur.
 * \param[in] int * numPion : contient la réponse de l'utilisateur.
 * 
 * \return void : Pas de retour pour la fonction car réponse enregistré dans **numPion**.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
void SGO_demanderQuelPionJouer(char *** map3D, char ** stackArray, int * numStack, int * numPion);

/**
 * \fn void SGO_demanderQuelPionJouer(char *** map3D, char ** stackArray, int * numStack, int * numPion)
 * \brief Fonction qui demande le pion que veut jouer le joueur dans sa pile. **Avec vérification.**\n
 *
 * Vérification : indice invalide, le pion existe et on peut le déplacer.
 *  
 * \param[in] char *** map3D : plateau de jeu détaillé.
 * \param[in] char **  stackArray : contient les piles du joueur.
 * \param[in] char *  numStack : contient le numéro de pile du joueur.
 * \param[in] int * numPion : contient la réponse de l'utilisateur.
 * 
 * \return void : Pas de retour pour la fonction car réponse enregistré dans **numPion**.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */
void SGO_demanderQuelleCaseJouerPion(char *** map3D, int * numPion, int * endPion);

/**
 * \fn int SF_demandeDeplacement()
 * \brief Fonction qui demande l'option du mode de jeu. Les déplacements sont restriens de 1 ou pas. **Avec vérification.**\n
 *
 * Vérification : option valide, 1 ou 0.
 *  
 * \param[in] void : Pas de paramètre.
 * 
 * \return int : Return 0 si déplacement non restreint sinon 1 (restreint de connexité 1).
 * 
 * \author DUPOIS Thomas
 */
int SF_demandeDeplacement() ;

/**
 * \fn void SGO_verifEtDeplacementCaseAvecLimite(char *** map3D, char c, int * debPion, int * endPion) 
 * 
 * \brief Fonction qui demande au joueur le pion qu'il veut deplacer et verifie si il existe et qu'il peut le deplacer (avec deplacement restreint de 1). Et son emplacement d'arriver (si il existe et il peut le mettre).
 *
 * \param[in] char *** map3D : plateau de jeu détaillé.
 * \param[in] char c : identifiant du joueur.
 * \param[in] int * debPion : contient la réponse de l'utilisateur pour le pion de départ.
 * \param[in] int * endPion : contient la réponse de l'utilisateur pour le pion d'arriver.
 * 
 * \return int : Return 0 si déplacement non restreint sinon 1 (restreint de connexité 1).
 * 
 * \author DUPOIS Thomas
 */
void SGO_verifEtDeplacementCaseAvecLimite(char *** map3D, char c, int * debPion, int * endPion) ;

/**
 * \fn void SGO_verifEtDeplacementCaseAvecLimite(char *** map3D, char c, int * debPion, int * endPion) 
 * 
 * \brief Fonction qui demande au joueur le pion qu'il veut deplacer et verifie si il existe et qu'il peut le deplacer (sans restriction de déplacement). Et son emplacement d'arriver (si il existe et il peut le mettre).
 *
 * \param[in] char *** map3D : plateau de jeu détaillé.
 * \param[in] char c : identifiant du joueur.
 * \param[in] int * debPion : contient la réponse de l'utilisateur pour le pion de départ.
 * \param[in] int * endPion : contient la réponse de l'utilisateur pour le pion d'arriver.
 * 
 * \return int : Return 0 si déplacement non restreint sinon 1 (restreint de connexité 1).
 * 
 * \author DUPOIS Thomas
 */
void SGO_verifEtDeplacementCaseSansLimite(char *** map3D, char c, int * debPion, int * endPion);

#endif
