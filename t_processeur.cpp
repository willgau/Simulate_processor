#include <stdio.h>
#include <stdlib.h>
#include "t_fichier.h"
#include "t_processeur.h"
#include "t_paquet.h"
#include "t_liste.h"


/*int traiter_paquet(t_processeur* processeur, t_fichier* fichier){
	
	int i;
	int nb_fichier_ecrit = 0;

	for (i = processeur->temps_restant; i >= 0; i--){
		if (!i){
			placer_paquet( fichier,	processeur ->paquet_en_traitement);
		
			if(fichier ->tab[fichier -> nb_paquets - 1]){
				ecrire_fichier (fichier);
				liberer_paquets(fichier);
				nb_fichier_ecrit ++;
			}
			processeur ->disponible = TRUE;
		}	
	}
	return nb_fichier_ecrit;
}*/

void servir_paquet(t_processeur* processeur, const t_paquet* paquet){
	
	//ASSOCIÉ LE PAQUET AU PROCESSEUR
	processeur -> paquet_en_traitement = paquet;

	processeur->disponible = FALSE;
	processeur->temps_restant = ((processeur->categorie) * (paquet->taille_paquet)) / FACTEUR_VITESSE;
}
int traiter_paquet(t_processeur* processeur, t_liste* lst_fic) {

	int i;
	int nb_fichier_ecrit = 0;
	t_fichier* nouveau_fic;
	int trouve;


	for (i = processeur->temps_restant; i >= 0; i--) {
		if (!i) {
			
		
			trouve = fichier_pos_element(lst_fic,(t_elements)processeur ->paquet_en_traitement->id_unique);
			if (!trouve) {
				//sil nexiste pas
				*nouveau_fic = nouveau_fichier(processeur->paquet_en_traitement->nb_total_paquet, processeur->paquet_en_traitement->id_unique);

				inserer_debut(lst_fic, nouveau_fic);
			}
			else
				nouveau_fic=(t_fichier*)obtenir_element(lst_fic);

			placer_paquet(nouveau_fic, processeur->paquet_en_traitement);
			
			if (nouveau_fic->tab[nouveau_fic->nb_paquets - 1]) {
				ecrire_fichier(nouveau_fic);
				liberer_paquets(nouveau_fic);
				supprimer(lst_fic);
				nb_fichier_ecrit++;
			}
			processeur->disponible = TRUE;
		}
	}
	return nb_fichier_ecrit;
}

//La position est sur l'élément 
int fichier_pos_element(t_liste* liste, t_elements element) {
	t_noeud* tmp;
	int trouve = FALSE;

	if (!est_vide(liste)) {
		tmp= liste->debut;

		while (tmp->suivant != NULL && tmp->element != element) {
			tmp = tmp->suivant;
		}
		trouve = tmp != NULL;
	}
	return trouve;
}


