/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_print_and_handle.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 23:02:02 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 13:39:07 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		erase_and_print(char *s)
{
	ft_putstr(CLEAR_LINES);
	ft_putstr(SAVE_CURSOR);
	ft_putstr(s);
	ft_putstr(RESTORE_CURSOR);
}

static char		*inword_erase(char *s, t_cursor *p)
{
	int			i;
	t_uint		pos;
	char		*tmp;

	pos = (count_lines(s) == 1) ? p->lpos : p->spos;
	if ((i = ft_strlen(s) - pos) > 0)
	{
		tmp = ft_substr(s, ft_strlen(s) - pos, pos);
		if (s[i - 1] != '\n')
			ft_putstr("\b \b");
		else if (s[i - 1] == '\n' && count_lines(s) > 1 && p->lnum > 0)
		{
			changing_line(p);
			p->lpos = (count_lines(tmp) == 1) ? ft_strlen(tmp) :
				(ft_strlen(p->arr[p->lnum + 1]));
		}
		s[i - 1] = '\0';
		erase_and_print(tmp);
		s = ft_strjoin_nl(s, tmp);
		free(tmp);
	}
	return (s);
}

static char		*frankenstr(char *s, char *buf, char *s1)
{
	char	*s2;

	s2 = ft_substr(s, 0, ft_strlen(s) - ft_strlen(s1));
	s2 = ft_strjoin_nl(s2, buf);
	s2 = ft_strjoin_nl(s2, s1);
	free(s);
	return (s2);
}

static char		*inword_write(char *s, char *buf, t_cursor p)
{
	t_uint		pos;
	char		*tmp;

	pos = (count_lines(s) == 1) ? p.lpos : p.spos;
	tmp = ft_substr(s, ft_strlen(s) - pos, pos);
	ft_putchar(buf[0]);
	erase_and_print(tmp);
	s = frankenstr(s, buf, tmp);
	free(tmp);
	return (s);
}

char			*str_print_and_handle(char *s, char *buf, t_cursor *p)
{
	if (buf[0] == '\n')
	{
		while ((p->lpos)--)
			ft_putstr(CURSOR_RIGHT);
		ft_putchar(buf[0]);
		return (s);
	}
	if (p->lpos == 0 && p->spos == 0 && (ft_isprint(buf[0])))
	{
		ft_putchar(buf[0]);
		s = ft_strjoin_nl(s, buf);
	}
	else
	{
		if (buf[0] == BACKSPACE)
			s = inword_erase(s, p);
		else if (ft_isprint(buf[0]))
			s = inword_write(s, buf, *p);
	}
	return (s);
}
