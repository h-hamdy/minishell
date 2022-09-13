/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhamdy <hhamdy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:06:03 by fbouanan          #+#    #+#             */
/*   Updated: 2022/09/05 12:39:13 by hhamdy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	c_builtins(char *cmd)
{
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "$?"))
		return (1);
	return (0);
}

void	exec_builtins(char *cmd, t_list *pipeline, t_exec *exec)
{
	if (!ft_strcmp(cmd, "cd"))
		ft_cd(pipeline);
	else if (!ft_strcmp(cmd, "env"))
		ft_env(pipeline);
	else if (!ft_strcmp(cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd, "exit"))
		ft_exit(pipeline);
	else if (!ft_strcmp(cmd, "echo"))
		ft_echo(pipeline);
	else if (!ft_strcmp(cmd, "export"))
		ft_export(pipeline, exec);
	else if (!ft_strcmp(cmd, "unset"))
		ft_unset(pipeline);
}

void	builtins(t_list *pipeline)
{
	t_exec	*exec;
	char	*cmd;

	cmd = ((t_cmd *)pipeline->content)->arg[0];
	exec = malloc(sizeof(t_exec));
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
	exec_builtins(cmd, pipeline, exec);
	free(exec);
}
