/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:13:48 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/26 14:48:45 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	close_pipes()

void	ft_child(t_node *node, t_vec envv)
{
	if (node->infile != 0)
		if (dup2(node->infile, STDIN_FILENO) < 0)
			perror("ft_child: dup2");
	if (node->outfile != 1)
		if (dup2(node->outfile, STDOUT_FILENO) < 0)
			perror("ft_child: dup2");
	// close_pipes();
	if (execve(node->full_cmd[0], node->full_cmd, ft_strenv(envv)) < 0)
		perror(node->full_cmd[0]);
}
// void close_parents_pipes(t_node *node)
// {
// 	node = node->next;
// 	while (node)
// 	{
// 		close(node->infile);
// 		close(node->outfile);
// 		node = node->next;
// 	}
// 	close(node->infile);
// 	close(node->outfile);
// }

int	ft_executor(t_node *node, t_vec envv)
{
	int i;

	i = 0;
	while (node)
	{
		node->pid = fork();
		if (node->pid == -1)
			perror("ft_executor: fork");
		if (node->pid == 0)
			ft_child(node, envv);

		if (i != 0)
		{
			close(node->infile);
			close(node->outfile);
		}
		if (node->pid > 0)
		{
			i++;
			node = node->next;
		}
	}
	return (0);
}
