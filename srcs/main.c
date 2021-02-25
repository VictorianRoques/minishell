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

int     main(int ac, char **argv, char **env)
{
    t_lexer lexer;
    t_node *exec_tree;

    ft_bzero(&lexer, sizeof(t_lexer));
    if (build_lexer(argv[1], &lexer) == -1)
    {
        free_lexer(lexer.tokens);
        return (-1);
    }
    // print_lst_tokens(&lexer);
    if (lexer.nb_tokens == 0 || parse(&lexer, &exec_tree) == -1)
    {
        free_lexer(lexer.tokens);
        return (-1);
    }
    execute_ast_tree(exec_tree, env);
    free_lexer(lexer.tokens);
    return(0);
}