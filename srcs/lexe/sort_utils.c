/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 19:16:25 by viroques          #+#    #+#             */
/*   Updated: 2021/04/07 19:27:37 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check_closing_quote(t_list *tokens, t_token_type type)
{
	t_list	*cur_tok;

	cur_tok = tokens->next;
	while (cur_tok)
	{
		if (t_access_tok(cur_tok)->type == type)
			return (1);
		cur_tok = cur_tok->next;
	}
	return (0);
}

int			check_pre_space(t_lexer *lexer)
{
	t_list		*cur_tok;
	t_list		*prev;

	cur_tok = lexer->tokens->next;
	prev = lexer->tokens;
	while (cur_tok && (t_access_tok(cur_tok)->type == SPACE
			|| t_access_tok(cur_tok)->type == NEWLINE))
	{
		prev = cur_tok;
		cur_tok = cur_tok->next;
		free(t_access_tok(prev)->data);
		ft_lstdelone(prev, &free);
	}
	if (cur_tok)
		lexer->tokens->next = cur_tok;
	else
		return (-1);
	return (0);
}

void		word_interpolation(t_main *m, t_list **cur_tok, t_list **prev)
{
	char	*tmp;

	tmp = t_access_tok(*cur_tok)->data;
	t_access_tok(*cur_tok)->data = check_vars(m, tmp, m->ehead, m->exit_status);
	free(tmp);
	*prev = *cur_tok;
	*cur_tok = (*cur_tok)->next;
}

char		*join_and_free(char *s1, char *s2)
{
	char	*data;
	char	*tmp1;
	char	*tmp2;

	if (!s1)
	{
		if (!(s1 = malloc(sizeof(char))))
			return (NULL);
		*s1 = '\0';
	}
	tmp1 = s1;
	tmp2 = s2;
	data = ft_strjoin(s1, s2);
	free(tmp1);
	free(tmp2);
	return (data);
}
