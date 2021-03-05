/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:26:57 by viroques          #+#    #+#             */
/*   Updated: 2021/03/04 12:35:10 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_node      *build_command_4(t_list **token)
{
    return (build_builtin(token));
}

static t_node      *build_command_3(t_list **token)
{
    t_node  *result;
    t_node  *builtin;
    char    *filename;
    
   if ((builtin = build_builtin(token)) == NULL)
       return (NULL);
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
    if (!(result = malloc(sizeof(t_node))))
        return (NULL);
    ast_set_data(result, filename);
    ast_set_type(result, NODE_REDIRECT_OVER);
    ast_attach_branch(result, builtin, build_filename(token));
    return (result);
}

static t_node      *build_command_2(t_list **token)
{
    t_node  *result;
    t_node  *builtin;
    char    *filename;

   if ((builtin = build_builtin(token)) == NULL)
       return (NULL);
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
    if (!(result = malloc(sizeof(t_node))))
        return (NULL);
    ast_set_data(result, filename);
    ast_set_type(result, NODE_REDIRECT_OUT);
    ast_attach_branch(result, builtin, build_filename(token));
    return (result);
}

static t_node      *build_command_1(t_list **token)
{
    t_node  *result;
    t_node  *builtin;
    char    *pathname;

   if ((builtin = build_builtin(token)) == NULL)
       return (NULL);
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
    if (!(result = malloc(sizeof(t_node))))
        return (NULL);
    ast_set_data(result, pathname);
    ast_set_type(result, NODE_REDIRECT_IN);
    ast_attach_branch(result, builtin, build_filename(token));
    return (result);
}

t_node      *build_command(t_list **token)
{
    t_node *node;
    t_list *save;

    save = *token;
    if ((*token = save) && (node = build_command_1(token)))
        return (node);
    if ((*token = save) && (node = build_command_2(token)))
        return (node);
    if ((*token = save) && (node = build_command_3(token)))
        return (node);
    if ((*token = save) && (node = build_command_4(token)))
        return (node);
    return (NULL);
}