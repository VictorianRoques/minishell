/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:59 by viroques          #+#    #+#             */
/*   Updated: 2021/03/02 16:15:51 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
t_node      *build_args(t_list **token);
t_node      *build_arg_1(t_list **token);
t_node      *build_arg_2();
t_node      *build_builtin(t_list **token);
t_node      *build_builtin_1(t_list **token);
t_node      *build_filename(t_list **token);
t_node      *build_filename_1(t_list **token);
t_node      *build_filename_2(t_list **token);
t_node      *build_filename_3(t_list **token);
t_node      *build_command(t_list **token);
t_node      *build_command_1(t_list **token);
t_node      *build_command_2(t_list **token);
t_node      *build_command_3(t_list **token);
t_node      *build_command_4(t_list **token);
t_node      *build_job(t_list **token);
t_node      *build_job_1(t_list **token);
t_node      *build_job_2(t_list **token);
t_node      *build_line(t_list **token);
t_node      *build_line_1(t_list **token);
t_node      *build_line_2(t_list **token);
t_node      *build_line_3(t_list **token);

int     check(int tok_type, char** bufferptr, t_list **token)
{
	if (*token == NULL)
		return 0;
    if (t_access(*token)->type == tok_type)
    {
		if (bufferptr != NULL) {
			*bufferptr = ft_strdup(t_access(*token)->data);
		}
		*token = (*token)->next;
        return 1;
    }
    *token = (*token)->next;
    return 0;
}

void        print_preorder(t_node *node)
{
    if (node == NULL)
        return;
    printf("%s %i\n", node->data, node ->type);
    print_preorder(node->left);
    print_preorder(node->right);
}
t_node      *build_line(t_list **token)
{
    t_node *node;
    t_list *save;

    save = *token;
    if ((*token = save) && (node = build_line_1(token)))
        return (node);
    if ((*token = save) && (node = build_line_2(token)))
        return (node);
    if ((*token = save) && (node = build_line_3(token)))
        return (node);
    return (NULL);
}
t_node      *build_line_1(t_list **token)
{
    t_node *result;
    t_node *job;
    t_node *line;

    if ((job = build_job(token)) == NULL)
        return (NULL);
    if (!check(SEMICOLON, NULL, token))
    {
        ast_delete_node(job);
        return (NULL);
    }
    if ((line = build_line(token)) == NULL)
    {
        ast_delete_node(job);
        return (NULL);
    }
    result = malloc(sizeof(*result));
    ast_set_type(result, NODE_LINE);
    ast_set_data(result, NULL);
    ast_attach_branch(result, job, line);
    return (result);
}

t_node      *build_line_2(t_list **token)
{
    t_node *job;

    if ((job = build_job(token)) == NULL)
        return (NULL);
    if (!check(SEMICOLON, NULL, token))
    {
        ast_delete_node(job);
        return (NULL);
    }
    return (job);
}

t_node      *build_line_3(t_list **token)
{
    return (build_job(token));
}

t_node      *build_job(t_list **token)
{
    t_node *node;
    t_list *save;

    save = *token;
    if ((*token = save) && (node = build_job_1(token)))
        return (node);
    if ((*token = save) && (node = build_job_2(token)))
        return (node);
    return (NULL);
}

t_node      *build_job_1(t_list **token)
{
    t_node *result;
    t_node *command;
    t_node *job;

    if ((command = build_command(token)) == NULL)
        return (NULL);
    if (!check(PIPE, NULL, token))
    {
        ast_delete_node(command);
        return (NULL);
    }
    if ((job = build_job(token)) == NULL)
    {
        ast_delete_node(command);
        return (NULL);
    }
    result = malloc(sizeof(*result));
    ast_set_type(result, NODE_PIPE);
    ast_set_data(result, NULL);
    ast_attach_branch(result, command, job);
    return (result);
}

t_node      *build_job_2(t_list **token)
{
  return (build_command(token));
}

t_node      *build_command(t_list **token)
{
    t_node *node;
    t_list *save;

    save = *token;
    if ((*token = save) && (node = build_command_1(token)))
        return (node);
    if ((*token = save) && (node = build_command_2(token)))
        return (node);
    if ((*token = save) && (node = build_command_3(token)))
        return (node);
    if ((*token = save) && (node = build_command_4(token)))
        return (node);
    return (NULL);
}

t_node      *build_command_4(t_list **token)
{
    return (build_builtin(token));
}

t_node      *build_command_3(t_list **token)
{
    t_node *result;
    t_node *builtin;
    char *filename;

   if ((builtin = build_builtin(token)) == NULL)
       return (NULL);
    if (!check(DGREATER, NULL, token))
    {
        ast_delete_node(builtin);
        return (NULL);
    }
    if (!check(WORD, &filename, token))
    {
        ast_delete_node(builtin);
        return (NULL);
    }
    result = malloc(sizeof(*result));
    ast_set_data(result, filename);
    ast_set_type(result, NODE_REDIRECT_DIN);
    ast_attach_branch(result, builtin, NULL);
    return (result);
}

t_node      *build_command_2(t_list **token)
{
    t_node *result;
    t_node *builtin;
    char *filename;

   if ((builtin = build_builtin(token)) == NULL)
       return (NULL);
    if (!check(LESSER, NULL, token))
    {
        ast_delete_node(builtin);
        return (NULL);
    }
    if (!check(WORD, &filename, token))
    {
        ast_delete_node(builtin);
        return (NULL);
    }
    result = malloc(sizeof(*result));
    ast_set_data(result, filename);
    ast_set_type(result, NODE_REDIRECT_OUT);
    ast_attach_branch(result, builtin, NULL);
    return (result);
}

t_node      *build_command_1(t_list **token)
{
    t_node  *result;
    t_node  *builtin;
    t_node  *filename;
    char *pathname;

   if ((builtin = build_builtin(token)) == NULL)
       return (NULL);
    if (!check(GREATER, NULL, token))
    {
        ast_delete_node(builtin);
        return (NULL);
    }
    if (!check(WORD, &pathname, token))
    {
        ast_delete_node(builtin);
        return (NULL);
    }
    result = malloc(sizeof(*result));
    ast_set_data(result, pathname);
    ast_set_type(result, NODE_REDIRECT_IN);
    ast_attach_branch(result, builtin, build_filename(token));
    return (result);
}

t_node      *build_filename(t_list **token)
{
    t_list *save;
    t_node *node;

    save = *token;
    if ((*token = save) && (node = build_filename_1(token)))
        return (node);
    if ((*token = save) && (node = build_filename_2(token)))
        return (node);
    if ((*token = save) && (node = build_filename_3(token)))
        return (node);
    return NULL;
}

t_node      *build_filename_1(t_list **token)
{
    t_node *result;
    char *pathname;

    if (!check(GREATER, NULL, token))
        return (NULL);
    if (!check(WORD, &pathname, token))
        return (NULL);
    result = malloc(sizeof(*result));
    ast_set_data(result, pathname);
    ast_set_type(result, NODE_REDIRECT_IN);
    ast_attach_branch(result, NULL, build_filename(token));
    return result;
}

t_node      *build_filename_2(t_list **token)
{
    t_node *result;
    char *pathname;

    if (!check(DGREATER, NULL, token))
        return (NULL);
    if (!check(WORD,&pathname, token))
        return (NULL);
    result = malloc(sizeof(*result));
    ast_set_data(result, pathname);
    ast_set_type(result, NODE_REDIRECT_DIN);
    ast_attach_branch(result, NULL, build_filename(token));
    return result;
}

t_node          *build_filename_3(t_list **token)
{
  return (NULL);
}

t_node        *build_builtin(t_list **token)
{
    return (build_builtin_1(token));
}

t_node          *build_builtin_1(t_list **token)
{
    t_node      *result;
    t_node      *args;
    char        *pathname;

    if (!check(WORD, &pathname, token))
        return (NULL);
    args = build_args(token);
    result = malloc(sizeof(*result));
    ast_set_data(result, pathname);
    ast_set_type(result, NODE_BUILTIN);
    ast_attach_branch(result, args, NULL);
    return (result);
}

t_node        *build_args(t_list **token)
{
    t_node *node;
    t_list *save;

    save = *token;
    if ((*token = save) && (node = build_arg_1(token)))
        return node;
    if ((*token = save) && (node = build_arg_2()))
        return node;
    return NULL;
}

t_node      *build_arg_1(t_list **token)
{
    t_node *args_list;
    t_node *result;
    char *arg;

    if (!check(WORD, &arg, token))
        return NULL;
    args_list = build_args(token);
    result = malloc(sizeof(*result));
    ast_set_data(result, arg);
    ast_set_type(result, NODE_ARG);
    ast_attach_branch(result, args_list, NULL);
    return (result);
}

t_node      *build_arg_2()
{
    return (NULL);
}

int       parse(t_lexer *lexer, t_node **exec_tree)
{
    t_list *tokens;

    tokens = lexer->tokens;
    *exec_tree = build_line(&(tokens));
     if (tokens != NULL)
        return (error_parsing(t_access(tokens)->data));
    // printf("PARSING\n");
    // print_preorder(*exec_tree);
    return (0);
} 