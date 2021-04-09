/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:28:59 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 13:49:59 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_env(t_main *m, t_list **head)
{
	t_list	*l;
	t_env	*tmp;

	l = *head;
	while (l != NULL)
	{
		tmp = t_access_env(l);
		if (tmp->value)
			printf("%s=%s\n", tmp->name, tmp->value);
		l = l->next;
	}
	m->exit_status = 0;
	return (1);
}
