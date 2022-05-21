CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror

NAME	=	minishell

LIBFT	=	libft/libft.a

SRCS	=	minishell.c \

OBJS	=	$(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(LIBFT) $(NAME)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT)

$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	rm -rf $(OBJS)

fclean:	clean
	rm -rf libft/libft.a
	rm -rf $(NAME)

re:
	fclean all

.PHONY:	all clean fclean re