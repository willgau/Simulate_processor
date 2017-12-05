#ifndef _T_PAQUET__
#define _T_PAQUET__

/*
*Ce module repr�sente un paquet dans un contexte de communication de
*donn�es provenant d'un �metteur.  Il contient les donn�es et les informations 
*pertinentes � la reconstruction du fichier emis.
*
*tp3 inf145 A15 (voir �nonc�)
*
*/

#include "constantes.h"

typedef struct
{

	//Combienti�me paquet du fichier
	int num_paquet; 

	// La taille en bytes du contenu du paquet
	int taille_paquet ; 

	//Les fichiers sont des char mais imagine
	//des bytes.
	unsigned char * buffer ;
	
	// Nombre total de paquets que donnera ce fichier
	int nb_total_paquet; 

	 //Nom de l'identifiant (nom de fichier pour le tp).
	char id_unique[MAX_CAR_ID]; 

}t_paquet;

// ATTENTION CELLE-CI NE SERA
// UTILE QU'EN D�BUG
void affich_paquet( const t_paquet * p);
/*==========================================================*/


#endif