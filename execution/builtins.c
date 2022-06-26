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

void	builtins(t_list *pipeline, char **env)
{
	t_exec	*exec;
	char	*cmd;

	cmd = ((t_cmd*)pipeline->content)->cmd;
	//printf("--->%s\n", cmd);
	exec = malloc(sizeof(t_exec));
	//init_data(exec);
	if (!ft_strcmp(cmd, "cd"))
	ft_cd(pipeline);
	else if (!ft_strcmp(cmd, "env"))
		ft_env();
	else if (!ft_strcmp(cmd, "pwd"))
		ft_pwd();
	else if (!ft_strcmp(cmd, "exit"))
		ft_exit(exec);
	else if (!ft_strcmp(cmd, "echo"))
		ft_echo(pipeline, env);
	else if (!ft_strcmp(cmd, "export"))
		ft_export(pipeline, exec);
	else if (!ft_strcmp(cmd, "unset"))
		ft_unset(pipeline);
	else
		printf("minishell: command not found: %s\n", cmd);
}
