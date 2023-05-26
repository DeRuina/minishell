/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:13:48 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/26 11:47:45 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	close_pipes()

void	ft_child(t_node *node, t_vec envv)
{
	if (node->infile != 0)
		if (dup2(node->infile, STDIN_FILENO) < 0)
			ft_pexit("ft_child: dup2");
	if (node->outfile != 1)
		if (dup2(node->outfile, STDOUT_FILENO) < 0)
			ft_pexit("ft_child: dup2");
	// close_pipes();
	if (execve(node->full_cmd[0], node->full_cmd, ft_strenv(envv)) < 0)
		ft_pexit(node->full_cmd[0]);
}

int	ft_executor(t_node *node, t_vec envv)
{
	while (node)
	{
		node->pid = fork();
		if (node->pid == -1)
			ft_pexit("ft_executor: fork");
		if (node->pid == 0)
			ft_child(node, envv);
		close(node->infile);
		close(node->outfile);
		if (node->pid > 0)
			node = node->next;
	}
	return (1);
}
