/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_merge.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 16:12:21 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/08 00:57:29 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_merge(char **a)
{
	int		x;
	int		len;
	char	*s;

	x = -1;
	len = 0;
	if (!a)
		return (NULL);
	while (a[++x])
		if (a[x])
			len += ft_strlen(a[x]);
	if (!(s = malloc((len + 1) * sizeof(char))))
		return (NULL);
	x = -1;
	while (a[++x])
		if (a[x])
		{
			if (x == 0)
				ft_strcpy(s, a[x]);
			else
				ft_strcpy(s + ft_strlen(s), a[x]);
		}
	s[len] = '\0';
	ft_free_array(a);
	return (s);
}
