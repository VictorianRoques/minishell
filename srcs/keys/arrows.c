/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrows.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:35:38 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 14:10:42 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		arrow_up(char **s, char **h, t_cursor *p)
{
	int		i;

	i = -1;
	i = ft_arrlen(h);
	if ((p->hnum + 1) == (t_uint)i)
		return (1);
	if (p->hnum < (t_uint)(i - 1))
		(p->hnum)++;
	home(*s, p);
	ft_putstr(CLEAR_LINES);
	ft_putstr(h[p->hnum]);
	p->lpos = 0;
	p->spos = 0;
	p->lnum = count_lines(h[p->hnum]) - 1;
	ft_free_array(p->arr);
	p->arr = split_keep(h[p->hnum], '\n');
	free(*s);
	(*s) = ft_strdup(h[p->hnum]);
	return (1);
}

int		arrow_down(char **s, char **h, t_cursor *p)
{
	int		i;

	i = -1;
	i = ft_arrlen(h);
	home(*s, p);
	if (p->hnum > 0)
		(p->hnum)--;
	ft_putstr(CLEAR_LINES);
	ft_putstr(h[p->hnum]);
	p->lpos = 0;
	p->spos = 0;
	p->lnum = count_lines(h[p->hnum]) - 1;
	ft_free_array(p->arr);
	p->arr = split_keep(h[p->hnum], '\n');
	free(*s);
	(*s) = ft_strdup(h[p->hnum]);
	return (1);
}

int		arrow_left(char *s, t_cursor *p)
{
	t_uint		i;
	t_uint		pos;

	pos = (count_lines(s) == 1) ? p->lpos : p->spos;
	if ((i = ft_strlen(s) - pos) > 0)
	{
		if (s[i - 1] != '\n')
		{
			(p->lpos)++;
			ft_putstr(CURSOR_LEFT);
			if (count_lines(s) > 1)
				(p->spos)++;
		}
		else if (s[i - 1] == '\n' && count_lines(s) > 1 && p->lnum > 0)
		{
			changing_line(p);
			p->lpos = 0;
			(p->spos)++;
		}
	}
	return (1);
}

int		arrow_right(char *s, t_cursor *p)
{
	t_uint	nln;

	nln = count_lines(s) - 1;
	if (p->lpos > 0)
	{
		(p->lpos)--;
		ft_putstr(CURSOR_RIGHT);
		if (count_lines(s) > 1)
			(p->spos)--;
	}
	else if (p->lpos == 0 && nln > 0 && p->lnum < nln)
	{
		ft_putstr(CURSOR_DOWN);
		(p->spos)--;
		if (p->lnum == 0)
			home("minish $ ", p);
		p->lpos = 0;
		home(p->arr[p->lnum], p);
		(p->lnum)++;
		p->lpos = (p->arr[p->lnum]) ? ft_strlen(p->arr[p->lnum]) : 0;
	}
	return (1);
}
