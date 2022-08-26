

CC        =    gcc

CFLAGS    =    -Wall -Wextra -Werror -g #-fsanitize=address -g

NAME    =    minishell

LIBFT    =    libft/libft.a

SRCS    =  	minishell.c \
			parsing/parsing.c \
			parsing/error_handling.c \
			parsing/pipe_check.c \
			parsing/redirection_check.c \
			parsing/utils.c \
			parsing/dollar_handling.c \
			parsing/dollar_handling_tools.c \
			parsing/get_tokens.c \
			parsing/utils1.c \
			parsing/get_full_cmd.c \
			parsing/signals/signals.c \
			execution/builtins.c \
			execution/cd.c \
			execution/echo.c \
			execution/env.c \
			execution/exit.c \
			execution/export.c \
			execution/pwd.c \
			execution/unset.c \
			execution/utils.c \
			execution/other_cmd.c \

all:    $(NAME)

$(NAME):    $(LIBFT) $(SRCS)
	@ $(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(LIBFT) -lreadline -L /Users/fbouanan/.brew/opt/readline/lib -lreadline -I /Users/fbouanan/.brew/opt/readline/include
	@ echo "\n\033[1;32mMinishell has been compiled!\033[0m\n"

$(LIBFT):
	@ make -C libft > /dev/null
	@ make bonus -C libft > /dev/null

clean:
	@make clean -C libft

fclean:    clean
	@rm -rf libft/libft.a
	@rm -rf $(NAME)

re: fclean all

.PHONY:    all clean fclean re