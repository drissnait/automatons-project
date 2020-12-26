#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct etat{
	int num_etat;
	bool is_final;
}etat;

typedef struct arrete{	
	etat sommet_depart;
	etat sommet_destination;
	char* symbole;
}arrete;

typedef struct graphe{
	etat sommet_initial;
	int nb_etats;
	int nb_transitions;
	struct etat* tab_etats;
	struct arrete* tab_arretes;
}graphe;

