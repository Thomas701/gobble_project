/**
 * \file ia.c
 * 
 * \brief Fichier contenant les code des fonctions concernant l'intelligence artificielle.
 * 
 * \author DUPOIS Thomas
 * \author VILLEPREUX Thibault
 */

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
int ** createTabOfCoups()
{
    int nbreIndex = 2;                                      //index de départ et d'arrivé
    int ** tab = (int **) malloc(sizeof(int *)*2);       // alloue le tableau 1D
    if(!tab) errorInCreate2D();                             // appelle fonction qui envoie message + quit prog si NULL (malloc impossible)
    for(int i = 0; i < 2; i++) 
    {
        tab[i] = (int *) malloc(sizeof(int)*67);          // alloue le tab2D
        if(!tab[i]) 
        {                                       // free proprement + appelle fonction qui envoie message + quit prog si NULL (malloc impossible)
            for(int j = 0; j < i; j++) 
                free(tab[j]); 
            free(tab);
            errorInCreateTabOfCoups();
        }
    }
    return tab;
}

/**
 * \fn void afficheTabOfCoups(int ** tab)
 * \brief Permet d'afficher le tableau contenant les coups pouvants être joué par l'IA
 *  
 * \param[in] int ** tab : tableau de coups possible que l'on doit afficher
 * 
 * \return void : Ne Retourne rien, il s'agit seulement d'un affichage console
 * 
 * \author DUPOIS Thomas
 */
void afficheTabOfCoups(int ** tab)
{
    printf("------------ TAB DE COUPS ------------\n");
    for(int i = 0; i < 2; i++) 
    {
        for(int j = 0; j < 67; j++)
        {
            if (tab[i][j] == -1 && i == 0)
                continue;
            else if (tab[i][j] == -1 && i == 1)
                continue;
            printf("%d ", tab[i][j]);
            if (tab[i][j] < 10)
                printf(" ");
        }
        printf("\n");
    }
    printf("\n");
    printf("--------------------------------\n");
}

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
void initTabOfCoups(int ** tab)
{
    for(int i = 0; i < 2; i++) 
    {
        for(int j = 0; j < 67; j++)
            tab[i][j] = -1;
    }
}

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
char *** copyMap3D(char *** map3D)
{
    char *** newMap3D = createMap();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int k = 0; k < N; k++)
            {
                newMap3D[i][j][k] = map3D[i][j][k];
            }
        }
    } 
    return newMap3D;
}

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
char ** copyMap2D(char ** map2D)
{
    char ** newMap2D = createMap2D();
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            newMap2D[i][j] = map2D[i][j];
    } 
    return newMap2D;
}

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
char ** copyStack(char ** pile)
{
    char ** newPile = createStack('b');
    for (int i = 0; i < N-1; i++)
    {
        for (int j = 0; j < N; j++)
            newPile[i][j] = pile[i][j];
    } 
    return newPile;
}

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
void listTabOfCoups(char *** map3D, char ** stacks, int ** tabOfCoups, char c)
{
    initTabOfCoups(tabOfCoups);
    int num; //correspond à l'index dans la pile représentant la taille du pion souhaité
    int numberOfStack; // un joueur à deux piles, représente la pile dans laquelle le pion joué sera choisi
    int indexTabOfCoups = 0; //représente l'index du tableau de coups
    int x1; int x2; int y1; int y2; // coordonnée des index de départ et d'arrivé
    for (int i = 0; i < 15; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (i == j)
                continue;
            //si l'index ne correspond pas au bon joueur pour les piles
            if ( (c == 'b' && (i == 12 || i == 13 || i == 14)) || (c == 'n' && (i == 9 || i == 10 || i == 11)) )
                continue;
            //si l'index ciblé n'a pas le bon caractère, ou qu'aucun déplacement n'est possible dans la map,
            // ou que le pion ciblé ne peut pas se déplacer, ou que le déplacement n'est pas valide, ou que la distance de déplacement est trop grande
            int x1 = (i - i % N) / N;   int y1 = i % N; 
            int x2 = (j - j % N) / N;   int y2 = j % N;
            if (i < 9 && (getCaractereOnCase(map3D, i) != c || !canEffectDeplacementWithDistance(map3D, c) 
            || !canMooveThisPionD(map3D, i, c) || !canMoove(map3D, i, j) || maximum(abs(x1-x2), abs(y1-y2)) > 1))
                continue;
            //si l'index ciblé est une pile mais que la pile du joueur est vide
            if (i > 8 && isEmptyStacks(stacks))
                continue;
            //si un petit pion est sélectionné mais que la map est pleine (donc coup impossible)
            if ((i == 11 || i == 14) && !isEmptyCase2(map3D))
                continue;

            /* DANS LE CAS OU L'INDEX DE DEPART EST UNE PILE */
            if (i > 8)
            {
                numberOfStack = -1;
                num = (N-1) - i%3;
                for (int k = 0; k < N-1; k++)
                {
                    if (stacks[k][num] == c)
                    {
                        numberOfStack = k;
                        break;
                    }
                }
                // si il n'existe pas de pion de la bonne taille dans la pile
                if (numberOfStack == -1)
                    continue;
                // si le coups n'est pas valide car la case d'arrivé est mauvaise
                if (!canPutPion(map3D, num, j))
                    continue;
                else
                {
                    tabOfCoups[0][indexTabOfCoups] = i;
                    tabOfCoups[1][indexTabOfCoups] = j;
                    indexTabOfCoups++;
                }
            }
            /* DANS LE CAS OU L'INDEX DE DEPART EST UNE CASE DU PLATEAU DE JEU*/
            else
            {
                tabOfCoups[0][indexTabOfCoups] = i;
                tabOfCoups[1][indexTabOfCoups] = j;
                indexTabOfCoups++;
            }
        }
    }
}

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
void placePionByIa(int ** tab, int bestCoup, char *** map3D, char ** stacks, char c)
{
    /* PLACE LE PION A PARTIR D'UNE PILE */
    if (tab[0][bestCoup] > 8)
    {
        for (int i = 0; i < N-1; i++) 
        {
            if (stacks[i][(N-1) - (tab[0][bestCoup] % N)] != '0') 
            {
                mooveSinceStack(map3D, stacks, i, (N-1) - (tab[0][bestCoup] % N), tab[1][bestCoup], c);
                break;
            }
        }
    }
    /* DEPLACE UN PION SUR LA MAP */
    else
        moove(map3D, tab[0][bestCoup], tab[1][bestCoup]); 
}


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
int * play(char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, char c, int ia, int prof, int alphaBeta, int * tableauParam)
{
    int max = -99999;                               // le max
    int calcul;                                     // correspond au résultat effectué par la fonction prédiction
    int ** tab = createTabOfCoups();                // créer un nouveau tableau de coups
    liste * l = createListe();
    int index = 0;                                  // index tu tableau de coups initialisé à 0
    int bestCoup;                                   // retiens le meilleurs coups à jouer pour l'IA
    char ** stacks = (c == 'b') ? pileJ1 : pileJ2;  // pile correspondant au bon joueur
    int alpha = -999999;
    int beta = 999999; 
    int * tabResult = (int*) malloc(sizeof(int)*3);
    int eatingPion;
    /* créer le tableau des coups-----------*/
    initTabOfCoups(tab);                    //
    listTabOfCoups(map3D, stacks, tab, c);  //
    /* -------------------------------------*/
    //afficheTabOfCoups(tab);
    //printf("2\n");
    while (tab[0][index] != -1)
    {
        //printf("index: %d\n dep=%d, end=%d\n", index, tab[0][index], tab[1][index]);
        calcul = prediction(prof, map3D, map2D ,pileJ1, pileJ2, tab, index, ia, c, alphaBeta, alpha, beta, tableauParam); // calcule le score de chaque coups
        //printf("RESULTAT: %d\n", calcul);
        if (max < calcul)
        {
            clear(l);
            add(l, index);
            max = calcul;
            bestCoup = index; // recupère l'index du meilleur coup
        }
        else if (max == calcul)
            add(l, index);
        index++;
    }
    //afficheListe(l);
    /* --- SELECTION MEILLEUR COUP PARMIS LES CHOIX HESITANTS --- */
    liste * l2 = createListe();
    max = -999;
    if (size(l) > 1)
    {
        for (int i = 0; i < size(l); i++)
        {
            calcul = evaluation(tableauParam, map3D, map2D, tab, get(l, i), c);
            if (calcul > max)
            {
                clear(l2);
                add(l2, get(l, i));
                max = calcul;
                bestCoup = get(l, i);
            }
            else if (max == calcul)
                add(l2, get(l, i));
        }
        bestCoup = get(l2, rand()%(size(l2)));
    }
    
    //printf("size = %d, bestCoup = %d\n", size(l), bestCoup);
    eatingPion = getIndexPionWhoAreEat(map3D, tab[1][bestCoup]);
    //printf("Eating pion = %d\n", eatingPion);
    placePionByIa(tab, bestCoup, map3D, stacks, c);
    tabResult[0] = tab[0][bestCoup]; tabResult[1] = tab[1][bestCoup]; tabResult[2] = eatingPion;
    freeTableOfCoups(tab);
    // free la liste
    clear(l);
    free(l);
    clear(l2);
    free(l2);
    return tabResult;
}

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
void allFree(char *** map3D, char ** map2D, char ** stacks, char ** stacksOp, int ** tab, liste * l)
{
    freeMap(map3D);
    freeMap2D(map2D);
    freeStack(stacks);
    freeStack(stacksOp);
    freeTableOfCoups(tab);
    free(l);
}


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
int prediction(int prof, char *** map3D, char ** map2D, char ** pileJ1, char ** pileJ2, int ** tabOfCoups, int index, int ia, char c, int alphaBeta, int alpha, int beta, int * tableauParam)
{
    if (prof == -1)
        return evaluation(tableauParam, map3D, map2D, tabOfCoups, index, c);
    /* ----- */
    char ** stacks; char ** stacksOp;
    int iaOp = (ia == 1) ? 0 : 1;       // IA OPPOSE
    char cOp = (c == 'b') ? 'n' : 'b';  // PION OPPOSE
    int choix = (c == 'b') ? 1 : 0;                                 // boolean qui sert seulement à savoir si stack = pileJ1 ou stack = pileJ2
    stacks = (c == 'b') ? copyStack(pileJ1) : copyStack(pileJ2);    // si pion bleu: stacks = j1
    stacksOp = (c == 'b') ? copyStack(pileJ2) : copyStack(pileJ1);  // si pion rouge stacks == j2
    char *** newMap3D = copyMap3D(map3D);
    char ** newMap2D = copyMap2D(map2D);
    /* ---- */
    placePionByIa(tabOfCoups, index, newMap3D, stacks, c);  // jouer le pion en question
    initMap2D(newMap2D, newMap3D);                          // mettre à jour la map
    /* ---- */
    if (count_pion(newMap2D, N, cOp)) // gagner, perdu?
    {
        freeMap(newMap3D);
        freeMap2D(newMap2D);
        freeStack(stacks);
        freeStack(stacksOp);
        return (ia == 1) ? -100-prof : 100+prof ;
    }
    if (count_pion(newMap2D, N, c)) // gagner, perdu?
    {
        freeMap(newMap3D);
        freeMap2D(newMap2D);
        freeStack(stacks);
        freeStack(stacksOp);
        return (ia == 1) ? 100+prof : -100-prof;
    }
    // ----------------------------------------------------
    else
    {
        int max = -999999; int min = 999999;
        int ** tab = createTabOfCoups();                    // création d'un nouveau tableau des coups
        initTabOfCoups(tab); 
        listTabOfCoups(newMap3D, stacksOp, tab, cOp); 
        liste * l = createListe();
        int indexTab = 0;
        int mem; int continuer = 1;

        while (tab[0][indexTab] != -1 && continuer)
        {
            if (choix)
            {
                mem = prediction(prof-1, newMap3D, newMap2D, stacks, stacksOp, tab, indexTab, iaOp, cOp, alphaBeta, alpha, beta, tableauParam);
                add(l, mem);
                if (ia == 1 && mem > alpha)
                    alpha = mem;
                else if (ia == 0 && mem < beta)
                    beta = mem;
                if (alpha > beta && alphaBeta)
                    continuer = 0;
            }
            else
            {
                mem = prediction(prof-1, newMap3D, newMap2D, stacksOp, stacks, tab, indexTab, iaOp, cOp, alphaBeta, alpha, beta, tableauParam);
                add(l, mem);
                if (ia == 1 && mem > alpha)
                    alpha = mem;
                else if (ia == 0 && mem < beta)
                    beta = mem;
                if (alpha > beta && alphaBeta)
                    continuer = 0;
            }
            indexTab++;
        }

        while (l != NULL)
        {
            liste * l2 = l-> suivant;
            if(ia && min > l->value)
                min = l->value;
            else if(!ia && max < l->value)
                max = l->value;
            free(l);
            l = l2;
        }
        allFree(newMap3D, newMap2D, stacks, stacksOp, tab, l);
        return (ia) ? min : max ;
    }
}

// ----------------- Evalutation de la grille ---------------------- //
// Liste des paramètres 
// <- [0]deplacer un pion 
// <- [1]placer un pion 
// <- [2]manger un pion (difference = 1)  
// <- [3]manger un pion (difference = 2)  
// <- [4]case d'arrivé au centre  
// <- [5]case d'arrivé coin  
// <- [6]case d'arrivé middle  
// <- [7]jouer un gros 
// <- [8]jouer un moyen 
// <- [9]jouer un petit   

/**
 * \fn int evaluation(int * tabParam, char *** map3D, char ** map2D, int ** tabOfCoups, int index, char c)
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
int evaluation(int * tabParam, char *** map3D, char ** map2D, int ** tabOfCoups, int index, char c)
{
    int result = 0;
    //placer un pion (déplacement depuis une pile)
    if(tabOfCoups[0][index] > 8)
        result += tabParam[1];
    //deplacer un pion (déplacement depuis une case de la map)
    if(tabOfCoups[0][index] < 9)
        result += tabParam[0];
    //deplacer un pion sur le centrer
    if(tabOfCoups[1][index] == 4)
        result += tabParam[4];
    //deplacer un pion sur un coin
    if(tabOfCoups[1][index] == 0 || tabOfCoups[1][index] == 2 || tabOfCoups[1][index] == 6 || tabOfCoups[1][index] == 8)
        result += tabParam[5];
    //deplacer un pion sur une case middle
    if(tabOfCoups[1][index] == 1 || tabOfCoups[1][index] == 3 || tabOfCoups[1][index] == 5 || tabOfCoups[1][index] == 7)
        result += tabParam[6];
    //jouer un gros pion
    if (( tabOfCoups[0][index] > 8 && tabOfCoups[0][index]%3 == 0) || (tabOfCoups[0][index] < 9 && getSizePionOnCase2(map3D, tabOfCoups[0][index]) == 2))
        result += tabParam[7];
    //jouer un pion de taille moyenne
    if ((tabOfCoups[0][index] > 8 && tabOfCoups[0][index]%3 == 1) || (tabOfCoups[0][index] < 9 && getSizePionOnCase2(map3D, tabOfCoups[0][index]) == 1))
        result += tabParam[8];
    //jouer un pion de petite taille
    if ((tabOfCoups[0][index] > 8 && tabOfCoups[0][index]%3 == 2) || (tabOfCoups[0][index] < 9 && getSizePionOnCase2(map3D, tabOfCoups[0][index]) == 0))
        result += tabParam[9];
    //manger un pion avec une différence de 1
    if ((tabOfCoups[0][index] > 8 && getSizePionOnCase2(map3D, tabOfCoups[1][index]) > -1 && getCaractereOnCase(map3D,tabOfCoups[1][index]) != c && (N-1) - tabOfCoups[0][index]%3 - getSizePionOnCase2(map3D, tabOfCoups[1][index]) == 1)
    || (tabOfCoups[0][index] < 9 && getSizePionOnCase2(map3D, tabOfCoups[1][index]) > -1 && getCaractereOnCase(map3D,tabOfCoups[1][index]) != c && getSizePionOnCase2(map3D, tabOfCoups[0][index]) - getSizePionOnCase2(map3D, tabOfCoups[1][index]) == 1))
        result += tabParam[2];
    //manger un pion avec une différence de 2
    if ((tabOfCoups[0][index] > 8 && getSizePionOnCase2(map3D, tabOfCoups[1][index]) > -1 && getCaractereOnCase(map3D,tabOfCoups[1][index]) != c && (N-1) - tabOfCoups[0][index]%3 - getSizePionOnCase2(map3D, tabOfCoups[1][index]) == 2)
    || (tabOfCoups[0][index] < 9 && getSizePionOnCase2(map3D, tabOfCoups[1][index]) > -1 && getCaractereOnCase(map3D,tabOfCoups[1][index]) != c && getSizePionOnCase2(map3D, tabOfCoups[0][index]) - getSizePionOnCase2(map3D, tabOfCoups[1][index]) == 2))
        result += tabParam[3];

    return result;
}

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
int countDiff(char ** map2D, char c)
{
    int count = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            count = (map2D[j][j] == c) ? count + 1 : 0;
    }
    return count;
}

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
int rdm (int i, int j)
{
   int x = i + rand() % (j + 1 - i);
   return x;
}

/**
 * \fn int *generateTab(int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9)
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
 * 
 * \return int : retourne le tableau contenant les paramètre de l'ia
 * 
 * \author DUPOIS Thomas
 */
int *generateTab(int i1, int i2, int i3, int i4, int i5, int i6, int i7, int i8, int i9, int i10)
{
    int * tab = (int*) malloc(sizeof(int)*10);
    tab[0] = i1; tab[1] = i2; tab[2] = i3; tab[3] = i4;
    tab[4] = i5; tab[5] = i6; tab[6] = i7; tab[7] = i8;
    tab[8] = i9, tab[9] = i10;
    return tab;
}

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
void writeChampion(int * tabParam, char nom[20]) 
{
    FILE* fichier = NULL;
 
    fichier = fopen(nom, "a");
    char nbre[3];
    printf("->%s\n", nbre);
    if (fichier != NULL)
    {
        for (int i = 0; i < 10; i++)
        {   
            itoa(tabParam[i], nbre, 10);
            fputs(nbre, fichier);
            fputs(";", fichier);
        }
        fputs("\n", fichier);
        fclose(fichier);
    }
}

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
int nbreChampion(char nom[20])
{
    FILE *f;
    char c;
    int counter = 0;
    f = fopen(nom,"r");
    while((c=fgetc(f)) != EOF)
    {
        if (c == '\n')
            counter++;
    }
    fclose(f);
    return counter;
}

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
void readChampion(int ** tabIA, char nom[20])
{
    FILE *f;
    f = fopen(nom,"r");   
    int i1, i2, i3, i4, i5, i6, i7, i8, i9, i10;
    int i = 0;
    char *file_contents = malloc(30);

    while (fscanf(f, "%[^\n] ", file_contents) != EOF) 
    {
        //printf("> %s\n", file_contents);
        sscanf(file_contents,"%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;",&i1,&i2,&i3,&i4,&i5,&i6,&i7,&i8,&i9,&i10);
        tabIA[i][0] = i1; tabIA[i][1] = i2; tabIA[i][2] = i3; tabIA[i][3] = i4; tabIA[i][4] = i5;
        tabIA[i][5] = i6; tabIA[i][6] = i7; tabIA[i][7] = i8; tabIA[i][8] = i9; tabIA[i][9] = i10;
        i++;
    }
    free(file_contents);
    fclose(f);
}

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
void clearFile(char nom[20])
{
    FILE *f;
    f = fopen(nom,"w+");
    fclose(f);
}






