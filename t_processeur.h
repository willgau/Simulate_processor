#ifndef  _T_processeur__
#define _T_processeur__

#include "constantes.h"
#include "t_fichier.h"
#include "t_paquet.h"
#include "t_liste.h"

/*
* Dans le contexte de la communication (voir �nonc�), un processeur permet la 
* reconstitution des fichiers en mettant le paquet en traitement � son endroit sp�cifique
* dans son fichier respectif.  Dans la communication, le processeur a un temps de r�ponse d� � sa 
* cat�gorie (LENT, MOYEN, RAPIDE).
*
*/
//D�finition d'un guichet avec sa propre file d'attente
typedef struct
{
	//L'adresse du paquet en cours de traitement
	const t_paquet* paquet_en_traitement;

	//Bool�en qui indique si le processeur est disponible
	int disponible;

	//Le temps de d�part est initialis� � la cat�gorie * le nombre
	//d'octets du paquet et le FACTEUR_VITESSE
	//Il est d�cr�ment� � chaque traitement
	int temps_restant;

	//LENT, MOYEN ou RAPIDE
	int categorie;

}t_processeur;


//La proc�dure traiter_paquet est celle qui d�clenche la 
//cr�ation dynamique des paquets (nouveau_fichier) si c�est le premier
//paquet d�un fichier .  L�id du fichier est celui du paquet pr�fix� 
//du mot � copie �.  En s�quence, on d�cr�mente le temps restant. 
//S'il devient 0, le paquet est mis � sa position dans le tableau de 
//paquets du fichier. Le processeur redevient disponible. Si le fichier 
//est complet , il est �crit sur disque.  De plus, elle retourne TRUE 
//si le fichier de ce paquet a �t� �crit sur disque et FALSE dans le 
//cas contraire.  Lorsque le fichier est �crit, l�espace allou� pour les 
//paquets et celle du fichier sont lib�r�s
//int traiter_paquet(t_processeur* processeur, t_fichier* fichier);
int traiter_paquet(t_processeur* processeur, t_liste* lst_fic);

//Assigne le paquet en t�te de file au processeur re�u.  Le processeur est mis
//non disponible. et le temps restant est ajust�.
void servir_paquet(t_processeur* processeur, const t_paquet* paquet);

int fichier_pos_element(t_liste* liste, t_elements element);


#endif