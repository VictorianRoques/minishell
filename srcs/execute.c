#include "../includes/minishell.h"

char    *search_path(char *cmd_name)
{
    char *path;

    if (!ft_strncmp("ls", cmd_name, 2))
        path = ft_strjoin("/bin/", cmd_name);
    else
        path = ft_strjoin("/usr/bin/", cmd_name);
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
void    handle_piping(t_executor *exec)
{
    if (exec->stdin_pipe && exec->stdout_pipe)
        {
            dup2(exec->pipe_read, 0);
            dup2(exec->pipe_write, 1);
        }
        else if (exec->stdout_pipe)
        {
            close(exec->pipe_read);
            dup2(exec->pipe_write, 1);
        }
        else if (exec->stdin_pipe)
        {
            close(exec->pipe_write);
            dup2(exec->pipe_read, 0);
        }
}

int     execute(t_node *cmd, t_executor *exec)
{
    pid_t pid;
    t_node *node = cmd;
    char *path;
    char **args;

    if ((pid = fork()) < 0)
        return (-1);
    if (pid == 0)
    {
        handle_piping(exec);
        path = search_path(node->data);
        args = create_cmd_table(node);
        if ((execve(path, args, exec->env)) == -1)
            perror("execve");
        free(path);
        free_tab(args);
    }
    return (1);
}

void        execute_builtin(t_node *builtin, t_executor *exec)
{
    execute(builtin, exec);
}

void    handle_redirection(t_node *node_redirect)
{
    int fdout;
    int fdin;
    t_node *redirect = node_redirect;

    while (redirect)
    {
        if (redirect->type == NODE_REDIRECT_IN)
        {
            fdout = open(redirect->data, O_RDWR | O_CREAT);
            dup2(fdout, 1);
            close(fdout);
        }
        else if (redirect->type == NODE_REDIRECT_OUT)
        {
            fdin = open(redirect->data, O_RDONLY);
            dup2(fdin, 0);
            close(fdin);
        }
        else if (redirect->type == NODE_REDIRECT_DIN)
        {
            fdout = open(redirect->data, O_RDWR | O_CREAT | O_APPEND);
            dup2(fdout, 1);
            close(fdout);
        }
        redirect = redirect->right;
    }
}

void        execute_command(t_node *command, t_executor *exec)
{
    //initialize to NULL redirections
    if (!command)
        return;
    if (command->type == NODE_REDIRECT_IN || command->type == NODE_REDIRECT_OUT
        || command->type == NODE_REDIRECT_DIN)
    {
        handle_redirection(command);
        execute_builtin(command->left, exec);
    }
    else
        execute_builtin(command, exec);
}

void        set_pipe_bool(int stdin_pipe, int stdout_pipe, t_executor *exec)
{
    exec->stdin_pipe = stdin_pipe;
    exec->stdout_pipe = stdout_pipe;
}

void        execute_pipe(t_node *node_pipe, t_executor *exec)
{
    int fd[2];
    pipe(fd);

    exec->pipe_read = fd[0];
    exec->pipe_write = fd[1];
    set_pipe_bool(0, 1, exec);
    execute_command(node_pipe->left, exec);

    t_node *job = node_pipe->right;
    while (job && job->type == NODE_PIPE)
    {
        exec->pipe_read = fd[0];
        exec->pipe_write = fd[1];
        set_pipe_bool(1, 1, exec);
        close(exec->pipe_write);
        pipe(fd);
        exec->pipe_write = fd[1];
        execute_command(job->left, exec);
        close(exec->pipe_read);
        exec->pipe_read= fd[0];
        job = job->right;
    }
    exec->pipe_read = fd[0];
    exec->pipe_write = fd[1];
    set_pipe_bool(1, 0,exec);
    execute_command(job, exec);
    close(exec->pipe_read);
}

void        execute_job(t_node *job, t_executor *exec)
{
    if (!job)
        return;
    if (job->type == NODE_PIPE)
    {
        execute_pipe(job, exec);
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