/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:23:59 by hhamdy            #+#    #+#             */
/*   Updated: 2022/05/29 17:08:48 by hhamdy           ###   ########.fr       */
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

/********************PARCING_PART__1********************/
void	parcing_function(void);
void	error_handling(char *line);

/*********************UTILS****************************/
void	error_msg(char *s);
int		ignore_space(char *line, int i);
char	*skip_space(char *s);
char	*add_space(char *s);
int		trow_err(int d_quote, int s_quote);
int		skip_char_inside_quote(char *line, int i, int flag);

/********************CHECK_TOKENS***********************/
int		check_pipe_error(char *line);
int		redirection_error(char **s_line);

#endif