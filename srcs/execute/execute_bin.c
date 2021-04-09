/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:18:41 by viroques          #+#    #+#             */
/*   Updated: 2021/04/06 23:10:09 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_dir_and_absolute(t_main *m, char *path)
{
	DIR		*dir;
	int		fd;

	if ((dir = opendir(path)))
	{
		error(NO_ERRNO, "is a directory");
		m->exit_status = 126;
		closedir(dir);
		return (1);
	}
	if (path[0] == '/' || path[0] == '.')
	{
		if ((fd = open(path, O_RDONLY)) == -1)
		{
			error(ERRNO, NULL);
			m->exit_status = 127;
			return (1);
		}
		close(fd);
	}
	return (0);
}

int				execute_bin(t_main *m)
{
	char	*path;
	pid_t	pid;

	if (check_dir_and_absolute(m, m->arr[0]))
		return (-1);
	if (!(path = search_path(m->arr[0], m->pathdirs)))
		return (0);
	if (path)
	{
		if ((pid = fork()) < 0)
			return (0);
		if (pid == 0)
		{
			if ((execve(path, m->arr, m->env)) == -1)
				return (0);
			return (1);
		}
		else
			m->exit_status = exit_status(pid);
		if (path != m->arr[0])
			free(path);
		return (1);
	}
	return (0);
}
