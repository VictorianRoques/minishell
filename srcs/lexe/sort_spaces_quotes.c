/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_spaces_quotes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 22:24:23 by viroques          #+#    #+#             */
/*   Updated: 2021/04/07 13:59:05 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		while_sorting(t_main *m, t_list **cur_tok, t_list **prev)
{
	int type;

	while (*cur_tok)
	{
		type = t_access_tok(*cur_tok)->type;
		if (type == SPACE || type == NEWLINE)
			del_cur_tok_and_link_next(prev, cur_tok);
		else if (type == DQUOTE || type == SQUOTE || type == WORD)
		{
			if (add_new_word(prev, cur_tok, m))
				return (t_access_tok(*cur_tok)->type);
		}
		else
		{
			*prev = *cur_tok;
			*cur_tok = (*cur_tok)->next;
		}
	}
	return (0);
}

int				sort_space_and_quote(t_lexer *lexer, t_main *m)
{
	t_list	*cur_tok;
	t_list	*prev;
	int		type;

	cur_tok = lexer->tokens->next;
	prev = lexer->tokens;
	if ((type = while_sorting(m, &cur_tok, &prev)))
		return (type);
	return (0);
}
