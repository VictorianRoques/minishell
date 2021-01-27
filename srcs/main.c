#include "../includes/minishell.h"

char        *ft_getenv(char **env, char *elem)
{
    int i;
    char *tmp;

    i = 0;
    while (env[i])
    {
        if ((tmp = ft_strnstr(env[i], elem, ft_strlen(env[i]))))
            return (tmp + 5);
        i++;
    }
    return (0);
}


int     main(int ac, char **argv, char **env)
{
    (void)ac;
    (void)argv;
    (void)env;
    char buff[4096];
    char **cmd;
    while (42)
    read(0, buff, 4096);
    cmd = ft_split(buff, ' ');
    int i = 0;
    while(cmd[i])
    {
        printf("%s\n", cmd[i]);
        i++;
    }
}