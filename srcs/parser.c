#include "../includes/minishell.h"

t_node      *create_node(void *data, int type)
{
    t_node *toto = malloc(sizeof(t_node));
    toto->data = data;
    toto->type = type;
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
void    parse_pathname(t_node *root, t_list **tokens)
{
    t_node *node;

    if (!*tokens)
        return ;
    if (t_access(*tokens)->type == WORD)
    {
        node = create_node(t_access(*tokens)->data, NODE_CMD);
        attach_left(root, node);
        *tokens = (*tokens)->next;
    }
}

void    parse_arg(t_node *root, t_list **tokens)
{
    t_node *node;

    if (!*tokens)
        return ;
    if (t_access(*tokens)->type == WORD)
    {
        node = create_node(t_access(*tokens)->data, NODE_ARG);
        attach_left(root, node);
        *tokens = (*tokens)->next;
    }
}
void    parse_args_list(t_node *root, t_list **tokens)
{
    t_node *node;

    if (!*tokens)
        return ;
    parse_arg(root, tokens);
    if (t_access(*tokens)->type == WORD)
        parse_arg(root->left, tokens);
}

void    parse_cmd_and_args(t_node *root, t_list **tokens)
{
    t_node *node;

    if (!*tokens)
        return ;
    parse_pathname(root, tokens);
    if (t_access(*tokens)->type == WORD)
        parse_args_list(root->left, tokens);
    if (t_access(*tokens)->type == GREATER ||
        t_access(*tokens)->type == LESSER)
    {
        node = create_node(t_access(*tokens)->data, NODE_IO_MODIFIER);
        attach_right(root, node);
        *tokens = (*tokens)->next;
        parse_arg(root->right, tokens);
    }
}

void    parse_pipe(t_node *root, t_list **tokens)
{
    t_node *node;

    if (!*tokens)
        return ;
    parse_cmd_and_args(root, tokens);
    if (t_access(*tokens)->type == PIPE)
    {
        node = create_node(t_access(*tokens)->data, NODE_PIPE);
        attach_right(root, node);
        *tokens = (*tokens)->next;
        parse_pipe(root->right, tokens);
    }
}
t_node      *parse_pipe_list(t_list **tokens)
{
    t_node *root;
    
    if (!*tokens)
        return NULL;
    root = create_node("PIPE_LST", NODE_CMD_LINE);
    parse_pipe(root, tokens);
    return (root);
}

void        print_preorder(t_node *node)
{
    if (node == NULL)
        return;
    printf("%s %i\n", node->data, node ->type);
    print_preorder(node->left);
    print_preorder(node->right);
}

t_node        *parse(t_lexer *lexer)
{
    t_list *tokens;
    t_node *tree;

    tokens = lexer->tokens;
    tree = parse_pipe_list(&tokens);
    // printf("PARSING\n");
    // print_preorder(tree);
    return (tree);
}