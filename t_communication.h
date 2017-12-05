#ifndef _T_communication__
#define _T_communication__

#include <time.h>

//#include "t_liste.h"
#include "t_fichier.h"
#include "m_emission.h"
#include "m_traitement.h"


/*
* La communication de reconstruction de fichiers par un processeur 
* 
*/
typedef struct
{
	//Les processeurs sont générés dynamiquement au début
	//de la communication.   
	//Le nombre dépend du module de traitement
	t_liste lst_processeurs;

	//Liste de  files statiques. 
	//Le nombre dépend du module de traitement
	t_liste lst_files;

	//Liste contenant les fichiers à reconstituer
	//Le nombre dépend du module d’émission et
	//nous ne le connaissons pas à l’avance.
	t_liste lst_fic;

	//Pour fin statistiques
	int nb_fic_envoye;

	//Les temps de reconstitution des fichiers
	clock_t debut;
	clock_t fin;


}t_communication;

//Prépare la communication selon le module de traitement inclus
void init_communication(t_communication* communication);

//Obtient les paquets en provenance du module t_emission
//les distribue et les traite.
void demarrer_communication(t_communication* communication);

//On ne reçoit plus de paquet et tous les processeurs sont disponibles et 
//toutes les files sont vides.Tous les fichiers devraient avoir été écrits.
int communication_finie(t_communication* communication);

#endif