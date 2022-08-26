#include "test.h"

char	*ft_strjoin1(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	if (!(str = (char*)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '/';
	i++; j = 0;
	while (s2[j])
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	return (str);
}

char    *get_key(char *s)
{
	char	*hold;
	int		i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	hold = malloc(sizeof(char) * i + 1);
	i = 0;
	while (s[i] && s[i] != '=')
	{
		hold[i] = s[i];
		i++;
	}
	hold[i] = '\0';
	return (hold);
}

char *get_path(char **env)
{
	int i;
	char *path;

	i = 0;
	while (env[i])
	{
		if (ft_strcmp(get_key(env[i]), "PATH") == 0)
		{
			path = ft_strchr(env[i], '=') + 1;
			return (path);
		}
		i++;
	}
	return (NULL);
}

char* function(t_test *test)
{
	while (test->split[test->i])
	{
		test->f_path = ft_strjoin(test->split[test->i], test->argv[1]);
		if (access (test->f_path, F_OK) == 0)
			return (test->f_path);
		test->i++;
	}
	return (NULL);
}

int main(int argc, char **argv, char **env)
{
	t_test *test;
	test = malloc(sizeof(t_test));
	test->env = env;
	test->argc = argc;
	test->argv = argv;
	(void)argv;
	if (argc != 0)
	{
		test->path = get_path(env);
		test->split = ft_split(test->path, ':');
		test->i = 0;
		test->f_path = function(test);
		test->id = fork();
		if (test->id == 0)
		{

		}
		// else

			// f_path = f_path;
		// if (id == 0)
		// {
		// }
	}

	return (0);
}