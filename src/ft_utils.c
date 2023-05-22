/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:03:31 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/22 16:24:08 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_nodes(t_node *node)
{
	t_node *temp;
	while(node->next != NULL)
	{
		temp = node;
		free_2d(node->full_cmd);
		node = node->next;
		free(temp);
	}
	free_2d(node->full_cmd);
	free(node);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}
