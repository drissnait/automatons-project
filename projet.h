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

int write_is_final(int sommet, bool isfinal); /*verifie si un sommet est terminal*/

struct graphe automate_langage_vide();/*genere un automate pour le langage vide*/
struct graphe automate_mot_vide(); /*genere un automate pour le mot vide*/
struct graphe automate_un_mot(char* mot);/*genere un automate pour un mot*/
struct graphe reunion_automate(struct graphe g1, struct graphe g2);/*reunion de deux automates*/
struct graphe concatenation_automate(struct graphe g1, struct graphe g2);/*concatene deux graphes*/
struct graphe fermeture_kleene(struct graphe g);/*fermeture de kleene*/

void addToGraphe(struct graphe* g, struct etat etat); /*ajoute etat dans le graphe s'il n'y figure pas*/

void print_automate_langage_vide(struct graphe g); /*print l'automate généré du langage vide*/
void print_automate_mot_vide(struct graphe g2);/*affiche l'automate généré du mot vide*/
void print_automate_un_mot(struct graphe g3);/*affiche l'automate généré pour un mot*/
void print_reunion(struct graphe g);/*affiche l'automate de la réunion*/
void print_concatenate(struct graphe g);/*affiche le graphe de la concatenation*/
void print_kleene(struct graphe g);/*affiche le graphe de la fermeture de kleene*/





