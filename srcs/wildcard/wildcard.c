/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:36:44 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/08 00:10:15 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		is_dir(char *path, char *fname)
{
	char	*npath;
	DIR		*dir;

	npath = ft_strjoin_nl(path, fname);
	npath = ft_strjoin_nl(npath, "/");
	if ((dir = opendir(npath)))
	{
		closedir(dir);
		free(npath);
		return (1);
	}
	free(npath);
	return (0);
}

static void		add_to_final(t_list **hmatch, char *path, t_list **final)
{
	t_list	*l;
	char	*fname;

	l = *hmatch;
	while (l)
	{
		fname = t_access_files(l)->name;
		add_elem_to_list(final, ft_strjoin(path, fname));
		l = l->next;
	}
}

static char		*cut_str(char *s, int type)
{
	int		i;
	char	*tmp;

	i = 0;
	while (s[i] && s[i] != '/')
		i++;
	if (type == 0)
		return (ft_substr(s, 0, i));
	if (type == 1)
	{
		i++;
		tmp = ft_substr(s, i, ft_strlen(s) - i);
		free(s);
		return (tmp);
	}
	return (s);
}

static void		r_create_list(char *s, char *path, t_list **head,
	t_list **final)
{
	char	*fname;
	char	*npath;
	t_list	*hmatch;
	t_list	*l;

	hmatch = star_to_str(cut_str(s, 0), path, head);
	if (!ft_strchr(s, '/') && hmatch)
		add_to_final(&hmatch, path, final);
	l = hmatch;
	s = cut_str(s, 1);
	while (l && s[0] != 0)
	{
		fname = t_access_files(l)->name;
		if (is_dir(ft_strdup(path), fname))
		{
			npath = ft_strjoin(path, fname);
			npath = ft_strjoin_nl(npath, "/");
			r_create_list(ft_strdup(s), npath, head, final);
			free(npath);
		}
		l = l->next;
	}
	ft_lstclear(&hmatch, files_del);
	free(s);
}

t_list			*wildcard(char *s)
{
	char		*path;
	t_list		*head;
	t_list		*final;
	t_uint		start;

	if (ft_strncmp(s, "./", 2) == 0)
		path = ft_strdup("./");
	else if (ft_strncmp(s, "/", 1) == 0)
		path = ft_strdup("/");
	else
		path = ft_strdup("");
	final = NULL;
	start = ft_strlen(path);
	r_create_list(s + start, path, &head, &final);
	if (ft_lstsize(final) == 0)
	{
		free(path);
		return (NULL);
	}
	final = list_sort_files(&final);
	free(path);
	return (lst_to_token_lst(final));
}
