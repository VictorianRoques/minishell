/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:23:16 by viroques          #+#    #+#             */
/*   Updated: 2021/04/07 18:34:25 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*sort_backslash(char *str, t_main *m, int quote)
{
	int		i;
	char	*new;
	int		j;

	if (!(new = malloc(sizeof(char) * ft_strlen(str) + 1)))
		malloc_error(m, NULL, NO_READING);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (!quote && str[i] == '\\')
			i++;
		if (quote && str[i] == '\\' &&
			str[i + 1] && (str[i + 1] == '\\'
			|| str[i + 1] == '\'' || str[i + 1] == '\"'))
			i++;
		new[j] = str[i];
		j++;
		if (str[i])
			i++;
	}
	new[j] = '\0';
	return (new);
}

char			*add_quote(char *str, int *i, t_main *m)
{
	int		start;
	char	*sub;
	char	*var;
	char	*backslash;

	start = *i;
	while (str[*i])
	{
		if (str[*i] == '\\' && str[*i + 1] && str[*i + 1] == '\"')
			*i += 1;
		else if (str[*i] == '\"')
		{
			*i += 1;
			break ;
		}
		*i += 1;
	}
	sub = ft_substr(str, start, *i - start - 1);
	var = check_vars(m, sub, m->ehead, m->exit_status);
	backslash = sort_backslash(var, m, 1);
	free(var);
	free(sub);
	return (backslash);
}

char			*add_squote(char *str, int *i)
{
	int		start;

	start = *i;
	while (str[*i])
	{
		if (str[*i] == '\'')
		{
			*i += 1;
			break ;
		}
		*i += 1;
	}
	return (ft_substr(str, start, *i - start - 1));
}

char			*add_w(char *str, int *i, t_main *m)
{
	int		start;
	char	*sub;
	char	*var;
	char	*backslash;

	start = *i;
	while (str[*i])
	{
		if (str[*i] == '\\')
		{
			if (str[*i + 1] && (str[*i + 1] == '\''
				|| str[*i + 1 == '\"']))
				*i += 1;
		}
		else if (str[*i] == '\'' || str[*i] == '\"')
			break ;
		*i += 1;
	}
	sub = ft_substr(str, start, *i - start);
	var = check_vars(m, sub, m->ehead, m->exit_status);
	backslash = sort_backslash(var, m, 0);
	free(var);
	free(sub);
	return (backslash);
}

char			*change_data(char *str, t_main *m)
{
	int		i;
	char	*data;

	data = NULL;
	i = 0;
	while ((size_t)i < ft_strlen(str))
	{
		if (str[i] && str[i] == '\"')
		{
			i++;
			data = join_and_free(data, add_quote(str, &i, m));
		}
		else if (str[i] == '\'')
		{
			i++;
			data = join_and_free(data, add_squote(str, &i));
		}
		else
			data = join_and_free(data, add_w(str, &i, m));
	}
	return (data);
}
