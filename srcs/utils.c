#include "../includes/minishell.h"

int     error(char *msg, int ret)
{
    write(2, "Error\n", 7);
    write(2, msg, ft_strlen(msg));
    return (ret);
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
    return ((t_token*)lst->content);
}