/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 18:27:00 by fmanetti          #+#    #+#             */
/*   Updated: 2021/04/07 16:34:51 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer(t_lexer *lexer)
{
	t_list		*lst;
	t_list		*tmp;
	t_token		*tok;

	lst = lexer->tokens;
	while (lst)
	{
		tok = lst->content;
		if (tok->data)
			free(tok->data);
		free(tok);
		tmp = lst;
		lst = lst->next;
		free(tmp);
	}
	if (lexer)
		free(lexer);
	lexer = NULL;
}

void	env_del(void *l)
{
	t_env	*tmp;

	tmp = (t_env*)l;
	free(tmp->name);
	if (tmp->value)
		free(tmp->value);
	free(tmp);
}

void	files_del(void *l)
{
	t_files		*tmp;

	tmp = (t_files*)l;
	free(tmp->name);
	free(tmp);
}

void	free_all(t_main *m)
{
	free(m->home);
	ft_lstclear(m->ehead, env_del);
	free(m->ehead);
	free(m->p);
	ft_free_array(m->hist);
	free(m->hist_path);
	ft_free_array(m->pathdirs);
	free(m->base_term);
	free(m);
}
