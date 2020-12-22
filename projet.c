#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.c"

struct graphe automate_langage_vide(){
	struct graphe g;
	g.sommet_initial=1;
	g.tab_etats=malloc(1*sizeof(struct etat));
	g.tab_etats[0].num_etat=1;
	g.tab_etats[0].is_final=false;
	return g;	
}

struct graphe automate_mot_vide(){
	struct graphe g;
	g.sommet_initial=1;
	g.tab_etats=malloc(1*sizeof(struct etat));
	g.tab_etats[0].num_etat=1;
	g.tab_etats[0].is_final=true;
	return g;	
}

int write_is_final(int sommet, bool isfinal){
	if (isfinal==true)		
		return sommet;
	else
		return false;
	
}

int main(){
	printf("------------------------Graphe pour le langage vide-----------------------------\n");
	struct graphe g;	
	g=automate_langage_vide();
	printf("sommet initial : %d\n", g.sommet_initial);
	printf("liste des sommets : %d\n", g.tab_etats[0].num_etat);

	printf("------------------------Graphe pour le mot vide-----------------------------\n");

	struct graphe g2;
	g2=automate_mot_vide();
	printf("sommet initial : %d\n", g2.sommet_initial);
	printf("liste des sommets : %d\n", g2.tab_etats[0].num_etat);
	printf("Sommet(s) final/finaux : %d\n", write_is_final(g2.tab_etats[0].num_etat, g2.tab_etats[0].is_final));
}



