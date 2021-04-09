/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star_to_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:30:49 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 13:15:11 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		files_parser(char *path, t_list **head)
{
	DIR				*dir_stream;
	struct dirent	*dir;
	char			*tmp_path;

	if (ft_strcmp(path, "") == 0)
		tmp_path = ft_strjoin(path, "./");
	else
		tmp_path = ft_strdup(path);
	if (!(dir_stream = opendir(tmp_path)))
	{
		free(tmp_path);
		return ;
	}
	while ((dir = readdir(dir_stream)) > 0)
		add_elem_to_list(head, ft_strdup(dir->d_name));
	closedir(dir_stream);
	free(dir);
	free(tmp_path);
}

static t_list	*find_matches(char *s, t_list **head)
{
	t_list	*l;
	t_list	*hmatch;
	char	*fname;

	l = *head;
	hmatch = NULL;
	while (l)
	{
		fname = t_access_files(l)->name;
		if (starcmp(s, fname) && fname[0] != '.')
			add_elem_to_list(&hmatch, ft_strdup(fname));
		l = l->next;
	}
	ft_lstclear(head, files_del);
	free(s);
	return (hmatch);
}

t_list			*star_to_str(char *s, char *path, t_list **head)
{
	*head = NULL;
	if (ft_strcmp(s, "") == 0)
	{
		free(s);
		return (*head);
	}
	files_parser(path, head);
	return (find_matches(s, head));
}
