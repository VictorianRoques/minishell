/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:21:26 by viroques          #+#    #+#             */
/*   Updated: 2021/03/03 16:23:22 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_node      *build_line_1(t_list **token)
{
    t_node *result;
    t_node *job;
    t_node *line;

    if ((job = build_job(token)) == NULL)
        return (NULL);
    if (!check(SEMICOLON, NULL, token))
    {
        ast_delete_node(job);
        return (NULL);
    }
    if ((line = build_line(token)) == NULL)
    {
        ast_delete_node(job);
        return (NULL);
    }
    result = malloc(sizeof(*result));
    ast_set_type(result, NODE_LINE);
    ast_set_data(result, NULL);
    ast_attach_branch(result, job, line);
    return (result);
}

static t_node      *build_line_2(t_list **token)
{
    t_node *job;

    if ((job = build_job(token)) == NULL)
        return (NULL);
    if (!check(SEMICOLON, NULL, token))
    {
        ast_delete_node(job);
        return (NULL);
    }
    return (job);
}

static t_node      *build_line_3(t_list **token)
{
    return (build_job(token));
}

t_node      *build_line(t_list **token)
{
    t_node *node;
    t_list *save;

    save = *token;
    if ((*token = save) && (node = build_line_1(token)))
        return (node);
    if ((*token = save) && (node = build_line_2(token)))
        return (node);
    if ((*token = save) && (node = build_line_3(token)))
        return (node);
    return (NULL);
}