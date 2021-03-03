/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:15:30 by viroques          #+#    #+#             */
/*   Updated: 2021/03/03 19:51:11 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int         len_data(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_strchr("<>;|", str[i]))
            break;
        if (str[i] == '\\')
            i++;
        i++;
    }
    return (i);
}

char        *get_data_word(char *str)
{
    int i;
    int j;
    char *new;

    i = 0;
    j = 0;
    if (!(new = malloc(sizeof(char) * ft_strlen(str) + 1)))
        return (NULL);
    while (str[i])
    {
        if (ft_strchr("<>;|", str[i]))
            break;
        if (str[i] == '\\')
            i++;
        new[j] = str[i];
        i++;
        j++;
    }
    new[j] = 0;
    return (new);
}

int         create_word_token(char *str, t_lexer *lexer)
{
    t_list  *lst;
    t_token *tok;
    char    *data;
    int     len;

    len = len_data(str);
    if (!(data = get_data_word(str)))
        return (-1);
    if (!(tok = malloc(sizeof(t_token))))
        return (-1);
    tok->data = data;
    tok->type = WORD;
    if (!(lst = ft_lstnew(tok)))
        return (-1);
    ft_lstadd_back(&(lexer->tokens), lst);
    lexer->nb_tokens++;
    return (len);
}

int     create_operator_token(char *data, int type, t_lexer *lexer)
{
    t_list *lst;
    t_token *token;

    if (!(token = malloc(sizeof(t_token))))
        return (-1);
    if (!(token->data = ft_strdup(data)))
        return (-1);
    token->type = type;
    if (!(lst = ft_lstnew(token)))
        return (-1);
    ft_lstadd_back(&(lexer->tokens), lst);
    lexer->nb_tokens++;
    if (type == DGREATER)
        return (2);
    return (1);
}