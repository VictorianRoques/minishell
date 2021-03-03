/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:15:30 by viroques          #+#    #+#             */
/*   Updated: 2021/03/03 16:52:45 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void        ast_attach_branch(t_node *root, t_node *left, t_node *right)
{
    if (!root)
        return ;
    root->left = left;
    root->right = right;
}

void        ast_set_data(t_node *node, char *data)
{
    if (!node)
        return ;
    node->data = data;
}
void    ast_set_type(t_node *node, int type)
{
    if (!node)
        return;
    node->type = type;
}

void    ast_delete_node(t_node *node)
{
    if (!node)
        return;
    if (node->data)
        free(node->data);
    ast_delete_node(node->left);
    ast_delete_node(node->right);
    free(node);
}