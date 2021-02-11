#ifndef AST_TREE_H
# define AST_TREE_H
# include "../libft/libft.h"

typedef enum e_node_type {
    CMD_LINE,
    COMMAND,
    PATHNAME,
    ARGS_LST,
    ARG
} t_node_type;

typedef struct s_node {
    int type;
    void *data;
    struct s_node *left;
    struct s_node *right;
} t_node;

#endif