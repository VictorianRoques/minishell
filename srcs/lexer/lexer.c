/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:45 by viroques          #+#    #+#             */
/*   Updated: 2021/03/03 19:52:04 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int      last_tab_element(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        i++;
    return (i - 1);
}

static int      is_closing_quote(char *str, char quote)
{
    int i;

    i = 1;
    while (str[i])
    {
        if (str[i] == quote && str[i - 1] != '\\')
            return (1);
        i++;
    }
    return (0);
}

int     handle_quote(char *str, t_lexer *lexer, char quote)
{
    int     i;
    int     j;
    char    *new;
    t_token *tok;
    t_list  *lst;

    i = 1;
    if (!is_closing_quote(str, quote))
        return (0);
    while (str[i] != quote)
        i++;
    new = malloc(sizeof(char) * i);
    j = 0;
    i = 1;
    while (str[i] != quote)
    {
        new[j] = str[i];
        j++;
        i++;
    }
    new[j] = 0;
    tok = malloc(sizeof(t_token));
    tok->data = new;
    tok->type = WORD;
    lst = ft_lstnew(tok);
    ft_lstadd_back(&(lexer->tokens), lst);
    lexer->nb_tokens++;
    return (i);
}

int     is_an_operator(char c, char *next, t_lexer *lexer)
{
    if (c == '|')
        return (create_operator_token("|", PIPE, lexer));
    if (c == ';')
        return (create_operator_token(";", SEMICOLON, lexer));
    if (c == '>')
    {
        if (next && *next == '>')
            return (create_operator_token(">>", DGREATER, lexer));
        return (create_operator_token(">", GREATER, lexer));
    }
    if (c == '<')
        return (create_operator_token("<", LESSER, lexer));
    return (0);
}

int     build_lexer(char **tab, t_lexer *lexer)
{
    int i;
    int j;
    int ret;

    i = 0;
    j = 0;
    while (tab[i])
    {
        j = 0;
        while (tab[i][j])
        {
            if (tab[i][j] == '|')
            {
                if (i == last_tab_element(tab) && j == ft_strlen(tab[i]) - 1)
                {
                    printf("call multiligne for piping\n");
                }
            }
            if ((ret = is_an_operator(tab[i][j], tab[i] + j, lexer)))
            {
                if (ret == -1)
                    return (error("Malloc failed\n", -1));
                j += ret;
            }
            else if (tab[i][j] == '\'')
            {
                if (!(ret = handle_quote(tab[i] + j, lexer, '\'')))
                    return (error("Missing closing quote\n", -1));
                j += ret + 1;
            }
            else if (tab[i][j] == '\"')
            {
                if (!(ret = handle_quote(tab[i] + j, lexer, '\"')))
                    return (error("Missing closing quote\n", -1));
                j += ret + 1;  
            }
            else
            {
                ret = create_word_token(tab[i] + j, lexer);
                if (ret == -1)
                    return (error("Malloc failed\n", -1));
                j += ret;
            }
        }
        i++;
    }
    return (0);
}