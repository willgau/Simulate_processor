#include <stdlib.h>
#include <stdio.h>
#include <random>

#include "constantes.h"
#include "t_processeur.h"
#include "t_file.h"
#include "m_traitement.h"
#include "module_utilitaire.h"


void init_traitement(t_liste* lst_processeurs, t_liste* lst_files){
	int i; //compteur
	t_processeur* nouveau_processeur;
	t_file* nouvelle_file;

	init_liste(lst_files);
	init_liste(lst_processeurs);

	for (i = 0; i < NB_PROCESSEUR; i++) {
		nouveau_processeur = (t_processeur*)malloc(sizeof(t_processeur));
		init_processeur(nouveau_processeur);
		inserer_debut(lst_processeurs,nouveau_processeur);
	}
	for (i = 0; i < NB_FILE; i++) {
		nouvelle_file = (t_file*) malloc (sizeof(t_file));
		init_file(nouvelle_file);
		inserer_debut(lst_files,nouvelle_file);
	}



}
void init_processeur(t_processeur* processeur) {
	processeur->categorie = choix_categorie();
	processeur->disponible = TRUE;
	processeur->paquet_en_traitement = NULL;
	processeur->temps_restant = NULL;

}

int traiter_arrivee_paquet(const t_paquet* paquet, t_liste* lst_files,t_liste* lst_processeurs){
	int paquet_arrive = FALSE;

	while (lst_files->pc->suivant != NULL || !paquet_arrive) {
		if (!file_est_pleine((t_file*)lst_files->pc->element)) {
			enfiler((t_file*)lst_files->pc->element, paquet);
			paquet_arrive = TRUE;
		}
	}	
	return paquet_arrive;	
}

void distribuer_paquet(t_liste* lst_files, t_liste* lst_processeurs) {
	int i;
	t_processeur* processeur_dispo;
	
	t_file* file_dispo;

	set_pc_debut(lst_files);
	set_pc_debut(lst_processeurs);

	for (i = 0; i < NB_PROCESSEUR; i++) {
		processeur_dispo = (t_processeur*)lst_processeurs->pc->element;
		file_dispo = (t_file*)lst_files->pc->element;

		if (processeur_dispo->disponible && file_est_vide(file_dispo)) {
			processeur_dispo->paquet_en_traitement = defile(file_dispo);
			lst_processeurs->pc->element = processeur_dispo;
		}
		set_pc_suivant(lst_files);
		set_pc_suivant(lst_processeurs);
	}	
}

int servir_prochain_paquet(t_liste* lst_processeurs,t_liste* lst_files,t_liste* lst_fic){
	
	return traiter_paquet((t_processeur*)lst_processeurs->pc->element, lst_fic);

}

//Genere un entier entre MIN_CATEGORIE et MAX_CATEGORIE
int alea_categorie(int min,int max){

//Strategie, on utilise le generateur de C qui retourne une valeur en 1 et 3
return rand() % (max - min + 1) + min ;
}

int choix_categorie(){

int choix;

	choix = alea_categorie(MIN_CATEGORIE,MAX_CATEGORIE);

	switch (choix) {

	case 1: choix = LENT; break;
	case 2: choix = MOYEN; break;
	case 3: choix = RAPIDE; break;

	}
	return choix;
}
void init_traitement(t_liste* lst_processeurs,  t_liste* lst_files);