/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:31:41 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 13:49:47 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_options(char **a, int *x)
{
	int		i;
	int		c;

	c = 0;
	while (a[*x])
	{
		if (ft_strncmp(a[*x], "-n", 2) != 0)
			return (c);
		i = 1;
		while (a[*x][++i])
			if (a[*x][i] != 'n')
				return (c);
		c = 1;
		(*x)++;
	}
	return (c);
}

int				ft_echo(t_main *m, char **a)
{
	int x;

	x = 1;
	if (!(a[1]))
		ft_putchar('\n');
	else
	{
		check_options(a, &x);
		while (a[x])
		{
			ft_putstr(a[x]);
			if (a[x + 1])
				ft_putchar(' ');
			x++;
		}
		x = 1;
		if (!(check_options(a, &x)))
			ft_putchar('\n');
	}
	m->exit_status = 0;
	return (1);
}
