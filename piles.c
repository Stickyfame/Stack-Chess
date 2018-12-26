#include"piles.h"

/* ensures retourne une pile vide */
stack create(int n) {
	stack	s;

	s.tab = malloc(n*sizeof(piece));
	s.size = n;
	s.summit = -1;
	return s;
}

/* ensures retourne 1 si s est vide, 0 sinon */
int is_empty(stack s) {
	return (s.summit == -1);
}

/* requires s non vide
assigns modifie s
ensures retourne le premier element de s en l'enlevant */
char *pop(stack *s) {
	char	*res;

	res = (s->tab[s->summit]).nom;
	s->summit = s->summit - 1;
	return res;
}

/* requires str de taille 2 (3 avec le '\0')
assigns modifie s
ensures place l'element str en haut de s */
void push (char *str, stack *s) {
	int 	i, n;
	piece	*tmp;

	n = s->size;
	s->summit = s->summit + 1;
	if (s->summit == n) {
		tmp = malloc(2*n*sizeof(piece));
		for (i=0 ; i<n ; i=i+1)
			tmp[i] = s->tab[i];
		free(s->tab);
		s->tab = tmp;
	}

	(s->tab[s->summit]).nom[0] = str[0];
	(s->tab[s->summit]).nom[1] = str[1];
	(s->tab[s->summit]).nom[2] = '\0';
}

/* ensures retourne la taille de la pile */
int len(stack s) {
	return (s.summit + 1);
}

/* requires s non vide
ensures retourne le premier element de s sans l'enlever */
char *top(stack *s) {
	return (s->tab[s->summit]).nom;
}

/* ensures affiche la pile s */
void print_stack(stack s) {
	printf("haut:");
	/* terminaison : la pile s est vide */
	while (!is_empty(s))
		printf("%s:", pop(&s));
	printf("bas\n");
}
