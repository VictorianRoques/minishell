/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:15:14 by viroques          #+#    #+#             */
/*   Updated: 2021/04/07 20:45:22 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_uint			count_lines(char *s)
{
	int		x;
	int		wrd;

	x = 0;
	wrd = 0;
	if (s[0] == '\n')
		wrd++;
	while (s[x])
		if (s[x] == '\n')
		{
			wrd++;
			x++;
			while (s[x] && s[x] != '\n')
				x++;
		}
		else
		{
			wrd++;
			while (s[x] && s[x] != '\n')
				x++;
		}
	if (wrd == 0)
		return (1);
	return (wrd);
}

void			changing_line(t_cursor *p)
{
	ft_putstr(CURSOR_UP);
	(p->lnum)--;
	p->lpos = ft_strlen(p->arr[p->lnum]);
	if (p->lnum == 0)
		p->lpos += (p->multi == 0) ? 9 : 2;
	end(p->arr[p->lnum], p);
}
