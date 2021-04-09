/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_ln.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 22:44:28 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/06 17:29:06 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_ln(char *s, char *s1)
{
	char	*tmp;

	tmp = ft_strdup(s1);
	free(s1);
	s1 = ft_strjoin(s, tmp);
	free(tmp);
	return (s1);
}
