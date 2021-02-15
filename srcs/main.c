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
    if (root)
        root->left = left;
}

void    attach_right(t_node *root, t_node *right)
{
    if (root)
        root->right = right;
}

void     parse_token(t_node *root, t_list **lst_tokens)
{
    t_node  *node;
    int     type;
    char    *data;

    if (!*lst_tokens)
        return ;
    type = t_access(*lst_tokens)->type;
    data = t_access(*lst_tokens)->data;
    if (type == WORD)
    {
        node = create_node(data, TOKEN);
        attach_left(root, node);
        *lst_tokens = (*lst_tokens)->next;
    }
}

void     parse_tokens_list(t_node *root, t_list **lst_tokens)
{
    t_node *node;
    int     type;
    char    *data;

    if (!*lst_tokens)
        return ;
    
    parse_token(root, lst_tokens);
    type = t_access(*lst_tokens)->type;
    data = t_access(*lst_tokens)->data;
    if (type == WORD)
    {
        root = root->left;
        parse_tokens_list(root, lst_tokens);
    }
}

void     parse_simple_cmd(t_node *root, t_list **lst_tokens)
{
    t_node *node;
    t_node *toto;

    char *data;
    int type;

    if (!*lst_tokens)
        return ;
    data = t_access(*lst_tokens)->data;
    type = t_access(*lst_tokens)->type;
    if (type == WORD)
    {
        node = create_node(data, PATHNAME);
        attach_left(root, node);
        *lst_tokens = (*lst_tokens)->next;
        type = t_access(*lst_tokens)->type;
        if (type == WORD)
        {
            toto = create_node(t_access(*lst_tokens)->data, TOKENS_LST);
            attach_left(node, toto);
            parse_tokens_list(node, lst_tokens);
        }
    }
}

void     parse_cmd(t_node *root, t_list **lst_tokens)
{
    t_node *node;
    int type;

    if (!*lst_tokens)
        return ;
    parse_simple_cmd(root, lst_tokens);
    type = t_access(*lst_tokens)->type;
    if (type == GREATER || type == DGREATER || type == LESSER)
    {
        node = create_node(t_access(*lst_tokens)->data, type);
        attach_right(root, node);
        *lst_tokens = (*lst_tokens)->next;
        if (t_access(*lst_tokens)->type == WORD)
        {
            node = create_node(t_access(*lst_tokens)->data, FILENAME);
            attach_left(root->right, node);
            *lst_tokens = (*lst_tokens)->next;

        }
        else
            printf("Error no filename after redirection \n");
    }
}

void     parse_task(t_node *root, t_list **lst_tokens)
{
    t_node *node;

    if (!*lst_tokens)
        return ;
    parse_cmd(root, lst_tokens);
    if (t_access(*lst_tokens)->type == PIPE)
    {
        node = create_node(t_access(*lst_tokens)->data, PIPE);
        attach_right(root, node);
        *lst_tokens = (*lst_tokens)->next;
        parse_task(root->right, lst_tokens);
    }
}

void     parse_cmd_line(t_node *root, t_list **lst_tokens)
{
    t_node *node;

    if (!*lst_tokens)
        return ;
    parse_task(root, lst_tokens);
    if (t_access(*lst_tokens)->type == SEMICOLON
        || t_access(*lst_tokens)->type == AMPERSAND)
    {
        node = create_node(t_access(*lst_tokens)->data, SEMICOLON);
        attach_right(root, node);
        *lst_tokens = (*lst_tokens)->next;
        parse_cmd_line(root->right, lst_tokens);
    }
}
void         parse_input(t_node *root, t_list **lst_tokens)
{
    t_node *node;

    if (!*lst_tokens)
        return ;
    parse_cmd_line(root, lst_tokens);
    if (t_access(*lst_tokens)->type == NEWLINE)
    {
        node = create_node(t_access(*lst_tokens)->data, '\n');
            attach_right(root, node);
        *lst_tokens = (*lst_tokens)->next;
    }
}

void        print_preorder(t_node *node)
{
    if (node == NULL)
        return;
    printf("%s %d\n", node->data, node->type);
    print_preorder(node->left);
    print_preorder(node->right);
}

void        parse(t_node *root, t_lexer *lexer)
{
    t_list *lst_tokens;

    t_node *tree;
    lst_tokens = lexer->tokens;
    // parse_input(root, &lst_tokens);
    parse_cmd_line(root, &lst_tokens);
    printf("PARSING\n");
    print_preorder(root);
}

int     main()
{
    t_lexer lexer;
    t_node *tree;

    ft_bzero(&lexer, sizeof(t_lexer));
    if (build_lexer("echo toto > popo eoeo toto ; I; AM ; GROOT;\n", &lexer) == -1)
    {
        free_lexer(lexer.tokens);
        return (-1);
    }
    print_lst_tokens(&lexer);
    tree = create_node("input", INPUT);
    parse(tree, &lexer);
    free_lexer(lexer.tokens);
    return(0);
}