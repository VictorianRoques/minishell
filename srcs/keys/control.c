/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 14:07:42 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 22:32:49 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		control_c(t_main *m, char *s)
{
	ft_putchar('\n');
	m->exit_status = 1;
	s[0] = '\0';
	return (1);
}

void	control_d(t_main *m, char **s)
{
	int	status;

	status = m->exit_status;
	set_term_cano(m->base_term);
	make_history(m->hist_path, m->hist);
	ft_free_array(m->p->arr);
	free(*s);
	free_all(m);
	ft_putstr("exit\n");
	exit(status);
}
