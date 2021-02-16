#include "../includes/minishell.h"


void        print_lst_tokens(t_lexer *lexer)
{
    t_list *toto;

    toto = lexer->tokens;
    printf("\n LEXER \n");
    while (toto)
    {
        t_token *t = toto->content;
        printf("%s     ---------- %u\n", t->data, t->type);
        toto = toto->next;
    }
    printf("nb=%d\n", lexer->nb_tokens);
}

void        free_lexer(t_list *lst_tokens)
{
    t_list *lst = lst_tokens;
    t_list *tmp;
    t_token *tok;

    while (lst)
    {
        tok = lst->content;
        free(tok->data);
        free(tok);
        tmp = lst;
        lst = lst->next;
        free(tmp);
    }
}

t_node *create_node(void *data)
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

int     main()
{
    t_lexer lexer;
    t_node *tree;

    ft_bzero(&lexer, sizeof(t_lexer));
    if (build_lexer("echo toto > popo | ls >; toto; yoyo \n", &lexer) == -1)
    {
        free_lexer(lexer.tokens);
        return (-1);
    }
    print_lst_tokens(&lexer);
    tree = create_node("input");
    parse(tree, &lexer);
    free_lexer(lexer.tokens);
    return(0);
}