/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:23:59 by hhamdy            #+#    #+#             */
/*   Updated: 2022/06/02 10:28:06 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <sys/stat.h>

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_node
{
	char		**full_cmd;
	char		*cmd;
	char		*arguments;
	char		*infile;
	char		*outfile;
	char		*limiter;
}				t_node;

typedef struct s_data
{
	t_node	*node;
	char	**path;
	int		pipe_num;
	pid_t	pid;
}				t_data;

typedef struct s_tokens
{
	char	*value;
	enum 
	{
		WORD,
		RDRI,
		RDRO,
		HERDOC,
		APPEND,
		PIPE
	} e_type;
}	t_tokens;

/********************PARCING_PART__1********************/
void	parcing_function(char **env);
void	error_handling(char *line, char **env);
void    handel_echo(char *line, char **env);
void    *after_split(char *s_line);
int 	ft_count(char *token);
char	*handel_many_red(char *token);
void    *check_tokens(char *token, char *value);

/*********************UTILS****************************/
void	error_msg(char *s);
int		ignore_space(char *line, int i);
char	*skip_space(char *s);
char	*add_space(char *s);
int		trow_err(int d_quote, int s_quote);
int		skip_char_inside_quote(char *line, int i, int flag);
char	*fo_strjoin(char *str, char c);

/********************CHECK_TOKENS***********************/
int		check_pipe_error(char *line);
int		redirection_error(char **s_line);

#endif