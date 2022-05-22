/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 09:23:59 by hhamdy            #+#    #+#             */
/*   Updated: 2022/05/22 10:11:18 by hhamdy           ###   ########.fr       */
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

typedef	struct	s_node
{
	char		*cmd;
	char		*arguments;
	char		*infile;
	char		*outfile;
	char		*limiter;
}				t_node;

typedef struct	s_data
{
	t_node	*node;
	char	**path;
	pid_t	pid;
}				t_data;

/******************PARCING_PART*****************/
void	parcing_function(void);
/*-----------------------------------------------*/

#endif