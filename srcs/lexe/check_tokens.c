/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:00:05 by viroques          #+#    #+#             */
/*   Updated: 2021/03/30 18:43:52 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			is_quote_or_space(char c, t_lexer *lexer)
{
	if (c == '\n')
		return (create_tok("\n", NEWLINE, lexer));
	if (c == '\"')
		return (create_tok("\"", DQUOTE, lexer));
	if (c == '\'')
		return (create_tok("\'", SQUOTE, lexer));
	if (c == ' ')
		return (create_tok(" ", SPACE, lexer));
	return (0);
}

int			is_redirection(char c, char *next, t_lexer *lexer, int *i)
{
	if (c == '>')
	{
		if (next && *next == '>')
		{
			*i += 1;
			return (create_tok(">>", DGREATER, lexer));
		}
		return (create_tok(">", GREATER, lexer));
	}
	if (c == '<')
	{
		if (next && *next == '<')
		{
			*i += 1;
			return (create_tok("<<", DLESSER, lexer));
		}
		return (create_tok("<", LESSER, lexer));
	}
	return (is_quote_or_space(c, lexer));
}

int			is_an_operator(char c, char *next, t_lexer *lexer, int *i)
{
	if (c == '|')
	{
		if (next && *next == '|')
		{
			*i += 1;
			return (create_tok("||", DPIPE, lexer));
		}
		return (create_tok("|", PIPE, lexer));
	}
	if (c == '&' && next && *next == '&')
	{
		*i += 1;
		return (create_tok("&&", DAMPERSTAND, lexer));
	}
	if (c == '(')
		return (create_tok("(", OPEN_PAR, lexer));
	if (c == ')')
		return (create_tok(")", CLOSE_PAR, lexer));
	if (c == ';')
		return (create_tok(";", SEMICOLON, lexer));
	return (is_redirection(c, next, lexer, i));
}
