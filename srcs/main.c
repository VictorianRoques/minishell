#include "../includes/minishell.h"
// void        free_tab(char **tab)
// {
//     int i;

//     i = 0;
//     while (tab[i])
//     {
//         free(tab[i]);
//         i++;
//     }
//     free(tab);
// }

// static void exec_cmd(char **cmd)
// {
//     pid_t pid = 0;                                                                                                                                
//     int status = 0;

//     pid = fork();
//     if (pid == -1)
//         perror("fork");
//     else if (pid > 0) {
//         waitpid(pid, &status, 0);
//         kill(pid, SIGTERM);
//     }
//     else {
//         if (execve(cmd[0], cmd, NULL) == -1)
//             perror("shell");
//         exit(EXIT_FAILURE);
//     }
// }


int main(int ac, char **argv, char **envp)
{
    (void)ac;
    (void)argv;
    (void)envp;
//     char    buff[2048];
//     char    **cmd;

//     env->data = NULL;
//     write(1, "$>", 3);
//     // init_env(env, envp);
//     while(read(0, buff, 2048) > 0)
//     {
//         cmd = ft_split(buff, ' ');
//         //get_absolute_path(cmd)
//         if (cmd[0] == NULL)
//             printf("Command not found \n");
//         else
//             exec_cmd(cmd);
//         write(1, "$>", 3);
//         free_array(cmd);   
//     }
//     printf("Bye \n");
    t_list *list = NULL;
    t_list deux;
    t_list trois;
    list->content = ft_strdup("toto");
    deux.content = "lalala";
    trois.content = "trois";
    list->next = &deux;
    deux.next = NULL;
    // ft_lstadd_back(&list, &trois);
    printf("%s\n", list->next->next->content);
}