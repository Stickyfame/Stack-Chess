#ifndef FCT_AUX_H
#define FCT_AUX_H

#include"piles.h"
#include<stdlib.h>

/* ensures retourne 1 si la case selectionnee est valide
		0 sinon */
int is_valid_indice(char str[4], int n);

/* requires 0 <= i < len(tab), tab[i] pile non vide
	ensures retourne 1 si la case i contient des pieces blanches,
			0 sinon */
int is_white(stack *tab, int i);

/* requires str est une case valide du jeu
ensures retourne l'indice du talbeau de jeu correspondant
		à la case selectionnee par le joueur */
int get_indice(char str[2], int n);

/* requires *white et *black valides, tab de taille n*n
assigns modifie white et black
ensures white (resp black) contient le nombre de pieces blanches (resp noires) */
void count_pcs(stack *tab, int n, int *white, int *black);

/* requires tab de taille n*n, old et new indices valides
	ensures retourne 1 si le deplacement de old a new ne pass pas au-dessus
			d'une autre piece ,0 sinon */
int is_jumping(stack *tab, int n, int old, int new);

/* requires 0 < nbr < len(tab[old])
	ensures retourne 1 si toutes les nbr pieces peuvent se deplacer
	 		de tab[old] a tab[new], 0 sinon */
int is_valid_deplacemt(stack *tab, int n, int nbr, int old, int new);

#endif
