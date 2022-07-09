xCC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address

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
			execution/builtins.c \
			execution/cd.c \
			execution/echo.c \
			execution/env.c \
			execution/exit.c \
			execution/export.c \
			execution/pwd.c \
			execution/unset.c \
			execution/utils.c \

OBJS	=	$(SRCS:.c=.o)

all:	$(NAME)

$(NAME):	$(LIBFT) $(OBJS)
	@	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline -L /Users/fbouanan/.brew/opt/readline/lib -lreadline -I /Users/fbouanan/.brew/opt/readline/include

$(LIBFT):
	make -C libft
	make bonus -C libft

clean:
	@make clean -C libft
	@rm -rf $(OBJS)

fclean:	clean
	@rm -rf libft/libft.a
	@rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re§