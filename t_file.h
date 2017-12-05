#ifndef _T_FILE_PAQUET__
#define _T_FILE_PAQUET__

#include "constantes.h"
#include "t_paquet.h"

/*
* File statique de t_paquets* dont la dimension 
* est fixée à la taille MAX_PAQUETS_PAR_FILE
*
*/

typedef  const t_paquet* t_element;

#define FILE_VIDE -1

typedef struct
{
	t_element tab[MAX_PAQUET_PAR_FILE];
	int nb_elements;

	int debut;
	int fin;

}t_file;

//Initialise la file à vide
void init_file(t_file* file);

//Met l'élément en fin de file
void enfiler(t_file* file,t_element element);

//Retourne l'élément en tête de file
t_element defile(t_file* file);

//Retourne le nombre d'éléments
int obtenir_nb_elements(t_file* file);

//Fonction booléenne qui retourne si la file
//est pleine
int file_est_pleine(t_file* file);

//Fonction booléenne qui retourne si la file
//est vide
int file_est_vide(t_file* file);

#endif