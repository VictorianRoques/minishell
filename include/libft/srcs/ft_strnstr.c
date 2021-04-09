/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 10:28:48 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/22 10:33:03 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int				z;
	unsigned int	x;
	unsigned int	y;

	x = 0;
	z = 0;
	while (haystack[x])
	{
		y = 0;
		while (haystack[x + y] == needle[y] && (x + y) < len)
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
