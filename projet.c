#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "projet.h"
#include <string.h>

/*
*@param int sommet
*@param bool isfinal
*Vérifie si un sommet est final
*/
int write_is_final(int sommet, bool isfinal){
	if (isfinal==true)		
		return sommet;
	else
		return false;
	
}


/*
Génére un automate qui reconnait le langage vide 
*/
struct automate automate_langage_vide(){
	struct automate g;				
	g.sommet_initial.num_etat=1;			
	g.sommet_initial.is_final=false;		
	g.tab_etats=malloc(1*sizeof(struct etat));
	g.tab_etats[0].num_etat=1;			/*1 seul etat*/
	g.tab_etats[0].is_final=false;			/*l'etat n'est final*/
	return g;	
}
/*
*@param automate g
*Affichage d'un automate qui reconnait le langage vide 
*/
void print_automate_langage_vide(struct automate g){
	printf("Automate:\n");
	printf("---nombre de sommets : 1\n");
	printf("---liste des sommets : %d\n", g.tab_etats[0].num_etat);
	printf("---sommet initial : %d\n", g.sommet_initial.num_etat);
}

/*
*Génére un automate qui reconnait le mot vide 
*/
struct automate automate_mot_vide(){
	struct automate g;
	g.sommet_initial.num_etat=1;			
	g.sommet_initial.is_final=true;
	g.tab_etats=malloc(1*sizeof(struct etat));
	g.tab_etats[0].num_etat=1;			/*1 seul etat*/
	g.tab_etats[0].is_final=true;			/*l'etat est final*/
	return g;	
}
/*
*@param automate g2
*affiche un automate qui reconnait le mot vide 
*/
void print_automate_mot_vide(struct automate g2){
	printf("Automate:\n");
	printf("---nombre de sommets : 1\n");
	printf("---liste des sommets : %d\n", g2.tab_etats[0].num_etat);
	printf("---sommet initial : %d\n", g2.sommet_initial.num_etat);
	printf("---Sommet(s) final/finaux : %d\n", write_is_final(g2.tab_etats[0].num_etat, g2.tab_etats[0].is_final));
}

/*
*@param char* mot composé d'un seul caractére 
*Genere un automate qui reconnait un mot composé d'un caractere
*/
struct automate automate_un_mot(char* mot){
	struct automate g;
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

/*
*@param automate g3
*Affiche un automate qui reconnait un mot
*/
void print_automate_un_mot(struct automate g3){
	printf("Automate:\n");
	printf("---nombre de sommets : 2\n");
	printf("---liste des sommets : %d - %d\n", g3.tab_etats[0].num_etat, g3.tab_etats[1].num_etat);
	printf("---sommet initial : %d\n", g3.sommet_initial.num_etat);
	printf("---Sommet(s) final/finaux : %d\n", write_is_final(g3.tab_etats[1].num_etat, g3.tab_etats[1].is_final));
	printf("---nombre des transitions : 1\n");
	printf("---Transition(s) : %d, %s, %d\n",g3.tab_arretes[0].sommet_depart.num_etat, g3.tab_arretes[0].symbole, g3.tab_arretes[0].sommet_destination.num_etat);
}

/*
*@param automate automate g
*@param etat etat 
*Ajoute un etat a l'automate
*/
void addToGraphe(struct automate* g, struct etat etat){
	for (int k=0;k<g->nb_etats;k++){
		if (g->tab_etats[k].num_etat == etat.num_etat){
			return;
		}
	}
	g->tab_etats[g->nb_etats]=etat;
	g->nb_etats++;
	return; 
}

/*
*@param automate g1
*@param automate g2
*Genere un automate qui reconnait la reunion des langages des deux automates passés en parametres
*/
struct automate reunion_automate(struct automate g1, struct automate g2){
	int i;
	int indiceGraphe;
	int dernierElement=1;
	int nb_etats=g1.nb_etats+g2.nb_etats-1;
	int j=0;
	int numero_etat=g1.nb_etats;
	int nbr_transitions=g1.nb_transitions+g2.nb_transitions;
	struct automate g;
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

/*
/*
*@param automate 
*Affiche un automate resultat de la reunion
*/
void print_reunion(struct automate g){
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

/*
*@param automate g1
*@param automate g2
*Genere un automate qui la concatenation des langages des deux automates passés en paramétre 
*/
struct automate concatenation_automate(struct automate g1, struct automate g2){
	int i;
	int indiceGraphe;
	int dernierElement=1;
	int nb_etats=g1.nb_etats+g2.nb_etats-1;
	int j=0;
	int numero_etat=g1.nb_etats;
	int nbr_transitions=g1.nb_transitions+g2.nb_transitions;
	struct automate g;
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

/*
*@param automate g
*Affiche un automate resultat de la concatenation
*/
void print_concatenate(struct automate g){
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


/*
*@param automate g
*Genere un automate qui reconnait la fermeture de kleene pour l'automate passe en parametres
*/
struct automate fermeture_kleene(struct automate g){
	int nbrEtatsFinaux=0;
	int transitionsSommetInit=0;
	for (int i=0;i<g.nb_transitions;i++){
		if (g.tab_arretes[i].sommet_destination.is_final==true){
			nbrEtatsFinaux++;
		}
	}
	for (int i=0;i<g.nb_transitions;i++){
		if(g.tab_arretes[i].sommet_depart.num_etat==1){
			transitionsSommetInit++;
		}	
	}
	struct automate gRetour;
	int nbr_transitions=g.nb_transitions+transitionsSommetInit*nbrEtatsFinaux;
	gRetour.tab_etats=malloc(g.nb_etats*sizeof(struct etat)+1);
	gRetour.tab_arretes=malloc(nbr_transitions*sizeof(struct arrete)+1);
	for (int i=0;i<g.nb_transitions;i++){
		gRetour.tab_arretes[i]=g.tab_arretes[i];
	}
	int ajout=0;
	int j=0;
	int indice_while=0;
	for (int i=0; i<g.nb_transitions;i++){
		if (g.tab_arretes[i].sommet_destination.is_final==true){		
				while(indice_while<g.nb_transitions){
					if(g.tab_arretes[indice_while].sommet_depart.num_etat==1){	
						gRetour.tab_arretes[g.nb_transitions+ajout].sommet_depart=g.tab_arretes[i].sommet_destination;
						gRetour.tab_arretes[g.nb_transitions+ajout].sommet_destination.num_etat=g.tab_arretes[indice_while].sommet_destination.num_etat;
						gRetour.tab_arretes[g.nb_transitions+ajout].symbole=g.tab_arretes[indice_while].symbole;				
						ajout++;
						j++;	
					}
				indice_while++;
				}
				indice_while=0;
				j=0;
		}
	}
	gRetour.nb_transitions=nbr_transitions;
	gRetour.nb_etats=g.nb_etats;
	return gRetour;
}

/*
*@param automate 
*Affiche l'automate de la fermeture de kleene genere
*/
void print_kleene(struct automate g){
	printf("\nAutomate : \n");
	printf("---nombre de sommets : %d\n", g.nb_etats);
	printf("---sommet initial : %d\n", g.tab_etats[0].num_etat);
	printf("---nombre des transitions : %d\n",g.nb_transitions);
	for (int i=0;i<g.nb_transitions;i++){
		printf("---Etat n° : %d\n",g.tab_arretes[i].sommet_depart.num_etat);
		printf("------Transition avec le symbole %s vers l'etat n° %d\n", g.tab_arretes[i].symbole, g.tab_arretes[i].sommet_destination.num_etat);		
		printf("------Final : %d\n", g.tab_arretes[i].sommet_depart.is_final);
	}
}

/*
* @param automate
* @param sylbole c 
*Execute un mot sur un automate et verifie s'il est valide
*/
bool mot_sur_automate(struct automate g,char* c ){
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
/*
* @param automate
* @param sylbole c 
*affiche un mot genere sur un automate et verifie s'il est valide ou pas 
*/
void print_mot_sur_automate(struct automate g,char * c)
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
	if(mot_sur_automate(g,c)==0){
		printf("string %s non valide sur l'automate  \n",c);
	}else{
		printf("string %s valide sur l'automate  \n",c);
	}
}

/*
*@param numero
* prend en entrée un int et retourne sa longueur
*/
int get_length_digit(int numero){
	int nb_digit=0;
	while (numero){
		nb_digit++;
		numero/=10;			
	}
	return nb_digit;
}

/*
* @param automate
* @param symbole
* calcule le nombre d'occurences du symbole dans l'automate
*/
int get_nbr_transition_symbole(struct automate g, char* symbole){
	int nb_occurences=0;
	for (int i=0;i<g.nb_transitions;i++){
		if(g.tab_arretes[i].symbole==symbole){
			nb_occurences++;		
		}	
	}
	return nb_occurences;
}

/*
* @param automate
* @param symbole
* @param numero d'automate
* retourne toutes les transitions qui ont comme etat de depart l'etat avec depart comme numero
*/
struct transitionArray get_transitions(struct automate g, int depart, char* symbole){
	struct transitionArray transitions;
	transitions.tab_arretes=malloc(g.nb_transitions*sizeof(struct arrete)); 
	transitions.nb_transitions=0;
	int indiceStock=0;
	etat etat;
	bool in=0;
	for (int i=0;i<g.nb_etats;i++){
		if (g.tab_etats[i].num_etat==depart){
			etat = g.tab_etats[i];		
			in = 1;		
		}
	}
	if(in==1){
		for (int i=0;i<g.nb_transitions;i++){
			if(g.tab_arretes[i].symbole==symbole && g.tab_arretes[i].sommet_depart.num_etat==etat.num_etat){
				transitions.tab_arretes[indiceStock].sommet_depart = etat;
				transitions.tab_arretes[indiceStock].symbole = symbole;
				transitions.tab_arretes[indiceStock].sommet_destination = g.tab_arretes[i].sommet_destination;
				transitions.nb_transitions++;
				indiceStock++;
			}	
		}
	}
	return transitions;
}

/*
* @param automate
* @param etat
* Vérifie si un état existe dans un automate et retourne 1 si c'est le cas, sinon retourne 0
*/
bool etat_in_automate(struct a_fd g,etat_a_fd etat){
	for (int i=0;i< g.nb_etats;i++){
		if(g.tab_etats[i].nb_elements==etat.nb_elements){
			bool not_equals=0;
			for (int j=0;j< etat.nb_elements;j++){
				if(etat.num_etat[j]!=g.tab_etats[i].num_etat[j]){
					not_equals=1;
				}
			}
			if(not_equals==0){
				return 1;		
			}
		}
	}
	return 0;
}

/*
* @param automate
* Affiche l'automate de determinisation
*/
void print_automate_deterministe(struct a_fd* g){
	printf("\n---Automate\n");
	for (int i=0;i<g->nb_transitions;i++){
		printf("------Transition de {");	
		for (int j=0; j< g->tab_arretes[i].sommet_depart.nb_elements;j++){
			printf("%d ",g->tab_arretes[i].sommet_depart.num_etat[j]);	
		}
		printf("}Avec le symbole : %s vers l'etat {", g->tab_arretes[i].symbole);
		for (int j=0; j< g->tab_arretes[i].sommet_destination.nb_elements;j++){
			printf("%d ",g->tab_arretes[i].sommet_destination.num_etat[j]);	
		}
		printf("}\n");
	}
}

/*
* @param automate
* Déterminise un automate donnée en entrée et retourne l'automate determinisé
*/
struct a_fd determinisation(struct automate g){
	struct a_fd gr;
	gr.tab_etats=malloc(g.nb_etats*g.nb_etats*sizeof(struct etat_a_fd));
	gr.tab_arretes=malloc(g.nb_transitions*g.nb_transitions*sizeof(struct arrete_a_fd));
	gr.tab_etats[0].num_etat=malloc(g.nb_etats*sizeof(struct etat_a_fd));
	gr.tab_etats[0].num_etat[0]=1;
	gr.tab_etats[0].nb_elements=1;
	gr.tab_etats[0].is_final=0;
	gr.nb_etats=1;
	int c_sommet=0;

	/*Get alphabet*/
	char** alphabet;
	alphabet= malloc(sizeof(char**)*g.nb_transitions);
	bool est_dedans;
	int nombre_symbole=0;
	bool is_in=0;
	for(int i=0;i<g.nb_transitions;i++){
		if(i==0){
			alphabet[i]=g.tab_arretes[i].symbole;
			nombre_symbole++;
		}else{
			for (int j=0;j<nombre_symbole;j++){
				if(alphabet[j]==g.tab_arretes[i].symbole){
					is_in=1;				
				}			
			}
			if(is_in==0){
				alphabet[nombre_symbole]=g.tab_arretes[i].symbole;
				nombre_symbole++;	
			}
			is_in=0;
		}
	}
	int ajoutTransition=0;
	int ajoutEtat=1;
	int indiceEtat=1;
	gr.nb_transitions=0;
	while(c_sommet<gr.nb_etats){ /*tant qu'il existe des elements qui n'ont pas encore été traité*/
		for (int i=0;i<nombre_symbole;i++){/*on parcourt pour chaque symbole*/
			int indiceTabTransitions=0;
			arrete* tab_transitions=malloc(nombre_symbole*10*sizeof(struct arrete));
			struct transitionArray tab_arretes_sommet;
			for (int k=0;k<gr.tab_etats[c_sommet].nb_elements;k++){/*pour chaque numero dans l'etat*/
				/*recuperer toutes les transitions*/
				tab_arretes_sommet=get_transitions(g, gr.tab_etats[c_sommet].num_etat[k], alphabet[i]);		
				for (int indice_t=0;indice_t<tab_arretes_sommet.nb_transitions;indice_t++){

					tab_transitions[indiceTabTransitions]=tab_arretes_sommet.tab_arretes[indice_t];		
					indiceTabTransitions++;	
				}

			}
			/*Stocker les transitions récupérés précédemment s'ils existent*/
			if(indiceTabTransitions	>0){
					char s1[30];
					sprintf(s1, "%d", tab_transitions[0].sommet_destination.num_etat);
					int sommet_arrivee=0;
					int* tabEntiers=malloc(10*sizeof(int));;
					tabEntiers[0]= tab_transitions[0].sommet_destination.num_etat;
					for (int ind=1;ind<indiceTabTransitions;ind++){
						tabEntiers[ind]= tab_transitions[ind].sommet_destination.num_etat;
					}
					gr.tab_arretes[ajoutTransition].sommet_depart=gr.tab_etats[c_sommet];
					gr.tab_arretes[ajoutTransition].symbole=alphabet[i];
					struct etat_a_fd nouveauEtat;
					nouveauEtat.num_etat=tabEntiers;
					nouveauEtat.is_final=0;
					nouveauEtat.nb_elements=indiceTabTransitions;
					gr.tab_arretes[ajoutTransition].sommet_destination=nouveauEtat;
					ajoutTransition++;
					gr.nb_transitions++;
					/*Ajouter l'etat s'il n'a pas été ajouté auparavant*/
					if (etat_in_automate(gr,nouveauEtat)==0){
						gr.tab_etats[ajoutEtat]=nouveauEtat;
						ajoutEtat++;
						gr.nb_etats++;
					}
			}
			
		}
		c_sommet++;	
	}
	return gr;
}


int main(){
	struct automate g;	
	g=automate_langage_vide();
	//print_automate_langage_vide(g);
	struct automate ga;
	ga=automate_un_mot("a");
	struct automate gb;
	gb=automate_un_mot("b");
	struct automate gc;
	gc=automate_un_mot("c");
	struct automate gd;
	gd=automate_un_mot("d");
	struct automate ge;
	ge=automate_un_mot("e");

	struct automate gab_reunion;
	gab_reunion=reunion_automate(ga, gb);

	struct automate gcd_reunion;
	gcd_reunion=reunion_automate(gc, gd);

	struct automate gabcd_reunion;
	gabcd_reunion=reunion_automate(gab_reunion, gcd_reunion);
	//print_reunion(gabcd_reunion);

	struct automate gab;
	gab=concatenation_automate(ga, gb);

	struct automate gcd;
	gcd=concatenation_automate(gc, gd);

	printf("\n------------------------concatenation-----------------------------\n");
	struct automate gabcd;
	gabcd=concatenation_automate(gab, gcd);

	struct automate gabcde;
	gabcde=concatenation_automate(gabcd, ge);
	print_concatenate(gabcde);/*concatenation sur les automate gabcd et ge */

	printf("\n------------------------reunion------------------------------------\n");
	struct automate gabcd_re_conc;
	gabcd_re_conc=reunion_automate(gab, gcd);
	print_reunion(gabcd_re_conc); /*reunion  les automate gab et gcd */

	printf("\n------------------------fermeture de kleene-----------------------------\n");
	/***Test Fermeture de kleene***/
	struct automate automate_kleene=fermeture_kleene(gabcd);	/*abcd devient (abcd)* */
	print_kleene(automate_kleene);

	printf("\n------------------------Automate deterministe -----------------------------\n");
	
	print_mot_sur_automate(gab,"ab");
	print_mot_sur_automate(gabcd,"abcd");
	print_mot_sur_automate(ga,"e");

	/******************Determinisation********************/
	struct automate gaa_reunion;
	gaa_reunion=reunion_automate(ga, ga);
	struct automate gaaab_reunion;
	gaaab_reunion=reunion_automate(gaa_reunion, gab_reunion);
	
	struct automate gaaabb_reunion;	
	gaaabb_reunion =reunion_automate(gaaab_reunion, gb);
	printf("\n======Graphe avant determinisation :=====\n");
	print_reunion(gaaabb_reunion);
	struct a_fd afd=determinisation(gaaabb_reunion);
	printf("\n======Graphe après determinisation :=====\n");
	print_automate_deterministe(&afd);
	
}

