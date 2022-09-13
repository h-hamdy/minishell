/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbouanan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 15:25:38 by fbouanan          #+#    #+#             */
/*   Updated: 2022/08/28 15:25:40 by fbouanan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_print_error(t_list *pipeline)
{
	if (ft_strchr(((t_cmd *)pipeline->content)->arg[0], '/'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(((t_cmd *)pipeline->content)->arg[0], 2);
		if (opendir(((t_cmd *)pipeline->content)->arg[0]))
		{
			ft_putstr_fd(": is a directory\n", 2);
			g_v.exit_code = 126;
		}
		else
		{
			if (!access(((t_cmd *)pipeline->content)->arg[0], F_OK) && \
				access(((t_cmd *)pipeline->content)->arg[0], X_OK))
			{
				ft_putstr_fd(": Permision denied\n", 2);
				g_v.exit_code = 1;
			}
			else
			{
				ft_putstr_fd(": No such file or directory\n", 2);
				g_v.exit_code = 127;
			}
		}
	}
	else
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(((t_cmd *)pipeline->content)->arg[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		g_v.exit_code = 127;
	}
	exit(g_v.exit_code);
}

void	help_no_type(t_list *pipeline)
{
	if (((t_cmd *)pipeline->content)->in != 0)
	{
		dup2(((t_cmd *)pipeline->content)->in, 0);
		close(((t_cmd *)pipeline->content)->in);
	}
	if (execve(((t_cmd *)pipeline->content)->cmd_path,
			((t_cmd *)pipeline->content)->arg, g_v.envp))
		ft_print_error(pipeline);
}

void	ft_unset_tool(t_list *pipeline, char **tmp, int k)
{
	int		j;
	char	*hold;

	j = -1;
	if (check_var(((t_cmd *)pipeline->content)->arg[k]))
		for_unset(pipeline, k);
	else if (check_unset(((t_cmd *)pipeline->content)->arg[k]))
		return ;
	else
	{
		while (tmp[++j])
		{
			hold = get_key(tmp[j]);
			if (!ft_strcmp(((t_cmd *)pipeline->content)->arg[k], hold))
			{
				tmp[j][0] = '\0';
				free(hold);
				break ;
			}
			free(hold);
		}
		g_v.exit_code = 0;
	}
}

void	ft_putstr(char *s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		write (1, &s[i], 1);
		i++;
	}
}

void	write_expo_2(int i, char **sor_exp, char **value_h)
{
	char	*hold;

	if (sor_exp[i][0] == '\0')
		i++;
	else if (get_eq_s(sor_exp[i]))
	{
		ft_putstr_fd("declare -x ", 1);
		hold = get_key(sor_exp[i]);
		ft_putstr_fd(hold, 1);
		free(hold);
		ft_putstr_fd("=\"", 1);
		ft_putstr_fd(value_h[i], 1);
		ft_putstr_fd("\"\n", 1);
	}
	else
	{
		ft_putstr_fd("declare -x ", 1);
		hold = get_key(sor_exp[i]);
		ft_putstr_fd(hold, 1);
		free(hold);
		ft_putstr_fd("\n", 1);
	}
}
