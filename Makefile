NAME = stack_chess
FLAGS = -Wall -Wextra -ansi
OBJ = fct_aux.o piles.o main.o

all : $(NAME)

$(NAME) : $(OBJ)
	gcc $(FLAGS) $(OBJ) -o $(NAME)

fct_aux.o : fct_aux.h piles.h

piles.o : piles.h

clean :
	rm -rf $(NAME) $(OBJ)

re : clean all
