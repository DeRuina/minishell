/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:03:31 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/25 16:51:55 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_a_builtin(char *cmd)
{
	if (ft_strncmp("echo", cmd, ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp("cd", cmd, ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp("pwd", cmd, ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp("export", cmd, ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp("unset", cmd, ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp("env", cmd, ft_strlen(cmd)) == 0)
		return (1);
	else if (ft_strncmp("exit", cmd, ft_strlen(cmd)) == 0)
		return (1);
	else
		return (0);
}

void free_nodes(t_node *node)
{
	t_node *temp;
	while(node->next != NULL)
	{
		temp = node;
		if (node->full_cmd)
			free_2d(node->full_cmd);
		node = node->next;
		free(temp);
	}
	if (node->full_cmd)
		free_2d(node->full_cmd);
	free(node);
}

int	ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

void	ft_pexit(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}
