/*
* Repr�sente le TDA liste qui permet d'ajouter, retirer et
* retrouver les donn�es incluses
*
*Toutes les op�rations osnt faites � partir d'une position
*courante qui peut �tre d�plac�e par les sous-programmes offerts.
*
*La position courante est toujours sur l'�l�ment qui vient d'�tre ins�r�,
*sur le suivant de celui qui vient d'�tre supprim� ou null.
*
* Les cas d'exceptions ne sont pas trait�.
* Il n'y a aucun message si on ne re�oit pas une bonne liste intialis�e.
*/
#ifndef __T_LISTE__
#define __T_LISTE__

//Le type des �l�ments dans la liste
//mettre void* pour des listes g�n�riques
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

//Retourne une liste initialis�e et vide
void init_liste(t_liste* liste);

//Les informatrices bool�ennes de base
int est_vide(const t_liste* liste);

//L'accesseur d'�l�ment � la position courante
//sans l'enlever ni d�placer la position courante
t_elements obtenir_element(const t_liste* liste);

//Acesseur du nombre d'�l�ments dans la liste
int obtenir_nb_elements(const t_liste* liste);

//Les mutatrices
//Dans tous les cas, la position courante est sur l'�l�ment ajout� apr�s l'insertion
void inserer_debut(t_liste* liste, t_elements element);
void inserer_avant_pc(t_liste* liste, t_elements element);
void inserer_apres_pc(t_liste* liste, t_elements element);
void inserer_fin(t_liste* liste, t_elements element);

//Supprime la valeur � la position courante.
//La position courante est sur le prochain �l�ment
//ou null si vide.
void supprimer(t_liste* l);


//Les mutatrices de la position courante.  Si l'op�ration
//est impossible, rien n'est effectu� (ex: precedent du premier,
//                                         suivant d'une liste vide, ...)
//
//On utilise "set" plut�t que "d�placer" (plus court)
void set_pc_debut(t_liste* liste);
void set_pc_fin(t_liste* liste);
void set_pc_suivant(t_liste* liste);
void set_pc_precedent(t_liste* liste);


//Lib�re l'espace associ� � la liste et met le param�tre effectif � NULL
//Il appelle liberer du type des �l�ments, qui doit exister
void liberer_liste(t_liste* liste);

#endif