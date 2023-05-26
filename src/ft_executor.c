/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:13:48 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/26 15:32:31 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void close_pipes(t_node *head, int infile, int outfile)
{

	while (head)
	{
		if (&infile == &head->infile)
			close(head->infile);
		if (&outfile == &head->outfile)
			close(head->outfile);
		head = head->next;
	}
	if (&infile == &head->infile)
			close(head->infile);
		if (&outfile == &head->outfile)
			close(head->outfile);
}

void	ft_child(t_node *head ,t_node *node, t_vec envv)
{
	close_pipes(head, node->infile, node->outfile);
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
	t_node *head;
	int i;

	i = 0;
	head = node;
	while (node)
	{
		node->pid = fork();
		if (node->pid == -1)
			perror("ft_executor: fork");
		if (node->pid == 0)
			ft_child(head ,node, envv);
		if (node->pid > 0)
		{
			i++;
			node = node->next;
		}
	}
	return (1);
}
