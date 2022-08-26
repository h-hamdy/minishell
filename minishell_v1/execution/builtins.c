/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 16:06:03 by fbouanan          #+#    #+#             */
/*   Updated: 2022/06/04 16:06:04 by fbouanan         ###   ########.fr       */
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
	return (0);
}

void	builtins(t_list *pipeline)
{
	t_exec	*exec;
	char	*cmd;

	// printf("---->%p\n", ((t_cmd*)pipeline->content)->arg[0]);
	// if (!((t_cmd*)pipeline->content)->arg)
	// {
	// 	if (((t_cmd*)pipeline->content)->type[0] == 2)
	// 		exit(1);
	// 	printf("Minishell: no such file or directory: %s\n",
	// 		((t_cmd*)pipeline->content)->red[0]);
	// 	return ;
	// }
	cmd = ((t_cmd*)pipeline->content)->arg[0];
	exec = malloc(sizeof(t_exec));
	if (((t_cmd*)pipeline->content)->in != 0)
	{
		dup2(((t_cmd*)pipeline->content)->in, 0);
		close(((t_cmd*)pipeline->content)->in);
	}
	if (((t_cmd*)pipeline->content)->out != 0)
	{
		dup2(((t_cmd*)pipeline->content)->out, 1);
		close(((t_cmd*)pipeline->content)->out);
	}
	if (!ft_strcmp(cmd, "cd"))
		ft_cd(pipeline);
	else if (!ft_strcmp(cmd, "env"))
		ft_env();
	else if (!ft_strcmp(cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd, "exit"))
		ft_exit(exec);
	else if (!ft_strcmp(cmd, "echo"))
		ft_echo(pipeline);
	else if (!ft_strcmp(cmd, "export"))
		ft_export(pipeline, exec);
	else if (!ft_strcmp(cmd, "unset"))
		ft_unset(pipeline);
	// else
	// {
	// 	other_cmd(pipeline);
	// 	while (wait(NULL) != -1)
	// 	;
	// }
}
