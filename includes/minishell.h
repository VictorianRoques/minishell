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

/*
** Recursive Descent Parsing algorithm for a subset of bash grammar
**
** DESCRIPTION
** Using backtracking, recursively test a linked list of bash-style tokens
** for all supported grammars, and organize them into abstract syntax tree
**
**  BNF:                                            HANDLER FUNCTION:
**  line    ::=     <job> ';' <line>                build_line_1
            |       <job> ';'                       build_line_2
            |       <job>                           build_line_5
**
**  job     ::=     <command> '|' <job>             build_job_tree_1
            |       <command>                       build_job_tree_2
**
**  command ::=     <builtin> '>' <filename>        build_command_1
**          |       <builtin> '<' <filename>        build_command_tree_2
**          |       <builtin> '>>' <filename>       build_command_tree_3
**          |       <builtin>                       build_command_tree_4
**          
** filemame ::=     <filename> '>' <filename>
**          |       <filename> '>>' <filename>
**          |       <token>
**
**  builtin ::==    <pathname> <args>               build_builtin_1
            |       <pathname>                      build_builtin_2

**  args    ::=     <arg> <args>                    build_arg_tree_1                    
            |       EMPTY                           build_arg_tree_2
*/

typedef enum e_token_type{
	PIPE,
	QOUTE,
	DQUOTE,
	SEMICOLON,
    AMPERSAND,
	NEWLINE,   
	GREATER,
    DGREATER,
	LESSER,
    WORD,
} t_token_type;

typedef enum e_node_type {
    NODE_ARG,
    NODE_BUILTIN,
    NODE_REDIRECT_IN,
    NODE_REDIRECT_OUT,
    NODE_REDIRECT_DIN,
    NODE_PIPE,
    NODE_LINE

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
int         parse(t_lexer *lexer, t_node **exec_tree);
void        ast_delete_node(t_node *node);
void        ast_set_data(t_node *node, char *data);
void        ast_set_type(t_node *node, int type);
void        ast_attach_branch(t_node *root, t_node *left, t_node *right);


#endif