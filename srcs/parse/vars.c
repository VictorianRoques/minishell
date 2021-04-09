/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 17:02:50 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/08 11:16:09 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*vars_replacer(char *s, t_list **head, int exit_status)
{
	char	*tmp;

	if (ft_strcmp(s, "$?") == 0)
		tmp = ft_itoa(exit_status);
	else if (ft_strcmp(s, "$") == 0)
		tmp = ft_strdup("$");
	else if (!(tmp = ft_strdup(get_env(head, s + 1))))
		tmp = ft_strdup("");
	free(s);
	return (tmp);
}

static char		*home_replacer(char *s, char *as, char *home, t_list **head)
{
	int		len;
	char	*tmp;
	char	*username;

	username = get_env(head, "USER");
	len = ft_strlen(username);
	if (s[ft_strlen(as)] == '$')
		return (as);
	free(as);
	if (ft_strcmp(s, "~") == 0 || ft_strcmp(s + 1, username) == 0)
		tmp = ft_strdup(home);
	else
	{
		tmp = ft_strjoin(home, "/");
		if ((ft_strncmp(s + 1, username, len) == 0 && s[len + 1] == '/'))
			tmp = ft_strjoin_nl(tmp, s + (len + 2));
		else if (ft_strncmp(s, "~/", 2) == 0)
			tmp = ft_strjoin_nl(tmp, s + 2);
		else
		{
			free(tmp);
			tmp = ft_strdup(s);
		}
	}
	return (tmp);
}

char			*check_vars(t_main *m, char *s, t_list **head, int exit_status)
{
	int		x;
	char	*tmp;
	char	**a;

	x = -1;
	a = split_var(s);
	if (a[0])
		while (a[++x])
			if (a[x][0] == '$' || a[x][0] == '~')
			{
				if (a[x][0] == '~')
				{
					a[x] = home_replacer(s, a[x], m->home, head);
				}
				else
					a[x] = vars_replacer(a[x], head, exit_status);
			}
	if (!(tmp = ft_merge(a)))
		malloc_error(m, s, NO_READING);
	return (tmp);
}
