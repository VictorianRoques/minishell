/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_heredoc_wild.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 22:21:14 by viroques          #+#    #+#             */
/*   Updated: 2021/04/07 18:22:58 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		call_multi_back(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\')
			break ;
		i++;
	}
	if (str[i] == '\\')
	{
		if (i == 0 && !(str[i + 1]))
			return (1);
		if (i > 0 && !(str[i + 1]) && str[i - 1] != '\\')
			return (1);
	}
	return (0);
}

static void		replace_wildcard(t_list **cur_tok, t_list *prev)
{
	t_list		*wild;
	t_list		*tmp;

	if ((wild = wildcard(ft_strdup(t_access_tok(*cur_tok)->data))))
	{
		(prev)->next = wild;
		wild = ft_lstlast(wild);
		wild->next = (*cur_tok)->next;
		tmp = *cur_tok;
		*cur_tok = wild;
		free(t_access_tok(tmp)->data);
		free(t_access_tok(tmp));
		free(tmp);
	}
	else
		t_access_tok(*cur_tok)->type = WORD;
}

static int		replace_heredoc(t_main *m, t_list *cur_tok, t_list *prev)
{
	prev = cur_tok;
	cur_tok = cur_tok->next;
	if (!cur_tok)
		return (0);
	if (t_access_tok(cur_tok)->type == WORD)
		if (!heredoc(m, t_access_tok(cur_tok)->data))
			return (-1);
	return (1);
}

int				sort_heredoc_and_wildcard(t_main *m, t_lexer *lexer)
{
	t_list		*cur_tok;
	t_list		*prev;
	int			ret;

	cur_tok = lexer->tokens->next;
	prev = lexer->tokens;
	while (cur_tok)
	{
		if (t_access_tok(cur_tok)->type == DLESSER)
		{
			ret = replace_heredoc(m, cur_tok, prev);
			if (!ret || ret == -1)
				return (ret);
		}
		else if (t_access_tok(cur_tok)->type == WILDCARD)
			replace_wildcard(&cur_tok, prev);
		else if (t_access_tok(cur_tok)->type == WORD)
		{
			if (call_multi_back(t_access_tok(cur_tok)->data))
				return (BACKSLASH);
		}
		prev = cur_tok;
		cur_tok = cur_tok->next;
	}
	return (0);
}
