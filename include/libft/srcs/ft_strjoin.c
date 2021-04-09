/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 15:50:10 by fmanetti          #+#    #+#             */
/*   Updated: 2021/03/07 19:05:18 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		x;
	int		i;
	char	*s3;

	if (!s1 || !s2)
		return (NULL);
	if (!(s3 = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	i = -1;
	while (s1[++i])
		s3[i] = s1[i];
	x = -1;
	while (s2[++x])
		s3[x + i] = s2[x];
	s3[x + i] = '\0';
	return (s3);
}
