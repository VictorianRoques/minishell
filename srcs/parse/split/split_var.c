/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 01:16:29 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/08 11:00:26 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_wrd(char *s)
{
	int		x;
	int		wrd;

	x = 0;
	wrd = 0;
	while (s[x])
		if (s[x] == '$')
		{
			if (x == 0 || (x > 0 && s[x - 1] != '\\'))
				wrd++;
			x++;
			while (s[x] && (ft_isalpha(s[x]) || s[x] == '_' || s[x] == '?'))
				x++;
		}
		else
		{
			wrd++;
			while (s[x] && !(s[x] == '$' && (x == 0 ||
				(x > 0 && s[x - 1] != '\\'))))
				x++;
		}
	return (wrd);
}

static int		is_var(char *s, char **a, int x)
{
	int		start;

	start = x - 1;
	while (s[x] && (ft_isalpha(s[x]) || s[x] == '_' || s[x] == '?'))
		x++;
	(*a) = ft_substr(s, start, x - start);
	return (x);
}

static int		is_not_var(char *s, char **a, int x)
{
	int		start;

	start = x;
	while (s[x])
	{
		if ((s[x] == '$' && (x == 0 || (x > 0 && s[x - 1] != '\\'))))
			break ;
		x++;
	}
	(*a) = ft_substr(s, start, x - start);
	return (x);
}

char			**split_var(char *s)
{
	int		x;
	int		y;
	char	**a;

	x = 0;
	y = 0;
	if (!(a = malloc((count_wrd(s) + 1) * sizeof(char*))))
		return (NULL);
	while (s[x])
	{
		if (s[x] == '$' && (x == 0 || s[x - 1] != '\\'))
			x = is_var(s, &(a[y]), ++x);
		else
			x = is_not_var(s, &(a[y]), x++);
		y++;
	}
	a[y] = NULL;
	return (a);
}
