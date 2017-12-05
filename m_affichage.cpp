#include <stdio.h>
#include <stdlib.h>
#include "t_communication.h"

//Affiche les stats dans un fichier dont le nom est 
//en constantes dans NOM_FICHIER_STATS
void afficher_stats(const t_communication* communication)
{
	//Pour tout suite, à l'écran
	printf("\nnb fichier : %d --- temps %lf en secondes",communication->nb_fic_envoye, (double) (communication->fin - communication ->debut) / CLOCKS_PER_SEC);
	system("pause");

}