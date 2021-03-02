#include "../includes/minishell.h"

int     error(char *msg, int ret)
{
    write(2, msg, ft_strlen(msg));
    return (ret);
}

int     error_parsing(char *data)
{
    char *error;

    error = ft_strjoin("Syntax error near: ", data);
    write(1, error, ft_strlen(error));
    write(1, "\n", 1);
    free(error);
    return (-1);
}

void        free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

t_token     *t_access(t_list *lst)
{
    if (!lst)
        return (NULL);
    return ((t_token*)lst->content);
}