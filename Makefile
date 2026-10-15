NAME = codexion

SRC = parse_args.c ft_atoi_strict.c main.c time.c

CC =  cc

CFLAGS = -Wall -Wextra -Werror

HEADER = codexion.h

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@


clean:
	rm -f $(OBJS)

fclean:clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re