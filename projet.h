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

typedef struct automate{
	etat sommet_initial;
	int nb_etats;
	int nb_transitions;
	struct etat* tab_etats;
	struct arrete* tab_arretes;
}afd;

int write_is_final(int sommet, bool isfinal); /*verifie si un sommet est terminal*/

struct automate automate_langage_vide();/*genere un automate pour le langage vide*/
struct automate automate_mot_vide(); /*genere un automate pour le mot vide*/
struct automate automate_un_mot(char* mot);/*genere un automate pour un mot*/
struct automate reunion_automate(struct automate g1, struct automate g2);/*reunion de deux automates*/
struct automate concatenation_automate(struct automate g1, struct automate g2);/*concatene deux graphes*/
struct automate fermeture_kleene(struct automate g);/*fermeture de kleene*/

void addToGraphe(struct automate* g, struct etat etat); /*ajoute etat dans le graphe s'il n'y figure pas*/

void print_automate_langage_vide(struct automate g); /*print l'automate généré du langage vide*/
void print_automate_mot_vide(struct automate g2);/*affiche l'automate généré du mot vide*/
void print_automate_un_mot(struct automate g3);/*affiche l'automate généré pour un mot*/
void print_reunion(struct automate g);/*affiche l'automate de la réunion*/
void print_concatenate(struct automate g);/*affiche le graphe de la concatenation*/
void print_kleene(struct automate g);/*affiche le graphe de la fermeture de kleene*/





