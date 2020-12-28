#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "projet.h"
#include <string.h>

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
	g.nb_etats=2;	
	g.nb_transitions=1;			/*2 etats*/

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


void addToGraphe(struct graphe* g, struct etat etat){
	for (int k=0;k<g->nb_etats;k++){
		if (g->tab_etats[k].num_etat == etat.num_etat){
			return;
		}
	}
	g->tab_etats[g->nb_etats]=etat;
	g->nb_etats++;
	return; 
}

struct graphe reunion_automate(struct graphe g1, struct graphe g2){
	int i;
	int indiceGraphe;
	int dernierElement=1;
	int nb_etats=g1.nb_etats+g2.nb_etats-1;
	int j=0;
	int numero_etat=g1.nb_etats;
	int nbr_transitions=g1.nb_transitions+g2.nb_transitions;
	struct graphe g;
	g.tab_etats=malloc(nb_etats*sizeof(struct etat));
	g.tab_arretes=malloc(nbr_transitions*sizeof(struct arrete));
	g.nb_transitions=g1.nb_transitions+g2.nb_transitions;
	
	for (int k=0;k<g1.nb_transitions;k++){
		g.tab_arretes[k]=g1.tab_arretes[k];
			
	}
	g.nb_etats=g1.nb_etats;
	for (int k=0;k<g1.nb_etats;k++){
		g.tab_etats[k]=g1.tab_etats[k];
	}

	for(i=g1.nb_transitions; i<nbr_transitions;i++){
		if(g2.tab_arretes[j].sommet_depart.num_etat==1){
			g.tab_arretes[i].sommet_depart.num_etat=1;
			g.tab_arretes[i].sommet_destination.num_etat=g2.tab_arretes[j].sommet_depart.num_etat+numero_etat;		
			g.tab_arretes[i].sommet_destination.is_final=g2.tab_arretes[j].sommet_destination.is_final;
			
		}		
		else{
			g.tab_arretes[i].sommet_depart.num_etat=g.tab_arretes[i-1].sommet_destination.num_etat;
			g.tab_arretes[i].sommet_destination.num_etat=g.tab_arretes[i].sommet_depart.num_etat+1;	
			g.tab_arretes[i].sommet_depart.is_final=g2.tab_arretes[j].sommet_depart.is_final;
			g.tab_arretes[i].sommet_destination.is_final=g2.tab_arretes[j].sommet_destination.is_final;
		}
		g.tab_arretes[i].symbole=g2.tab_arretes[j].symbole;
		addToGraphe(&g, g.tab_arretes[i].sommet_depart);
		addToGraphe(&g, g.tab_arretes[i].sommet_destination);
		j++;
		numero_etat++;
	}

	return g;
}

void print_reunion(struct graphe g){
	printf("\nAutomate\n");
	printf("---Nombre d'états : %d\n", g.nb_etats);
	printf("---Nombre de transactions : %d\n", g.nb_transitions);
	printf("---Etat initial : %d\n", g.tab_etats[0].num_etat);
	for(int i=0;i<g.nb_etats;i++){
		if(i<g.nb_etats-1){
			printf("-----Etat n° %d\n",g.tab_arretes[i].sommet_depart.num_etat);
			printf("-------Transaction avec le symbole %s vers l'etat %d\n",g.tab_arretes[i].symbole, g.tab_arretes[i].sommet_destination.num_etat);
			//printf("-------Final : %d\n",g.tab_arretes[i].sommet_depart.is_final);
		}
	}
	printf("\n-----Liste des etats finaux : \n");
	for (int i=0; i<g.nb_etats;i++){
		if(g.tab_etats[i].is_final==1){
			printf("-------Etat n° %d\n", g.tab_etats[i].num_etat);
		}
	}
	
}




struct graphe concatenation_automate(struct graphe g1, struct graphe g2){
	int i;
	int indiceGraphe;
	int dernierElement=1;
	int nb_etats=g1.nb_etats+g2.nb_etats-1;
	int j=0;
	int numero_etat=g1.nb_etats;
	int nbr_transitions=g1.nb_transitions+g2.nb_transitions;
	struct graphe g;
	g.tab_etats=malloc(nb_etats*sizeof(struct etat));
	g.tab_arretes=malloc(nbr_transitions*sizeof(struct arrete));
	g.nb_transitions=g1.nb_transitions+g2.nb_transitions;
	
	for (int k=0;k<g1.nb_transitions;k++){
		g.tab_arretes[k]=g1.tab_arretes[k];
			
	}
	g.nb_etats=g1.nb_etats;
	for (int k=0;k<g1.nb_etats;k++){
		g.tab_etats[k]=g1.tab_etats[k];
	}

	for(i=g1.nb_transitions; i<nbr_transitions;i++){
		if(g2.tab_arretes[j].sommet_depart.num_etat==1){
			g.tab_arretes[i].sommet_depart.num_etat=g1.tab_arretes[g1.nb_transitions-1].sommet_destination.num_etat;
			g.tab_arretes[i].sommet_destination.num_etat=g2.tab_arretes[j].sommet_depart.num_etat+numero_etat;		
			g.tab_arretes[i].sommet_destination.is_final=g2.tab_arretes[j].sommet_destination.is_final;
			
		}		
		else{
			g.tab_arretes[i].sommet_depart.num_etat=g.tab_arretes[i-1].sommet_depart.num_etat+1;
			g.tab_arretes[i].sommet_destination.num_etat=g.tab_arretes[i-1].sommet_destination.num_etat+1;	
			g.tab_arretes[i].sommet_depart.is_final=g2.tab_arretes[j].sommet_depart.is_final;
			g.tab_arretes[i].sommet_destination.is_final=g2.tab_arretes[j].sommet_destination.is_final;	
		}
		
		g.tab_arretes[i].symbole=g2.tab_arretes[j].symbole;
		addToGraphe(&g, g.tab_arretes[i].sommet_depart);
		addToGraphe(&g, g.tab_arretes[i].sommet_destination);
		j++;
		numero_etat++;
	}
	for (i=0; i< g.nb_etats;i++){		
		if(i<g.nb_etats-1){
			g.tab_etats[i].is_final=false;
		}else{
			g.tab_etats[i].is_final=true;
		}
	}
	for (i=0; i< g.nb_transitions;i++){
		g.tab_arretes[i].sommet_depart.is_final=false;
		g.tab_arretes[i].sommet_destination.is_final=false;
	}
	g.tab_arretes[i-1].sommet_destination.is_final=true;
	
	return g;
}

void print_concatenate(struct graphe g){
	printf("\nAutomate\n");
	printf("---Nombre d'états : %d\n", g.nb_etats);
	printf("---Nombre de transactions : %d\n", g.nb_transitions);
	printf("---Etat initial : %d\n", g.tab_etats[0].num_etat);
	for(int i=0;i<g.nb_etats;i++){
		if(i<g.nb_etats-1){
			printf("-----Etat n° %d\n",g.tab_arretes[i].sommet_depart.num_etat);
			printf("-------Transaction avec le symbole %s vers l'etat %d\n",g.tab_arretes[i].symbole, g.tab_arretes[i].sommet_destination.num_etat);
			printf("-------Final : %d\n",g.tab_arretes[i].sommet_depart.is_final);
		}
		else{
			printf("-----Etat n° %d\n",g.tab_arretes[i-1].sommet_destination.num_etat);
			printf("-------Final : %d\n",g.tab_arretes[i-1].sommet_destination.is_final);		
		}
	}
}



struct graphe fermeture_kleene(struct graphe g){
	int nbrEtatsFinaux=0;
	int transitionsSommetInit=0;
	for (int i=0;i<g.nb_transitions;i++){
		//printf(" transition de %d avec le symbole %s vers le sommet %d\n",g.tab_arretes[i].sommet_depart.num_etat, g.tab_arretes[i].symbole, g.tab_arretes[i].sommet_destination.num_etat);
		if (g.tab_arretes[i].sommet_destination.is_final==true){
			nbrEtatsFinaux++;
		}
	}
	for (int i=0;i<g.nb_transitions;i++){
		if(g.tab_arretes[i].sommet_depart.num_etat==1){
			transitionsSommetInit++;
		}	
	}
	struct graphe gRetour;
	int nbr_transitions=g.nb_transitions+transitionsSommetInit;
	gRetour.tab_etats=malloc(g.nb_etats*sizeof(struct etat)+1);
	gRetour.tab_arretes=malloc(nbr_transitions*sizeof(struct arrete)+1);
	for (int i=0;i<g.nb_transitions;i++){
		gRetour.tab_arretes[i]=g.tab_arretes[i];
	}
	int ajout=0;
	int j=0;
	for (int i=0; i<g.nb_transitions;i++){
		if (g.tab_arretes[i].sommet_destination.is_final==true){
				while(g.tab_arretes[j].sommet_depart.num_etat==1){
					gRetour.tab_arretes[g.nb_transitions+ajout].sommet_depart=g.tab_arretes[i].sommet_destination;
					gRetour.tab_arretes[g.nb_transitions+ajout].sommet_destination.num_etat=g.tab_arretes[0].sommet_destination.num_etat;
					gRetour.tab_arretes[g.nb_transitions+ajout].symbole=g.tab_arretes[0].symbole;
					ajout++;
					j++;
				}
				j=0;
		}

	}
	/*for (int i=0; i<nbr_transitions;i++){
		printf("Transition de %d avec le symbole %s vers le sommet %d\n", gRetour.tab_arretes[i].sommet_depart.num_etat, gRetour.tab_arretes[i].symbole, gRetour.tab_arretes[i].sommet_destination.num_etat);	
	}*/
	gRetour.nb_transitions=nbr_transitions;
	gRetour.nb_etats=g.nb_etats;
	return gRetour;
}



void print_kleene(struct graphe g){
	printf("\nAutomate : \n");
	printf("---nombre de sommets : %d\n", g.nb_etats);
	printf("---sommet initial : %d\n", g.tab_etats[0].num_etat);
	printf("---nombre des transitions : %d\n",g.nb_etats-1);
	for (int i=0;i<g.nb_etats;i++){
		printf("---Etat n° : %d\n",g.tab_arretes[i].sommet_depart.num_etat);
		printf("------Transition avec le symbole %s vers l'etat n° %d\n", g.tab_arretes[i].symbole, g.tab_arretes[i].sommet_destination.num_etat);		
		printf("------Final : %d\n", g.tab_arretes[i].sommet_depart.is_final);
	}
}

bool automate_deterministe(struct graphe g,char* c ){
	//la longeur de la chaine de charactere c
	
	int l_c;
	l_c=(int)strlen(c);
	if(g.nb_etats<l_c){
		return 0;
	}
	
    int i;

    /* s'assure si le string est en ascii*/
    int code;
    for(i=0;i<l_c;i++){
    	code=c[i];
    	if(code>255 || code<0){
    		printf("le string n'est pas en ascii \n");
    		return 0;

    	}

    }

    for(i=0;i<l_c;i++){
    	
    	

    	if(*(g.tab_arretes[i].symbole) != c[i]){
    		


    		return 0;

    	}
    	
    }

    return 1;

}
void print_automate_deterministe(struct graphe g,char * c)
{

    int l_c;
	l_c=(int)strlen(c);
	/* s'assure si le string est en ascii*/
    int code;

    int i;
    for(i=0;i<l_c;i++){
    	code = c[i];
    	
    	

    	if(code>255 || code <0){
    		printf("le string %s n'est pas en ascii \n",c);
    		return;
    		

    	}

    }
	if(automate_deterministe(g,c)==0){
		printf("string %s non valider sur l'automate  \n",c);
	}else{
		printf("string %s valider sur l'automate  \n",c);
	}
	


}





int main(){
	printf("------------------------Graphe pour le langage vide-----------------------------\n");
	struct graphe g;	
	g=automate_langage_vide();
	//print_automate_langage_vide(g);
	struct graphe ga;
	ga=automate_un_mot("a");
	struct graphe gb;
	gb=automate_un_mot("b");
	struct graphe gc;
	gc=automate_un_mot("c");
	struct graphe gd;
	gd=automate_un_mot("d");
	struct graphe ge;
	ge=automate_un_mot("e");

	printf("\n\n\n----------reunion------------");
	struct graphe gab_reunion;
	gab_reunion=reunion_automate(ga, gb);
	print_reunion(gab_reunion);

	struct graphe gcd_reunion;
	gcd_reunion=reunion_automate(gc, gd);
	print_reunion(gcd_reunion);

	struct graphe gabcd_reunion;
	gabcd_reunion=reunion_automate(gab_reunion, gcd_reunion);
	print_reunion(gabcd_reunion);

	/*struct graphe gabcde_reunion;
	gabcde_reunion=reunion_automate(gabcd_reunion, ge);
	print_reunion(gabcde_reunion);*/

	/*struct graphe gab;
	gab=concatenation_automate(gab_reunion, gcd_reunion);
	print_concatenate(gab);*/

	//printf("\n\n\n----------concatenation------------");
	struct graphe gab;
	gab=concatenation_automate(ga, gb);
	//print_concatenate(gab);

	struct graphe gcd;
	gcd=concatenation_automate(gc, gd);
	//print_concatenate(gcd);


	struct graphe gabcd;
	gabcd=concatenation_automate(gab, gcd);
	print_concatenate(gabcd);

	/*struct graphe gabcd_re_conc;
	gabcd_re_conc=reunion_automate(gabcd, ge);
	print_reunion(gabcd_re_conc);*/


	struct graphe gabcde;
	gabcde=concatenation_automate(gabcd, ge);
	//print_concatenate(gabcde);
	printf("------------------------fermeture de kleene-----------------------------\n");
	/***Test Fermeture de kleene***/
	struct graphe graphe=fermeture_kleene(gabcd);	/*abcd devient (abcd)* */
	print_kleene(graphe);

	printf("------------------------Automate deterministe -----------------------------\n");
	
	print_automate_deterministe(ga,"√");
	print_automate_deterministe(gab,"ab");
	print_automate_deterministe(gabcd,"abcd");
	print_automate_deterministe(ga,"elie");
	print_automate_deterministe(gabcd,"elie");
	
}

