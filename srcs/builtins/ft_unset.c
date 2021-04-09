/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 19:40:29 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 13:52:54 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		delete_elem(t_main *m, t_list *l, t_list *prev)
{
	t_env	*tmp;

	if (ft_strcmp(t_access_env(l)->name, "PATH") == 0)
	{
		ft_free_array(m->pathdirs);
		if (!(m->pathdirs = malloc(sizeof(char*))))
			malloc_error(m, NULL, NO_READING);
		m->pathdirs[0] = NULL;
	}
	tmp = t_access_env(l);
	prev->next = l->next;
	free(tmp->name);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
	free(l);
}

static int		check_errors(t_main *m, char *s)
{
	if (!(ft_isalpha(s[0])))
		return (status_error(m, NO_ERRNO, 1, "not a valid identifier"));
	return (0);
}

int				ft_unset(t_main *m, char **a, t_list **head)
{
	int		x;
	t_list	*l;
	t_list	*prev;

	x = 0;
	m->exit_status = 0;
	while (a[++x])
	{
		if (check_errors(m, a[x]))
			return (1);
		l = *head;
		prev = *head;
		while (l)
		{
			if (ft_strcmp(a[x], t_access_env(l)->name) == 0)
			{
				delete_elem(m, l, prev);
				break ;
			}
			prev = l;
			l = l->next;
		}
	}
	return (1);
}
