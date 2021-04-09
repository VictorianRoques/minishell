/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmanetti <fmanetti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:14:59 by viroques          #+#    #+#             */
/*   Updated: 2021/04/08 01:33:46 by fmanetti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			return_parse(t_list *tokens, t_node **exec_tree, \
	t_lexer *lexer, t_main *m)
{
	if (tokens != NULL || !exec_tree)
	{
		ft_putstr_fd("minish: ", STDERR_FILENO);
		ft_putstr_fd(SYNTAX_ERROR, STDERR_FILENO);
		ft_putstr_fd(" near unexpected token: `", STDERR_FILENO);
		if (tokens != NULL)
			ft_putstr_fd(t_access_tok(tokens)->data, STDERR_FILENO);
		else if (!exec_tree)
			ft_putstr_fd(t_access_tok(lexer->tokens)->data, STDERR_FILENO);
		ft_putstr_fd("'\n", STDERR_FILENO);
		m->exit_status = 258;
		free_lexer(lexer);
		ast_delete_node(*exec_tree);
		return (0);
	}
	free_lexer(lexer);
	m->exec_tree = *exec_tree;
	return (1);
}

void		count_closing_parenthese(t_list **tokens, t_lexer *lexer)
{
	t_list	*tok;
	t_list	*prev;
	int		close;
	int		open;

	tok = lexer->tokens;
	open = 0;
	close = 0;
	while (tok)
	{
		if (t_access_tok(tok)->type == CLOSE_PAR)
			close++;
		if (t_access_tok(tok)->type == OPEN_PAR)
			open++;
		prev = tok;
		tok = tok->next;
	}
	if (close > open)
	{
		*tokens = prev;
		t_access_tok(*tokens)->type = OPEN_PAR;
	}
}

void		sort_parenthese(t_node *exec_tree, t_list **tokens,
								t_lexer *lexer)
{
	t_node *node;

	node = exec_tree;
	while (node)
	{
		if (node->left && node->left->parenthese)
		{
			if (node->right && node->right->left)
				node->right->left->parenthese = node->left->parenthese;
		}
		node = node->right;
	}
	count_closing_parenthese(tokens, lexer);
}

int			call_multiligne(t_lexer *lexer, t_list *tokens)
{
	t_list	*check;
	int		type;

	check = lexer->tokens;
	if (tokens != NULL && !tokens->next && tokens != lexer->tokens)
	{
		type = t_access_tok(tokens)->type;
		if (type == DPIPE || type == DAMPERSTAND || type == PIPE
			|| type == CLOSE_PAR)
		{
			while (check)
			{
				if (check->next && check->next == tokens)
				{
					if (t_access_tok(check)->type == SEMICOLON
						|| t_access_tok(check)->type == OPEN_PAR)
						return (0);
				}
				check = check->next;
			}
			return (1);
		}
	}
	return (0);
}

int			parse(t_lexer **lexer, t_node **exec_tree, char **s, t_main *m)
{
	t_list	*tokens;

	tokens = (*lexer)->tokens;
	*exec_tree = build_line(&(tokens), m);
	sort_parenthese(*exec_tree, &tokens, *lexer);
	if (call_multiligne(*lexer, tokens))
	{
		if ((*s = multilines(m, *s, t_access_tok(tokens)->type)))
		{
			free_lexer(*lexer);
			*lexer = build_lexer(m, s);
			ast_delete_node(*exec_tree);
			return (parse(lexer, exec_tree, s, m));
		}
		else
			return (0);
	}
	return (return_parse(tokens, exec_tree, *lexer, m));
}
