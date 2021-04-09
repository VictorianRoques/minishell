/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_word_or_column.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 11:55:44 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 23:37:43 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				word_right(char *s, t_cursor *p)
{
	t_uint	i;
	t_uint	len;
	t_uint	pos;

	len = ft_strlen(s);
	pos = (count_lines(s) == 1) ? p->lpos : p->spos;
	i = len - pos;
	if (!len || i == len)
		return (1);
	while ((ft_isalpha(s[i]) || ft_isdigit(s[i])) && i < len)
	{
		arrow_right(s, p);
		i++;
	}
	while (!(ft_isalpha(s[i]) || ft_isdigit(s[i])) && i < len)
	{
		arrow_right(s, p);
		i++;
	}
	return (1);
}

static int		move_left(char *s, t_cursor *p, int i)
{
	arrow_left(s, p);
	return (i - 1);
}

int				word_left(char *s, t_cursor *p)
{
	int		i;
	t_uint	len;
	t_uint	pos;

	len = ft_strlen(s);
	pos = (count_lines(s) == 1) ? p->lpos : p->spos;
	i = len - pos;
	if (!len || i < 1)
		return (1);
	if (i > 0 && (ft_isalpha(s[i]) || ft_isdigit(s[i])))
		i = move_left(s, p, i);
	while (!(ft_isalpha(s[i]) || ft_isdigit(s[i])) && i > 0)
		i = move_left(s, p, i);
	while ((ft_isalpha(s[i]) || ft_isdigit(s[i])) && i > 0)
	{
		if (i > 0 && !(ft_isalpha(s[i - 1]) || ft_isdigit(s[i - 1])))
			break ;
		arrow_left(s, p);
		i--;
	}
	return (1);
}

int				column_up(char *s, t_cursor *p)
{
	t_uint lpos;

	if (p->lnum > 0)
	{
		lpos = p->lpos;
		if (lpos > ft_strlen(p->arr[p->lnum - 1]))
			lpos = ft_strlen(p->arr[p->lnum - 1]);
		arrow_left(s, p);
		while (p->lpos != lpos)
			arrow_left(s, p);
	}
	return (1);
}

int				column_down(char *s, t_cursor *p)
{
	t_uint lpos;

	if (p->lnum < (count_lines(s) - 1))
	{
		lpos = p->lpos;
		if (lpos > ft_strlen(p->arr[p->lnum + 1]))
		{
			lpos = ft_strlen(p->arr[p->lnum + 1]);
			arrow_right(s, p);
			while (p->lpos != lpos)
				arrow_right(s, p);
		}
		arrow_right(s, p);
		while (p->lpos != lpos)
			arrow_right(s, p);
	}
	return (1);
}
