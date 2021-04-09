/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:21:37 by viroques          #+#    #+#             */
/*   Updated: 2021/04/08 01:45:27 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			init_std(t_std *std)
{
	std->tmp_in = dup(STDIN_FILENO);
	std->tmp_out = dup(STDOUT_FILENO);
	pipe(std->fd);
	std->fd_in = std->fd[0];
	std->fd_out = std->fd[1];
}

void			execute_inter_pipe(t_std *std, char **s, t_main *m, t_node *job)
{
	close(std->fd_out);
	std->fd_in = std->fd[0];
	pipe(std->fd);
	std->fd_out = std->fd[1];
	dup2(std->fd_in, STDIN_FILENO);
	dup2(std->fd_out, STDOUT_FILENO);
	execute_command(m, s, job->left);
	close(std->fd_in);
	std->fd_in = std->fd[0];
}
