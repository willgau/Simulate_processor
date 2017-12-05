#ifndef _T_TRIAGE__
#define _T_TRIAGE__

/*
* Le centre de traitement d'un paquet pour l'instant.  
* Ce module sera d'une importance capitale dans la deuxième partie.
*/

#include "t_paquet.h"
#include "m_emission.h"
#include "t_processeur.h"
#include "t_file.h"
#include "t_fichier.h"

//Crée et Initialise le processeur et initialise la file 
//d'attente pour traiter les paquets.  La catégorie 
//du processeur est généré aléatoirement et il est disponible.
//La file est vide.
void init_traitement(t_liste* lst_processeurs, t_liste* lst_files);

void init_processeur(t_processeur* processeur);

//Distribue le paquet dans la file si elle n'est pas pleine.
//Retourne si le paquet a été enfilé.
int traiter_arrivee_paquet(const t_paquet* paquet,t_liste* lst_files, t_liste* lst_processeurs);

//Si le processeur est disponible, il reçoit un paquet en tête de file 
//(si elle n’est pas vide).
void distribuer_paquet(t_liste* lst_files, t_liste* lst_processeurs);

//Le processeur traite son paquet pour un tour.  Un processeur a 
//terminé lorsque le paquet en traitement est mis dans son fichier 
//et potentiellement écrit sur disque. Retourne le nombre de fichiers
//émis lors du service (un seul pour l’instant).
int servir_prochain_paquet(t_liste* lst_processeurs, t_liste* lst_files, t_liste* lst_fic);

//Genere un entier entre min et max
int alea_categorie(int minimum,int maximum);

int choix_categorie();

#endif