/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:23:59 by hhamdy            #+#    #+#             */
/*   Updated: 2022/05/25 19:33:16 by hhamdy           ###   ########.fr       */
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

# define GETEXIT 0
# define POSTEXIT 1

# define RED_I "<"
# define RED_O ">"
# define HER "<<"
# define APP ">>"

/*________HER_________*/
# define ERR1 "<<<"
# define ERR2 ">>>"
# define ERR3 "<<>"
# define ERR4 ">><"

/*________RED__________*/
# define ERR5 "<>"
# define ERR6 "><"
# define ERR7 ">|"
# define ERR8 "<|"

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

/******************PARCING_PART__1*****************/
void	parcing_function(void);
void	error_handling(char *line);
void	error_msg(char *s);
char	*skip_space(char *s);
char	*add_space(char *s);
// int     exit_code_handler(int mod, int value);
int	check_pipe_error(char *line);
/*-----------------PARCING_PART_2--------------*/

#endif