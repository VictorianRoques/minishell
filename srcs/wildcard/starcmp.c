/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starcmp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 14:19:51 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/08 00:01:01 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ending(char **a, int ret)
{
	ft_free_array(a);
	return (ret);
}

static int		beginning_and_end(char *s, char *fname)
{
	int		i;
	t_uint	len;

	if (s[0] && s[0] != '*')
	{
		i = 0;
		while (s[i] && s[i] != '*')
			i++;
		if (ft_strncmp(s, fname, i) != 0)
			return (0);
	}
	len = ft_strlen(s) - 1;
	if (s[len] && s[len] != '*')
	{
		i = len;
		len = ft_strlen(fname) - 1;
		while (i > 0 && s[i] != '*')
		{
			if (s[i] != fname[len])
				return (0);
			i--;
			len--;
		}
	}
	return (1);
}

static int		check_matches(char *fname, char **a)
{
	int		i;
	int		x;
	int		c;

	i = 0;
	x = 0;
	c = 0;
	while (fname[i] && a[x])
	{
		if (fname[i] == a[x][0])
			c = 0;
		if (ft_strncmp(fname + i, a[x], ft_strlen(a[x])) == 0)
		{
			c = 1;
			i += ft_strlen(a[x]);
			x++;
		}
		else
			i++;
	}
	return ((fname[i] == 0 && a[x]) ? 0 : c);
}

static int		is_star(char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] != '*')
			return (0);
	return (1);
}

int				starcmp(char *s, char *fname)
{
	int		ret;
	char	**a;

	if (is_star(s) && fname[0] != '.')
		return (1);
	a = ft_split(s, '*');
	if (!(ret = check_matches(fname, a)) || !(beginning_and_end(s, fname)))
		return (ending(a, 0));
	if (ret == 1)
		return (ending(a, 1));
	return (ending(a, 0));
}
