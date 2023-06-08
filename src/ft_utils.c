/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:03:31 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/08 16:52:59 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if the command is a builtin

int	is_builtin(char *cmd)
{
	size_t	len;

	if (!cmd)
		return (-1);
	len = ft_strlen(cmd);
	if (len == ft_strlen("echo") && ft_strncmp("echo", cmd, len) == 0)
		return (ECHO);
	else if (len == ft_strlen("cd") && ft_strncmp("cd", cmd, len) == 0)
		return (CD);
	else if (len == ft_strlen("pwd") && ft_strncmp("pwd", cmd, len) == 0)
		return (PWD);
	else if (len == ft_strlen("export") && ft_strncmp("export", cmd, len) == 0)
		return (EXPORT);
	else if (len == ft_strlen("unset") && ft_strncmp("unset", cmd, len) == 0)
		return (UNSET);
	else if (len == ft_strlen("env") && ft_strncmp("env", cmd, len) == 0)
		return (ENV);
	else if (len == ft_strlen("exit") && ft_strncmp("exit", cmd, len) == 0)
		return (EXIT);
	return (NONE);
}

// Loops through the nodes and frees them

void	free_nodes(t_node *node)
{
	t_node	*temp;

	while (node->next != NULL)
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

void	ft_pexit(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}

// SAME FUNCTION ??

int	ft_perror(char *error_msg)
{
	perror(error_msg);
	return (EXIT_FAILURE);
}
