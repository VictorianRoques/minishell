#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include "../libft/libft.h"

typedef struct      s_token {
    char            *data;
    int             type;
    struct s_token  *next;
}                   token;

#endif