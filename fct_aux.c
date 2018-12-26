#include"fct_aux.h"

/* ensures retourne 1 si la case selectionnee est valide
		0 sinon */
int is_valid_indice(char str[4], int n) {
	int 	tmp;
	char	*buftmp;

	if (str[0]<'a' || str[0]>'a'+n-1)
		return 0;

	buftmp = str;
	/* on utilise buftmp pour ne pas modifier str */
	buftmp++;
	tmp = (int) strtol(buftmp, NULL, 10);
	if (tmp < 1 || tmp > n)
		return 0;

	return 1;
}

/* requires 0 <= i < len(tab), tab[i] pile non vide
ensures retourne 1 si la case i contient des pieces blanches,
		0 sinon */
int is_white(stack *tab, int i) {
	char 	*buf;

	buf = malloc(3*sizeof(char));
	buf = top(&tab[i]);
	return (buf[1] == 'B');
}

/* requires str est une case valide du jeu
ensures retourne l'indice du talbeau de jeu correspondant
		à la case selectionnee par le joueur */
int get_indice(char str[4], int n) {
	int 	line;
	int 	col;
	char 	*buftmp;

	col = str[0] - 'a';
	buftmp = str;
	/* on utilise buftmp pour ne pas modifier str */
	buftmp++;
	line = n - strtol(buftmp, NULL, 10);
	return (n*line + col);
}

/* requires *white et *black valides, tab de taille n*n
assigns modifie white et black
ensures white (resp black) contient le nombre de pieces blanches (resp noires) */
void count_pcs(stack *tab, int n, int *white, int *black) {
	int 	i;

	for (i=0 ; i<n*n ; i=i+1) {
		if (is_empty(tab[i]))
			;
		else if (is_white(tab, i))
			*white = *white + 1;
		else
			*black = *black + 1;
	}
}

/* requires tab de taille n*n, old et new indices valides
ensures retourne 1 si le deplacement de old a new ne pass pas au-dessus
		d'une autre piece ,0 sinon */
int is_survoling(stack *tab, int n, int old, int new) {
	int		i_old[2];
	int 	i_new[2];
	int 	i;
	int 	j;

	i_old[0] = old/n;
	i_old[1] = old%n;
	i_new[0] = new/n;
	i_new[1] = new%n;

	/* sur une meme ligne */
	if (i_old[0] == i_new[0]) {
		if (i_old[1] > i_new[1]) {
			for (i=1; i<i_old[1]-i_new[1]; i=i+1)
				if (!is_empty(tab[old-i]))
					return 0;
		}
		else {
			for (i=1; i<i_new[1]-i_old[1]; i=i+1)
				if (!is_empty(tab[old+i]))
					return 0;
		}
	}
	/* sur une meme colonne */
	else if (i_old[1] == i_new[1]) {
		if (i_old[0] > i_new[0]) {
			for (i=1; i<i_old[0]-i_new[0]; i=i+1)
				if (!is_empty(tab[old-i*n]))
					return 0;
		}
		else {
			for (i=1; i<i_new[0]-i_old[0]; i=i+1)
				if (!is_empty(tab[old+i*n]))
					return 0;
		}
	}
	/* sur une meme diagonale */
	else if (abs(i_old[1]-i_new[1]) == abs(i_old[0]-i_new[0])) {
		if (i_old[0]<i_new[0] && i_old[1]<i_new[1]) {
			for (i=i_old[0]+1 ; i<i_new[0] ; i++)
				for (j=i_old[1]+1 ; j<i_new[1] ; j++)
					if (!is_empty(tab[i*n+j]))
						return 0;
		}
		else if (i_old[0]<i_new[0] && i_old[1]>i_new[1]) {
			for (i=i_old[0]+1 ; i<i_new[0] ; i++)
				for (j=i_new[1]+1 ; j<i_old[1] ; j++)
					if (!is_empty(tab[i*n+j]))
						return 0;
		}
		else if (i_old[0]>i_new[0] && i_old[1]<i_new[1]) {
			for (i=i_new[0]+1 ; i<i_old[0] ; i++)
				for (j=i_old[1]+1 ; j<i_new[1] ; j++)
					if (!is_empty(tab[i*n+j]))
						return 0;
		}
		else {
			for (i=i_new[0]+1 ; i<i_old[0] ; i++)
				for (j=i_new[1]+1 ; j<i_old[1] ; j++)
					if (!is_empty(tab[i*n+j]))
						return 0;
		}
	}
	return 1;
}

/* requires 0 < nbr < len(tab[old])
ensures retourne 1 si toutes les nbr pieces peuvent se deplacer
 		de tab[old] a tab[new], 0 sinon */
int is_valid_deplacemt(stack *tab, int n, int nbr, int old, int new){
	stack	tmp;
	char 	c;
	int 	i_old[2];
	int 	i_new[2];

	i_old[0] = old/n;
	i_old[1] = old%n;
	i_new[0] = new/n;
	i_new[1] = new%n;
	tmp = tab[old];
	/* terminaison : la pile tmp est vide */
	while (!is_empty(tmp) && nbr > 0){
		c = pop(&tmp)[0];
		switch (c) {
			case 'T' : if (i_old[0] != i_new[0] && i_old[1] != i_new[1])
					return 0;
				break;
			case 'F' : if (abs(i_old[0] - i_new[0]) != abs(i_old[1] - i_new[1]))
					return 0;
				break;
			case 'P' : if (is_white(tab, old)) {
					if (i_old[0] == n-2 && i_new[0]== n-4)
						break;
					else if (i_old[0]-i_new[0] == 1 && i_new[1] == i_old[1] &&
							(is_empty(tab[new]) || is_white(tab, new)))
						break;
					else if (abs(i_new[1]-i_old[1]) == 1 && i_old[0]-i_new[0] == 1 &&
							!is_empty(tab[new]) && !is_white(tab, new))
						break;
					else return 0;
				}
				else {
					if (i_old[0] == 1 && i_new[0] == 3)
						continue;
					else if (i_new[0]-i_old[0] == 1 && i_new[1] == i_old[1] &&
							(is_empty(tab[new]) || !is_white(tab, new)))
						break;
					else if (abs(i_new[1]-i_old[1]) == 1 && i_new[0]-i_old[0] == 1 &&
							!is_empty(tab[new]) && is_white(tab, new))
						break;
					else return 0;
				} break;
			case 'D' : if (i_old[0] == i_new[0] || i_old[1] == i_new[1])
					break;
				else if (abs(i_old[0] - i_new[0]) == abs(i_old[1] - i_new[1]))
					break;
				else return 0;
				break;
			case 'R' : if (i_new[0]>i_old[0]+1 || i_new[0] < i_old[0]-1 ||
							i_new[1] > i_old[1]+1 || i_new[1] < i_old[1]-1)
					return 0;
				break;
		}
		nbr = nbr - 1;
	}
	return 1;
}
