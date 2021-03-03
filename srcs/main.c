/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:54 by viroques          #+#    #+#             */
/*   Updated: 2021/03/03 19:43:09 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
    t_list  *lst;
    t_list  *tmp;
    t_token *tok;

    lst = lst_tokens;
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
    t_node  *exec_tree;
    char    **tab;

    tab = ft_split(argv[1], ' ');
    if (build_lexer(tab, &lexer) == -1)
    {
        free_tab(tab);
        free_lexer(lexer.tokens);
        return (-1);
    }
    free_tab(tab);
    // print_lst_tokens(&lexer);
    if (lexer.nb_tokens == 0 || parse(&lexer, &exec_tree) == -1)
    {
        free_lexer(lexer.tokens);
        return (-1);
    }
    free_lexer(lexer.tokens);
    execute_ast_tree(exec_tree, env);
    ast_delete_node(exec_tree);
    return (0);
}