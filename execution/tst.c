#include "minishell.h"

char    *get_value(char *s)
{
	char	*hold;
	int		i;

	i = 0;
	while (s[i])
		i++;
	hold = malloc(sizeof(char) * i + 1);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		hold[i] = s[i];
		i++;
	}
	hold[i + 1] = '\0';
	return (hold);
}

int main(int ac, char **av, char **env)
{
    (void)ac;
    char **holder;
    int i;

    i = 0;
    while (env[i])
        i++;
    holder = malloc(sizeof(char *) * i + 1);
    if (!holder)
        return 1;
    i = 0;
    while (env[i])
    {
        holder[i] = env[i];
        i++;
    }
    i = 0;
    int k = 1;
    while (holder[i])
	{
		if (!ft_strcmp(av[k], get_value(holder[i])))
		{
			holder[i][0] = '\0';
			holder[i][1] = 127;
			//printf("%s\n", ft_strchr(exec->envp[i], '=') + 1);
			// return ;
		}
		i++;
	}
    i = 0;
    while (holder[i])
        printf("%s\n", holder[i++]);
}