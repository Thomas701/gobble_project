/**
 * \file liste.h
 * 
 * \brief Fichier contenant les codes des fonctions permettant la créations de listes
 * 
 * \author DUPOIS Thomas
 */

#ifndef LISTE_H_
#define LISTE_H_

// Structure liste
typedef struct liste
{
    int value;
    struct liste * suivant;
} liste;

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
liste * createListe();

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
void add(liste * l, int n);

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
void clear(liste * l);

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
int contains(liste * l, int n);

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
int size(liste * l);

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
void afficheListe(liste * l);

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
int get(liste * l, int n);

#endif