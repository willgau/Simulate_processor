#include <stdlib.h>

#include "t_liste.h"

/*
* STRATÉGIE : Une liste simplement chaînée avec un noeud
*                        contenant l'élément et un lien vers son suivant.
*
*
*  Pour la liste, on conserve l'adresse du noeud de début, de fin, 
*  de position courante et le nombre d'éléments.
*
*  Chacun est mis à jour par les SP disponibles et les stratégies y 
*  sont expliquées en commentaires.
*
* L'allocation de la liste et des noeuds sont dynamiques
*
*/
static t_noeud* nouveau_noeud(t_elements element, t_noeud* lien)
{
	//Les noeuds sont dynamiques.  On crée d'abord le noeud
	t_noeud* n = (t_noeud*) malloc(sizeof(t_noeud));

	//On l'initialise avec les valeurs reçues
	n->element = element;
	n->suivant = lien;

	//On retourne le noeud
	return n;
}

//Retourne une liste initialisée et vide
void init_liste(t_liste* liste)
{
	liste->debut = NULL;
	liste->fin = NULL;
	liste->pc = NULL;
	liste->nbr_element = 0;

}

//Les informatrices booléennes de base
int est_vide(const t_liste* liste)
{
	//On retourne s'il y a des éléments ou non
	return liste->nbr_element == 0;
}


//L'accesseur d'élément à la position courante
//sans l'enlever ni déplacer la position courante
t_elements obtenir_element(const t_liste* liste)
{
	return liste->pc->element;
}

//Accesseur du nombre d'éléments
int obtenir_nb_elements(const t_liste* liste)
{
	return liste->nbr_element;
}


//Dans tous les cas, la position courante est sur l'élément ajouté après l'insertion
void inserer_debut(t_liste* liste, t_elements element)
{
	//Sert à obtenir un nouveau noeud
    //(Notez que la gestion des 
	//liens est faite grâce à liste->debut)
	t_noeud* n = nouveau_noeud(element, liste->debut);
	
	//Le début et la pc sont sur le nouveau noeud c'est sûr
	liste->debut = n;
	liste->pc = n;

	//La première fois, il faut aussi ajuster le pointeur de fin (juste cette fois)
	if(est_vide(liste))
	{
		liste->fin = n;
	}


	//un élément de plus
	liste->nbr_element++;
}


void inserer_apres_pc(t_liste* liste, t_elements element)
{
	//Sert à retenir des adresses de noeud temporairemnt
	t_noeud* n;

	//Si c'est vide on utilise la procédure prévue
	if(est_vide(liste))
		inserer_debut(liste,element);

	else
	{

		//On crée un noeud avec un lien suivant de la pc
		n = nouveau_noeud(element, liste->pc->suivant);

		//Si on ajoute après le dernier
		if(liste->pc == liste->fin)
		{
			//On place la fin sur le nouveau noeud
			liste->fin = n;
		}

		//On ajuste le chaînage du noeud de la pc
		liste->pc->suivant = n;

		//On met la pc sur le nouveau noeud
		liste->pc = n;

		//un élément de plus
		liste->nbr_element++;

	}

}

void inserer_avant_pc(t_liste* liste, t_elements element)
{

	/*STRATÉGIE : On insère après mais on interchange les données.
	*
	*             Pour l'utilisateur, cela ne paraît pas mais cela évite
	*             de parcourir la liste.
	*
	*          
	*/

	//Sert à obtenir l'élément de la liste pour l'échange
	t_elements elementTransfere ;

	//Si c'est vide, ou que pc est au début,
	//on utilise la procédure prévue pour insérer au début
	if(est_vide(liste) || liste->pc == liste->debut)
		inserer_debut(liste,element);

	else
	{

		//On retient l'élément du noeud qui est à la pc
		elementTransfere = obtenir_element(liste);

		//On retient la pc pour la replacer après l'insertion
		t_noeud* tmp =liste->pc;

		//On insérer un noeud après la pc avec l'élément retenu
		inserer_apres_pc(liste, elementTransfere);

		//On remplace la valeur de l'élément du noeud à la pc par l'élément reçu
		liste->pc->element = element;

		//Il faut replacer la pc sur le noeud qui contient
		//l'élément qui vient d'être inséré
		liste->pc = tmp;

	}

}


void inserer_fin(t_liste* liste, t_elements element)
{

	//Stratégie : On déplace simplement la position courante
	//à la fin et on insère après à l'aide de la procédure locale.
	set_pc_fin(liste);
	inserer_apres_pc(liste,element);
}

//Supprime la valeur à la position courante.  La position courante est sur le prochain
//noeud sur le dernier ou null si vide.
void supprimer(t_liste* liste)
{
	
	//STRATÉGIE : On triche en supprimant le noeud
	//                      suivant et en replaçant son élément dans le noeud de la pc.
	//                      Cela évite de parcourir toute la liste sauf si l'élément 
	//                       est le dernier.

	//                      Sauf évidemment pour le premier, le dernier noeud et lorsqu'il y 
	//                      un seul élément qui sont des cas spéciaux.
	if (obtenir_nb_elements(liste) == 1) {

		//on libère l'espace mémoire
		free(liste->pc);
		//on initialise la liste pour mettre tout à 0 ou à NULL
		init_liste(liste);

	}
	else if (!est_vide(liste)) {
		if (liste->pc == liste->debut) {

			//On remplace l'élément de la position courante par celui de la position suivante
			liste->pc->element = liste->pc->suivant->element;
			//On remplace le pointeur suivant de la position courante par celui de la position suivante
			liste->pc->suivant = liste->pc->suivant->suivant;
			//on libère l'espace mémoire
			free(liste->pc->suivant);

			//on change le debut de la liste pour la position courante
			liste->debut = liste->pc;

		}
		else if (liste->pc == liste->fin) {

			//pointeur qui retient la position courante de départ
			t_noeud* ptr_noeud_a_supprimer = liste->pc;
			//on libère l'espace mémoire
			free(liste->pc);
			//on positionne la position courante au debut de la liste
			set_pc_debut(liste);

			//boucle qui positionne pc au noeud précédent
			while (liste->pc->suivant != ptr_noeud_a_supprimer) {
				set_pc_suivant(liste);
			}

			//on met à NULL le pointeur suivant de la position courante
			liste->pc->suivant = NULL;
			//on change la fin de la liste pour la position courante
			liste->fin = liste->pc;

		}
		else {

			//On remplace l'élément de la position courante par celui de la position suivante
			liste->pc->element = liste->pc->suivant->element;
			//On remplace le pointeur suivant de la position courante par celui de la position suivante
			liste->pc->suivant = liste->pc->suivant->suivant;
			//on libère l'espace mémoire
			free(liste->pc->suivant);

		}

		//on décrémente le nombre d'élément de la liste
		liste->nbr_element--;
	}
}

/***************************************
Les mutatrices de la position courante
***************************************/
void set_pc_debut(t_liste* liste)
{
	//On affecte directement la valeur du pointeur de début à la pc
	liste->pc = liste->debut;
}


void set_pc_fin(t_liste* liste)
{
	//On affecte directement la valeur du pointeur de fin à la pc
	liste->pc = liste->fin;
}

//S'il n'y a pas de suivant, la position courante ne bouge pas.
void set_pc_suivant(t_liste* liste)
{
	//On déplace seulement s'il y a un suivant
	if(liste->pc != liste->fin)
		liste->pc = liste->pc->suivant;
}

void set_pc_precedent(t_liste* liste)
{

	//Sert au parcours
	t_noeud* tmp;

	//Si c'est possible de passer au précédent
	if(!est_vide(liste) && liste->pc != liste->debut)
	{
		//On a pas le choix, il faut une boucle
		//On part du début et on arrête quand le suivant c'est
		//la position courante
		tmp = liste->debut;

		//On parcourt la liste et on cherche le
		//noeud dont le suivant est la position courante
		while(tmp->suivant != liste->pc)
			tmp = tmp->suivant;

		//On déplace la position courante sur le précédent
		liste->pc = tmp;

	}
}

//Libère l'espace associé à la liste et met le paramètre effectif à NULL
void liberer_liste(t_liste* liste)
{
	/*
	*STRATÉGIE : Ici, on se contente de détruire chaque noeud de la liste
	*            à l'aide de la procédure publique supprime
	*/

	//Seulement si pas déjà vide
	if(!est_vide(liste))
	{
		set_pc_debut(liste);

		//On parcourt la liste
		while(!est_vide(liste))
		{
			supprimer(liste);
		}
	}
}