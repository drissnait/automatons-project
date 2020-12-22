#include <stdio.h>
#include <stdlib.h>
#include "struct.c"

struct graphe automate_langage_vide(){
	struct graphe g;
	g.sommet_initial=0;
	g.tab_etats.num_etat=0;
	return g;	
}

int main(){
	struct graphe g;	
	g=automate_langage_vide();
	printf("sommet initial : %d\n", g.sommet_initial);
	printf("liste des sommets : %d\n", g.tab_etats);
}
