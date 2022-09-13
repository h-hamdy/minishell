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

void	change_pwd(char *pwd, int i)
{
	char	*key;
	char	*tmp;

	key = fo_strjoin(get_key(g_v.envp[i]), '=');
	free(g_v.envp[i]);
	g_v.envp[i] = NULL;
	tmp = ft_strjoin(key, pwd);
	g_v.envp[i] = tmp;
	free(key);
}

void	rest_cd(char *pwd, char *oldpwd)
{
	int		i;
	char	*hold;

	i = 0;
	while (g_v.envp[i])
	{
		hold = get_key(g_v.envp[i]);
		if (!ft_strcmp(hold, "PWD"))
			change_pwd(pwd, i);
		else if (!ft_strcmp(hold, "OLDPWD"))
			change_pwd(oldpwd, i);
		free(hold);
		i++;
	}
}

void	ft_do(char *path, char *oldpwd)
{
	g_v.exit_code = 1;
	if (!access(path, F_OK))
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": Not a directory\n", 2);
	}
	else
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putendl_fd(": no such file or directory", 2);
	}
	free(path);
	free(oldpwd);
}

int	ft_do2(char *oldpwd)
{
	if (!getenv("HOME"))
	{
		free(oldpwd);
		g_v.exit_code = 1;
		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
		return (1);
	}
	return (0);
}

void	ft_cd(t_list *pipeline)
{
	int		i;
	char	*oldpwd;
	char	*pwd;

	oldpwd = getcwd(NULL, 1024);
	i = 1;
	if (!((t_cmd *)pipeline->content)->arg[i])
	{
		if (ft_do2(oldpwd))
			return ;
		g_v.path = ft_strdup(getenv("HOME"));
	}
	else
		g_v.path = ft_strdup(((t_cmd *)pipeline->content)->arg[i]);
	if (chdir(g_v.path) == -1)
	{
		ft_do(g_v.path, oldpwd);
		return ;
	}
	pwd = getcwd(NULL, 1024);
	rest_cd(pwd, oldpwd);
	free(g_v.path);
	free(pwd);
	free(oldpwd);
	g_v.exit_code = 0;
}
