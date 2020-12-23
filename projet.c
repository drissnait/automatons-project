#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "struct.c"

int write_is_final(int sommet, bool isfinal){
	if (isfinal==true)		
		return sommet;
	else
		return false;
	
}

/*
Génére un automate qui reconnait le langage vide 
*/
struct graphe automate_langage_vide(){
	struct graphe g;				
	g.sommet_initial.num_etat=1;			
	g.sommet_initial.is_final=false;		
	g.tab_etats=malloc(1*sizeof(struct etat));
	g.tab_etats[0].num_etat=1;			/*1 seul etat*/
	g.tab_etats[0].is_final=false;			/*l'etat n'est final*/
	return g;	
}
void print_automate_langage_vide(struct graphe g){
	printf("Automate:\n");
	printf("---nombre de sommets : 1\n");
	printf("---liste des sommets : %d\n", g.tab_etats[0].num_etat);
	printf("---sommet initial : %d\n", g.sommet_initial.num_etat);
}

struct graphe automate_mot_vide(){
	struct graphe g;
	g.sommet_initial.num_etat=1;			
	g.sommet_initial.is_final=true;
	g.tab_etats=malloc(1*sizeof(struct etat));
	g.tab_etats[0].num_etat=1;			/*1 seul etat*/
	g.tab_etats[0].is_final=true;			/*l'etat est final*/
	return g;	
}

void print_automate_mot_vide(struct graphe g2){
	printf("Automate:\n");
	printf("---nombre de sommets : 1\n");
	printf("---liste des sommets : %d\n", g2.tab_etats[0].num_etat);
	printf("---sommet initial : %d\n", g2.sommet_initial.num_etat);
	printf("---Sommet(s) final/finaux : %d\n", write_is_final(g2.tab_etats[0].num_etat, g2.tab_etats[0].is_final));
}

struct graphe automate_un_mot(char* mot){
	struct graphe g;
	g.tab_etats=malloc(2*sizeof(struct etat));
	g.tab_arretes=malloc(1*sizeof(struct etat));

	g.sommet_initial.num_etat=1;		/*etat initial*/
	g.sommet_initial.is_final=false;	/*etat initial n'est pas final*/
	g.nb_etats=2;				/*2 etats*/

	g.tab_etats[0].num_etat=1;
	g.tab_etats[0].is_final=false;
	
	g.tab_etats[1].num_etat=2;		/* 2eme etat*/
	g.tab_etats[1].is_final=true;		/*2 etats, donc le deuxieme etat est final*/

	g.tab_arretes[0].sommet_depart.num_etat=1;
	g.tab_arretes[0].sommet_depart.is_final=false;

	g.tab_arretes[0].sommet_destination.num_etat=2;
	g.tab_arretes[0].sommet_destination.is_final=true;

	g.tab_arretes[0].symbole=mot;	
	return g;
}

void print_automate_un_mot(struct graphe g3){
	printf("Automate:\n");
	printf("---nombre de sommets : 2\n");
	printf("---liste des sommets : %d - %d\n", g3.tab_etats[0].num_etat, g3.tab_etats[1].num_etat);
	printf("---sommet initial : %d\n", g3.sommet_initial.num_etat);
	printf("---Sommet(s) final/finaux : %d\n", write_is_final(g3.tab_etats[1].num_etat, g3.tab_etats[1].is_final));
	printf("---nombre des transitions : 1\n");
	printf("---Transition(s) : %d, %s, %d\n",g3.tab_arretes[0].sommet_depart.num_etat, g3.tab_arretes[0].symbole, g3.tab_arretes[0].sommet_destination.num_etat);
}

struct graphe concatenate_automate(struct graphe g1, struct graphe g2){
	struct graphe g;
	g.nb_etats=g1.nb_etats+g2.nb_etats-1;
	int num_sommet=0;			/*variable qui va servir pour repérer les états finaux dans le nv graphe*/
	int j=0;
	g.tab_etats=malloc(g.nb_etats*2*sizeof(struct etat));
	g.tab_arretes=malloc(g.nb_etats*2*sizeof(struct etat));
	int i;
	for (i=0;i<g1.nb_etats-1;i++){
		g.tab_etats[j].num_etat=i+1;
		g.tab_arretes[i].sommet_depart.num_etat=i+1;
		g.tab_arretes[i].symbole =g1.tab_arretes[i].symbole;
		g.tab_arretes[i].sommet_destination.num_etat=g1.tab_arretes[i].sommet_destination.num_etat;
		
		//printf("---Transition(s) : %d, %s, %d\n",g.tab_arretes[i].sommet_depart.num_etat, g.tab_arretes[i].symbole, g.tab_arretes[i].sommet_destination.num_etat);
	}
		
	
	for (int k=0,j=i;j<g.nb_etats-1;j++,k++){
		g.tab_etats[j].num_etat=j+1;
		g.tab_arretes[j].sommet_depart.num_etat=j+1;
		g.tab_arretes[j].symbole =g2.tab_arretes[k].symbole;
		g.tab_arretes[j].sommet_destination.num_etat=g2.tab_arretes[k].sommet_destination.num_etat+1;
		//printf("---Transition(s) : %d, %s, %d\n",g.tab_arretes[j].sommet_depart.num_etat, g.tab_arretes[j].symbole, g.tab_arretes[j].sommet_destination.num_etat);
		
	}	
	for (int i=0;i<g.nb_etats;i++){
		if(i<g.nb_etats-1){
			g.tab_etats[i].is_final=false;
		}
		else{
			g.tab_etats[i].is_final=true;	
		}	
	}
	g.sommet_initial.num_etat=g.tab_arretes[0].sommet_depart.num_etat;
		
	return g;
}

void print_automate_concatene(struct graphe g){
	printf("---nombre de sommets : %d\n", g.nb_etats);
	printf("---sommet initial : %d\n", g.sommet_initial.num_etat);
	printf("---nombre des transitions : %d\n",g.nb_etats-1);
	for (int i=0;i<g.nb_etats;i++){
		if(i<g.nb_etats-1){
			printf("---Etat n° : %d\n",g.tab_arretes[i].sommet_depart.num_etat);
			printf("------Transition avec le symbole %s vers l'etat n° %d\n",g.tab_arretes[i].symbole, g.tab_arretes[i].sommet_destination.num_etat);
		
		
			printf("------Final : Non\n");
		}
		
		else{
			printf("---Etat n° : %d\n",i+1);
			printf("------Final : Oui\n");
		}
	}
}





int main(){
	printf("------------------------Graphe pour le langage vide-----------------------------\n");
	struct graphe g;	
	g=automate_langage_vide();
	//print_automate_langage_vide(g);
	

	printf("------------------------Graphe pour le mot vide-----------------------------\n");

	struct graphe g2;
	g2=automate_mot_vide();
	//print_automate_mot_vide(g2);
	printf("------------------------Graphe pour un mot d'un caractere-----------------------------\n");
	struct graphe g3;
	g3=automate_un_mot("a");
	struct graphe g4;
	g4=automate_un_mot("b");
	struct graphe g8;
	g8=automate_un_mot("c");
	struct graphe g9;
	g9=automate_un_mot("d");
	
	//print_automate_un_mot(g3);
	struct graphe g5;
	g5=concatenate_automate(g3, g4);
	
	struct graphe g6;
	g6=concatenate_automate(g5, g8);
	struct graphe g7;
	g7=concatenate_automate(g6, g9);
	
	print_automate_concatene(g7);

	
}



