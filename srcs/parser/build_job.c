/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:23:55 by viroques          #+#    #+#             */
/*   Updated: 2021/03/03 16:26:42 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_node      *build_job_1(t_list **token)
{
    t_node *result;
    t_node *command;
    t_node *job;

    if ((command = build_command(token)) == NULL)
        return (NULL);
    if (!check(PIPE, NULL, token))
    {
        ast_delete_node(command);
        return (NULL);
    }
    if ((job = build_job(token)) == NULL)
    {
        ast_delete_node(command);
        return (NULL);
    }
    result = malloc(sizeof(*result));
    ast_set_type(result, NODE_PIPE);
    ast_set_data(result, NULL);
    ast_attach_branch(result, command, job);
    return (result);
}

static t_node      *build_job_2(t_list **token)
{
  return (build_command(token));
}

t_node      *build_job(t_list **token)
{
    t_node *node;
    t_list *save;

    save = *token;
    if ((*token = save) && (node = build_job_1(token)))
        return (node);
    if ((*token = save) && (node = build_job_2(token)))
        return (node);
    return (NULL);
}