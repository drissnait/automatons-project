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
}automate;


/************************AFD*************************/
typedef struct etat_a_fd{
	int* num_etat;
	int nb_elements;
	bool is_final;
}etat_a_fd;

typedef struct arrete_a_fd{	
	etat_a_fd sommet_depart;
	etat_a_fd sommet_destination;
	char* symbole;
}arrete_a_fd;

typedef struct a_fd{
	etat_a_fd sommet_initial;
	int nb_etats;
	int nb_transitions;
	struct etat_a_fd* tab_etats;
	struct arrete_a_fd* tab_arretes;
}a_fd;

/*Structure pour avoir le nombre de transition pour les afd*/
typedef struct transitionArray{
	struct arrete* tab_arretes;
	int nb_transitions;
}transitionArray;

int write_is_final(int sommet, bool isfinal); /*verifie si un sommet est terminal*/

struct automate automate_langage_vide();/*genere un automate pour le langage vide*/
struct automate automate_mot_vide(); /*genere un automate pour le mot vide*/
struct automate automate_un_mot(char* mot);/*genere un automate pour un mot*/
struct automate reunion_automate(struct automate g1, struct automate g2);/*reunion de deux automates*/
struct automate concatenation_automate(struct automate g1, struct automate g2);/*concatene deux graphes*/
struct automate fermeture_kleene(struct automate g);/*fermeture de kleene*/
struct a_fd determinisation(struct automate g);/*Déterminise un automate donnée en entrée et retourne l'automate determinisé*/

void addToGraphe(struct automate* g, struct etat etat); /*ajoute etat dans le graphe s'il n'y figure pas*/

bool mot_sur_automate(struct automate g,char* c );/*Execute un mot sur un automate et verifie s'il est valide*/
void print_mot_sur_automate(struct automate g,char * c);/*affiche un mot genere sur un automate et verifie s'il y est */
int get_length_digit(int numero);/*prend en entrée un int et retourne sa longueur*/
int get_nbr_transition_symbole(struct automate g, char* symbole);/*calcule le nombre d'occurences du symbole dans l'automate*/
transitionArray get_transitions(struct automate g, int depart, char* symbole);/*retourne toutes les transitions qui ont comme etat de depart l'etat avec depart comme numero*/
bool etat_in_automate(struct a_fd g,etat_a_fd etat);/*Vérifie si un état existe dans un automate et retourne 1 si c'est le cas, sinon retourne 0*/
void print_automate_deterministe(struct a_fd* g);/*Affiche l'automate de determinisation*/

void print_automate_langage_vide(struct automate g); /*print l'automate généré du langage vide*/
void print_automate_mot_vide(struct automate g2);/*affiche l'automate généré du mot vide*/
void print_automate_un_mot(struct automate g3);/*affiche l'automate généré pour un mot*/
void print_reunion(struct automate g);/*affiche l'automate de la réunion*/
void print_concatenate(struct automate g);/*affiche le graphe de la concatenation*/
void print_kleene(struct automate g);/*affiche le graphe de la fermeture de kleene*/





