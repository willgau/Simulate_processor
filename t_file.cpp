#include <stdio.h>
#include <stdlib.h>
#include "t_file.h"

//Initialise la file a vide
void init_file(t_file* file){
	file->debut = FILE_VIDE;
	file->fin = FILE_VIDE;
	file->nb_elements = 0;
	file->tab[MAX_PAQUET_PAR_FILE] = NULL;
}

//Met l'élément en fin de file
void enfiler(t_file* file, t_element element){
	
	if (!file_est_pleine (file)){
		
		//première fois
		if ( file ->nb_elements == 0){
			file ->debut = 0;
			file ->fin = 0;
		}
		
		else{
			file -> fin = (file -> fin++) % MAX_PAQUET_PAR_FILE;
			file -> tab [file ->fin] = element;
		}
	file ->nb_elements++;
	}
}

//Fonction booléenne qui retourne si la file
//est pleine
int file_est_pleine(t_file* file){
	
	return file ->nb_elements == MAX_PAQUET_PAR_FILE;
}
//Fonction booléenne qui retourne si la file
//est vide
int file_est_vide(t_file* file){
	
	return file -> nb_elements;
}


//Retourne l'élément en tête de file
t_element defile(t_file* file){
	
	t_element element;

	if (file_est_vide (file)){
		element = file ->tab[file ->debut];
		file -> debut = ( file ->debut++) % MAX_PAQUET_PAR_FILE;
		file -> nb_elements --;
			if(file -> nb_elements ==0)
				file -> debut = file ->fin = FILE_VIDE;
	}

return element;
}

//Retourne le nombre d'éléments
int obtenir_nb_elements(t_file* file){
	
	return file -> nb_elements;
}