/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:31:54 by viroques          #+#    #+#             */
/*   Updated: 2021/04/06 13:01:58 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node		*build_arg_word(t_list **token, t_main *m)
{
	t_node	*args_list;
	t_node	*result;
	char	*arg;

	if (!check(WORD, &arg, token))
		return (NULL);
	args_list = build_args(token, m);
	if (!(result = create_node(NODE_ARG, arg)))
		malloc_error(m, NULL, NO_READING);
	ast_attach_branch(result, args_list, NULL);
	return (result);
}

static t_node		*build_arg_null(void)
{
	return (NULL);
}

t_node				*build_args(t_list **token, t_main *m)
{
	t_node	*node;
	t_list	*save;

	save = *token;
	if ((*token = save)
		&& (node = build_arg_word(token, m)))
		return (node);
	if ((*token = save)
		&& (node = build_arg_null()))
		return (node);
	return (NULL);
}
