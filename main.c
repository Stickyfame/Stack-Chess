#include<stdio.h>
#include<stdlib.h>
#include"piles.h"
#include"fct_aux.h"

/* requires n>=4, tab de taille n*n
ensures affiche le plateau de jeu */
void print_game(stack *tab, int n) {
	int 	i;
	char	*line;
	char 	*letters;
	/* taille d'une ligne sur l'affichage */
	int	nl = 3*(n+1)+1;

	/* construction de la ligne separatrice +--+ */
	line = (char *)malloc(nl*sizeof(char));
	line[0] = ' ';
	line[1] = ' ';
	for (i = 2 ; i < nl ; i = i+3)
		line[i] = '+';
	for (i = 3 ; i < nl-2 ; i = i+3) {
		line[i] = '-';
		line[i+1] = '-';
	}
	line[nl-1] = '\0';

	/* construction de la ligne de lettres */
	letters = (char *)malloc(nl*sizeof(char));
		for (i=1 ; i<nl-2 ; i=i+3 ) {
		letters[i] = ' ';
		letters[i+1] = ' ';
		letters[i+2] = 97+i/3;
	}
	letters[0] = ' ';
	letters[nl-1] = '\0';

	/* affichage */
	puts(letters);
	puts(line);
	printf("%2i", n);
	for (i=0 ; i < n*n ; i++) {
		/* gere la fin d'une ligne et les chiffres de debut de ligne */
		if (i > 0 && i%n==0 ) {
			printf("|\n");
			puts(line);
			printf("%2i", n-i/n);
		}
		/* affichage en cas de case vide */
		if (is_empty(tab[i]))
			printf("|  ");
		/* affichage en cas de case pleine */
		else
			printf("|%s", top(&tab[i]));
	}
	printf("|\n");
	puts(line);
	free(line);
	free(letters);
}

/* requires n>=4, tab de taille n*n
assigns modifies les cases (piles) de tab
ensures tab represente la situation initiale du jeu */
void init(stack *tab, int n) {
	int	j;
	/* on repere le roi pour placer les pieces */
	int	posRoi;

	/* deuxieme ligne */
	for (j=n ; j < 2*n ; j++)
		push ("PN", &tab[j]);
	/* avant derniere ligne */
	for (j=n*(n-2) ; j < n*(n-1) ; j++)
		push ("PB", &tab[j]);

	/* premiere ligne */
	posRoi = n/2;
	for (j=posRoi-2 ; j>-1 ; j=j-2)
		push("FN", &tab[j]);
	for (j=posRoi-3 ; j>-1 ; j=j-2)
		push("TN", &tab[j]);
	for (j=posRoi+1 ; j<n ; j=j+2)
		push("FN", &tab[j]);
	for (j=posRoi+2 ; j<n ; j=j+2)
		push("TN", &tab[j]);
	push ("DN", &tab[posRoi-1]);
	push ("RN", &tab[posRoi]);

	/* derniere ligne */
	posRoi = n*(n-1)+n/2;
	for (j=posRoi-2 ; j>n*(n-1)-1 ; j=j-2)
		push("FB", &tab[j]);
	for (j=posRoi-3 ; j>n*(n-1)-1 ; j=j-2)
		push("TB", &tab[j]);
	for (j=posRoi+1 ; j<n*n ; j=j+2)
		push("FB", &tab[j]);
	for (j=posRoi+2 ; j<n*n ; j=j+2)
		push("TB", &tab[j]);
	push ("DB", &tab[posRoi-1]);
	push ("RB", &tab[posRoi]);
}

/*requires old et now indices valides dans tab
ensures deplace n elements de la pile en case old sur celle en case new
		en conservant l'ordre */
void deplacer(int n, stack *tab, int old, int new) {
	stack 	tmp;
	int 	i;

	i = 0;
	tmp = create(n);
	/* terminaison : la pile tab[old] est vide */
	while(!is_empty(tab[old]) && i < n) {
		i = i + 1;
		push(pop(&tab[old]), &tmp);
	}
	/* terminaison : la pile tmp est vide */
	while(!is_empty(tmp))
		push(pop(&tmp), &tab[new]);
	free(tmp.tab);
}

/*requires old et new indices valides dans tab, tab[new] non vide
ensures deplace n elements de la pile en case old vers la case new en supprimant
		les elements presents dans la case new */
void manger(int n, stack *tab, int old, int new) {
	stack 	tmp;
	int 	i;

	i = 0;
	tmp = create(n);
	/* terminaison : la pile tab[old] est vide */
	while(!is_empty(tab[old]) && i < n) {
		i = i + 1;
		push(pop(&tab[old]), &tmp);
	}
	/* terminaison : la pile tab[new] est vide */
	while(!is_empty(tab[new]))
		pop(&tab[new]);
	/* terminaison : la pile tmp est vide */
	while(!is_empty(tmp))
		push(pop(&tmp), &tab[new]);
	free(tmp.tab);
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

int main() {
	int 	i, n;
	int 	old, new;
	stack 	*tab;
	char 	buf[4];
	char	c;
	int 	play_color, abandon, nbr_black, nbr_white;
	long 	nbr_deplacemt;

	printf("Entrez la taille du plateau, min 4 max 26 : ");
	scanf("%s", buf);
	n = strtol(buf,NULL,10);
	/* si l'utilisateur ne rentre pas un nombre valide*/
	while (n<4 || n>26) {
		printf("Veuillez entrer une taille valide : ");
		scanf("%s", buf);
		n = strtol(buf,NULL,10);
	}
	/* creation du plateau de jeu */
	tab = (stack *) malloc (n*n*sizeof(stack));
	for (i=0 ; i < n*n ; i++) {
			tab[i] = create(5);
	}
	init(tab, n);
	play_color = 1;
	abandon = 1;
	nbr_black = 0;
	nbr_white = 0;
	buf[3] = '\0';
	count_pcs(tab, n, &nbr_white, &nbr_black);

	/* boucle de jeu principale
	condition d'arret : abandon ou victoire ou match nul */
	while (abandon && nbr_black && nbr_white) {
		print_game(tab, n);
		if (play_color)
			printf("C'est au tour des blancs.\n");
		else
			printf("C'est au tour des noirs.\n");

		/* terminaison : break lors du changement de joueur après un
		deplacement valide */
		while (1) {
			printf("Selectionnez une case : ");
			fflush(stdin);
			scanf("%3s", buf);
			/* terminaison : coordonees d'une case valide */
			while (!is_valid_indice(buf,n)) {
				printf("Veuillez selectionner une case valide : ");
				fflush(stdin);
				scanf("%3s", buf);
			}
			printf("\n%s :  ", buf);
			old = get_indice(buf, n);
			print_stack(tab[old]);

			/* decisions du joueur */
			printf("\nQue voulez vous faire ?\nc - selectionner\nd - deplacer\n\
a - abandonner\n");
			fflush(stdin);
			scanf("%1s", buf);
			c = buf[0];
			fflush(stdin);
			/* terminaison : choix valide */
			while (c != 'c' && c != 'd' && c != 'a') {
				printf("Veuillez choisir un action valide\n");
				printf("Que voulez vous faire ?\nc - selectionner\nd - deplacer\
\na - abandonner\n");
				fflush(stdin);
				scanf("%1s", buf);
				fflush(stdin);
				c = buf[0];
			}

			/* verifie que la case a vouloir deplacer est non vide */
			if (is_empty(tab[old]) && c == 'd') {
				printf("Veuillez deplacer une case non vide\n");
				continue;
			}
			/* verfifie que le joueur est de la bonne couleur pour deplacer
				les pieces */
			if ( (play_color && c == 'd' && !is_white(tab, old)) ||
				(!play_color && c == 'd' && is_white(tab, old)) ) {
				printf("Ce n'est pas votre couleur de pieces\n");
				continue;
			}
			if (c == 'd') {
				printf("Sur quelle case voulez vous vous deplacer ? ");
				fflush(stdin);
				scanf("%3s", buf);
				/* terminaison : coordonees d'une case valide */
				while (!is_valid_indice(buf,n)) {
					printf("Veuillez selectionner une case valide : ");
					fflush(stdin);
					scanf("%3s", buf);
				}
				new = get_indice(buf, n);
				printf("Combien d'elements voulez-vous deplacer ? ");
				fflush(stdin);
				scanf("%2s", buf);
				nbr_deplacemt = strtol(buf, NULL, 10);
				/* terminaison : nombre de piece a deplacer valide */
				while (nbr_deplacemt < 1 || nbr_deplacemt > len(tab[old])) {
					printf("Veuillez saisir un nombre valide de pieces\n");
					fflush(stdin);
					scanf("%2s", buf);
					nbr_deplacemt = strtol(buf, NULL, 10);
				}
				if (!is_valid_deplacemt(tab, n, nbr_deplacemt, old, new)){
					printf("Toutes les pieces selectionnees ne peuvent pas\
effectuer ce deplacement\n");
					continue;
				}
				if ( is_survoling(tab, n, old, new) && (is_empty(tab[new])
					|| (play_color && is_white(tab, new))
					|| (!play_color && !is_white(tab, new))) )
					deplacer(nbr_deplacemt, tab, old, new);
				else if (is_survoling(tab, n, old, new)
					&& nbr_deplacemt > len(tab[new]))
					manger(nbr_deplacemt, tab, old, new);
				else {
					printf("Deplacement impossible\n");
					continue;
				}
				play_color = 1 - play_color;
				count_pcs(tab, n, &nbr_white, &nbr_black);
				break;
			}
			else if (c == 'a') {
				printf("Abandon.\n");
				abandon = 0;
				break;
			}
			else if (c == 'c') {
				print_game(tab, n);
				continue;
			}
		}
	}
	if (nbr_black == 0)
		printf("Victoire des blancs\n");
	else if (nbr_white == 0)
		printf("Victoire des noirs\n");
	else if (!abandon && play_color)
		printf("Abandon des blancs, victoire des noirs\n");
	else if (!abandon && !play_color)
		printf("Abandon des noirs, victoire des blancs\n");
	else
		printf("Match nul\n");
	free(tab);
	return 0;
}
