/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:12:43 by viroques          #+#    #+#             */
/*   Updated: 2021/03/03 17:13:17 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
    char    *path_filename;
    DIR     *dir_stream;
    struct dirent   *dir; 
    pid_t           pid;
    char *path;
    char *tmp;
    int i;
    i = 0; 

    while (directories[i])
    {
        dir_stream = opendir(directories[i]);
        while ((dir = readdir(dir_stream)))
        {
            if (ft_strncmp(dir->d_name, cmd_name, ft_strlen(dir->d_name)) == 0)
            {
                tmp = ft_strjoin("/", cmd_name);
                path = ft_strjoin(directories[i], tmp);
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