/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:45 by viroques          #+#    #+#             */
/*   Updated: 2021/03/02 16:15:24 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int         create_word_token(char *str, t_lexer *lexer)
{
    int     i;
    t_list  *lst;
    t_token *tok;
    char    *string;

    i = 0;
    while (str[i] && !ft_strchr("<>;|", str[i]))
        i++;
    string = malloc(sizeof(char) * i + 1);
    i = 0;
    while (str[i] && !ft_strchr("<>;|", str[i]))
    {
        string[i] = str[i];
        i++;
    }
    string[i] = 0;
    tok = malloc(sizeof(t_token));
    tok->data = string;
    tok->type = WORD;
    lst = ft_lstnew(tok);
    ft_lstadd_back(&(lexer->tokens), lst);
    lexer->nb_tokens++;
    return (i);
}
static int      strlen_closing_quote(char *str, char c)
{
    int i;

    i = 0;
    while(str[i] && str[i] != c)
        i++;
    return (i);
}

static int     create_operator_token(char *data, int type, t_lexer *lexer)
{
    t_list *lst;
    t_token *token;

    token = malloc(sizeof(t_token));
    token->data = ft_strdup(data);
    token->type = type;
    lst = ft_lstnew(token);
    if (!token | !token->data | !lst)
        return (-1);
    ft_lstadd_back(&(lexer->tokens), lst);
    lexer->nb_tokens++;
    return (0);
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

static  int     handle_quote(char *str, t_lexer *lexer, char quote)
{
    int i;
    int j;
    char *new;
    t_token *tok;
    t_list *lst;

    i = 1;
    if (!is_closing_quote(str, quote))
        return (0);
    while (str[i] != quote && str[i - 1] != '\\')
        i++;
    new = malloc(sizeof(char) * i);
    j = 0;
    i = 1;
    while (str[i] != quote && str[i - 1] != '\\')
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

int     build_lexer(char **tab, t_lexer *lexer)
{
    int i;
    int j;
    int ret;

    ret = 0;
    i = 0;
    j = 0;
    while (tab[i])
    {
        j = 0;
        while(tab[i][j])
        {
            if (tab[i][j] == '|')
            {
                if (tab[i + 1] == NULL){
                    return (error("Error missing instruction after pipe\n", -1));
                    // CALL MULTILIGNE INSTEAD AND WAIT FOR USER INPUT
                }
                create_operator_token("|", PIPE, lexer);
            }
            else if (tab[i][j] == ';')
                create_operator_token(";", SEMICOLON, lexer);
            else if (tab[i][j] == '>')
                create_operator_token(">", GREATER, lexer);
            else if (tab[i][j] == '<')
                create_operator_token("<", LESSER, lexer);
            else if (tab[i][j] == '\n')
                create_operator_token("\n", NEWLINE, lexer);
            else if (tab[i][j] == '\'')
            {
                if (!tab[i][j - 1] || tab[i][j - 1] != '\\')
                {
                    if (!(ret = handle_quote(tab[i] + j, lexer, '\'')))
                        return (error("Error missing closing quote\n", -1));
                    j += ret;
                }
            }
            else if (tab[i][j] == '\"')
            {
                if (!tab[i][j - 1] || tab[i][j - 1] != '\\')
                {
                    if (!(ret = handle_quote(tab[i] + j, lexer, '\"')))
                        return (error("Error missing closing quote\n", -1));
                    j += ret;
                }
            }
            else
                j += create_word_token(tab[i] + j, lexer) - 1;
            j++;
        }   
        i++;
    }
    return (0);
}