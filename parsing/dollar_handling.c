
#include "../minishell.h"

char	*count_word(char *line)
{
	char *holder;
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			while (line[i] && line[i] != ' ')
				i++;
		}
		i++;
	}
	holder = malloc(sizeof(char) * i + 1);
	if (!holder)
		return (0);
	return (holder);
}

void    handel_echo(char *line, char **env)
{
	int		i;
	int		j;
	char	*holder;
	char	*value;

	i = 0;
	j = 0;
	holder = count_word(line);
	while (line[i])
	{
		if (line[i] == '$')
		{
			i++;
			while (line[i] && line[i] != ' ')
				holder[j++] = line[i++];
		}
		i++;
	}
	holder[j + 1] = '\0';
	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(holder, env[i], ft_strlen(holder)))
			value = ft_strchr(env[i], '=') + 1;
		i++;
	}
}
