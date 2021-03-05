/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:51 by viroques          #+#    #+#             */
/*   Updated: 2021/03/04 19:30:35 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void        execute_builtin(t_node *builtin, t_executor *exec, t_flux *flux)
{
    execute_bin(builtin, exec, flux);
}

static void        execute_command(t_node *command, t_executor *exec, t_flux *flux)
{
    if (!command)
        return;
    if (command->type == NODE_REDIRECT_IN || command->type == NODE_REDIRECT_OUT
        || command->type == NODE_REDIRECT_OVER)
    {
        handle_redirection(command);
        execute_builtin(command->left, exec, flux);
    }
    else
        execute_builtin(command, exec, flux);
}

static void        execute_pipe(t_node *node_pipe, t_executor *exec, t_flux *flux)
{
    int     fd[2];
    t_node  *job;
    
    pipe(fd);
    set_pipe_bool(0, 1, fd, flux);
    execute_command(node_pipe->left, exec, flux);
    job = node_pipe->right;
    while (job && job->type == NODE_PIPE)
    {
        set_pipe_bool(1, 1, fd, flux);
        close(flux->pipe_write);
        pipe(fd);
        flux->pipe_write = fd[1];
        execute_command(job->left, exec, flux);
        close(flux->pipe_read);
        flux->pipe_read= fd[0];
        job = job->right;
    }
    set_pipe_bool(1, 0, fd, flux);
    execute_command(job, exec, flux);
    close(flux->pipe_read);
}

static void        execute_job(t_node *job, t_executor *exec, t_flux *flux)
{
    if (!job)
        return;
    if (job->type == NODE_PIPE)
    {
        execute_pipe(job, exec, flux);
    }
    else
        execute_command(job, exec, flux);
}

static void        execute_command_line(t_node *cmd_line, t_executor *exec, t_flux *flux)
{
    int tmp_in;
    int tmp_out;
    
    if (!cmd_line)
        return ;
    tmp_in = dup(0);
    tmp_out = dup(1);
    if (cmd_line->type == NODE_LINE)
    {
        execute_job(cmd_line->left, exec, flux);
        dup2(tmp_in, 0);
        dup2(tmp_out, 1);
        execute_command_line(cmd_line->right, exec, flux);
    }
    else
    {   
        execute_job(cmd_line, exec, flux);
        dup2(tmp_in, 0);
        dup2(tmp_out, 1);
    }
}

void     execute_ast_tree(t_node *exec_tree, char **env)
{
    t_executor  exec;
    t_flux      flux;
    
    ft_bzero(&exec, sizeof(t_executor));
    ft_bzero(&flux, sizeof(t_flux));
    exec.env = env;
    exec.directories = get_directories_path(env);
    execute_command_line(exec_tree, &exec, &flux);
    free_tab(exec.directories);
}