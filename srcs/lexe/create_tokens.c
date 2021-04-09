/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 17:15:30 by viroques          #+#    #+#             */
/*   Updated: 2021/04/07 18:47:12 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int					create_tok(char *data, t_token_type type, t_lexer *lexer)
{
	t_list		*lst;
	t_token		*token;

	if (!(token = malloc(sizeof(t_token))))
		return (-1);
	token->type = type;
	if (!(token->data = ft_strdup(data)))
		return (-1);
	if (!(lst = ft_lstnew(token)))
		return (-1);
	if (!(lexer->tokens))
		lexer->tokens = lst;
	else
		ft_lstadd_back(&(lexer->tokens), lst);
	lexer->nb_tokens++;
	return (1);
}

int					create_tok_lst(char *data, t_token_type type, t_list **head)
{
	t_list		*lst;
	t_token		*token;

	if (!(token = malloc(sizeof(t_token))))
		return (-1);
	token->type = type;
	if (!(token->data = ft_strdup(data)))
		return (-1);
	if (!(lst = ft_lstnew(token)))
		return (-1);
	if (!*head)
		*head = lst;
	else
		ft_lstadd_back(head, lst);
	return (1);
}

t_list				*generate_tok(char *data, t_token_type type, t_main *m)
{
	t_list		*lst;
	t_token		*token;

	if (!(token = malloc(sizeof(t_token))))
		malloc_error(m, NULL, NO_READING);
	token->type = type;
	if (data)
	{
		if (!(token->data = data))
			malloc_error(m, NULL, NO_READING);
	}
	else
		data = NULL;
	if (!(lst = ft_lstnew(token)))
		malloc_error(m, NULL, NO_READING);
	return (lst);
}
