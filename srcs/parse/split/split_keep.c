/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_keep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 01:16:29 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 14:28:58 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		count_word(char *s, char c)
{
	int		x;
	int		wrd;

	x = 0;
	wrd = 0;
	if (s[0] == c)
		wrd++;
	while (s[x])
		if (s[x] == c)
		{
			wrd++;
			x++;
			while (s[x] && s[x] != c)
				x++;
		}
		else
		{
			wrd++;
			while (s[x] && s[x] != c)
				x++;
		}
	return (wrd);
}

char			**split_keep(char *s, char c)
{
	int		x;
	int		y;
	int		start;
	char	**a;

	x = -1;
	y = 0;
	start = 0;
	if (!(a = malloc((count_word(s, c) + 1) * sizeof(char*))))
		return (NULL);
	while (s[++x])
		if (s[x] == c)
		{
			a[y] = ft_substr(s, start, x - start);
			if (s[x + 1])
				start = x + 1;
			y++;
		}
	if (x != 0 && !s[x] && s[x - 1] != c)
		a[y++] = ft_substr(s, start, x - start);
	a[y] = NULL;
	return (a);
}
