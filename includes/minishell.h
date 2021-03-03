#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include "../libft/libft.h"
# include <sys/errno.h>

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
**  job     ::=     <command> '|' <job>             build_job__1
            |       <command>                       build_job_2
**
**  command ::=     <builtin> '>' <filename>        build_command_1
**          |       <builtin> '<' <filename>        build_command_2
**          |       <builtin> '>>' <filename>       build_command_3
**          |       <builtin>                       build_command_4
**          
** filemame ::=     <filename> '>' <filename>       build_filename_1
**          |       <filename> '>>' <filename>      build_filename_2
**          |       <token>                         build_filename_3
**
**  builtin ::==    <pathname> <args>               build_builtin_1
            |       <pathname>                      build_builtin_2
**
**  args    ::=     <arg> <args>                    build_arg_tree_1                    
            |       EMPTY                           build_arg_tree_2
*/

typedef enum e_token_type{
	PIPE,
	QOUTE,
	DQUOTE,
	SEMICOLON,  
	GREATER,
    DGREATER,
	LESSER,
    NEWLINE,
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

typedef struct s_executor {
    int stdin_pipe;
    int stdout_pipe;
    int pipe_read;
    int pipe_write;
    char *redirect_in;
    char *redirect_out;
    char *redirect_din;
    char **env;
    char **dirs_path;
    char *path;
} t_executor;


//utils
int         error(char *msg, int ret);
int         error_parsing(char *data);
void        free_tab(char **tab);
t_token     *t_access(t_list *lst);

//lexer
int         build_lexer(char **tab, t_lexer *lexer);
int         create_operator_token(char *data, int type, t_lexer *lexer);
int         create_word_token(char *str, t_lexer *lexer);
//parsing function
int         parse(t_lexer *lexer, t_node **exec_tree);
t_node      *build_line(t_list **token);
t_node      *build_job(t_list **token);
t_node      *build_command(t_list **token);
t_node      *build_filename(t_list **token);
t_node      *build_builtin(t_list **token);
t_node      *build_args(t_list **token);
int         check(int tok_type, char** bufferptr, t_list **token);

//execute function
int         execute_bin(t_node *cmd, t_executor *exec);
void        handle_redirection(t_node *node_redirect);
void        handle_piping(t_executor *exec);
void        set_pipe_bool(int stdin_pipe, int stdout_pipe, int *fd ,t_executor *exec);
char        *search_path(char *cmd_name, char **directories);
char        **get_directories_path(char **env);
void        execute_ast_tree(t_node *exec_tree, char **env);

//ast_tree
void        ast_delete_node(t_node *node);
void        ast_set_data(t_node *node, char *data);
void        ast_set_type(t_node *node, int type);
void        ast_attach_branch(t_node *root, t_node *left, t_node *right);
void        execute_ast_tree(t_node *exec, char **env);

#endif