/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:15:19 by viroques          #+#    #+#             */
/*   Updated: 2021/03/04 12:04:32 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    handle_piping(t_flux *flux)
{
    if (flux->stdin_pipe && flux->stdout_pipe)
        {
            dup2(flux->pipe_read, 0);
            dup2(flux->pipe_write, 1);
        }
        else if (flux->stdout_pipe)
        {
            close(flux->pipe_read);
            dup2(flux->pipe_write, 1);
        }
        else if (flux->stdin_pipe)
        {
            close(flux->pipe_write);
            dup2(flux->pipe_read, 0);
        }
}

void        set_pipe_bool(int stdin_pipe, int stdout_pipe, int *fd , t_flux *flux)
{
    flux->stdin_pipe = stdin_pipe;
    flux->stdout_pipe = stdout_pipe;
    flux->pipe_read = fd[0];
    flux->pipe_write = fd[1];
}