#include "../includes/minishell.h"

static int         word_token(char *str, t_lexer *lexer)
{
    int i;
    t_list *lst;
    t_token *tok;
    char *string;

    i = 0;
    while (ft_isalpha(str[i]) || str[i] == '-')
        i++;
    string = malloc(sizeof(char) * i + 1);
    i = 0;
    while (ft_isalpha(str[i]) || str[i] == '-')
    {
        string[i] = str[i];
        i++;
    }
    string[i] = 0;
    tok = malloc(sizeof(t_token));
    tok->data = string;
    tok->type = WORD;
    lst = ft_lstnew(tok);
    ft_lstadd_back(&(lexer->tokens), lst);
    lexer->nb_tokens++;
    return (i);
}

static int     create_token(char *data, int type, t_lexer *lexer)
{
    t_list *lst;
    t_token *token;

    token = malloc(sizeof(t_token));
    token->data = ft_strdup(data);
    token->type = type;
    lst = ft_lstnew(token);
    if (!token | !token->data | !lst)
        return (-1);
    ft_lstadd_back(&(lexer->tokens), lst);
    lexer->nb_tokens++;
    return (0);
}

static void     del_token(t_list *lst)
{
    free(t_access(lst)->data);
    free(t_access(lst));
}

static int     check_closing_quote(t_lexer *lexer)
{
    t_list *lst;
    int q;
    int d;

    q = 0;
    d = 0;
    lst = lexer->tokens;
    while (lst)
    {
        if (t_access(lst)->type == QOUTE)
            q++;
        if (t_access(lst)->type == DQUOTE)
            d++;
        lst = lst->next;
    }
    if (q % 2 != 0 || d % 2 != 0)
        return (-1);
    // remove_quote_from_lexer(lexer);
    return (0);
}

int     check_operator_control(t_lexer *lexer)
{
    t_list  *lst;
    int     type;

    lst = lexer->tokens;
    while (lst)
    {
        type = t_access(lst)->type;
        if (type == GREATER || type == LESSER || type == DGREATER
            || type == PIPE)
        {
            if (!lst->next || t_access(lst->next)->type != WORD)
                return (-1);
        }
        lst = lst->next;
    }
    return (0);
}

static int     lexer_control_op(char *line, t_lexer *lexer, int *index)
{
    int i;
    int ok;

    ok = 0;
    i = 0;
    while (line[i])
    {
        if (ft_isalpha(line[i]))
        {
            ok = 1;
            break;
        }
        i++;
    }
    if (ok)
    {
        i = 0;
        if (line[i] == '>')
        {
            if (line[i + 1] && line[i + 1] == '>')
            {
                create_token(">>", DGREATER, lexer);
                *index = *index + 1;
            }
            else
                create_token(">", GREATER, lexer);
        }
        else if (line[i] == '|')
            create_token("|", PIPE, lexer);
        return (1);
    }
    else
        return (0);
}

int     build_lexer(char *line, t_lexer *lexer)
{
    int i = 0;
    int len;

    while (line[i])
    {
        if (ft_isalpha(line[i]))
        {
            len = word_token(line + i, lexer);
            i += len - 1;
        }
        if (line[i] == '|' || line[i] == '>' || line[i] == '<')
        {
            if (!lexer_control_op(line + i, lexer, &i))
                return (error("error around controle operator\n", -1));
        }
        if (line[i] == ';')
            create_token(";", SEMICOLON, lexer);
        if (line[i] == '&')
            create_token("&", SEMICOLON, lexer);
        if (line[i] == '-')
        {
            len = word_token(line + i, lexer);
            i += len - 1;
        }
        if (line[i] == '\n')
            create_token("\n", NEWLINE, lexer);
        if (line[i] == '\'')
            create_token("\'", QOUTE, lexer);
        if (line[i] == '\"')
            create_token("\"", DQUOTE, lexer);
        i++;
    }
    if (check_closing_quote(lexer) == -1)
        return (error("error missing closing quote\n", -1));
    if (check_operator_control(lexer) == -1)
        return (error("error around controle operator\n", -1));
    return (0);
}