/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling_tools.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 15:59:26 by fbouanan          #+#    #+#             */
/*   Updated: 2022/09/09 15:59:28 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	wait_function(void)
{
	int		exec_s;

	exec_s = 0;
	g_v.ret = 1;
	while (g_v.ret != -1)
	{
		g_v.ret = waitpid(-1, &exec_s, 0);
		if (g_v.ret == g_v.pid)
		{
			if (WIFSIGNALED(exec_s))
			{
				g_v.sig = WTERMSIG(exec_s);
				g_v.exit_code = 128 + g_v.sig;
			}
			if (WIFEXITED(exec_s))
				g_v.exit_code = WEXITSTATUS(exec_s);
		}
	}
}

void	do_openning(t_list *pipeline, int *fd)
{
	(void)fd;
	if (!g_v.flag)
		open_herdoc(pipeline);
	// while (pipeline)
	// {
	// 	// if (!g_v.perm)
	// 	// {
	// 		// if (!g_v.flag)
	// 		// 	open_files(pipeline, fd);
	// 		// g_v.perm = 0;
	// 	// }
	// 	pipeline = pipeline->next;
	// }
}

void	pipeline_loop(t_list *pipeline, int *fd, t_list *head)
{
	do_openning(pipeline, fd);
	pipeline = head;
	while (pipeline)
	{
		if (!g_v.flag)
		{
			open_files(pipeline, fd);
			if (g_v.perm)
				break;
			g_v.perm = 0;
		}
		if (g_v.flag)
		{
			g_v.flag = 0;
			break ;
		}
		printf("%d\n", g_v.perm);
		// if (g_v.perm)
		// {
		// 	g_v.perm = 0;
		// 	break ;
		// }
		if (g_v.f_f == -1)
			break ;
		if (pipe(fd) == -1)
		{
			ft_putstr_fd("pipe failed\n", 2);
			return ;
		}
		other_cmd(pipeline, fd);
		if (pipeline->next != NULL)
			dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		pipeline = pipeline->next;
	}
	signal(SIGINT, SIG_IGN);
	dup2(g_v.dup_0, 0);
	dup2(g_v.dup_1, 1);
	close(g_v.dup_0);
	close(g_v.dup_1);
	wait_function();
}
