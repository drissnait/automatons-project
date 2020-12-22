#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct etat{
	int num_etat;
	bool is_final;
}etat;

struct arrete{	
	int sommet_depart;
	int sommet_destination;
	char* symbole;
}arrete;

struct graphe{
	int sommet_initial;
	struct etat* tab_etats;
	struct arrete* tab_arretes;
}graphe;


