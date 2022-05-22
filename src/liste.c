/**
 * \file liste.c
 * 
 * \brief Fichier contenant les codes des fonctions permettant la créations de listes
 * 
 * \author DUPOIS Thomas
 */

/**
 * \fn liste * createListe()
 * \brief creer une liste
 *  
 * \param[in] void : pas de paramètre
 * 
 * \return liste * : Retourne la liste cree
 * 
 * \author DUPOIS Thomas
 */
liste * createListe()
{
    liste * l = malloc(sizeof(liste));
    l->value = -1;
    l->suivant = NULL;
    return l;
}


/**
 * \fn void add(liste * l, int n)
 * \brief ajoute un élément au début d'une liste
 *  
 * \param[in] liste * l : liste dans laquelle on ajoute l'élément
 * \param[in] int n : élément à ajouter
 * 
 * \return void : Ne retourne rien
 * 
 * \author DUPOIS Thomas
 */
void add(liste * l, int n)
{
    if (-1 == l->value)
        l->value = n;
    else
    {
        while (l->suivant != NULL)
        {
            l = l->suivant;
        }
        liste * l2 = createListe();
        l2->value = n;
        l->suivant = l2;
    }
}

/**
 * \fn void clear(liste * l)
 * \brief reset une liste
 *  
 * \param[in] liste * l : liste qui va être reset
 * 
 * \return void : Ne retourne rien
 * 
 * \author DUPOIS Thomas
 */
void clear(liste * l)
{
    liste * l2 = l->suivant;
    while(l2 != NULL)
    {
        liste * l3 = l2->suivant;
        free(l2);
        l2 = l3;
    }
    l->value = -1;
    l->suivant = NULL;
}

/**
 * \fn int contains(liste * l, int n)
 * \brief renvoie 0 ou 1 selon si la liste contient l'élément
 *  
 * \param[in] liste * l : liste utilisée
 * 
 * \return int : Retourne 1 ou 0
 * 
 * \author DUPOIS Thomas
 */
int contains(liste * l, int n)
{
    while(l != NULL)
    {
        if (l->value == n)
            return 1;
        l = l->suivant;
    }
    return 0;
}

/**
 * \fn int size(liste * l)
 * \brief renvoie la taille de la liste
 *  
 * \param[in] liste * l : liste utilisée
 * 
 * \return int : Retourne la taille de la liste
 * 
 * \author DUPOIS Thomas
 */
int size(liste * l)
{
    int n = 0;
    while(l != NULL)
    {
        l = l->suivant;
        n++;
    }
    return n;
}

/**
 * \fn void afficheListe(liste * l)
 * \brief affiche la liste
 *  
 * \param[in] liste * l : liste utilisée
 * 
 * \return void : ne retourne rien
 * 
 * \author DUPOIS Thomas
 */
void afficheListe(liste * l)
{
    printf("--- Liste ---\n");
    while(l != NULL)
    {
        printf("->%d ", l->value);
        l = l->suivant;
    }
    printf("\n");
}

/**
 * \fn int get(liste * l, int n)
 * \brief renvoie la valeur contenu dans l'indice à l'index n
 *  
 * \param[in] liste * l : liste utilisée
 * \param[in] int n : index
 * 
 * \return int : Retourne l'élément à l'index n
 * 
 * \author DUPOIS Thomas
 */
int get(liste * l, int n)
{
    int i = 0;
    while(i < n)
    {
        l = l->suivant;
        i++;
    }
    return l->value;
}





