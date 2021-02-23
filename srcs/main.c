#include "../includes/minishell.h"


void        print_lst_tokens(t_lexer *lexer)
{
    t_list *toto;

    toto = lexer->tokens;
    printf("\n LEXER \n");
    while (toto)
    {
        t_token *t = toto->content;
        printf("%s     ---------- %u\n", t->data, t->type);
        toto = toto->next;
    }
    printf("nb=%d\n", lexer->nb_tokens);
}

void        free_lexer(t_list *lst_tokens)
{
    t_list *lst = lst_tokens;
    t_list *tmp;
    t_token *tok;

    while (lst)
    {
        tok = lst->content;
        free(tok->data);
        free(tok);
        tmp = lst;
        lst = lst->next;
        free(tmp);
    }
}

char    *search_path(char *cmd_name)
{
    char *path;

    path = ft_strjoin("/bin/", cmd_name);
    return (path);
}

char        **create_cmd_table(t_node *root)
{
    t_node *node;
    char **args;
    int nbcmd;

    nbcmd = 0;
    node = root;
    while(node)
    {
        nbcmd++;
        node = node->left;
    }
    args = malloc(sizeof(char *) * nbcmd + 1);
    node = root;
    nbcmd = 0;
    while (node)
    {
        args[nbcmd] = ft_strdup(node->data);
        node = node->left;
        nbcmd++;
    }
    args[nbcmd] = NULL;
    return (args);
}

int     execute_cmd(t_node *cmd, char **env)
{
    pid_t pid;
    t_node *node = cmd;
    char *path;
    char **args;

    path = search_path(node->data);
    args = create_cmd_table(node);
    if ((pid = fork()) < 0)
        return (-1);
    if (pid == 0)
    {
        execve(path, args, env);
        free(path);
        free_tab(args);
    }
    return (1);
}

int     main(int ac, char **argv, char **env)
{
    t_lexer lexer;
    t_node *exec_tree;

    ft_bzero(&lexer, sizeof(t_lexer));
    if (build_lexer("ls la > toto\n", &lexer) == -1)
    {
        free_lexer(lexer.tokens);
        return (-1);
    }
    print_lst_tokens(&lexer);
    if (lexer.nb_tokens == 0 || parse(&lexer, &exec_tree) == -1)
    {
        free_lexer(lexer.tokens);
        return (-1);
    }
    // execute_pipe_lst(tree, env);
    free_lexer(lexer.tokens);
    return(0);
}