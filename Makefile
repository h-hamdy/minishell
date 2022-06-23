CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -g #-fsanitize=address

NAME	=	minishell

LIBFT	=	libft/libft.a

SRCS	=	minishell.c \
			parsing/parsing.c \
			parsing/error_handling.c \
			parsing/pipe_check.c \
			parsing/redirection_check.c \
			parsing/utils.c \
			parsing/dollar_handling.c \
			parsing/get_tokens.c \
			parsing/utils1.c \
			parsing/get_full_cmd.c \

OBJS	=	$(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline

$(LIBFT):
	make -C libft
	make bonus -C libft

clean:
	make clean -C libft
	rm -rf $(OBJS)

fclean:	clean
	rm -rf libft/libft.a
	rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re§