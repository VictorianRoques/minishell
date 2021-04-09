/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:23:55 by viroques          #+#    #+#             */
/*   Updated: 2021/04/07 19:38:18 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_node	*build_job_pipe(t_list **token, t_main *m)
{
	t_node *result;
	t_node *command;
	t_node *job;

	if ((command = build_command(token, m)) == NULL)
		return (NULL);
	if (!check(PIPE, NULL, token))
	{
		ast_delete_node(command);
		return (NULL);
	}
	if (!(job = build_job(token, m)))
	{
		ast_delete_node(command);
		return (NULL);
	}
	if (!(result = create_node(NODE_PIPE, NULL)))
		malloc_error(m, NULL, NO_READING);
	ast_attach_branch(result, command, job);
	return (result);
}

static t_node	*build_job_command(t_list **token, t_main *m)
{
	return (build_command(token, m));
}

t_node			*build_job(t_list **token, t_main *m)
{
	t_node	*node;
	t_list	*save;
	int		job_par;

	job_par = check_par(OPEN_PAR, token);
	save = *token;
	if ((*token = save) &&
		(node = build_job_pipe(token, m)))
		return (check_closing_par(job_par, token, node));
	if ((*token = save) &&
		(node = build_job_command(token, m)))
		return (check_closing_par(job_par, token, node));
	return (NULL);
}
