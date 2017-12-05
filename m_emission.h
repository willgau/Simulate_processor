/*==========================================================*/

/*==========================================================*/
/* Le module offre un type et deux  fonctions :

    La fonction d'intialisation qui prend les noms de fichier dans un fichier texte
	dont le nom ets fourni.
	void init_emission(const char* nom_fic);

	une  fonction pour émettre un paquet, le paquet obtenu peut provenir 
	de tout fichier actuellement en traitement
	int get_paquet(t_paquet* p);

*/
/*==========================================================*/
#ifndef _MEMISSION_5_
#define _MEMISSION_5_

/*==========================================================*/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <assert.h>

#include "mtwister.h"
#include "t_paquet.h"

/*==========================================================*/
// LES CONSTANTES

// deux servent à définir la taille minimum et maximum d'un paquet
#define TAIL_MIN_PAQUET 100 
#define TAIL_MAX_PAQUET 256 

/*==========================================================*/

/*==========================================================*/

//Prépare l'émetteur en lui donnant les fichiers à transmettre
void	init_emission(const char* nom_fic);

/*
fonction qui retourne le nombre de fichiers actuellement paquetés...

PARAMETRE(s): une référence sur un paquet

SORTIE: 1 si un paquet a été obtenu ou 0 sinon (si tous les fichiers sont épuisés)

SPECS:  un paquet obtenu peut venir d'un quelconque fichier en cours de traitement
		le client ne peut contrôler la provenance du paquet si plus d'un fichier sont
		traités simultanément.
*/
int get_paquet(t_paquet* p);
/*==========================================================*/

/*==========================================================*/
#endif	
/*==========================================================*/