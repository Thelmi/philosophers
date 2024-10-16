NAME = philo

SRC = input_parsing.c parsing.c philo_utilities.c program.c routine.c routine_utilities.c eating.c

OBJ = $(SRC:.c=.o)

CFLAGS = cc -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJ)
	$(CFLAGS) $(OBJ) -o $(NAME) -lpthread

%.o:%.c
	$(CFLAGS) -c $< -o $@

re: fclean all

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

.PHONY: all re clean fclean 
