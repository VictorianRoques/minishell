#include "../includes/minishell.h"
#include "../includes/lexer.h"

static int         generate_cmd_token(char *str, t_lexer *lexer)
{
    int i = 0;
    t_list *lst;
    t_token *tok;

    while(ft_isalpha(str[i]))
        i++;
    char *string = malloc(sizeof(char) * i + 1);
    i = 0;
    while(ft_isalpha(str[i]))
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

int     build_lexer(char *line, t_lexer *lexer)
{
    int i = 0;
    int len;

    while(line[i])
    {
        if (ft_isalpha(line[i]))
        {
            len = generate_cmd_token(line + i, lexer);
            i += len - 1;
        }
        else if (line[i] == '|')
            create_token("|", PIPE, lexer);
        else if (line[i] == '\'')
            create_token("'", QOUTE, lexer);
        else if (line[i] == '\"')
            create_token("\"", DQUOTE, lexer);
        else if (line[i] == ';')
            create_token(";", SEMICOLON, lexer);
        else if (line[i] == '&')
            create_token("&", AMPERSAND, lexer);
        else if (line[i] == '\n')
            create_token("\n", NEWLINE, lexer);
        else if (line[i] == '>')
        {
            if (line[i + 1] && line[i + 1] == '>')
                create_token(">>", DGREATER, lexer);
            else
                create_token(">", GREATER, lexer);
        }
        else if (line[i] == '<')
            create_token("<", LESSER, lexer);
        else if (line[i] == '-')
            create_token("-", DASH, lexer);
        i++;
    }
    return (0);
}