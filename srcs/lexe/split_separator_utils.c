/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_separator_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 22:45:49 by viroques          #+#    #+#             */
/*   Updated: 2021/04/06 22:51:06 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_in(char *charset, char c, const char *str)
{
	int	i;

	i = 0;
	if (c == '\\' && str[1] && str[1] == '\'')
		return (1);
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	if (charset[i] == c)
		return (1);
	return (0);
}

int				is_sep(const char *s, int i, char *charset)
{
	if (i == 0)
	{
		if (is_in(charset, s[i], s + i) || is_in(charset, s[i + 1], s + i + 1)
			|| s[i + 1] == '\0')
			return (1);
	}
	else
	{
		if ((is_in(charset, s[i], s + i) && s[i - 1] != '\\')
			|| (is_in(charset, s[i + 1], s + i + 1) && s[i] != '\\')
			|| s[i + 1] == '\0')
			return (1);
	}
	return (0);
}
