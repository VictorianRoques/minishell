/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:31:04 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 13:52:06 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_pwd(t_main *m)
{
	char	*pwd;
	char	*old_pwd;
	char	buf[1024];

	old_pwd = get_env(m->ehead, "PWD");
	if (!(pwd = getcwd(buf, 1024)))
	{
		if (ft_strncmp(old_pwd + (ft_strlen(old_pwd) - 3), "/..", 3) == 0)
			pwd = old_pwd;
		else
			return (error(ERRNO, NULL));
	}
	else
		set_env(m->ehead, "PWD", pwd);
	ft_putstr(pwd);
	ft_putchar('\n');
	m->exit_status = 0;
	return (1);
}
