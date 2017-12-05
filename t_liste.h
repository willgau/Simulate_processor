/*
* Représente le TDA liste qui permet d'ajouter, retirer et
* retrouver les données incluses
*
*Toutes les opérations osnt faites à partir d'une position
*courante qui peut être déplacée par les sous-programmes offerts.
*
*La position courante est toujours sur l'élément qui vient d'être inséré,
*sur le suivant de celui qui vient d'être supprimé ou null.
*
* Les cas d'exceptions ne sont pas traité.
* Il n'y a aucun message si on ne reçoit pas une bonne liste intialisée.
*/
#ifndef __T_LISTE__
#define __T_LISTE__

//Le type des éléments dans la liste
//mettre void* pour des listes génériques
typedef void* t_elements;

typedef struct t_noeud
{
	t_elements element;         //l'element contenu dans le noeud
	t_noeud* suivant;          //pointe sur le suivant de la liste
}t_noeud;


typedef struct 
{
	t_noeud* debut;                  //pointe sur le debut de la liste
	t_noeud* fin;                    //pointe sur la fin de la liste
	t_noeud* pc;                     //la pc en mouvement dans la liste

	int nbr_element;                 //nombre d'elements en tout temps
}t_liste;

//Retourne une liste initialisée et vide
void init_liste(t_liste* liste);

//Les informatrices booléennes de base
int est_vide(const t_liste* liste);

//L'accesseur d'élément à la position courante
//sans l'enlever ni déplacer la position courante
t_elements obtenir_element(const t_liste* liste);

//Acesseur du nombre d'éléments dans la liste
int obtenir_nb_elements(const t_liste* liste);

//Les mutatrices
//Dans tous les cas, la position courante est sur l'élément ajouté après l'insertion
void inserer_debut(t_liste* liste, t_elements element);
void inserer_avant_pc(t_liste* liste, t_elements element);
void inserer_apres_pc(t_liste* liste, t_elements element);
void inserer_fin(t_liste* liste, t_elements element);

//Supprime la valeur à la position courante.
//La position courante est sur le prochain élément
//ou null si vide.
void supprimer(t_liste* l);


//Les mutatrices de la position courante.  Si l'opération
//est impossible, rien n'est effectué (ex: precedent du premier,
//                                         suivant d'une liste vide, ...)
//
//On utilise "set" plutôt que "déplacer" (plus court)
void set_pc_debut(t_liste* liste);
void set_pc_fin(t_liste* liste);
void set_pc_suivant(t_liste* liste);
void set_pc_precedent(t_liste* liste);


//Libère l'espace associé à la liste et met le paramètre effectif à NULL
//Il appelle liberer du type des éléments, qui doit exister
void liberer_liste(t_liste* liste);

#endif