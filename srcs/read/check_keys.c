/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_keys.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 13:21:23 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 22:34:13 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		move_word_or_column(char *s, t_cursor *p)
{
	char	buf[3];

	read(STDOUT_FILENO, buf, 2);
	buf[2] = '\0';
	if (ft_strcmp(buf, ";5") == 0)
	{
		read(STDOUT_FILENO, buf, 1);
		buf[1] = '\0';
		if (buf[0] == ARR_RIGHT)
			return (word_right(s, p));
		if (buf[0] == ARR_LEFT)
			return (word_left(s, p));
		if (buf[0] == ARR_UP)
			return (column_up(s, p));
		if (buf[0] == ARR_DOWN)
			return (column_down(s, p));
	}
	return (0);
}

static int		home_end(char *s, char c, t_cursor *p)
{
	if (c == HOME)
		return (home(s, p));
	if (c == END)
		return (end(s, p));
	return (0);
}

static int		control(t_main *m, char **s, char *buf)
{
	if (buf[0] == CTRL_C)
		return (control_c(m, *s));
	if (buf[0] == CTRL_D)
	{
		if ((*s)[0] == '\0')
		{
			if (m->p->multi == 1)
			{
				m->exit_status = 0;
				return (1);
			}
			else
				control_d(m, s);
		}
		return (1);
	}
	if (buf[0] == CTRL_Z || buf[0] == CTRL_BSLASH)
		return (1);
	return (0);
}

static int		arrows(t_main *m, char **s, char c)
{
	if (c == ARR_UP)
		return (arrow_up(s, m->hist, m->p));
	if (c == ARR_DOWN)
		return (arrow_down(s, m->hist, m->p));
	if (c == ARR_RIGHT)
		return (arrow_right(*s, m->p));
	if (c == ARR_LEFT)
		return (arrow_left(*s, m->p));
	return (0);
}

int				check_key(t_main *m, char **s, char *buf)
{
	if (buf[0] == CTRL_C || buf[0] == CTRL_D ||
		buf[0] == CTRL_Z || buf[0] == CTRL_BSLASH)
		return (control(m, s, buf));
	if (buf[0] == TAB)
		return (1);
	if (buf[0] != ESCAPE)
		return (0);
	read(STDOUT_FILENO, buf, 1);
	if (buf[0] == '[' || buf[0] == 'O')
	{
		read(STDOUT_FILENO, buf, 1);
		if (buf[0] == ARR_UP || buf[0] == ARR_DOWN ||
			buf[0] == ARR_RIGHT || buf[0] == ARR_LEFT)
			return (arrows(m, s, buf[0]));
		if (buf[0] == DELETE)
			return (delete(*s, buf, m->p));
		if (buf[0] == HOME || buf[0] == END)
			return (home_end(*s, buf[0], m->p));
		if (buf[0] == '1')
			return (move_word_or_column(*s, m->p));
	}
	return (0);
}
