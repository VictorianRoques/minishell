#include "../includes/minishell.h"

char    *search_path(char *cmd_name)
{
    char *path;

    path = ft_strjoin("/bin/", cmd_name);
    return (path);
}

char        **create_cmd_table(t_node *root)
{
    t_node *node;
    char **args;
    int nbcmd;

    nbcmd = 0;
    node = root;
    while(node)
    {
        nbcmd++;
        node = node->left;
    }
    args = malloc(sizeof(char *) * nbcmd + 1);
    node = root;
    nbcmd = 0;
    while (node)
    {
        args[nbcmd] = ft_strdup(node->data);
        node = node->left;
        nbcmd++;
    }
    args[nbcmd] = NULL;
    return (args);
}

int     execute(t_node *cmd, t_executor *exec)
{
    pid_t pid;
    t_node *node = cmd;
    char *path;
    char **args;
    int fdout;
    int fdin;
    int statut;
    path = search_path(node->data);
    args = create_cmd_table(node);
    // redirections
    if (exec->redirect_in)
    {
        
        fdout = open(exec->redirect_in, O_RDWR | O_CREAT);
        dup2(fdout, 1);
        close(fdout);
    }
    else if (exec->redirect_out)
    {
        fdin = open(exec->redirect_out, O_RDONLY);
        dup2(fdin, 0);
        close(fdin);
    }
    else if (exec->dredirect_in)
    {
        fdout = open(exec->dredirect_in, O_RDWR | O_CREAT | O_APPEND);
        dup2(fdout, 1);
        close(fdout);
    }
    //end redirection
    if ((pid = fork()) < 0)
        return (-1);
    if (pid == 0)
    {
        execve(path, args, exec->env);
    }
    free(path);
    free_tab(args);
    return (1);
}

void        execute_builtin(t_node *builtin, t_executor *exec)
{
    execute(builtin, exec);
}

void        execute_command(t_node *command, t_executor *exec)
{
    //initialize to NULL redirections
    if (!command)
        return;
    if (command->type == NODE_REDIRECT_IN)
    {
        exec->redirect_in = command->data;
        execute_builtin(command->left, exec);
    }
    else if (command->type == NODE_REDIRECT_OUT)
    {
        exec->redirect_out = command->data;
        execute_builtin(command->left, exec);
    }
    else if (command->type == NODE_REDIRECT_DIN)
    {
        exec->dredirect_in = command->data;
        execute_builtin(command->left, exec);
    }
    else
        execute_builtin(command, exec);
}

void        execute_job(t_node *job, t_executor *exec)
{
    if (!job)
        return;
    if (job->type == NODE_PIPE)
    {
        execute_command(job->left, exec);
        execute_job(job->right, exec);
    }
    else
        execute_command(job, exec);
}

void        execute_command_line(t_node *cmd_line, t_executor *exec)
{
    if (!cmd_line)
        return ;
    if (cmd_line->type == NODE_LINE)
    {
        execute_job(cmd_line->left, exec);
        execute_command_line(cmd_line->right, exec);
    }
    else
        execute_job(cmd_line, exec);
}

void     execute_ast_tree(t_node *exec_tree, char **env)
{
    t_executor exec;
    ft_bzero(&exec, sizeof(t_executor));
    exec.env = env;
    execute_command_line(exec_tree, &exec);
}