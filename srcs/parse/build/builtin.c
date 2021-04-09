/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:30:47 by viroques          #+#    #+#             */
/*   Updated: 2021/04/07 20:42:03 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node		*build_builtin_1(t_list **token, t_main *m)
{
	t_node	*result;
	t_node	*args;
	char	*pathname;

	if (!check(WORD, &pathname, token))
		return (NULL);
	args = build_args(token, m);
	if (!(result = create_node(NODE_BUILTIN, pathname)))
		malloc_error(m, NULL, NO_READING);
	ast_attach_branch(result, args, NULL);
	return (result);
}

t_node				*build_builtin(t_list **token, t_main *m)
{
	t_list	*save;
	t_node	*builtin;

	save = *token;
	if (!(builtin = build_builtin_1(token, m)))
		*token = save;
	check_par(CLOSE_PAR, token);
	return (builtin);
}
