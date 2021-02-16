#include "../includes/minishell.h"

t_node      *create_node(void *data)
{
    t_node *toto = malloc(sizeof(t_node));
    toto->data = data;
    toto->left = NULL;
    toto->right = NULL;
    return (toto);
}

void        attach_left(t_node *root, t_node *left)
{
    if (root)
        root->left = left;
}

void    attach_right(t_node *root, t_node *right)
{
    if (root)
        root->right = right;
}

void    parse_token(t_node *root, t_list **tokens)
{
    t_node *node;

    if (!*tokens)
        return ;
    if (t_access(*tokens)->type == WORD)
    {
        node = create_node(t_access(*tokens)->data);
        attach_left(root, node);
        *tokens = (*tokens)->next;
    }
}
void    parse_simple_command(t_node *root, t_list **tokens)
{
    t_node *node;

    if (!*tokens)
        return ;
    parse_token(root, tokens);
    if (t_access(*tokens)->type == WORD)
        parse_simple_command(root->left, tokens);
}

void    parse_command(t_node *root, t_list **tokens)
{
    t_node *node;

    if (!*tokens)
        return ;
    parse_simple_command(root, tokens);
    if (t_access(*tokens)->type == GREATER || t_access(*tokens)->type == LESSER)
    {
        node = create_node(t_access(*tokens)->data);
        attach_right(root->left, node);
        *tokens = (*tokens)->next;
        parse_command(root->left->right, tokens);
    }
}
void        parse_task(t_node *root, t_list **tokens)
{
    t_node *node;

    if (!*tokens)
        return;
    parse_command(root, tokens);
    if (t_access(*tokens)->type == PIPE)
    {
        node = create_node(t_access(*tokens)->data);
        attach_right(root, node);
        *tokens = (*tokens)->next;
        parse_task(root->right, tokens);
    }
}
void    parse_cmd_line(t_node *root, t_list **tokens)
{
    t_node *node;

    if (!*tokens)
        return;
    parse_task(root, tokens);
    if (t_access(*tokens)->type == SEMICOLON || t_access(*tokens)->type == AMPERSAND)
    {
        node = create_node(t_access(*tokens)->data);
        *tokens = (*tokens)->next;
        if (root->right)
        {
            attach_right(root->right, node);
            parse_cmd_line(root->right->right, tokens);
        }
        else
        {
            attach_right(root, node);
            parse_cmd_line(root->right, tokens);
        }
    }
}

void        print_preorder(t_node *node)
{
    if (node == NULL)
        return;
    printf("%s\n", node->data);
    print_preorder(node->left);
    print_preorder(node->right);
}

void        parse(t_node *root, t_lexer *lexer)
{
    t_list *lst_tokens;

    t_node *tree;
    lst_tokens = lexer->tokens;
    parse_cmd_line(root, &lexer->tokens);
    printf("PARSING\n");
    print_preorder(root);
}