/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viroques <viroques@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 23:06:50 by viroques          #+#    #+#             */
/*   Updated: 2021/04/06 23:09:18 by viroques         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			len_empty_tab(char **tab)
{
	int		i;
	int		nb;

	nb = 0;
	i = 0;
	while (tab[i])
	{
		if (tab[i][0] != '\0')
			nb++;
		i++;
	}
	return (nb);
}

static char			**remove_empty_tab(char **tab, t_main *m)
{
	int		i;
	int		nb;
	char	**new;

	i = 0;
	nb = len_empty_tab(tab);
	if (!(new = malloc(sizeof(char *) * (nb + 1))))
		malloc_error(m, NULL, NO_ERRNO);
	i = 0;
	nb = 0;
	while (tab[i])
	{
		if (tab[i][0] != '\0')
		{
			new[nb] = ft_strdup(tab[i]);
			nb++;
		}
		i++;
	}
	new[nb] = NULL;
	ft_free_array(tab);
	return (new);
}

static char			**check_empty_case(char **tab, t_main *m)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		if (tab[i][0] == '\0')
			return (remove_empty_tab(tab, m));
		i++;
	}
	return (tab);
}

char				**create_cmd_table(t_node *root, t_main *m)
{
	t_node	*node;
	char	**args;
	int		nbcmd;

	nbcmd = 0;
	node = root;
	while (node)
	{
		nbcmd++;
		node = node->left;
	}
	if (!(args = malloc(sizeof(char *) * (nbcmd + 1))))
		return (NULL);
	node = root;
	nbcmd = 0;
	while (node)
	{
		args[nbcmd] = change_data(node->data, m);
		node = node->left;
		nbcmd++;
	}
	args[nbcmd] = NULL;
	return (check_empty_case(args, m));
}
