/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_sort_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 20:23:19 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 14:23:59 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		null(t_list **lhead)
{
	ft_lstclear(lhead, env_del);
	lhead = NULL;
}

static void		copy_list(t_list **head, t_list **lhead)
{
	t_list	*l;
	t_list	*l1;
	t_env	*tmp;

	l = *head;
	while (l)
	{
		if (!(tmp = malloc(sizeof(t_env))))
			return (null(lhead));
		tmp->name = t_access_env(l)->name;
		tmp->value = t_access_env(l)->value;
		if (!(l1 = ft_lstnew(tmp)))
			return (null(lhead));
		if (ft_strcmp(t_access_env(l)->name, t_access_env(*head)->name) == 0)
			*lhead = l1;
		ft_lstadd_back(lhead, l1);
		l = l->next;
		l1 = l1->next;
	}
}

t_list			*list_sort_env(t_list **head)
{
	t_list	*l;
	t_env	*tmp;
	t_list	*lhead;

	copy_list(head, &lhead);
	if (!head || !lhead)
		return (NULL);
	l = lhead;
	while (l->next)
	{
		tmp = t_access_env(l);
		tmp->next = t_access_env(l->next);
		if (ft_strcmp(tmp->name, (tmp->next)->name) > 0)
		{
			ft_swap_s(&(tmp->name), &((tmp->next)->name));
			ft_swap_s(&(tmp->value), &((tmp->next)->value));
			l = lhead;
		}
		else
			l = l->next;
	}
	return (lhead);
}
