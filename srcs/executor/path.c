/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:12:43 by viroques          #+#    #+#             */
/*   Updated: 2021/03/04 12:05:06 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char        **get_directories_path(char **env)
{
    int i;
    char **directories;

    i = 0;
    while (env[i])
    {
        if ((ft_strnstr(env[i], "PATH", 4)))
        {
            directories = ft_split(env[i] + 5, ':');
            return (directories);
        }
        i++;
    }
    return (NULL);
}

char    *search_path(char *cmd_name, char **directories)
{
    DIR             *dir_stream;
    struct dirent   *dir; 
    char            *path;
    int             i;
    
    i = 0;
    while (directories[i])
    {
        if (!(dir_stream = opendir(directories[i])))
            return (cmd_name);
        while ((dir = readdir(dir_stream)) > 0)
        {
            if (ft_strncmp(dir->d_name, cmd_name, ft_strlen(dir->d_name)) == 0)
            {
                char *tmp = ft_strjoin(directories[i], "/");
                path = ft_strjoin(tmp, cmd_name);
                free(tmp);
                closedir(dir_stream);
                return (path);
            }
        }
        i++;
        closedir(dir_stream);
    }
    return (cmd_name);
}