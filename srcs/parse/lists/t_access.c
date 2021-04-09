/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_access.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 12:37:21 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 14:24:30 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token		*t_access_tok(t_list *lst)
{
	if (!lst)
		return (NULL);
	return ((t_token*)lst->content);
}

t_env		*t_access_env(t_list *lst)
{
	if (!lst)
		return (NULL);
	return ((t_env*)lst->content);
}

t_files		*t_access_files(t_list *lst)
{
	if (!lst)
		return (NULL);
	return ((t_files*)lst->content);
}
