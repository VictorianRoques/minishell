/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multilines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 12:21:37 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 13:37:01 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		multi_error(t_main *m, t_token_type type)
{
	if (type == SQUOTE || type == DQUOTE || type == CLOSE_PAR)
	{
		ft_putstr_fd("minish: unexpected EOF while looking for matching",
			STDERR_FILENO);
		if (type == SQUOTE)
			ft_putstr_fd(" `\''\n", STDERR_FILENO);
		if (type == DQUOTE)
			ft_putstr_fd(" `\"'\n", STDERR_FILENO);
		if (type == CLOSE_PAR)
			ft_putstr_fd(" `)'\n", STDERR_FILENO);
	}
	ft_putstr_fd("minish: ", STDERR_FILENO);
	ft_putstr_fd(SYNTAX_ERROR, STDERR_FILENO);
	ft_putstr_fd(": unexpected end of file\n", STDERR_FILENO);
	m->exit_status = 258;
}

static char		*ending(t_main *m, char *shist, int ret, t_token_type type)
{
	set_term_cano(m->base_term);
	m->p->multi = 0;
	if (ret < 0)
	{
		if (!(m->hist = history(shist, m->hist, m->p->hnum)))
			malloc_error(m, NULL, NO_READING);
		if (ret == -2)
			multi_error(m, type);
		free(shist);
		return (NULL);
	}
	return (shist);
}

static char		*join_multichar(char *shist, t_token_type type)
{
	if (type == SQUOTE || type == DQUOTE || type == CLOSE_PAR)
		shist = ft_strjoin_nl(shist, "\n");
	else if (type == BACKSLASH)
		shist[ft_strlen(shist) - 1] = '\0';
	else
		shist = ft_strjoin_nl(shist, " ");
	return (shist);
}

char			*multilines(t_main *m, char *s, t_token_type type)
{
	int		ret;
	char	*shist;

	ret = -2;
	set_term_noncano();
	m->p->multi = 1;
	shist = ft_strdup(s);
	ft_putstr(MULTI_PROMPT);
	s[0] = '\0';
	while ((ret = reading(m, &s)) > 0)
		;
	if (ret < 0)
	{
		free(s);
		return (ending(m, shist, ret, type));
	}
	shist = join_multichar(shist, type);
	shist = ft_strjoin_nl(shist, s);
	free(s);
	m->p->lpos = 0;
	m->p->hnum = 0;
	return (ending(m, shist, NO_BREAK, type));
}
