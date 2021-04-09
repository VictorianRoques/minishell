/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 00:22:26 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 16:08:40 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		exit_signals(int signal)
{
	if (signal == SIGINT)
		return (130);
	else if (signal == SIGQUIT)
		return (131);
	else if (signal == SIGTSTP)
		return (146);
	return (0);
}

int				exit_status(pid_t pid)
{
	int		ret;
	int		status;

	ret = waitpid(pid, &status, 0);
	if (ret < 0)
		printf("Failed to wait for process %d (errno = %d)\n", (int)pid, errno);
	else if (ret != pid)
		printf("Got ret of process %d (status 0x%.4X) when expecting PID %d\n"
				, ret, status, (int)pid);
	else if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (exit_signals(WTERMSIG(status)));
	else
		return (-1);
	return (1);
}
