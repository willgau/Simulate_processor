/*************************************************
Travail Pratique #3 ; Module t_communication.cpp
Vincent Cournoyer
William Gauvin
Bastien Giroux
Olivier Pelletier
3 Decembre 2015
**************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "t_liste.h"
#include "t_fichier.h"
#include "m_emission.h"
#include "m_traitement.h"
#include "t_communication.h"
#include "t_paquet.h"
#include "constantes.h"
#include "m_affichage.h"
#include "t_file.h"
#include "t_processeur.h"



//Prépare la communication selon le module de traitement inclus en initialisant la liste
//de processeur,la liste de files et la liste de fichiers. En plus d'initialiser le fichier
//comprenant les noms de fichier et en mettant le nombre de fichier Null.
void init_communication(t_communication* communication) {

	//Initialise la liste de processeurs et la liste de files à l’aide de 
	//init_traitement ainsi que la liste de fichiers.
	init_traitement(&communication->lst_processeurs,&communication ->lst_files);
	init_liste(&communication->lst_fic);


	//Initialise l’émission avec le fichier comprenant les noms de fichier et
	//met le nombre de fichiers envoyé à 0.
	init_emission(NOM_FICHIER);
	communication->nb_fic_envoye = 0;
}
//Obtient les paquets en provenance du module t_emission
//les distribue et les traite.
void demarrer_communication(t_communication* communication) {
	//Mis à TRUE lorsque tous les paquets ont été traités.
	int fini = FALSE;

	//Sert à obtenir les paquets en émission.  
	t_paquet* paquet = (t_paquet*)malloc(sizeof(t_paquet));

	communication->debut = clock();

	while (!fini)
	{
		//Si get_paquet retourne FALSE, il n'y a plus rien à recevoir
		if (get_paquet(paquet))
		{
			//On sert un paquet des files
			traiter_arrivee_paquet(paquet, &communication->lst_files,
				&communication->lst_processeurs);
		}

		//On distribue le prochain paquet à une file
		distribuer_paquet(&communication->lst_files,
			&communication->lst_processeurs);

		//On sert les paquets.  S'il y a eu un fichier envoyé, on incrémente 
		//le compteur pour les stats de fin
		communication->nb_fic_envoye +=
			servir_prochain_paquet(&communication->lst_processeurs,
				&communication->lst_files,
				&communication->lst_fic);

		//DEBUG
		printf("\n\nb envoye %d", communication->nb_fic_envoye);

		fini = communication_finie(communication);

		if (!fini)

			//Un nouveau paquet à chaque tour
			paquet = (t_paquet*)malloc(sizeof(t_paquet));
	}
	communication->fin = clock();
}


int communication_finie(t_communication* communication) {
	int i;
	int j;
	int fini = FALSE;

	t_file* file_fini;
	t_processeur* processeur_fini;
	t_paquet* paquet_fini;

	paquet_fini = (t_paquet*)malloc(sizeof(t_paquet));

	for (i = 0; i < NB_PROCESSEUR; i++) {
		processeur_fini = (t_processeur*)communication->lst_processeurs.pc->element;
		if (processeur_fini->disponible) {
			for (j = 0; j < NB_FILE; j++) {
				file_fini = (t_file*)communication->lst_files.pc->element;
				if (file_est_vide(file_fini)) {
					if (!get_paquet(paquet_fini))
						fini = TRUE;
					else
						traiter_paquet((t_processeur*)communication->lst_processeurs.pc->element, &communication->lst_fic);
				}
			}
		}
	}

	return fini;
}
