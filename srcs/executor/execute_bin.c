/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:18:41 by viroques          #+#    #+#             */
/*   Updated: 2021/03/04 20:26:01 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char        **create_cmd_table(t_node *root)
{
    t_node  *node;
    char    **args;
    int     nbcmd;

    nbcmd = 0;
    node = root;
    while(node)
    {
        nbcmd++;
        node = node->left;
    }
    args = malloc(sizeof(char *) * (nbcmd + 1));
    node = root;
    nbcmd = 0;
    while (node)
    {
        args[nbcmd] = ft_strdup(node->data);
        node = node->left;
        nbcmd++;
    }
    args[nbcmd] = NULL;
    return (args);
}

int     execute_bin(t_node *cmd, t_executor *exec, t_flux *flux)
{
    char **args;
    char *path;
    pid_t pid;
    
    if ((pid = fork()) < 0)
        return (-1);
    if (pid == 0)
    {   
        if (cmd->data[0] == '/')
            path = cmd->data;
        else
        path = search_path(cmd->data, exec->directories);
        args = create_cmd_table(cmd);
        handle_piping(flux);
        if ((execve(path, args, exec->env)) == -1)
        {
            write(2, strerror(errno), ft_strlen(strerror(errno)));
            write(2, "\n", 1);
        }
        free_tab(args);
    }
    return (1);
}