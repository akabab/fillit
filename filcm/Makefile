NAME = fillit

SRC = ft_utilitaries.c pieces.c main.c 

OBJ = $(SRC:.c=.o)

HEAD =  fillit.h 

CFLAGS = -Wall -Wextra -Werror

LIB = -L . -lft -I.

CC = gcc

all: $(NAME)

$(NAME): $(OBJ)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIB)

clean:
		/bin/rm -f $(OBJ)

fclean: clean
		/bin/rm -f $(NAME)

re: fclean all
	

.PHONY: fclean all re clean