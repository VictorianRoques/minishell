/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 18:46:05 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 17:16:59 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		error(int errtype, char *message)
{
	if (errtype == ERRNO)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
		ft_putstr_fd(ERROR, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else if (errtype == NO_ERRNO)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
		ft_putstr_fd(ERROR, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	return (1);
}

int		status_error(t_main *m, int errtype, int status, char *message)
{
	if (errtype == ERRNO)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
		ft_putstr_fd(ERROR, STDERR_FILENO);
		ft_putchar_fd(':', STDERR_FILENO);
		ft_putstr_fd(message, STDERR_FILENO);
		ft_putchar_fd(' ', STDERR_FILENO);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	if (errtype == NO_ERRNO)
		error(NO_ERRNO, message);
	m->exit_status = status;
	return (1);
}

void	malloc_error(t_main *m, char *s, int errtype)
{
	if (errtype == READING)
		free(s);
	error(ERRNO, NULL);
	free_all(m);
	exit(1);
}

void	malloc_error_lexer(t_main *m, t_lexer *lexer)
{
	ft_putstr_fd("minish: ", STDERR_FILENO);
	ft_putstr_fd(ERROR, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	free_all(m);
	free_lexer(lexer);
	exit(1);
}
