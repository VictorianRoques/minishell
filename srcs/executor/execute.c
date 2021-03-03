/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:51 by viroques          #+#    #+#             */
/*   Updated: 2021/03/03 17:11:39 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void        execute_builtin(t_node *builtin, t_executor *exec)
{
    execute_bin(builtin, exec);
}

static void        execute_command(t_node *command, t_executor *exec)
{
    if (!command)
        return;
    if (command->type == NODE_REDIRECT_IN || command->type == NODE_REDIRECT_OUT
        || command->type == NODE_REDIRECT_DIN)
    {
        handle_redirection(command);
        execute_builtin(command->left, exec);
    }
    else
        execute_builtin(command, exec);
}

static void        execute_pipe(t_node *node_pipe, t_executor *exec)
{
    int fd[2];
    t_node *job;
    
    pipe(fd);
    set_pipe_bool(0, 1, fd, exec);
    execute_command(node_pipe->left, exec);
    job = node_pipe->right;
    while (job && job->type == NODE_PIPE)
    {
        set_pipe_bool(1, 1, fd, exec);
        close(exec->pipe_write);
        pipe(fd);
        exec->pipe_write = fd[1];
        execute_command(job->left, exec);
        close(exec->pipe_read);
        exec->pipe_read= fd[0];
        job = job->right;
    }
    set_pipe_bool(1, 0, fd, exec);
    execute_command(job, exec);
    close(exec->pipe_read);
}

static void        execute_job(t_node *job, t_executor *exec)
{
    if (!job)
        return;
    if (job->type == NODE_PIPE)
    {
        execute_pipe(job, exec);
    }
    else
        execute_command(job, exec);
}

static void        execute_command_line(t_node *cmd_line, t_executor *exec)
{
    if (!cmd_line)
        return ;
    if (cmd_line->type == NODE_LINE)
    {
        execute_job(cmd_line->left, exec);
        execute_command_line(cmd_line->right, exec);
    }
    else
        execute_job(cmd_line, exec);
}

void     execute_ast_tree(t_node *exec_tree, char **env)
{
    t_executor exec;
    ft_bzero(&exec, sizeof(t_executor));
    exec.env = env;
    exec.dirs_path = get_directories_path(env);
    execute_command_line(exec_tree, &exec);
    free_tab(exec.dirs_path);
}