/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 19:57:44 by fmanetti          #+#    #+#             */
/*   Updated: 2021/02/28 19:21:22 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int			i;
	char		*s1;
	size_t		len;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	if (!(s1 = malloc((len + 1) * sizeof(char))))
		return (NULL);
	while (len--)
	{
		s1[i] = s[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}
