/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 22:32:50 by viroques          #+#    #+#             */
/*   Updated: 2021/04/06 22:52:07 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			del_cur_tok_and_link_next(t_list **prev, t_list **cur_tok)
{
	if ((*cur_tok)->next)
		(*prev)->next = (*cur_tok)->next;
	else
		(*prev)->next = NULL;
	free(t_access_tok(*cur_tok)->data);
	ft_lstdelone(*cur_tok, &free);
	(*cur_tok) = (*prev)->next;
}

void			print_lst(t_list *lst)
{
	t_list		*toto;
	t_token		*t;

	toto = lst;
	printf("\n LEXER \n");
	while (toto)
	{
		t = toto->content;
		printf("%s     ---------- %u\n", t->data, t->type);
		toto = toto->next;
	}
}
