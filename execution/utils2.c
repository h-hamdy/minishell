/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 19:54:48 by fbouanan          #+#    #+#             */
/*   Updated: 2022/08/27 19:54:50 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	rest_add_export(char **arg, t_list *pl, t_exec *exec, int i)
{
	char	*tmp;

	tmp = ft_substr(arg[i], 0, exec->index);
	if (!ft_check_export(tmp))
	{
		g_v.exit_code = 1;
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(arg[i], 2);
		ft_putstr_fd("\': not a valid identifier\n", 2);
	}
	else if (check_dup_key(tmp))
	{
		change_env(arg[i],
			ft_substr(arg[i], 0, exec->index));
	}
	else
		ft_valid_export(pl, exec, arg[i]);
	free(tmp);
}

void	add_export(char **arg, t_list *pipeline, t_exec *exec)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		exec->index = get_eq_s(arg[i]);
		if (exec->index == 0)
		{
			if (!ft_check_export(arg[i]))
			{
				g_v.exit_code = 1;
				ft_putstr_fd("export: `", 2);
				ft_putstr_fd(arg[i], 2);
				ft_putstr_fd("\': not a valid identifier\n", 2);
			}
			else if (check_dup_key(arg[i]))
				return ;
			else
				ft_valid_export(pipeline, exec, arg[i]);
		}
		else if (exec->index != 0)
			rest_add_export(arg, pipeline, exec, i);
		i++;
	}
}

pid_t	ft_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		g_v.f_f = -1;
		ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
		return (-1);
	}
	return (pid);
}

int	other_cmd_help(t_list *pipeline, int *fd)
{
	g_v.pid = ft_fork();
	if (g_v.pid == -1)
		return (1);
	if (g_v.pid == 0)
	{
		if (!((t_cmd *)pipeline->content)->arg)
		{
			close(fd[0]);
			close(fd[1]);
			exit(g_v.exit_code);
		}
		signal(SIGQUIT, SIG_DFL);
		if (!((t_cmd *)pipeline->content)->type)
		{
			if (((t_cmd *)pipeline->content)->in != 0)
				dup2(((t_cmd *)pipeline->content)->in, 0);
			if (execve(((t_cmd *)pipeline->content)->cmd_path,
					((t_cmd *)pipeline->content)->arg, g_v.envp))
			{
				ft_print_error(pipeline);
			}
		}
		exec_child(fd, pipeline);
	}
	return (0);
}

int	other_cmd_help2(t_list *pipeline, int *fd)
{
	g_v.pid = ft_fork();
	if (g_v.pid == -1)
		return (1);
	if (g_v.pid == 0)
	{
		close(fd[0]);
		if (!((t_cmd *)pipeline->content)->arg)
		{
			close(fd[1]);
			exit(g_v.exit_code);
		}
		if (pipeline->next != NULL)
			dup2(fd[1], 1);
		if (c_builtins(((t_cmd *)pipeline->content)->arg[0]))
		{
			builtins(pipeline);
			close(fd[0]);
			exit (g_v.exit_code);
		}
		if (!((t_cmd *)pipeline->content)->type)
			help_no_type(pipeline);
		exec_child(fd, pipeline);
	}
	return (0);
}
