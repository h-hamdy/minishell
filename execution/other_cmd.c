/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 17:08:33 by fbouanan          #+#    #+#             */
/*   Updated: 2022/09/06 22:39:20 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	infile_procces(t_list *pipeline, int i)
{
	int	infile;

	infile = open(((t_cmd *)pipeline->content)->red[i], O_RDONLY);
	if (infile < 0)
	{
		g_v.exit_code = 1;
		if (access(((t_cmd *)pipeline->content)->red[i], F_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(((t_cmd *)pipeline->content)->red[i], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else if (access(((t_cmd *)pipeline->content)->red[i], R_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(((t_cmd *)pipeline->content)->red[i], 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
		g_v.perm = 1;
	}
	((t_cmd *)pipeline->content)->in = infile;
	return (0);
}

int	outfile_procces(t_list *pipeline, int i)
{
	int	outfile;

	outfile = open(((t_cmd *)pipeline->content)->red[i],
			O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (outfile < 0)
	{
		g_v.exit_code = 1;
		if (access(((t_cmd *)pipeline->content)->red[i], F_OK) == -1)
			ft_putstr_fd("Error while trying to open the outfile.\n", 2);
		else if (access(((t_cmd *)pipeline->content)->red[i], W_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(((t_cmd *)pipeline->content)->red[i], 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
		g_v.perm = 1;
	}
	((t_cmd *)pipeline->content)->out = outfile;
	return (0);
}

int	append_hand(t_list *pipeline, int i)
{
	int	outfile;

	outfile = open(((t_cmd *)pipeline->content)->red[i],
			O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile < 0)
	{
		g_v.exit_code = 1;
		if (access(((t_cmd *)pipeline->content)->red[i], F_OK) == -1)
			ft_putstr_fd("Error while trying to open the outfile.\n", 2);
		else if (access(((t_cmd *)pipeline->content)->red[i], W_OK) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(((t_cmd *)pipeline->content)->red[i], 2);
			ft_putstr_fd(": Permission denied\n", 2);
		}
		g_v.perm = 1;
	}
	((t_cmd *)pipeline->content)->out = outfile;
	return (0);
}

void	exec_child(int *fd, t_list *pipeline)
{
	if (((t_cmd *)pipeline->content)->in != 0)
	{
		dup2(((t_cmd *)pipeline->content)->in, 0);
		close(((t_cmd *)pipeline->content)->in);
	}
	if (((t_cmd *)pipeline->content)->out != 0)
	{
		dup2(((t_cmd *)pipeline->content)->out, 1);
		close(((t_cmd *)pipeline->content)->out);
	}
	close(fd[0]);
	close(fd[1]);
	if (!g_v.perm)
	{
		if (execve(((t_cmd *)pipeline->content)->cmd_path,
				((t_cmd *)pipeline->content)->arg, g_v.envp))
			ft_print_error(pipeline);
	}
	exit(g_v.exit_code);
}

int	other_cmd(t_list *pipeline, int *fd)
{
	int		i;

	i = 0;
	if (g_v.n_node == 1)
	{
		if (other_cmd_tool(pipeline, fd))
			return (1);
		return (0);
	}
	else
	{
		if (other_cmd_help2(pipeline, fd))
			return (1);
		signal(SIGINT, SIG_IGN);
	}
	if (((t_cmd *)pipeline->content)->out != 0)
		close(((t_cmd *)pipeline->content)->out);
	if (((t_cmd *)pipeline->content)->in != 0)
		close(((t_cmd *)pipeline->content)->in);
	return (1);
}
