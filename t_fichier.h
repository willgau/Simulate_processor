#ifndef _t_fichier__
#define _t_fichier__

#include "constantes.h"
#include "t_paquet.h"

/*
* Repr�sentation  : Un fichier a son tableau  de paquets* et le nombre d'octets actuellement 
*                             re�u et le id du fichier � g�n�rer lors de l'envoi.
*/
typedef struct
{
	//Tableau qui contient les paquets
	const t_paquet** tab;

	 char id[MAX_CAR_ID];

	//Nombre de paquets du fichier
	int nb_paquets;

}t_fichier;


//Retourne un fichier du bon nombre de paquets avec l'id fourni.
//Aucun paquet re�u encore.
t_fichier nouveau_fichier(int nb_paquets, const char id[MAX_CAR_ID]);

//Place le paquet selon son num_paquet dans le tableau de paquets
void placer_paquet(t_fichier* fichier, const  t_paquet* paquet);

//Envoie le fichier dans un fichier sur disque au nom de l'identifiant du fichier
void ecrire_fichier (t_fichier* fichier);

//Lib�re le fichier et les paquets.  Le tableau est mis � NULL
void liberer_paquets(t_fichier* fichier);

//Retourne si le fichier a �t� envoy�
int fichier_est_envoye (const t_fichier* fichier);
 
#endif