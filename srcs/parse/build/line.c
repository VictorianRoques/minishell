/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:21:26 by viroques          #+#    #+#             */
/*   Updated: 2021/04/06 15:39:09 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*build_line_logic_pipe(t_list **token, t_main *m)
{
	t_node *result;
	t_node *job;
	t_node *line;

	if ((job = build_job(token, m)) == NULL)
		return (NULL);
	if (!check(DPIPE, NULL, token))
	{
		ast_delete_node(job);
		return (NULL);
	}
	if ((line = build_line(token, m)) == NULL)
	{
		ast_delete_node(job);
		return (NULL);
	}
	if (!(result = create_node(NODE_LOGIC_PIPE, NULL)))
		malloc_error(m, NULL, NO_READING);
	ast_attach_branch(result, job, line);
	return (result);
}

static t_node	*build_line_logic_amper(t_list **token, t_main *m)
{
	t_node *result;
	t_node *job;
	t_node *line;

	if ((job = build_job(token, m)) == NULL)
		return (NULL);
	if (!check(DAMPERSTAND, NULL, token))
	{
		ast_delete_node(job);
		return (NULL);
	}
	if ((line = build_line(token, m)) == NULL)
	{
		ast_delete_node(job);
		return (NULL);
	}
	if (!(result = create_node(NODE_LOGIC_AMPERSTAND, NULL)))
		malloc_error(m, NULL, NO_READING);
	ast_attach_branch(result, job, line);
	return (result);
}

static t_node	*build_line_semicolon(t_list **token, t_main *m)
{
	t_node *result;
	t_node *job;
	t_node *line;

	if ((job = build_job(token, m)) == NULL)
		return (NULL);
	if (!check(SEMICOLON, NULL, token))
	{
		ast_delete_node(job);
		return (NULL);
	}
	line = build_line(token, m);
	if (!(result = create_node(NODE_LINE, NULL)))
		malloc_error(m, NULL, NO_READING);
	ast_attach_branch(result, job, line);
	return (result);
}

static t_node	*build_line_job(t_list **token, t_main *m)
{
	return (build_job(token, m));
}

t_node			*build_line(t_list **token, t_main *m)
{
	t_node	*node;
	t_list	*save;
	int		line_par;

	line_par = check_line_open_par(token);
	save = *token;
	if ((*token = save)
		&& (node = build_line_logic_pipe(token, m)))
		return (check_line_closing_par(token, node, m, line_par));
	if ((*token = save) &&
		(node = build_line_logic_amper(token, m)))
		return (check_line_closing_par(token, node, m, line_par));
	if ((*token = save)
		&& (node = build_line_semicolon(token, m)))
		return (check_line_closing_par(token, node, m, line_par));
	if ((*token = save)
		&& (node = build_line_job(token, m)))
		return (check_line_closing_par(token, node, m, line_par));
	return (NULL);
}
