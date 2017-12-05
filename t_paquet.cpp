/* 
   Vincent Cournoyer
   William Gauvin
   Bastien Giroux
   Olivier Peletier 

   Code utilisée pour reconstituer les fichiers à partir d'un paquet
   Il contient les données et les informations 
   pertinentes à la reconstruction du fichier emis.

*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "t_paquet.h"

void  affich_paquet( const t_paquet * p){

	printf("\n Le nom de l'identifiant est : %s", p->id_unique);
	printf("\n C'est le paquet numéro %d du fichier %s", p->num_paquet, p->id_unique);
	printf("\n Le nombre total de paquet que donnera ce fchier est : %d", p->nb_total_paquet);
	printf("\n La taille en bytes du contenu du paquet est : %d", p->taille_paquet);
	printf("\n Le nombre d'octets du paquets est : %s", p->buffer);

	system("pause");

}