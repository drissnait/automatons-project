#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct etat{
	int num_etat;
	bool is_final;
}etat;

typedef struct arrete{	
	int sommet_depart;
	int sommet_destination;
	char* symbole;
}arrete;

typedef struct graphe{
	int sommet_initial;
	struct etat* tab_etats;
	struct arrete* tab_arretes;
}graphe;


