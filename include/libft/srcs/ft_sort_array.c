/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 12:57:43 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/06 17:26:36 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		**ft_sort_array_s(char **a)
{
	int		x;
	char	*tmp;

	x = 0;
	while (a[x + 1])
		if (ft_strcmp(a[x], a[x + 1]) > 0)
		{
			tmp = a[x + 1];
			a[x + 1] = a[x];
			a[x] = tmp;
			x = 0;
		}
		else
			x++;
	return (a);
}
