/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:18:41 by viroques          #+#    #+#             */
/*   Updated: 2021/03/03 19:32:50 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char        **create_cmd_table(t_node *root)
{
    t_node *node;
    char **args;
    int nbcmd;

    nbcmd = 0;
    node = root;
    while(node)
    {
        nbcmd++;
        node = node->left;
    }
    args = malloc(sizeof(char *) * nbcmd + 1);
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

int     execute_bin(t_node *cmd, t_executor *exec)
{
    pid_t pid;
    char **args;
    char *path;
    
    path = search_path(cmd->data, exec->dirs_path);
    if ((pid = fork()) < 0)
        return (-1);
    if (pid == 0)
    {
        handle_piping(exec);
        args = create_cmd_table(cmd);
        if ((execve(path, args, exec->env)) == -1)
            write(2, strerror(errno), ft_strlen(strerror(errno)));
        free_tab(args);
    }
    return (1);
}