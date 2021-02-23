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

int     handle_quote(char *line, t_lexer *lexer, char quote)
{
    int i;
    int j;
    char *str;
    t_token *token;
    t_list *lst;

    if (!line[1] || !ft_strchr(line + 1, quote))
        return (error("Missing closing quote\n", -1));
    i = 1;
    while (line[i] != quote)
        i++;
    str = malloc(sizeof(char) * i + 1);
    i = 1;
    j = 0;
    while (line[i] != quote)
    {
        str[j] = line[i];
        j++;
        i++;
    }
    str[j] = 0;
    token = malloc(sizeof(t_token));
    token->type = WORD,
    token->data = str;
    lst = ft_lstnew(token);
     ft_lstadd_back(&(lexer->tokens), lst);
    return (i);
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
        if (line[i] == '|')
            create_token("|", PIPE, lexer);
        if (line[i] == '>')
        {
            if (line[i + 1] && line[i + 1] == '>')
            {
                create_token(">>", DGREATER, lexer);
                i++;
            }
            else
                create_token(">", GREATER, lexer);
        }
        if (line[i] == '<')
            create_token("<", LESSER, lexer);
        if (line[i] == ';')
            create_token(";", SEMICOLON, lexer);
        if (line[i] == '&')
            create_token("&", AMPERSAND, lexer);
        if (line[i] == '-')
        {
            len = word_token(line + i, lexer);
            i += len - 1;
        }
        if (line[i] == '\n')
            create_token("\n", NEWLINE, lexer);
        if (line[i] == '\'' || line[i] == '\"')
        {
            if ((len = handle_quote(line + i, lexer, line[i])) == -1)
                return (-1);
            i += len;
        }
        i++;
    }
    return (0);
}