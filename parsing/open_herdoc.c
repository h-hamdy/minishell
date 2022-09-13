/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_herdoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 00:57:55 by hhamdy            #+#    #+#             */
/*   Updated: 2022/09/11 17:58:22 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_in(int index, int n_limiter, int *fd, t_cmd *node)
{
	if (index == n_limiter - 1)
	{
		node->in = dup(fd[0]);
		close(fd[1]);
		close(fd[0]);
	}
	else
		(close(fd[1]), close(fd[0]));
}

void	ft_pipe(int *fd)
{
	if (pipe(fd) == -1)
		display_msg("Pipe failture.\n");
}

void	her_sig(int sig)
{
	(void)sig;
	if (sig == SIGINT)
	{
		g_v.exit_code = 1;
		g_v.flag = 1;
		// g_v.perm = 1;
		printf("\n");
		g_v.check_her = 0;
		close(0);
	}	
}

int	find_limiter(char *str, int fd[2])
{
	char	*buff;

	buff = readline("> ");
	if (!buff)
		return (0);
	if (ft_strcmp(buff, str))
	{
		write (fd[1], buff, ft_strlen(buff));
		write(fd[1], "\n", 2);
	}
	else
	{
		free(buff);
		return (0);
	}
	free(buff);
	return (1);
}

void	open_herdoc(t_list *pipeline)
{
	int		index;
	int		fd[2];
	int		n_p;

	g_v.check_her = 1;
	while (pipeline)
	{
		signal(SIGINT, her_sig);
		index = 0;
		n_p = count_d_pointer(((t_cmd *)pipeline->content)->limiter);
		while (index < n_p)
		{
			ft_pipe(fd);
			while (g_v.check_her)
			{
				if (!find_limiter((\
					(t_cmd *)pipeline->content)->limiter[index], fd))
					break ;
			}
			fill_in(index, n_p, fd, ((t_cmd *)pipeline->content));
			index++;
		}
		pipeline = pipeline->next;
	}
}
