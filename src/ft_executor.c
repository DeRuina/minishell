/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:13:48 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/29 09:25:21 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	ft_child(t_node *node, t_vec envv)
{
	if (node->infile != 0)
		if (dup2(node->infile, STDIN_FILENO) < 0)
			ft_pexit("ft_child: dup2");
	if (node->infile != 0)
		close (node->infile);
	if (node->outfile != 1)
		if (dup2(node->outfile, STDOUT_FILENO) < 0)
			ft_pexit("ft_child: dup2");
	if (node->outfile != 1)
		close (node->outfile);
	if (execve(node->full_cmd[0], node->full_cmd, ft_strenv(envv)) < 0)
		ft_pexit(node->full_cmd[0]);
}

int	ft_executor(t_node *node, t_vec envv)
{

	while (node)
	{
		node->pid = fork();
		if (node->pid == -1)
			perror("ft_executor: fork");
		if (node->pid == 0)
			ft_child(node, envv);
		if (node->infile != 0)
			close(node->infile);
		if (node->outfile != 1)
			close(node->outfile);
		if (node->pid > 0)
			node = node->next;
	}
	return (1);
}
