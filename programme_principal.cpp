#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
* Strat�gie : La communication se d�marre dans la fonction main() mais elle est g�r� par le module t_communication.
*                Il contient le processeur, l'espace pour le fichier � reconstruire, et utilie  les algorithmes de traitement 
*                de pqquets qui sont dans le module traitement.  
*/
#include "t_communication.h"
#include "m_affichage.h"
#include "constantes.h"

int main(void)
{
	srand(time(NULL));
	//Contient le processeur, la file et le fichier � 
	//reconstituer (�ventuellement pls)
	t_communication communication;

	//Cr�e les files et les processeurs selon le 
	//traitement chosi dans t_communication
	init_communication(&communication);

	//Distribue les paquets
	demarrer_communication(&communication);

	afficher_stats(&communication);

	return EXIT_SUCCESS;
}