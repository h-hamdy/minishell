CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address

NAME	=	minishell

LIBFT	=	libft/libft.a

SRCS	=	minishell.c \
			parsing/parsing.c \
			parsing/error_handling.c \
        	parsing/error_handling_tools.c \
			parsing/fill_struct/allocate_red.c \
			parsing/fill_struct/allocate_arg.c \
			parsing/fill_struct/allocate_her.c \
			parsing/pipe_check.c \
			parsing/redirection_check.c \
			parsing/expand.c \
			parsing/expand_utils.c \
			parsing/expand_utils1.c \
			parsing/open_herdoc.c \
			parsing/utils.c \
			parsing/utils1.c \
			parsing/tools.c \
			parsing/tools1.c \
			parsing/free.c \
			parsing/display_msg.c \
			parsing/get_full_cmd.c \
			parsing/ft_count_red.c \
			parsing/signals/signals.c \
			execution/builtins.c \
			execution/cd.c \
			execution/echo.c \
			execution/env.c \
			execution/exit.c \
			execution/export.c \
			execution/export_tools.c \
			execution/utils2.c	\
			execution/utils3.c	\
			execution/pwd.c \
			execution/unset.c \
			execution/utils.c \
			execution/other_cmd.c \

all:	$(NAME)

$(NAME):	$(LIBFT) $(SRCS)
	@ $(CC) $(CFLAGS) $(SRCS) -o $(NAME) $(LIBFT) -lreadline -L /Users/fbouanan/.brew/opt/readline/lib -lreadline -I /Users/fbouanan/.brew/opt/readline/include
	@ echo "\n\033[1;32mMinishell has been compiled!\033[0m\n"

$(LIBFT):
	@ make -C libft > /dev/null
	@ make bonus -C libft > /dev/null

clean:
	@make clean -C libft

fclean:	clean
	@rm -rf libft/libft.a
	@rm -rf $(NAME)

re: fclean all

.PHONY:	all clean fclean re§