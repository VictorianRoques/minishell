#include "../includes/minishell.h"
#include "../includes/lexer.h"
#include "../includes/ast_tree.h"

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

t_token     *access_token(t_list *lst)
{
    return ((t_token*)lst->content);
}

t_node *create_node(void *data, int type)
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
    root->left = left;
}

void    attach_right(t_node *root, t_node *right)
{
    root->right = right;
}

void        parse_arg(t_node *root, t_list **lst_tokens)
{
    if (access_token(*lst_tokens)->type == WORD)
    {
        t_node *node = create_node(access_token(*lst_tokens)->data, ARG);
        attach_left(root, node);
        *lst_tokens = (*lst_tokens)->next;
    }
}
void        parse_args_lst(t_node *root, t_list **lst_tokens)
{
     if (access_token(*lst_tokens)->type == WORD)
    {
        t_node *node = create_node(access_token(*lst_tokens)->data, ARGS_LST);
        attach_left(root, node);
        parse_arg(node, lst_tokens);
    }
}

void        parse_path(t_node *root, t_list **lst_tokens)
{
    if (access_token(*lst_tokens)->type == WORD)
    {
        t_node *node = create_node(access_token(*lst_tokens)->data, PATHNAME);
        attach_left(root, node);
        *lst_tokens = (*lst_tokens)->next;
        if (*lst_tokens)
            parse_args_lst(node, lst_tokens);
    }
}

int     parse_cmd_line(t_node *root, t_list **lst_tokens)
{
    if (!*lst_tokens)
        return (0);
    if (*lst_tokens && access_token(*lst_tokens)->type == WORD)
    {
        t_node *node = create_node(access_token(*lst_tokens)->data, COMMAND);
        attach_left(root, node);
        parse_path(node, lst_tokens);
    }
    if (*lst_tokens && access_token(*lst_tokens)->type == SEMICOLON)
    {
        t_node *node = create_node(access_token(*lst_tokens)->data, CMD_LINE);
        attach_right(root, node);
        *lst_tokens = (*lst_tokens)->next;
        parse_cmd_line(node, lst_tokens);
    }
     if (*lst_tokens && access_token(*lst_tokens)->type == AMPERSAND)
    {
        printf("toto\n");
        t_node *node = create_node(access_token(*lst_tokens)->data, CMD_LINE);
        attach_right(root, node);
        *lst_tokens = (*lst_tokens)->next;
        parse_cmd_line(node, lst_tokens);
    }
    return (0);
}

void        print_tree(t_node *root)
{
    printf("\nPARSER\n");
    while (root->left)
    {
        printf("data=%s type%i\n", root->data, root->type);
        if (root->right)
        {
            printf("data=%s type%i\n", root->right->data, root->left->type);
        }
        root = root->left;
    }
    printf("data=%s type%i\n", root->data, root->type);
}

void        parse(t_node *root, t_lexer *lexer)
{
    t_list *lst_tokens;

    lst_tokens = lexer->tokens;
    parse_cmd_line(root, &lst_tokens);
    print_tree(root);
}

int     main()
{
    t_lexer lexer;
    t_node *tree;

    ft_bzero(&lexer, sizeof(t_lexer));
    build_lexer("echo toto; ls", &lexer);
    print_lst_tokens(&lexer);

    tree = create_node(NULL, CMD_LINE);
    parse(tree, &lexer);
    free_lexer(lexer.tokens);
    return(0);
}