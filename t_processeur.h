#ifndef  _T_processeur__
#define _T_processeur__

#include "constantes.h"
#include "t_fichier.h"
#include "t_paquet.h"
#include "t_liste.h"

/*
* Dans le contexte de la communication (voir énoncé), un processeur permet la 
* reconstitution des fichiers en mettant le paquet en traitement à son endroit spécifique
* dans son fichier respectif.  Dans la communication, le processeur a un temps de réponse dû à sa 
* catégorie (LENT, MOYEN, RAPIDE).
*
*/
//Définition d'un guichet avec sa propre file d'attente
typedef struct
{
	//L'adresse du paquet en cours de traitement
	const t_paquet* paquet_en_traitement;

	//Booléen qui indique si le processeur est disponible
	int disponible;

	//Le temps de départ est initialisé à la catégorie * le nombre
	//d'octets du paquet et le FACTEUR_VITESSE
	//Il est décrémenté à chaque traitement
	int temps_restant;

	//LENT, MOYEN ou RAPIDE
	int categorie;

}t_processeur;


//La procédure traiter_paquet est celle qui déclenche la 
//création dynamique des paquets (nouveau_fichier) si c’est le premier
//paquet d’un fichier .  L’id du fichier est celui du paquet préfixé 
//du mot « copie ».  En séquence, on décrémente le temps restant. 
//S'il devient 0, le paquet est mis à sa position dans le tableau de 
//paquets du fichier. Le processeur redevient disponible. Si le fichier 
//est complet , il est écrit sur disque.  De plus, elle retourne TRUE 
//si le fichier de ce paquet a été écrit sur disque et FALSE dans le 
//cas contraire.  Lorsque le fichier est écrit, l’espace alloué pour les 
//paquets et celle du fichier sont libérés
//int traiter_paquet(t_processeur* processeur, t_fichier* fichier);
int traiter_paquet(t_processeur* processeur, t_liste* lst_fic);

//Assigne le paquet en tête de file au processeur reçu.  Le processeur est mis
//non disponible. et le temps restant est ajusté.
void servir_paquet(t_processeur* processeur, const t_paquet* paquet);

int fichier_pos_element(t_liste* liste, t_elements element);


#endif