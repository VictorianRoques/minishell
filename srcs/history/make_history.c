/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 20:42:53 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 14:05:16 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	make_history(char *hist_path, char **h)
{
	int		i;
	int		fd;

	i = 0;
	if ((fd = open(hist_path, O_WRONLY | O_APPEND | O_CREAT
		| O_TRUNC, 0640)) < 0)
	{
		error(ERRNO, NULL);
		return ;
	}
	i = ft_arrlen(h);
	while (i--)
	{
		ft_putstr_fd(h[i], fd);
		ft_putchar_fd(SEPARATOR, fd);
		ft_putchar_fd('\n', fd);
		ft_putchar_fd(SEPARATOR, fd);
	}
	close(fd);
}
