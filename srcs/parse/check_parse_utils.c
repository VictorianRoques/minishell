/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 15:14:42 by viroques          #+#    #+#             */
/*   Updated: 2021/04/07 15:27:17 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			check(t_token_type tok_type, char **bufferptr, t_list **token)
{
	if (*token == NULL)
		return (0);
	if (t_access_tok(*token)->type == tok_type)
	{
		if (bufferptr != NULL)
			if (!(*bufferptr = ft_strdup(t_access_tok(*token)->data)))
				return (-1);
		*token = (*token)->next;
		return (1);
	}
	*token = (*token)->next;
	return (0);
}

t_node		*check_closing_par(int par, t_list **token, t_node *node)
{
	int		close_par;

	close_par = check_par(CLOSE_PAR, token);
	if ((close_par && !par) || (!close_par && par))
		node->parenthese = 1;
	return (node);
}

int			check_par(t_token_type tok_type, t_list **token)
{
	if (!token || !*token)
		return (0);
	if (t_access_tok(*token)->type == tok_type)
	{
		*token = (*token)->next;
		return (1);
	}
	return (0);
}

t_node		*check_line_closing_par(t_list **token, t_node *node,
										t_main *m, int par)
{
	check_par(CLOSE_PAR, token);
	if (par)
	{
		if ((check_par(DPIPE, token))
			|| (check_par(DAMPERSTAND, token))
			|| (check_par(SEMICOLON, token)))
			ast_attach_right(node->right, build_line(token, m));
	}
	return (node);
}

int			check_line_open_par(t_list **token)
{
	t_list		*tmp;

	tmp = NULL;
	if (!token || !*token)
		return (0);
	if (t_access_tok(*token)->type == OPEN_PAR)
	{
		if ((*token)->next)
			tmp = (*token)->next;
		if (tmp && t_access_tok(tmp)->type == OPEN_PAR)
		{
			*token = (*token)->next;
			return (1);
		}
	}
	return (0);
}
