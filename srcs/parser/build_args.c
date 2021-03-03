/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:31:54 by viroques          #+#    #+#             */
/*   Updated: 2021/03/03 17:10:35 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static t_node      *build_arg_1(t_list **token)
{
    t_node *args_list;
    t_node *result;
    char *arg;

    if (!check(WORD, &arg, token))
        return NULL;
    args_list = build_args(token);
    result = malloc(sizeof(*result));
    ast_set_data(result, arg);
    ast_set_type(result, NODE_ARG);
    ast_attach_branch(result, args_list, NULL);
    return (result);
}

static t_node      *build_arg_2(void)
{
    return (NULL);
}

t_node        *build_args(t_list **token)
{
    t_node *node;
    t_list *save;

    save = *token;
    if ((*token = save) && (node = build_arg_1(token)))
        return node;
    if ((*token = save) && (node = build_arg_2()))
        return node;
    return NULL;
}