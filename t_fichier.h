#ifndef _t_fichier__
#define _t_fichier__

#include "constantes.h"
#include "t_paquet.h"

/*
* Représentation  : Un fichier a son tableau  de paquets* et le nombre d'octets actuellement 
*                             reçu et le id du fichier à générer lors de l'envoi.
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
//Aucun paquet reçu encore.
t_fichier nouveau_fichier(int nb_paquets, const char id[MAX_CAR_ID]);

//Place le paquet selon son num_paquet dans le tableau de paquets
void placer_paquet(t_fichier* fichier, const  t_paquet* paquet);

//Envoie le fichier dans un fichier sur disque au nom de l'identifiant du fichier
void ecrire_fichier (t_fichier* fichier);

//Libère le fichier et les paquets.  Le tableau est mis à NULL
void liberer_paquets(t_fichier* fichier);

//Retourne si le fichier a été envoyé
int fichier_est_envoye (const t_fichier* fichier);
 
#endif