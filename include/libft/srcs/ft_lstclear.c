/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 21:10:09 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 22:11:19 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_list	*actual;

	if (!lst)
		return ;
	actual = *lst;
	while (actual)
	{
		tmp = actual;
		del(actual->content);
		actual = actual->next;
		free(tmp);
	}
	*lst = NULL;
}
