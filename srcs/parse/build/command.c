/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:26:57 by viroques          #+#    #+#             */
/*   Updated: 2021/04/07 19:40:50 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node		*build_command_heredoc(t_list **token, t_main *m)
{
	t_node	*result;
	t_node	*builtin;
	char	*filename;

	builtin = build_builtin(token, m);
	if (!check(DLESSER, NULL, token))
	{
		ast_delete_node(builtin);
		return (NULL);
	}
	if (!check(WORD, &filename, token))
	{
		ast_delete_node(builtin);
		return (NULL);
	}
	if (!(result = create_node(NODE_REDIRECT_HEREDOC, filename)))
		malloc_error(m, NULL, NO_READING);
	ast_attach_branch(result, builtin, build_command(token, m));
	return (result);
}

static t_node		*build_command_over(t_list **token, t_main *m)
{
	t_node	*result;
	t_node	*builtin;
	char	*filename;

	builtin = build_builtin(token, m);
	if (!check(DGREATER, NULL, token))
	{
		ast_delete_node(builtin);
		return (NULL);
	}
	if (!check(WORD, &filename, token))
	{
		ast_delete_node(builtin);
		return (NULL);
	}
	if (!(result = create_node(NODE_REDIRECT_OVER, filename)))
		malloc_error(m, NULL, NO_READING);
	ast_attach_branch(result, builtin, build_command(token, m));
	return (result);
}

static t_node		*build_command_in(t_list **token, t_main *m)
{
	t_node	*result;
	t_node	*builtin;
	char	*filename;

	builtin = build_builtin(token, m);
	if (!check(LESSER, NULL, token))
	{
		ast_delete_node(builtin);
		return (NULL);
	}
	if (!check(WORD, &filename, token))
	{
		ast_delete_node(builtin);
		return (NULL);
	}
	if (!(result = create_node(NODE_REDIRECT_IN, filename)))
		malloc_error(m, NULL, NO_READING);
	ast_attach_branch(result, builtin, build_command(token, m));
	return (result);
}

static t_node		*build_command_out(t_list **token, t_main *m)
{
	t_node	*result;
	t_node	*builtin;
	char	*pathname;

	builtin = build_builtin(token, m);
	if (!check(GREATER, NULL, token))
	{
		ast_delete_node(builtin);
		return (NULL);
	}
	if (!check(WORD, &pathname, token))
	{
		ast_delete_node(builtin);
		return (NULL);
	}
	if (!(result = create_node(NODE_REDIRECT_OUT, pathname)))
		malloc_error(m, NULL, NO_READING);
	ast_attach_branch(result, builtin, build_command(token, m));
	return (result);
}

t_node				*build_command(t_list **token, t_main *m)
{
	t_node *node;
	t_list *save;

	save = *token;
	if ((*token = save)
		&& (node = build_command_in(token, m)))
		return (node);
	if ((*token = save)
		&& (node = build_command_out(token, m)))
		return (node);
	if ((*token = save)
		&& (node = build_command_over(token, m)))
		return (node);
	if ((*token = save)
		&& (node = build_command_heredoc(token, m)))
		return (node);
	if ((*token = save)
		&& (node = build_command_builtin(token, m)))
		return (node);
	return (NULL);
}
