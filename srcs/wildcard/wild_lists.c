/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_lists.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 23:03:10 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 14:32:54 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list		*create_files_elem(char *s)
{
	t_files	*l;
	t_list	*tmp;

	if (!(l = malloc(sizeof(t_files))))
		return (0);
	l->name = s;
	if (!(tmp = ft_lstnew(l)))
		return (0);
	return (tmp);
}

void		add_elem_to_list(t_list **hmatch, char *s)
{
	t_list	*lmatch;

	lmatch = create_files_elem(s);
	ft_lstadd_back(hmatch, lmatch);
}

t_list		*lst_to_token_lst(t_list *final)
{
	t_list	*head;
	t_list	*l;
	char	*fname;

	head = NULL;
	l = final;
	while (l)
	{
		fname = t_access_files(l)->name;
		if (!create_tok_lst(fname, WORD, &head))
			return (NULL);
		l = l->next;
	}
	ft_lstclear(&final, files_del);
	return (head);
}
