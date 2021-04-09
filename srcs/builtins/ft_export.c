/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 14:58:16 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 13:51:37 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_varname(char *varname, char *s, t_list **ehead, int i)
{
	t_list	*l;
	t_env	*tmp;

	l = *ehead;
	while (l)
	{
		tmp = t_access_env(l);
		if (ft_strcmp(varname, tmp->name) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			if (s[i] && !s[i + 1])
				tmp->value = ft_strdup("");
			else if (s[i + 1])
				tmp->value = ft_substr(s, i + 1, ft_strlen(s) - i);
			else
				tmp->value = NULL;
			return (1);
		}
		l = l->next;
	}
	return (0);
}

static int		not_a_valid_identifier(t_main *m, char *varname)
{
	ft_putstr_fd("minish: ", STDERR_FILENO);
	ft_putstr_fd(ERROR, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(varname, STDERR_FILENO);
	ft_putstr_fd("': ", STDERR_FILENO);
	ft_putstr_fd("not a valid identifier\n", STDERR_FILENO);
	m->exit_status = 1;
	return (0);
}

static int		check_errors(t_main *m, char *varname)
{
	int		x;

	x = -1;
	if (!varname || !varname[0])
		return (not_a_valid_identifier(m, varname));
	while (varname[++x])
		if (!(ft_isalpha(varname[x]) || varname[x] == '_'))
			return (not_a_valid_identifier(m, varname));
	return (1);
}

static int		export_var(t_main *m, char **a, t_list **ehead)
{
	int		x;
	int		i;
	char	*varname;

	x = 0;
	while (a[++x])
	{
		i = 0;
		while (a[x][i] && a[x][i] != '=')
			i++;
		varname = ft_substr(a[x], 0, i);
		if (check_errors(m, varname))
			if (!(check_varname(varname, a[x], ehead, i)))
				ft_lstadd_back(ehead, create_env_elem(a[x]));
		if (ft_strcmp(varname, "PATH") == 0)
		{
			ft_free_array(m->pathdirs);
			m->pathdirs = path_parser(ehead);
		}
		free(varname);
	}
	return (1);
}

int				ft_export(t_main *m, char **a, t_list **ehead)
{
	t_list	*l;
	t_env	*tmp;
	t_list	*lhead;

	if (!(lhead = list_sort_env(ehead)))
		malloc_error(m, NULL, NO_READING);
	l = lhead;
	if (!(a[1]))
		while (l)
		{
			tmp = t_access_env(l);
			if (tmp->value)
				printf("declare -x %s=\"%s\"\n", tmp->name, tmp->value);
			else
				printf("declare -x %s\n", tmp->name);
			l = l->next;
		}
	else
	{
		if (!(export_var(m, a, ehead)))
			malloc_error(m, NULL, NO_READING);
	}
	m->exit_status = (m->exit_status == -1) ? 1 : 0;
	ft_lstclear(&lhead, free);
	return (1);
}
