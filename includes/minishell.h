#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include "../libft/libft.h"

typedef enum e_token_type{
	PIPE,
	QOUTE,
	DQUOTE,
	SEMICOLON,
    AMPERSAND,
	WHITESPACE,
	TAB,
	NEWLINE,   
	GREATER,
    DGREATER,
	LESSER,
    DASH,
    WORD,
} t_token_type;

typedef enum e_node_type {
    NODE_ARG,
    NODE_PIPE,
    NODE_PIPE_LST,
    NODE_CMD_LINE,
    NODE_CMD,
    NODE_IO_MODIFIER
} t_node_type;

typedef struct s_token {
    char *data;
    t_token_type type;
} t_token;

typedef struct s_lexer {
    t_list *tokens;
    int     nb_tokens;
} t_lexer;


typedef struct s_node {
    int type;
    char *data;
    struct s_node *left;
    struct s_node *right;
} t_node;

int         error(char *msg, int ret);
void        free_tab(char **tab);
t_token     *t_access(t_list *lst);
int         build_lexer(char *line, t_lexer *lexer);
t_node      *parse(t_lexer *lexer);
t_node      *create_node(void *data, int type);
#endif