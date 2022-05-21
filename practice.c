#include <stdio.h>

#include <readline/readline.h>
#include <readline/history.h>

int main()
{
        char *inpt;
        int his;

        inpt = readline("minishell: ");
        his = add_history("hello: ");
        printf("%s\n", inpt);
        printf("%d\n", his);
        printf("\n");
        while (1);
        return 0;
}
