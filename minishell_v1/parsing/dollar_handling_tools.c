
#include "../minishell.h"

char    *wrong_var( char *holder)
{
	char	*value;
	int		i;

	i = 0;
	value = ft_strdup("");
	while (holder[i])
	{
		if (holder[i] == ' ')
			i++;
		if (holder[i] == '>' || holder[i] == '<')
			break ;
		else
			value = fo_strjoin(value, holder[i++]);
	}
	return (value);
}

char	*correct_var(char **env, char *holder, int j)
{
	char	*value;
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup("");
	value = ft_strdup("");
	while (holder[i] && holder[i] != '$' && holder[i] != '"')
	{
		if (holder[i] == '>' || holder[i] == '<')
			break ;
		i++;
	}
	value = ft_strjoin(ft_strchr(env[j], '=') + 1, tmp);
	return (value);
}

char	*for_quote(char *line, int i)
{
	char	*tmp;

	tmp = ft_strdup("");
	if (line[i - 1] == '"')
	{
		while (line[i] && line[i] != '"')
			tmp = fo_strjoin(tmp, line[i++]);
	}
	else if (line[i - 1] == '\'')
	{
		while (line[i] && line[i] != '\'')
			tmp = fo_strjoin(tmp, line[i++]);
	}
	else
		return (line);
	return (tmp);
}

char	*find_sing_q(char *line)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] != '\'')
				tmp = fo_strjoin(tmp, line[i++]);
		}
		i++;
	}
	return tmp;
}

char	*check_digits(char *line)
{
	int		i;
	char	*tmp;

	tmp = ft_strdup("");
	i = 2;
	while (line[i] && line[i] != '"')
		tmp = fo_strjoin(tmp, line[i++]);
	return (tmp);
}

char	*rest_of_dollar(char **env, char *holder)
{
	char	*my_env;
	char	*value;
	int		j;

	j = 0;
	while (env[j])
	{
		my_env = ft_strdup("");
		my_env = find_equal_s(env[j]);
		if (ft_strcmp(holder, my_env))
		{
			value = wrong_var(holder);
		}
		else if (!ft_strcmp(holder, my_env))
		{
			value = correct_var(env, holder, j);
			break ;
		}
		j++;
	}
	return (value);
}
