/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:34:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 14:11:18 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		delete(char *s, char *buf, t_cursor *p)
{
	t_uint	pos;

	read(STDOUT_FILENO, buf, 1);
	if (buf[0] == '~')
	{
		pos = (count_lines(s) == 1) ? p->lpos : p->spos;
		if (ft_strlen(s) == 0 || pos == 0)
			return (1);
		arrow_right(s, p);
		buf[0] = BACKSPACE;
	}
	return (0);
}
