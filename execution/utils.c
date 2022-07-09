

#include "../minishell.h"


void	init_data(t_exec *exec)
{
	(void)exec;
	exec = NULL;
	// exec->cmd = cmd;
	// g_v.envp;
	// exec->envp = env;
	// if (!exec->hold)
	// {
	// 	while (g_v.envp[i])
	// 		i++;
	// 	exec->hold = malloc(sizeof(char *) * i + 2);
	// 	i = 0;
	// 	while (g_v.envp[i])
	// 	{
	// 		exec->hold[i] = g_v.envp[i];
	// 		i++;
	// 	}
	// // }
}

// char	*ft_strdup(char *s)
// {
// 	char	*n;
// 	int		i;

// 	i = 0;
// 	while (s[i] != '\0')
// 		i++;
// 	n = (char *) malloc (i + 1);
// 	if (!n)
// 		return (0);
// 	n[i] = '\0';
// 	while (i >= 0)
// 	{
// 		n[i] = s[i];
// 		i--;
// 	}
// 	return (n);
// }

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

void	ft_putendl(char *s)
{
	if (s)
		ft_putstr(s);
	write (1, "\n", 1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int diff;
	int i;

	// if (!s1 || !s2)
	// 	exit(1);
	i = 0;
	diff = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (s1[i] != s2[i])
	{
		diff = s1[i] - s2[i];
		return (diff);
	}
	else
		return (0);
}

// int	ft_strlen(char *s)
// {
// 	int i;

// 	i = 0;
// 	while (s[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	char	*s;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	if (!s1 || !s2)
// 		return (NULL);
// 	s = (char *) malloc (sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
// 	if (!s)
// 		return (NULL);
// 	while (s1[i])
// 	{
// 		s[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		s[i + j] = s2[j];
// 		j++;
// 	}
// 	s[i + j] = '\0';
// 	return (s);
// }

// int	ft_strncmp(char *s1,char *s2, int n)
// {
// 	int	i;

// 	i = 0;
// 	while (i < n)
// 	{
// 		if (!(s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0))
// 			return (s1[i] - s2[i]);
// 		i++;
// 	}
// 	return (0);
// }

// int	ft_isalpha(int c)
// {
// 	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
// 		return (1);
// 	return (0);
// }

// int	ft_isalnum(int c)
// {
// 	if (('0' <= c && c <= '9') || ('A' <= c && c <= 'Z')
// 		|| ('a' <= c && c <= 'z') || c == '=')
// 		return (1);
// 	return (0);
// }

// char	*ft_strrchr(char *str, char c)
// {
// 	int		i;

// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		i++;
// 	}
// 	while (i >= 0)
// 	{
// 		if (str[i] == c)
// 		{
// 			return (str + i);
// 		}
// 		i--;
// 	}
// 	return (0);
// }

// char	*ft_strchr(const char *s, int c)
// {
// 	size_t	i;
// 	char	*p;

// 	i = 0;
// 	p = (char *)s;
// 	while (p[i])
// 	{
// 		if (p[i] == (char)c)
// 			return (&p[i]);
// 		i++;
// 	}
// 	if (p[i] == (char)c)
// 		return (&p[i]);
// 	return (0);
// }
