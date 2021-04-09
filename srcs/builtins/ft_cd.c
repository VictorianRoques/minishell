/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/28 17:30:11 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 13:49:04 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*home_empty_or_back(t_main *m, char *s, char *path)
{
	if (!(s))
	{
		path = get_env(m->ehead, "HOME");
		if (!(path))
			status_error(m, NO_ERRNO, 1, "HOME is not set");
		else if (ft_strcmp(path, "") == 0)
			return (NULL);
	}
	else if (ft_strcmp(path, "") == 0)
		return (NULL);
	else if (ft_strcmp(path, "-") == 0)
	{
		path = get_env(m->ehead, "OLDPWD");
		if (!(path))
			status_error(m, NO_ERRNO, 1, "OLDPWD not set");
	}
	return (path);
}

int				corrector_is_bastard(t_main *m, char *s)
{
	if (ft_strcmp(s, "..") == 0)
	{
		set_env(m->ehead, "OLDPWD", get_env(m->ehead, "PWD"));
		set_env(m->ehead, "PWD", ft_strjoin(get_env(m->ehead, "PWD"), "/.."));
	}
	ft_putstr_fd("minish: ", STDERR_FILENO);
	ft_putstr_fd(ERROR, STDERR_FILENO);
	ft_putchar_fd(':', STDERR_FILENO);
	ft_putstr_fd("error retrieving current directory: ", STDERR_FILENO);
	ft_putstr_fd("getcwd: cannot access parent directories:", STDERR_FILENO);
	ft_putchar_fd(' ', STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	m->exit_status = 0;
	return (1);
}

int				ft_cd(t_main *m, char *s)
{
	char	*path;
	char	buf[1024];

	if (s)
		path = s;
	if (!(s) || ft_strcmp(path, "") == 0 || ft_strcmp(path, "-") == 0)
		if (!(path = home_empty_or_back(m, s, path)))
			return (1);
	if (chdir(path))
		return (status_error(m, ERRNO, 1, ""));
	if (!(path = getcwd(buf, 1024)))
		return (corrector_is_bastard(m, s));
	if (ft_strcmp(get_env(m->ehead, "PWD"), path) != 0)
		set_env(m->ehead, "OLDPWD", get_env(m->ehead, "PWD"));
	set_env(m->ehead, "PWD", path);
	m->exit_status = 0;
	return (1);
}
