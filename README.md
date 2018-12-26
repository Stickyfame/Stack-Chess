# Projet IPI
Stack Chess

## Règles du jeu
* Les pièces se déplacent comme sur un échiquier classique.
* Le joueur qui a les blancs commence.
* On peut empiler des pièces de la même couleur.
* On peut déplacer un nombre quelconque de pièces situées en haut d'une pile.
* Pour déplacer une pile de pièces, il faut que toutes les pièces de la pile
puissent effectuer ce déplacement.
* Il n'y a pas de situation d'échec.
* Pour se déplacer sur une case ennemie et manger les pièces, il faut déplacer
une pile de taille strictement supérieure en nombre de pièce que celle sur la
case ennemie. Les pièces ennemies sont alors retirées du jeu.
* Un déplacement est impossible si l'on saute au-dessus d'une pièce, adverse ou
ennemie.
* Le jeu se termine lorsqu'un joueur n'a plus de pièces (la prise du roi n'a
pas d'influence). Il peut y avoir des situations de match nul si les joueurs ne
possèdent que des pièces à déplacements incompatibles, ils ne peuvent alors
plus manger de pièces adverses.

## Utilisation du makefile
Commandes disponibles :
* `make` : crée l'exécutable *stack_chess* et tous les fichiers .o
* `make fichier.o` : crée le fichier *fichier.o*
* `make clean` : supprime l'exécutable et les fichiers .o
* `make re` : supprime les fichiers créés et recompile avec `make`

## Utilisation de l'exécutable *stack_chess*
La taille du plateau de jeu sera demandée à l'exécution. Le *stack_chess*
affiche pour chaque case la pièce située en haut de la pile. Les cases peuvent
être sélectionnées par des coordonées : une **lettre** pour leur **colonne**, un
**nombre** pour leur **ligne**
> La taille doit être inférieure à 26 dans un soucis de complexité de sélection
> par coordonées des cases

Les pièces de l'échiquier sont représentées par une chaîne de caractères
composée de la couleur et du type de la pièce. Exemple :
* `"DB"` pour une **dame** de couleur **blanche**
* `"FN"` pour un **fou** de couleur **noir**
> Le cavalier n'est pas disponible dans le jeu. Toutes les pièces sont désignées
> par leur initiale

Chaque joueur tour à tour choisit une case du jeu, ce qui a pour effet
d'afficher le contenu de la pile dans cette case.
Le joueur a ensuite 3 choix :
* `c` : le joueur est invité à sélectionner une nouvelle case pour afficher son
contenu
* `d` : le joueur souhaite déplacer la pile précédemment sélectionnée. Il est
invité à entrer les coordonées de destination, ainsi que le nombre de pièces de
la pile de départ à déplacer
* `a` : le joueur abandonne la partie

## Exemples
[Exemple en .jpg](https://drive.google.com/open?id=1QaStYyex1VVKDxYmlBiv21TU-_15eHzy "exemple après exécution")
```
Entrez la taille du plateau, min 4 max 26 : 6
   a  b  c  d  e  f  
  +--+--+--+--+--+--+
 6|TN|FN|DN|RN|FN|TN|
  +--+--+--+--+--+--+
 5|PN|PN|PN|PN|PN|PN|
  +--+--+--+--+--+--+
 4|  |  |  |  |  |  |
  +--+--+--+--+--+--+
 3|  |  |  |  |  |  |
  +--+--+--+--+--+--+
 2|PB|PB|PB|PB|PB|PB|
  +--+--+--+--+--+--+
 1|TB|FB|DB|RB|FB|TB|
  +--+--+--+--+--+--+
C'est au tour des blancs.
Selectionnez une case : b1

b1 :  haut:FB:bas

Que voulez vous faire ?
c - selectionner
d - deplacer
a - abandonner
d
Sur quelle case voulez vous vous deplacer ? c2
Combien d'elements voulez-vous deplacer ? 1
   a  b  c  d  e  f  
  +--+--+--+--+--+--+
 6|TN|FN|DN|RN|FN|TN|
  +--+--+--+--+--+--+
 5|PN|PN|PN|PN|PN|PN|
  +--+--+--+--+--+--+
 4|  |  |  |  |  |  |
  +--+--+--+--+--+--+
 3|  |  |  |  |  |  |
  +--+--+--+--+--+--+
 2|PB|PB|FB|PB|PB|PB|
  +--+--+--+--+--+--+
 1|TB|  |DB|RB|FB|TB|
  +--+--+--+--+--+--+
C'est au tour des noirs.
Selectionnez une case : c2

c2 :  haut:FB:PB:bas

Que voulez vous faire ?
c - selectionner
d - deplacer
a - abandonner
a
Abandon.
Abandon des noirs, victoire des blancs
```

## Auteur
Charles *Goupix* Anteunis [GitHub here](https://github.com/Stickyfame)
