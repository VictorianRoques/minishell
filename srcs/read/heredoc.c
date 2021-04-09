/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 23:35:25 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 14:43:05 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ending(t_main *m, int fd, char *s, t_uint type)
{
	set_term_cano(m->base_term);
	m->p->multi = 0;
	close(fd);
	free(s);
	if (type == BREAK)
	{
		remove(".heredoc");
		return (0);
	}
	return (1);
}

static int		check_read_ret(int ret, char *keywrd, char *s, int fd)
{
	if (ret == 0 && ft_strcmp(keywrd, s) != 0)
	{
		ft_putstr_fd(s, fd);
		ft_putchar_fd('\n', fd);
	}
	if (ret < 0)
		return (0);
	return (1);
}

int				heredoc(t_main *m, char *keywrd)
{
	int		fd;
	char	*s;
	int		ret;

	set_term_noncano();
	if ((fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0640)) < 0)
	{
		set_term_cano(m->base_term);
		return (0);
	}
	s = ft_strdup("");
	m->p->multi = 1;
	while (ft_strcmp(keywrd, s) != 0)
	{
		ft_putstr(MULTI_PROMPT);
		(s)[0] = '\0';
		while ((ret = reading(m, &s)) > 0)
			;
		if (!(check_read_ret(ret, keywrd, s, fd)))
			return (ending(m, fd, s, BREAK));
		m->p->lpos = 0;
		m->p->hnum = 0;
	}
	m->exit_status = 0;
	return (ending(m, fd, s, NO_BREAK));
}
