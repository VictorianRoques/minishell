/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 12:23:06 by viroques          #+#    #+#             */
/*   Updated: 2021/04/07 18:14:16 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_parenthese(t_lexer *lexer)
{
	t_list	*cur_tok;
	int		open;
	int		close;

	open = 0;
	close = 0;
	cur_tok = lexer->tokens;
	while (cur_tok)
	{
		if (t_access_tok(cur_tok)->type == OPEN_PAR)
			open++;
		if (t_access_tok(cur_tok)->type == CLOSE_PAR)
			close++;
		cur_tok = cur_tok->next;
	}
	if (open > close)
		return (CLOSE_PAR);
	return (0);
}

static int		is_wild(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (i == 0 && str[i] == '*')
			return (1);
		if (i > 0 && str[i - 1] != '\\' && str[i] == '*')
			return (1);
		i++;
	}
	return (0);
}

static void		type_wildcard(t_lexer *lexer)
{
	t_list	*cur_tok;
	t_list	*prev;

	cur_tok = lexer->tokens->next;
	prev = lexer->tokens;
	while (cur_tok)
	{
		if ((is_wild(t_access_tok(cur_tok)->data))
			&& t_access_tok(prev)->type == SPACE)
			t_access_tok(cur_tok)->type = WILDCARD;
		prev = cur_tok;
		cur_tok = cur_tok->next;
	}
}

int				sort_lexer(t_main *m, t_lexer *lexer)
{
	int		type;
	t_list	*head;
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->type = CHAR_NULL;
	token->data = NULL;
	head = ft_lstnew(token);
	ft_lstadd_front(&(lexer->tokens), head);
	if ((check_pre_space(lexer) == -1))
		return (-1);
	type_wildcard(lexer);
	if ((type = sort_space_and_quote(lexer, m))
		|| (type = sort_heredoc_and_wildcard(m, lexer))
		|| ((type = count_parenthese(lexer))))
		return (type);
	if (lexer->tokens->next)
	{
		lexer->tokens = lexer->tokens->next;
		ft_lstdelone(head, &free);
	}
	return (0);
}
