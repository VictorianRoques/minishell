/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_term.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:44:02 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 14:17:54 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal(int signalnum)
{
	if (signalnum == SIGINT)
		ft_putstr_fd("\b\b  \b\b", STDERR_FILENO);
	if (signalnum == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDERR_FILENO);
}

void	set_term_noncano(void)
{
	struct termios new;

	tcgetattr(STDIN_FILENO, &new);
	new.c_lflag &= ~(ICANON | ISIG | ECHO);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &new);
}

void	set_term_cano(struct termios *base_term)
{
	tcsetattr(STDIN_FILENO, TCSADRAIN, base_term);
}
