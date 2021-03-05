/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 16:17:01 by viroques          #+#    #+#             */
/*   Updated: 2021/03/04 19:26:32 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void    handle_redirection(t_node *node_redirect)
{
    int fdout;
    int fdin;
    t_node *redirect;
    
    redirect = node_redirect;
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
        else if (redirect->type == NODE_REDIRECT_OVER)
        {
            fdout = open(redirect->data, O_RDWR | O_CREAT | O_APPEND);
            dup2(fdout, 1);
            close(fdout);
        }
        redirect = redirect->right;
    }
}