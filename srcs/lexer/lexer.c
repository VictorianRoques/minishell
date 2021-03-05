/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:45 by viroques          #+#    #+#             */
/*   Updated: 2021/03/05 11:52:47 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int     is_an_operator(char c, char *next, t_lexer *lexer)
{
    if (c == '|')
        return (create_token("|", PIPE, lexer));
    if (c == ';')
        return (create_token(";", SEMICOLON, lexer));
    if (c == '>')
    {
        if (next && *next == '>')
            return (create_token(">>", DGREATER, lexer));
        return (create_token(">", GREATER, lexer));
    }
    if (c == '<')
        return (create_token("<", LESSER, lexer));
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
            if ((ret = is_an_operator(tab[i][j], tab[i] + j + 1, lexer)));
            else if (tab[i][j] == '\"')
                ret = create_token(tab[i] + j, DQUOTE, lexer);
            else if (tab[i][j] == '\'')
                ret = create_token(tab[i] + j, QUOTE, lexer);
            else
                ret = create_token(tab[i] + j, WORD, lexer);
            if (ret == -1)
                return (error("Missing closinig quote\n", -1));
            j += ret;
        }
        i++;
    }
    return (0);
}