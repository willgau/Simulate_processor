#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
* Stratégie : La communication se démarre dans la fonction main() mais elle est géré par le module t_communication.
*                Il contient le processeur, l'espace pour le fichier à reconstruire, et utilie  les algorithmes de traitement 
*                de pqquets qui sont dans le module traitement.  
*/
#include "t_communication.h"
#include "m_affichage.h"
#include "constantes.h"

int main(void)
{
	srand(time(NULL));
	//Contient le processeur, la file et le fichier à 
	//reconstituer (éventuellement pls)
	t_communication communication;

	//Crée les files et les processeurs selon le 
	//traitement chosi dans t_communication
	init_communication(&communication);

	//Distribue les paquets
	demarrer_communication(&communication);

	afficher_stats(&communication);

	return EXIT_SUCCESS;
}