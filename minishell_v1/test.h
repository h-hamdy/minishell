
#ifndef TEST_H
# define TEST_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <curses.h>
# include <term.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include "libft/libft.h"


typedef struct test
{
    int i;
    char **split;
    char *path;
    char *f_path;
    int id;
    char **env;
    char **argv;
    int argc;
} t_test ;

int		ft_strcmp(char *s1, char *s2);


#endif