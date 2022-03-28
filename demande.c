/**
 * \file demande.c
 * 
 * \brief Fichier contenant les codes des fonctions où l'on demande à l'utilisateurs ces choix d'action au clavier. Avec vérification.\n
 * 
 * SGO : sous game option car appelé dans game option. Elles sont appelées lors du lancement du jeu en console. 
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

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
void SGO_demandePileEtDeplacement(char *** map3D, char ** map2D, int * answer) {
  printMap2D(map2D); printMap3dDebug(map3D);
  printf("Que souhaitez-vous faire ? \n[1] Jouer un nouveau pion ? (de votre pile)  \n[2] Deplacer un pion se trouvant sur la map  \n");
  scanf(" %d", answer);
  vider_buffer(); // vide buffer pour éviter erreur
  while (*answer != 1 &&  *answer != 2) {
    printf("Je n'ai pas compris !  \n\nQue voulez-vous faire ? \n[1] Jouer un nouveau pion ? (de votre pile)  \n[2] Deplacer un pion se trouvant sur la map  \n");
    scanf(" %d", answer);
    vider_buffer();
  }
}

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
void SGO_demandeQuelPionDeplacer(char *** map3D, char ** map2D, int * debPion) {
  printMap2D(map2D);
  printMap3dDebug(map3D);
  printf("Quel pion voulez-vous deplacer ? \n");
  scanf(" %d", debPion);
  vider_buffer();
}

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
void SGO_demanderQuellePileJouer(char *** map3D, char ** map2D, char ** stackArray, int * numStack) {
  printMap2D(map2D); printMap3dDebug(map3D);
  printf("Voici vos piles : \n");
  printStacks(stackArray);
  printf("Quelle pile voulez vous jouer ?\n");
  scanf(" %d", numStack);
  // recommence la saisie si : indice invalide, la pile demandé ne contient aucun pion, on ne peut pas jouer de pion de cette pile sur le plateau
  while(*numStack < 0 || *numStack > N-2 || isEmptyStack(stackArray, *numStack) || !canPlayStack(sizePionMaxStack(stackArray , *numStack), map3D)) {
    printf("Vous ne pouvez rien faire avec cette pile ! \nVeuillez saisir un nouveau numero de pile.\n");
    scanf(" %d", numStack);
    vider_buffer();
  }
}

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
void SGO_demanderQuelPionJouer(char *** map3D, char ** stackArray, int * numStack, int * numPion) {
  printf("Quel pion voulez vous jouer (0 <= pion <= %d) ?\n", N-1);
  scanf(" %d", numPion);
  // Vérification : indice invalide, le pion existe et on peut le déplacer.
  while(*numPion < 0 || *numPion > N-1 || !existPionInStack(stackArray, *numStack, *numPion) || !canPlayStack(*numPion, map3D)) {
    printf("Vous ne pouvez rien faire avec ce pion! \nVeuillez saisir un nouveau pion dans cette pile.\n");
    scanf(" %d", numPion);
    vider_buffer();
  }
}

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
void SGO_demanderQuelleCaseJouerPion(char *** map3D, int * numPion, int * endPion) {
  printf("A quelle place voulez vous jouez le pion numero %d ? \n", *numPion);
  scanf(" %d", endPion);
  vider_buffer();
  while(*endPion < 0 || *endPion > (N*N)-1 || !canPutPion(map3D, *numPion, *endPion)) {
    printf("Position d'arrivee invalide !\nVeuillez resaisir le numero de case où vous voulez jouer [%d] \n", canPutPion(map3D, *numPion, *endPion));
    scanf(" %d", endPion);
    vider_buffer();
  }
}

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
int SF_demandeDeplacement(){
  int deplacement = -1; // deplacement à -1 evite do while car on n'aime pas
  printf("Voulez-vous restreindre les déplacements à une distance de 1?\n[0] Non\n[1] Oui\n"); scanf(" %d", &deplacement);
  while (deplacement != 0 && deplacement != 1) {
    printf("Resultat invalide");
    printf("Voulez-vous restreindre les déplacements à une distance de 1?\n[0] Non\n[1] Oui\n");
    scanf(" %d", &deplacement);
    vider_buffer();
  }
  return deplacement;
}

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
void SGO_verifEtDeplacementCaseAvecLimite(char *** map3D, char c, int * debPion, int * endPion) {
  while(*debPion < 0 || *debPion > N*N-1 || !canMooveThisPionDistance(map3D, *debPion, c)) {
    printf("Index non valide ! \nQuel pion voulez vous deplacer ?\n");
    scanf(" %d", debPion);
    vider_buffer();
  }
  int x1 = (*debPion - *debPion % N) / N; int y1 = *debPion % N; // transforme d'indice de la case de départ en coordonnée

  printf("Sur quel case voulez vous deplacer le pion %d ? \n", *debPion);
  scanf(" %d", endPion);
  int x2 = (*endPion - *endPion % N) / N; int y2 = *endPion % N; // transforme d'indice de la case d'arriver en coordonnée
  while (*endPion < 0 || *endPion > (N*N)-1 || *endPion == *debPion || !canMoove(map3D, *debPion, *endPion) || maximum(abs(x1-x2), abs(y1-y2)) > 1) {
    printf("Case invalide (distance>1)\nSur quel case voulez vous deplacer le pion %d ? \n", *debPion);
    scanf(" %d", endPion);
    x2 = (*endPion - *endPion % N) / N;
    y2 = *endPion % N;
    vider_buffer();
  }
}

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
void SGO_verifEtDeplacementCaseSansLimite(char *** map3D, char c, int * debPion, int * endPion) {
  while(*debPion < 0 || *debPion > N*N-1 || !canMooveThisPionD(map3D, *debPion, c)) {
    printf("Index non valide ! \nQuel pion voulez vous deplacer ?\n");
    scanf(" %d", debPion);
    vider_buffer();
  }
  printf("Sur quel case voulez vous deplacer le pion %d ? \n", *debPion);
  scanf(" %d", endPion);
  vider_buffer();
  while(*endPion < 0 || *endPion > (N*N)-1 || *endPion == *debPion || !canMoove(map3D, *debPion, *endPion)) {
    printf("Deplacement invalide, veuillez recommencer. \n");
    printf("Sur quelle case voulez vous deplacer le pion %d ? \n", *debPion);
    scanf(" %d", endPion);
    vider_buffer();
  }
}