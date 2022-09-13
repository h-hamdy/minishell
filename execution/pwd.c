/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:52:22 by fbouanan          #+#    #+#             */
/*   Updated: 2022/06/04 15:52:23 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_pwd(void)
{
	int		i;
	char	*hold;

	i = 0;
	while (g_v.envp[i])
	{
		hold = get_key(g_v.envp[i]);
		if (!ft_strcmp(hold, "PWD"))
		{
			free(hold);
			return (ft_substr(g_v.envp[i], get_eq_s(g_v.envp[i]) + 1,
					ft_strlen(g_v.envp[i])));
		}
		i++;
		free(hold);
	}
	return (0);
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		pwd = ft_get_pwd();
	ft_putstr_fd(pwd, 1);
	ft_putstr_fd("\n", 1);
	if (pwd)
		free(pwd);
	g_v.exit_code = 0;
}

int	other_cmd_tool(t_list *pipeline, int *fd)
{
	if (!((t_cmd *)pipeline->content)->arg)
	{
		close(fd[1]);
		return (0);
	}
	if (c_builtins(((t_cmd *)pipeline->content)->arg[0]))
	{
		if (!g_v.perm)
			builtins(pipeline);
		return (0);
	}
	else
	{
		if (other_cmd_help(pipeline, fd))
			return (1);
	}
	return (0);
}
