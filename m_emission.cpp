
/*==========================================================

Auteur  : Hugues Saulnier et Pierre Bélisle

Ce code n'est que pour permettre une simulation intéressante.  
Il n'a pas été écrit dans le but d'être lu par les étudiants.
Il est commenté minimalement.
==========================================================*/
#include "m_emission.h"
#include "constantes.h"


/*==========================================================*/

// type privé d'accès à un fichier pour le paquetage
typedef struct{
	FILE* fichier;

	int tail_fichier;

	int pack_actuel;

	int nb_paquet;

	int * tab_tailles;
	
	char id_unique[MAX_CAR_ID];

}t_file_paquets;

/*==========================================================*/
// privée, donne le nombre de fichiers actuellement actifs
static int nb_fichiers_paquetage = 0 ;

static int nb_fichiers_restants = 0;

/*==========================================================*/
static t_file_paquets tab_fichiers [MAX_FICHIERS];

typedef char t_nom[MAX_CAR_ID];
static t_nom noms_fic[MAX_FICHIERS];

//  fonctions privées servent ce tableau

// sert à initialiser le tableau, toutes les positions sont libres
static void  init_file_paquets(void){
	int i;
	for (i=0;i<nb_fichiers_paquetage;++i){
		tab_fichiers[i].fichier = NULL;
		tab_fichiers[i].nb_paquet = 0;
		tab_fichiers[i].pack_actuel  = 0;
		tab_fichiers[i].tail_fichier = 0;
	}
}
//

//// sert à obtenir une position libre du tableau de fichiers
static int get_pos_libre(void){
	int i ;
	for (i=0;i<MAX_FICHIERS;++i)
		if (tab_fichiers[i].fichier == NULL) return i;
	return -1;	
}

// Sert à choisir un fichier au hasard d'ou sera émis un paquet avec get_paquet
static int get_pos_aleatoire(void){

	int i = 0;
	int choisi;
	int trouve = FALSE ;

	while(!trouve && nb_fichiers_restants)
	{
		choisi = mt_randi(nb_fichiers_paquetage) - 1;

		if (tab_fichiers[choisi].fichier)
			trouve = TRUE;

		i++;
	} 

	return trouve?choisi:-1;
}


/*==========================================================*/

static void print_t_fichPaquets( t_file_paquets lui);

/*==========================================================*/
static int init_tab_tailles( t_file_paquets* p);

static int add_fichier(const char * fichier){

	t_file_paquets nv = {NULL,0,0,0, NULL};

	int position;

	// si le nombre de fichiers est déjà maximum
	position = get_pos_libre();

	if (position<0) return 0;

	// si ouverture ratée
	nv.fichier = fopen(fichier,"rb");
	if (nv.fichier == NULL) return 0;

	// obtenir taille du fichier
	fseek(nv.fichier,0,SEEK_END);
	nv.tail_fichier = ftell(nv.fichier);
	fseek(nv.fichier,0,SEEK_SET);

	if (init_tab_tailles(&nv)== 0) return 0;	
	nv.pack_actuel = 0;


	sprintf(nv.id_unique,"copie%s",fichier);

	tab_fichiers[position] = nv;

	print_t_fichPaquets(nv);
	return 1;
}
/*==========================================================*/


/*==========================================================*/
void	init_emission(const char* nom_fic)
{

	int i;

	FILE* fic = fopen(nom_fic,"rt");

	if(fic)
	{

		while(!feof(fic))
		{
			fgets(noms_fic[nb_fichiers_paquetage],MAX_CAR_ID, fic);

			if(noms_fic[nb_fichiers_paquetage][0] != NULL && noms_fic[nb_fichiers_paquetage][0] != '\n')
			{
			//Enlève le \n
			noms_fic[nb_fichiers_paquetage][strlen(noms_fic[nb_fichiers_paquetage]) -1] = 0;
			nb_fichiers_paquetage++;
			}
		}
		nb_fichiers_restants =  nb_fichiers_paquetage;

		for(i = 0; i < nb_fichiers_paquetage;i++)
			add_fichier(noms_fic[i]);

		fclose(fic);

		system("pause");
	}
}



/*==========================================================*/
// va créer le tableau dynamique des tailles de paquets.
// les champs 
static int init_tab_tailles( t_file_paquets* p ){

	int i;
	int tail_bloc;
	int somme =0;

	i = 0;

	p->tab_tailles = (int*) malloc( (p->tail_fichier/TAIL_MIN_PAQUET) *sizeof(int));

	if(	p->tab_tailles == NULL) return 0;

	while ((somme +TAIL_MAX_PAQUET) <  p->tail_fichier){
		tail_bloc = TAIL_MIN_PAQUET + mt_randi(TAIL_MAX_PAQUET-(TAIL_MIN_PAQUET+1));
		p->tab_tailles[i++] = tail_bloc;
		somme += tail_bloc;
	} 
	//le dernier bloc, on le fixe...
	if(somme<p->tail_fichier){
		tail_bloc = p->tail_fichier - somme;
		p->tab_tailles[i++]= tail_bloc;	
	}

	p->nb_paquet = i ;
	p->tab_tailles = (int *) realloc(p->tab_tailles,i*sizeof(int));
	return 1;
}
/*==========================================================*/



/*==========================================================*/
int get_paquet(t_paquet* p){

	int num_f;

	unsigned char  buffer[TAIL_MAX_PAQUET+2];

	int lu , lire , position ;

	num_f = get_pos_aleatoire();

	if (num_f<0) 
		return 0;

	p->nb_total_paquet = tab_fichiers[num_f].nb_paquet; // nb total paquet
	p->num_paquet = tab_fichiers[num_f].pack_actuel; // numero paquet
	
	position = p->num_paquet;
	lire = tab_fichiers[num_f].tab_tailles[position];

	lu = fread(buffer,1,lire ,tab_fichiers[num_f].fichier);

	p->taille_paquet = lu;
	if(lu) {
		assert(p->buffer = (unsigned char *) malloc(lu+1));
		memcpy(p->buffer,buffer,lu);
	}
	
	strcpy(p->id_unique, tab_fichiers[num_f].id_unique);

	// controle sur le fichier, on a lu un paquet
	// mais si on a lu le dernier paquet,   on ferme le fichier, 
	// on s'en débarrasse dans le tableau
	tab_fichiers[num_f].pack_actuel += 1; 
	if ( tab_fichiers[num_f].pack_actuel == tab_fichiers[num_f].nb_paquet) {
		fclose(tab_fichiers[num_f].fichier);
		tab_fichiers[num_f].fichier = NULL;
		nb_fichiers_restants--;
	}
	return 1;
}

/*==========================================================*/

static void print_t_fichPaquets( t_file_paquets lui){
	printf("\n\n taille du fichier  %d", lui.tail_fichier);
	printf("\n nombre de paquets  %d", lui.nb_paquet);
	printf("\n on sort le paquet   %d", lui.pack_actuel);
	printf("\n l'adresse du tableau   %d", lui.tab_tailles);
	printf("\n l'ID du fichier %s", lui.id_unique);
}

/*==========================================================*/