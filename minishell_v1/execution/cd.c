/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/04 15:51:41 by fbouanan          #+#    #+#             */
/*   Updated: 2022/06/04 15:51:43 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	change_pwd(char *pwd, int i, int id)
{
	char	*key;
	if (!id)
	{
		key = get_key(g_v.envp[i]);
		g_v.envp[i] = NULL;
		g_v.envp[i] = ft_strjoin(fo_strjoin(key, '='), pwd);
	}
	else if (id)
	{
		key = get_key(g_v.envp[i]);
		g_v.envp[i] = NULL;
		g_v.envp[i] = ft_strjoin(fo_strjoin(key, '='), pwd);
	}
}

void	ft_cd(t_list *pipeline)
{
	char 	*path;
	int		i;
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 1024);
	i = 1;
	if (!((t_cmd*)pipeline->content)->arg[i])
	{
		path = ft_strdup(getenv("HOME"));
	}
	else
		path = ft_strdup(((t_cmd*)pipeline->content)->arg[i]);
	// printf ("%s\n", path);
	if (chdir(path) == -1)
	{
		ft_putstr_fd("cd: no such file or directory: ", 1);
		ft_putendl_fd(path, 1);
		return ;
	}
	
	pwd = getcwd(NULL, 1024);
	i = 0;
	while (g_v.envp[i])
	{
		if (!ft_strcmp(get_key(g_v.envp[i]), "PWD"))
			change_pwd(pwd, i, 0);
		else if (!ft_strcmp(get_key(g_v.envp[i]), "OLDPWD"))
			change_pwd(oldpwd, i, 1);
		i++;
	}
	free(path);
	g_v.exit_code = 0;
}
