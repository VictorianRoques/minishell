#include "../includes/minishell.h"

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