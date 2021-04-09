/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 10:24:28 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/06 17:23:59 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int				z;
	unsigned int	x;
	unsigned int	y;

	x = 0;
	z = 0;
	while (haystack[x])
	{
		y = 0;
		while (haystack[x + y] == needle[y])
		{
			if (needle[y + 1] == '\0')
				return ((char*)haystack + x);
			y++;
			z++;
		}
		x++;
	}
	if (ft_strlen(needle) == 0)
		return ((char*)haystack);
	else
		return (NULL);
}
