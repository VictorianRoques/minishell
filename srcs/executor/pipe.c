/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:15:19 by viroques          #+#    #+#             */
/*   Updated: 2021/03/03 16:20:14 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    handle_piping(t_executor *exec)
{
    if (exec->stdin_pipe && exec->stdout_pipe)
        {
            dup2(exec->pipe_read, 0);
            dup2(exec->pipe_write, 1);
        }
        else if (exec->stdout_pipe)
        {
            close(exec->pipe_read);
            dup2(exec->pipe_write, 1);
        }
        else if (exec->stdin_pipe)
        {
            close(exec->pipe_write);
            dup2(exec->pipe_read, 0);
        }
}

void        set_pipe_bool(int stdin_pipe, int stdout_pipe, int *fd,t_executor *exec)
{
    exec->stdin_pipe = stdin_pipe;
    exec->stdout_pipe = stdout_pipe;
    exec->pipe_read = fd[0];
    exec->pipe_write = fd[1];
}