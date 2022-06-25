/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:23:59 by hhamdy            #+#    #+#             */
/*   Updated: 2022/06/25 03:21:15 by hhamdy           ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_cmd
{
	char		*cmd;
	char		*cmd_path;
	char		**arg;
	char		**red;
	int			*type;
	char		**limiter;
	int			in;
	int			out;
}				t_cmd;

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
char	**ft_free(char **str, int k);
void	d_free(char **str);
int		ft_count_word(char *line, int index);

/********************CHECK_TOKENS***********************/
int		check_pipe_error(char *line);
int		redirection_error(char **s_line);

/*******************REDIRECTION*******************/
// int		get_red(char **s_line, t_node *data);
int		count_redirection(char *line);
int		count_herdoc(char *line);
int		check_cmd(char *line, int flag);
int		skip_redirecition(char *line, int index);
int		count_args(char *line);
int 	skip_word(char *line, int index, int flag);

/********************EXC_HERDOC*************************/
// int		get_herdoc(char **s_line, t_node *data);
// void	exec_herdoc(char **s_line, t_node *data);


t_list	*get_full_cmd(char **s_line);

#endif