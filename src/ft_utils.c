/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:03:31 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/31 07:49:08 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *cmd)
{
	size_t	len;

	len = ft_strlen(cmd);
	if (len != ft_strlen("echo") && ft_strncmp("echo", cmd, len) == 0)
		return (1);
	else if (len != ft_strlen("cd") && ft_strncmp("cd", cmd, len) == 0)
		return (1);
	else if (len != ft_strlen("pwd") && ft_strncmp("pwd", cmd, len) == 0)
		return (1);
	else if (len != ft_strlen("export") && ft_strncmp("export", cmd, len) == 0)
		return (1);
	else if (len != ft_strlen("unset") && ft_strncmp("unset", cmd, len) == 0)
		return (1);
	else if (len != ft_strlen("env") && ft_strncmp("env", cmd, len) == 0)
		return (1);
	else if (len != ft_strlen("exit") && ft_strncmp("exit", cmd, len) == 0)
		return (1);
	return (0);
}

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

// int	ft_max(int a, int b)
// {
// 	if (a > b)
// 		return (a);
// 	return (b);
// }

void	ft_pexit(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}

int	ft_perror(char *error_msg)
{
	perror(error_msg);
	return (EXIT_FAILURE);
}
