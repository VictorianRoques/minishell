/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 10:44:38 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/28 15:59:16 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		d;
	int		i;

	d = 0;
	i = -1;
	while (s[++i])
		if (s[i] == c)
			d = i;
	if (c == 0)
		return ((char*)(s + i));
	if (s[0] == c || d != 0)
		return ((char*)(s + d));
	return (NULL);
}
