#ifndef PILES_H
#define PILES_H

#include<stdio.h>
#include<stdlib.h>

/* taille 3 pour 2 lettres plus le \0 */
typedef struct piece {
	char nom[3];
} piece ;

/* piles a taille variable */
typedef struct stack {
	piece	*tab;
	int 	summit;
	int 	size;
} stack ;

stack create(int n) ;

int is_empty(stack s) ;

char *pop(stack *s) ;

void push(char *str, stack *s) ;

int len(stack s);

char *top(stack *s) ;

void print_stack(stack s) ;

#endif
