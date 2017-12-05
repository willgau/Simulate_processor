#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "t_fichier.h"

t_fichier nouveau_fichier(int nb_paquets, const char id[MAX_CAR_ID]){
	t_fichier nouveau_fichier;

	nouveau_fichier.nb_paquets = nb_paquets;
	strcpy(nouveau_fichier.id, id);
	
	nouveau_fichier.tab = (const t_paquet**) calloc (nouveau_fichier.nb_paquets, sizeof(const t_paquet*));

	return nouveau_fichier;
}

void placer_paquet(t_fichier* fichier, const  t_paquet* paquet){
	fichier->tab[paquet->num_paquet] = paquet;
}

void ecrire_fichier (t_fichier* fichier){
	FILE* file = fopen(fichier->id, "wb");
	int i;

	for (i=0;i < fichier->nb_paquets;i++){
		fwrite(fichier->tab[i]->buffer,sizeof(unsigned char), fichier->tab[i]->taille_paquet,file);
	}
	fclose(file);
}

void liberer_paquets(t_fichier* fichier){
	free(fichier->tab);
	fichier->tab = NULL;

	fichier = NULL;
}

int fichier_est_envoye (const t_fichier* fichier){

	int resultat;

	FILE* file = fopen(fichier->id, "rt");

	if(file == NULL)
		resultat = FALSE;
	else
		resultat = TRUE;

	fclose(file);

	return resultat;
}