NAME	= codexion
CC		= cc
FLAGS	= -Wall -Wextra -Werror -pthread

SRCS	= srcs/main.c srcs/sim.c \
			srcs/parse_args.c

OBJS	= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

%.o: %.c
	$(CC) $(FLAGS) -I includes -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re