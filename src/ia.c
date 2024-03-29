/**
 * \file ia.c
 * 
 * \brief Fichier contenant les code des fonctions concernant l'intelligence artificielle.
 * 
 * \author DUPOIS Thomas
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
            x1 = (i - i % N) / N;   y1 = i % N; 
            x2 = (j - j % N) / N;   y2 = j % N;
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
    while (tab[0][index] != -1)
    {
        //printf("index: %d\n dep=%d, end=%d\n", index, tab[0][index], tab[1][index]);
        calcul = prediction(prof, map3D, map2D ,pileJ1, pileJ2, tab, index, ia, c, alphaBeta, alpha, beta, tableauParam); // calcule le score de chaque coups
        //printf("RESULTAT: %d\n", calcul);
        if (calcul < beta)
            beta = calcul;

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
    max = -999999;
    if (size(l) > 1)
    {
        for (int i = 0; i < size(l); i++)
        {
            //calcul = evaluation(tableauParam, map3D, map2D, tab, get(l, i), c, pileJ1, 1);
            calcul = evaluation2(tableauParam, map3D, map2D, c, 1);
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
    {
        return evaluation2(tableauParam, map3D, map2D, c, ((ia) ? 1 : -1));
    }
        
        //return evaluation(tableauParam, map3D, map2D, tabOfCoups, index, c, ((c == 'b') ? pileJ1 : pileJ2), ((ia) ? 1 : -1));
    /* ----- */
    char ** stacks; char ** stacksOp;
    int iaOp = (ia == 1) ? 0 : 1;       // IA OPPOSE
    char cOp = (c == 'b') ? 'n' : 'b';  // PION OPPOSE
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
        return (ia == 1) ? -1000-prof : 1000+prof ;
    }
    else if (count_pion(newMap2D, N, c)) // gagner, perdu?
    {
        freeMap(newMap3D);
        freeMap2D(newMap2D);
        freeStack(stacks);
        freeStack(stacksOp);
        /*if (ia)
        {
            printf("PROFONDEUR: %d\n", prof);
            printMap3dDebug(newMap3D);
        }*/
        return (ia == 1) ? 1000+prof : -1000-prof;
    }
    // ----------------------------------------------------
    else
    {
        /*if (ia && prof == 1)
        {
            printf("2eme Print\n");
            printMap3dDebug(newMap3D);
        }*/
        int max = -999999; int min = 999999;
        int ** tab = createTabOfCoups();                    // création d'un nouveau tableau des coups
        initTabOfCoups(tab); 
        listTabOfCoups(newMap3D, stacksOp, tab, cOp); 
        liste * l = createListe();
        int indexTab = 0;
        int mem; int continuer = 1;
        while (tab[0][indexTab] != -1 && continuer)
        {
            mem = prediction(prof-1, newMap3D, newMap2D, ((c == 'b') ? stacks : stacksOp), ((c == 'b') ? stacksOp : stacks), tab, indexTab, iaOp, cOp, alphaBeta, alpha, beta, tableauParam);
            add(l, mem);
            if (ia == 0 && mem > alpha)
                alpha = mem;
            else if (ia == 1 && mem < beta)
                beta = mem;
            if (alpha > beta && alphaBeta)
                continuer = 0;
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
        /*if (min == -1002 && prof == 5)
        {
            printMap3dDebug(newMap3D);
        }*/
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
// <- [10]case de départ au centre  
// <- [11]case de départ coin  
// <- [12]case de départ middle
// <- [13]manger un moyen
// <- [14]manger un petit
// <- [15] nbre pion > nbre pion adversaire
// <- [16] nbre pion = nbre pion adversaire
// <- [17] nbre pion < nbre pion adversaire
// <- [18] nbre de pion gobé > nbre de pion gobé adversaire
// <- [19] nbre de pion gobé < nbre de pion gobé adversaire
// <- [20] aligne 2 gobblets

/*-------------------------------------------------------------------*/
// Liste des paramètres 2 
//[0] <- nombre d'alignement  
//[1] <- nombre encapsulation petit coin
//[2] <- nombre encapsulation petit middle
//[3] <- nombre encapsulation petit center
//[4] <- nombre encapsulation moyen coin
//[5] <- nombre encapsulation moyen middle
//[6] <- nombre encapsulation moyen centre
//[7] <- nombre de possession center 
//[8] <- nombre de possession middle
//[9] <- nombre de possession coin 
//[10] <- nombre de case maîtres 
//[11] <- nombre d'alignement avec pion encapsulé

//[12] <- nombre d'alignement ad
//[13] <- nombre encapsulation petit coin ad
//[14] <- nombre encapsulation petit middle ad
//[15] <- nombre encapsulation petit center ad
//[16] <- nombre encapsulation moyen coin ad
//[17] <- nombre encapsulation moyen middle ad
//[18] <- nombre encapsulation moyen centre ad
//[19] <- nombre de possession center ad
//[20] <- nombre de possession middle ad
//[21] <- nombre de possession coin ad
//[22] <- nombre de case maîtres ad
//[23] <- nombre d'alignement avec pion encapsulé ad

//2;5;4;0;-5;-5;5;-4;-1;2;-4;3;3;5;3;4;-5;-2;-4;1;4;

//0;3;4;1;-1;-5;-2;-3;-5;-3;-2;1;-4;3;5;1;3;2;-4;2;2;
//-1;5;5;-5;-3;-5;-1;-2;3;2;-5;-3;4;5;-3;0;-3;1;1;3;-2;
//-5;1;5;-1;-4;-1;4;-5;2;1;-3;4;3;0;0;4;4;-3;0;3;3;

//-3;-3;-4;1;-1;1;0;1;3;-1;5;0;5;-5;-2;-1;-1;-5;4;-3;0;
//-1;5;5;-5;-3;-5;-1;-2;3;2;-5;-3;4;5;-3;0;-3;1;1;3;-2;
//2;3;5;-3;1;-3;-3;-5;-5;-3;-2;3;-2;2;3;2;1;4;-3;-3;2;
//0;-3;1;5;4;-4;-1;-3;-1;0;-5;5;-4;-4;-2;-1;-3;4;1;-3;-5;
//-3;1;0;-2;-4;-3;5;-3;5;-5;-3;3;3;-3;5;1;-4;2;4;3;-2;
//-5;-2;-1;2;1;-2;5;-3;-2;3;-5;5;0;-3;2;5;-5;-1;5;4;1;
//-2;1;2;-5;-1;-5;2;-5;-2;-1;-4;5;5;5;5;4;-4;-3;3;1;-4;
//-3;1;1;-4;5;-5;-5;2;5;3;-3;2;5;0;4;-2;-2;-2;-2;-2;2;
//-4;-4;3;-1;1;-5;2;-4;-1;0;-1;1;0;-2;1;1;-4;-2;1;-3;-4;
//-5;0;-1;5;-2;-4;1;-5;1;4;-3;2;4;5;4;5;2;2;-5;3;-1;

//-2;0;4;-4;1;3;-2;-5;1;2;-3;-3;3;2;0;-1;-3;1;0;-3;0;
//-4;5;-5;-4;3;2;1;-1;1;0;-3;0;5;4;2;-4;-4;-4;0;4;2;
//0;4;2;-3;1;-5;-3;-3;0;4;-3;-2;1;2;3;-2;1;-4;5;5;5;
//2;5;4;2;3;-5;-1;-4;0;0;-3;-4;2;-1;-1;2;1;1;2;-2;-3;
//-5;1;5;-1;-4;-1;4;-5;2;1;-3;4;3;0;0;4;4;-3;0;3;3;
//-4;3;4;1;3;-4;-2;-2;0;3;-5;-2;-5;-1;2;-2;-5;5;2;-5;0;
//-5;-1;5;3;-1;-4;2;-1;2;0;-4;-4;3;4;0;-3;-3;-2;0;0;-2;
//-4;1;-1;-3;2;-4;-2;-2;3;5;-3;5;3;5;5;-5;-5;-4;1;2;5;
//-5;-3;4;2;4;2;-1;-2;0;4;5;-4;-5;-1;5;2;-1;0;4;5;5;
//-3;-2;2;0;4;-3;-5;-4;-3;-3;-3;2;-2;-1;4;4;3;-4;0;-1;4;

int evaluation2(int * tabParam, char *** map3D, char ** map2D,char c, int ia)
{
    int result = 0;
    char cOp = (c == 'b') ? 'n' : 'b';
    // alignement
    result = result + tabParam[0] * numberAlign(c, map2D);
    result = result + tabParam[12] * numberAlign(cOp, map2D);
    // encapsulation petit coin
    result = result + tabParam[1] * nbrEncapPetitCoin(cOp, map3D);
    result = result + tabParam[13] * nbrEncapPetitCoin(c, map3D);
    // encapsulation petit middle
    result = result + tabParam[2] * nbrEncapPetitMiddle(cOp, map3D);
    result = result + tabParam[14] * nbrEncapPetitMiddle(c, map3D);
    // encapsulation petit center
    result = result + tabParam[3] * nbrEncapPetitCenter(cOp, map3D);
    result = result + tabParam[15] * nbrEncapPetitCenter(c, map3D);
    // encapsulation moyen coin
    result = result + tabParam[4] * nbrEncapMoyenCoin(cOp, map3D);
    result = result + tabParam[16] * nbrEncapMoyenCoin(c, map3D);
    // encapsulation moyen middle
    result = result + tabParam[5] * nbrEncapMoyenMiddle(cOp, map3D);
    result = result + tabParam[17] * nbrEncapMoyenMiddle(c, map3D);
    // encapsulation moyen center
    result = result + tabParam[6] * nbrEncapMoyenCenter(cOp, map3D);
    result = result + tabParam[18] * nbrEncapMoyenCenter(c, map3D);
    // possession centre
    result = result + tabParam[7] * getCenter(c, map2D);
    result = result + tabParam[19] * getCenter(cOp, map2D);
    // possession middle
    result = result + tabParam[8] * numberMiddle(c, map2D);
    result = result + tabParam[20] * numberMiddle(cOp, map2D);
    // possession coin
    result = result + tabParam[9] * numberCoin(c, map2D);
    result = result + tabParam[21] * numberCoin(cOp, map2D);
    // nbr cases maître
    result = result + tabParam[10] * nbrCaseMaitre(c, map2D);
    result = result + tabParam[22] * nbrCaseMaitre(cOp, map2D);
    // nbr alignement avec encapsulation
    result = result + tabParam[10] * nbrAlignProfondeur(c, map3D);
    result = result + tabParam[23] * nbrAlignProfondeur(cOp, map3D);
    return (result * ia);
}

/**
 * \fn int nbrAlignProfondeur(char c, char *** map3D)
 * \brief compte le nombre d'alignement avec encapsulation
 *  
 * \param[in] char c : caractère en question
 * \param[in] char *** map3D : map3D
 * 
 * \return int : Retourne le nombre d'alignement avec pion encapsulés
 * 
 * \author DUPOIS Thomas
 */
int nbrAlignProfondeur(char c, char *** map3D)
{
    int nbLigne = 0; int nbColonne = 0;
    int nbDiago1 = 0; int nbDiago2 = 0;
    int totalAlign = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (map3D[i][j][k] == c) {
                    nbLigne++;
                    k = 4;
                }
                if (map3D[j][i][k] == c) {
                    nbColonne++;
                    k = 4;
                }
            }
        }
        if (nbLigne >= 2)
            totalAlign++;
        if (nbColonne >= 2)
            totalAlign++;
        nbLigne = 0;
        nbColonne = 0;
    }
    for (int i = 0; i < 3; i++) {
        for (int k = 0; k < 3; k++) {
            if (map3D[i][i][k] == c) {
                nbDiago1++;
                k = 4;
            }
            if (map3D[i][2-i][k] == c) {
                nbDiago2++;
                k = 4; 
            }
        }
    }
    if (nbDiago1 >= 2)
        totalAlign++;
    if (nbDiago2 >= 2)
        totalAlign++;

    return totalAlign;
}

/**
 * \fn int nbrMovement(char c, char *** map3D, char ** stacks)
 * \brief compte le nombre de mouvement possible sur la grille
 *  
 * \param[in] char c
 * \param[in] char *** map3D
 * \param[in] char ** stacks
 * 
 * \return int : Retourne le nombre de coups possible
 * 
 * \author DUPOIS Thomas
 */
int nbrMovement(char c, char *** map3D, char ** stacks)
{
    int ** tab = createTabOfCoups();                    // création d'un nouveau tableau des coups
    initTabOfCoups(tab); 
    listTabOfCoups(map3D, stacks, tab, c); 
    int index = 0;
    while (tab[0][index] != -1)
        index++;
    for (int i = 0; i < 2; i++)
        free(tab[i]);
    return index;
}

/**
 * \fn int numberAlign(char c, char ** map)
 * \brief compte le nombre d'alignement dans la grille
 *  
 * \param[in] char c : caractere en question
 * \param[in] char ** map2D : map2D représentant la grille du jeu
 * 
 * \return int : Retourne le nombre d'alignement
 * 
 * \author DUPOIS Thomas
 */
int numberAlign(char c, char ** map)
{
    int totalAlign = 0;
    int countLigne = 0;
    int countColonne = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (map[i][j] == c)
                countLigne++;
            if (map[j][i] == c)
                countColonne++;
        }
        if(countLigne >= 2)
            totalAlign++;
        if(countColonne >= 2)
            totalAlign++;
        countLigne = 0;
        countColonne = 0;
    }
    if ((map[0][0] == c && map[1][1] == c) || (map[1][1] == c && map[2][2] == c) || (map[0][0] == c && map[2][2] == c))
        totalAlign++;
    if ((map[0][2] == c && map[1][1] == c) || (map[1][1] == c && map[2][0] == c) || (map[0][2] == c && map[2][0] == c))
        totalAlign++;
    return totalAlign;
}


/**
 * \fn int nbrEncapPetit(char c, char *** map3D)
 * \brief compte le nombre de petit gobble encapsulé
 *  
 * \param[in] char c : caractere en question qui est encapsulé
 * \param[in] char ** map3D : map3D représentant la grille du jeu
 * 
 * \return int : Retourne le nombre d'encapsulation
 * 
 * \author DUPOIS Thomas
 */
int nbrEncapPetit(char c, char *** map3D)
{
    char cOp = (c == 'b') ? 'n' : 'b';
    int totalEncap = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (map3D[i][j][0] == c && (map3D[i][j][1] == cOp || map3D[i][j][2] == cOp))
                totalEncap++;
        }
    }
    return totalEncap;
}

/**
 * \fn int nbrEncapPetitCoin(char c, char *** map3D)
 * \brief compte le nombre de petit gobble encapsulé dans les coins
 *  
 * \param[in] char c : caractere en question qui est encapsulé
 * \param[in] char ** map3D : map3D représentant la grille du jeu
 * 
 * \return int : Retourne le nombre d'encapsulation
 * 
 * \author DUPOIS Thomas
 */
int nbrEncapPetitCoin(char c, char *** map3D)
{
    char cOp = (c == 'b') ? 'n' : 'b';
    int totalEncap = 0;
    if (map3D[0][0][0] == c && (map3D[0][0][1] == cOp || map3D[0][0][2] == cOp)) {totalEncap++;}
    if (map3D[0][2][0] == c && (map3D[0][2][1] == cOp || map3D[0][2][2] == cOp)) {totalEncap++;}
    if (map3D[2][0][0] == c && (map3D[2][0][1] == cOp || map3D[2][0][2] == cOp)) {totalEncap++;}
    if (map3D[2][2][0] == c && (map3D[2][2][1] == cOp || map3D[2][2][2] == cOp)) {totalEncap++;}
    return totalEncap;
}

/**
 * \fn int nbrEncapPetitMiddle(char c, char *** map3D)
 * \brief compte le nombre de petit gobble encapsulé dans les middles
 *  
 * \param[in] char c : caractere en question qui est encapsulé
 * \param[in] char ** map3D : map3D représentant la grille du jeu
 * 
 * \return int : Retourne le nombre d'encapsulations
 * 
 * \author DUPOIS Thomas
 */
int nbrEncapPetitMiddle(char c, char *** map3D)
{
    char cOp = (c == 'b') ? 'n' : 'b';
    int totalEncap = 0;
    if (map3D[0][1][0] == c && (map3D[0][1][1] == cOp || map3D[0][1][2] == cOp)) {totalEncap++;}
    if (map3D[1][0][0] == c && (map3D[1][0][1] == cOp || map3D[1][0][2] == cOp)) {totalEncap++;}
    if (map3D[1][2][0] == c && (map3D[1][2][1] == cOp || map3D[1][2][2] == cOp)) {totalEncap++;} 
    if (map3D[2][1][0] == c && (map3D[2][1][1] == cOp || map3D[2][1][2] == cOp)) {totalEncap++;}
    return totalEncap;
}

/**
 * \fn int nbrEncapPetitCenter(char c, char *** map3D)
 * \brief compte le nombre de petit gobble encapsulé au centre
 *  
 * \param[in] char c : caractere en question qui est encapsulé
 * \param[in] char ** map3D : map3D représentant la grille du jeu
 * 
 * \return int : Retourne le nombre d'encapsulations
 * 
 * \author DUPOIS Thomas
 */
int nbrEncapPetitCenter(char c, char *** map3D)
{
    char cOp = (c == 'b') ? 'n' : 'b';
    if (map3D[1][1][0] == c && (map3D[1][1][1] == cOp || map3D[1][1][2] == cOp))
        return 1;
    else
        return 0;
}

/**
 * \fn int nbrEncapMoyen(char c, char *** map3D)
 * \brief compte le nombre de moyen gobble encapsulé
 *  
 * \param[in] char c : caractere en question qui est encapsulé
 * \param[in] char ** map3D : map3D représentant la grille du jeu
 * 
 * \return int : Retourne le nombre d'encapsulation
 * 
 * \author DUPOIS Thomas
 */
int nbrEncapMoyen(char c, char *** map3D)
{
    char cOp = (c == 'b') ? 'n' : 'b';
    int totalEncap = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (map3D[i][j][1] == c && map3D[i][j][2] == cOp)
                totalEncap++;
        }
    }
    return totalEncap;
}

/**
 * \fn int nbrEncapMoyenCoin(char c, char *** map3D)
 * \brief compte le nombre de moyen gobble encapsulés dans les coins
 *  
 * \param[in] char c : caractere en question qui est encapsulé
 * \param[in] char ** map3D : map3D représentant la grille du jeu
 * 
 * \return int : Retourne le nombre d'encapsulation
 * 
 * \author DUPOIS Thomas
 */
int nbrEncapMoyenCoin(char c, char *** map3D)
{
    char cOp = (c == 'b') ? 'n' : 'b';
    int totalEncap = 0;
    if (map3D[0][0][1] == c && map3D[0][0][2] == cOp) {totalEncap++;}
    if (map3D[0][2][1] == c && map3D[0][2][2] == cOp) {totalEncap++;}  
    if (map3D[2][0][1] == c && map3D[2][0][2] == cOp) {totalEncap++;} 
    if (map3D[2][2][1] == c && map3D[2][2][2] == cOp) {totalEncap++;}  
    return totalEncap;
}

/**
 * \fn int nbrEncapMoyenMiddle(char c, char *** map3D)
 * \brief compte le nombre de moyen gobble encapsulés dans les middle
 *  
 * \param[in] char c : caractere en question qui est encapsulé
 * \param[in] char ** map3D : map3D représentant la grille du jeu
 * 
 * \return int : Retourne le nombre d'encapsulation
 * 
 * \author DUPOIS Thomas
 */
int nbrEncapMoyenMiddle(char c, char *** map3D)
{
    char cOp = (c == 'b') ? 'n' : 'b';
    int totalEncap = 0;
    if (map3D[0][1][1] == c && map3D[0][1][2] == cOp) {totalEncap++;}     
    if (map3D[1][0][1] == c && map3D[1][0][2] == cOp) {totalEncap++;}    
    if (map3D[1][2][1] == c && map3D[1][2][2] == cOp) {totalEncap++;}   
    if (map3D[2][1][1] == c && map3D[2][1][2] == cOp) {totalEncap++;}
    return totalEncap;
}

/**
 * \fn int nbrEncapMoyenCenter(char c, char *** map3D)
 * \brief compte le nombre de moyen gobble encapsulé au centre
 *  
 * \param[in] char c : caractere en question qui est encapsulé
 * \param[in] char ** map3D : map3D représentant la grille du jeu
 * 
 * \return int : Retourne le nombre d'encapsulations
 * 
 * \author DUPOIS Thomas
 */
int nbrEncapMoyenCenter(char c, char *** map3D)
{
    char cOp = (c == 'b') ? 'n' : 'b';
    if (map3D[1][1][1] == c && map3D[1][1][2] == cOp)
        return 1;
    else
        return 0;
}

/**
 * \fn int nbrCaseMaitre(char c, char ** map2D)
 * \brief compte le nombre de case maître du joueur
 *  
 * \param[in] char c : caractere en question
 * \param[in] char ** map2D : map2D représentant la grille du jeu
 * 
 * \return int : Retourne le nombre de case maitre
 * 
 * \author DUPOIS Thomas
 */
int nbrCaseMaitre(char c, char ** map2D)
{
    int totalCaseMaitre = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (map2D[i][j] == c)
                totalCaseMaitre++;
        }
    }
    return totalCaseMaitre;
}

/**
 * \fn int getCenter(char c, char ** map2D)
 * \brief le caractère en question est-il maitre du centre
 *  
 * \param[in] char c : caractere en question
 * \param[in] char ** map2D : map2D représentant la grille du jeu
 * 
 * \return int : Retourne un boolean
 * 
 * \author DUPOIS Thomas
 */
int getCenter(char c, char ** map2D)
{
    return (map2D[1][1] == c) ? 1 : 0;
}

/**
 * \fn int numberCoin(char c, char ** map2D)
 * \brief renvoie le nombre de piont dans les coin
 *  
 * \param[in] char c : caractere en question
 * \param[in] char ** map2D : map2D représentant la grille du jeu
 * 
 * \return int : Retourne le nombre total de coin dominé
 * 
 * \author DUPOIS Thomas
 */
int numberCoin(char c, char ** map2D)
{
    int totalNbrCoin = 0;
    if (map2D[0][0] == c) {totalNbrCoin++;}
    if (map2D[0][2] == c) {totalNbrCoin++;}
    if (map2D[2][0] == c) {totalNbrCoin++;}
    if (map2D[2][2] == c) {totalNbrCoin++;}
    return totalNbrCoin;
}

/**
 * \fn int numberMiddle(char c, char ** map2D)
 * \brief renvoie le nombre de piont dans les middle
 *  
 * \param[in] char c : caractere en question
 * \param[in] char ** map2D : map2D représentant la grille du jeu
 * 
 * \return int : Retourne le nombre total de middle dominé
 * 
 * \author DUPOIS Thomas
 */
int numberMiddle(char c, char ** map2D)
{
    int totalNbrMiddle = 0;
    if (map2D[0][1] == c) {totalNbrMiddle++;}
    if (map2D[1][0] == c) {totalNbrMiddle++;}
    if (map2D[1][2] == c) {totalNbrMiddle++;}
    if (map2D[2][1] == c) {totalNbrMiddle++;}
    return totalNbrMiddle;
}

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
int number_pion_gobe(char *** map3D, char c)
{
    int a;
    int count = 0;
    char cOp = (c == 'b') ? 'n': 'b';
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            a = 0;
            for(int k = 0; k < N; k++)
            {
                if (a && map3D[i][j][k] == c)
                    count++;
                if (map3D[i][j][k] == cOp)
                    a = 1;
            }
        }
    }
    return count;
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
int i10, int i11, int i12, int i13, int i14, int i15, int i16, int i17, int i18, int i19, 
int i20, int i21, int i22, int i23, int i24)
{
    int * tab = (int*) malloc(sizeof(int)*24);
    tab[0] = i1; tab[1] = i2; tab[2] = i3; tab[3] = i4;
    tab[4] = i5; tab[5] = i6; tab[6] = i7; tab[7] = i8;
    tab[8] = i9, tab[9] = i10; tab[10] = i11; tab[11] = i12;
    tab[12] = i13; tab[13] = i14; tab[14] = i15; tab[15] = i16; 
    tab[16] = i17; tab[17] = i18; tab[18] = i19; tab[19] = i20; 
    tab[20] = i21; tab[21] = i22; tab[22] = i23; tab[23] = i24;
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
        for (int i = 0; i < 24; i++)
        {   
	  sprintf(nbre,"%d",tabParam[i]);
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
    int i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14, i15, i16, i17, i18, i19, i20, i21, i22, i23, i24;
    int i = 0;
    printf("Test malloc ligne\n");
    char *file_contents = malloc(sizeof(char)*63);
    printf("test malloc ligne reussi\n");

    while (fscanf(f, "%[^\n] ", file_contents) != EOF) 
    {
        sscanf(file_contents,"%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;",&i1,&i2,&i3,&i4,&i5,&i6,&i7,&i8,&i9,&i10,&i11,&i12,&i13,&i14,&i15,&i16,&i17,&i18,&i19,&i20,&i21,&i22,&i23,&i24);
        printf("TEST continue i=%d\n", i);
        tabIA[i][0] = i1; tabIA[i][1] = i2; tabIA[i][2] = i3; tabIA[i][3] = i4; tabIA[i][4] = i5;
        tabIA[i][5] = i6; tabIA[i][6] = i7; tabIA[i][7] = i8; tabIA[i][8] = i9; tabIA[i][9] = i10;
        tabIA[i][10] = i11; tabIA[i][11] = i12; tabIA[i][12] = i13; tabIA[i][13] = i14; tabIA[i][14] = i15;
        tabIA[i][15] = i16; tabIA[i][16] = i17; tabIA[i][17] = i18; tabIA[i][18] = i19; tabIA[i][19] = i20;
        tabIA[i][20] = i21; tabIA[i][21] = i22; tabIA[i][22] = i23; tabIA[i][23] = i24;
        i++;
    }
    free(file_contents);
    fclose(f);
}

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
void readTheChampion(int ** tabIA, char nom[20])
{
    FILE *f;
    f = fopen(nom,"r");   
    int i1, i2, i3, i4, i5, i6, i7, i8, i9, i10, i11, i12, i13, i14;
    int i = 0;
    printf("Test malloc ligne\n");
    char *file_contents = malloc(sizeof(char)*120);
    printf("test malloc ligne reussi\n");
    /* Théoriquement, la boucle ci-dessous, ne s'execute qu'une seule fois */
    while (fscanf(f, "%[^\n] ", file_contents) != EOF) 
    {
        sscanf(file_contents,"%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;%i;",&i1,&i2,&i3,&i4,&i5,&i6,&i7,&i8,&i9,&i10,&i11,&i12,&i13,&i14);
        printf("TEST continue 2 i=%d\n", i);
        tabIA[0][0] = i1; tabIA[0][1] = i2; tabIA[0][2] = i3; tabIA[0][3] = i4; tabIA[0][4] = i5;
        tabIA[0][5] = i6; tabIA[0][6] = i7; tabIA[0][7] = i8; tabIA[0][8] = i9; tabIA[0][9] = i10;
        tabIA[0][10] = i11; tabIA[0][11] = i12; tabIA[0][12] = i13; tabIA[0][13] = i14;
        i++;
    }
    for(int k = i; k < 10; k++)
    {
        if(k < 6) // différence minime
        {
            for (int j = 0; j < 24; j++)
                tabIA[k][j] = tabIA[0][j] + rdm(-1,1); 
        }
        else if (k == 6)
        {
            for (int j = 0; j < 24; j++)
                tabIA[k][j] = rdm(-5,5);
        }
        else if (k > 6 && k < 9) //croisé
        {
            for (int j = 0; j < 24; j++)
            {
                if (j < 11)
                    tabIA[k][j] = tabIA[10-k][j];
                else
                    tabIA[k][j] = tabIA[9-k][j];
            } 
        }
        else //increase
        {
            for(int j = 0; j <24; j++)
                tabIA[k][j] = tabIA[0][j] + ((tabIA[0][j] > 0) ? 1 : ((tabIA[0][j] < 0) ? -1 : 0));
        }
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
int lectureDetection(char nameFile[35], char firstAvert[35], char secondAvert[35], int ** tabIA, int * champ)
{
    if (nbreChampion(nameFile) == 10)
    {
        printf("%s",firstAvert);
        readChampion(tabIA, nameFile);
        printf("%s", secondAvert);
        *champ = 1;
        clearFile(nameFile);
        return 1;
    }
    else
        return 0;
}






