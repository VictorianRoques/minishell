/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:12:43 by viroques          #+#    #+#             */
/*   Updated: 2021/04/02 12:46:16 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*search_path(char *cmd_name, char **pathdirs)
{
	DIR				*dir_stream;
	struct dirent	*dir;
	char			*path;
	int				i;

	i = 0;
	if (cmd_name[0] == '/' || cmd_name[0] == '.')
		return (cmd_name);
	while (pathdirs[i])
	{
		if (!(dir_stream = opendir(pathdirs[i])))
			return (NULL);
		while ((dir = readdir(dir_stream)) > 0)
			if (ft_strcmp(dir->d_name, cmd_name) == 0)
			{
				path = ft_strjoin(pathdirs[i], cmd_name);
				closedir(dir_stream);
				return (path);
			}
		i++;
		closedir(dir_stream);
	}
	return (NULL);
}
