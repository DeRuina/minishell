/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:13:48 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/22 16:26:47 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// typedef struct node
// {
// 	char		**full_cmd;
// 	char		*path_name;
// 	int			pid;
// 	int			infile;
// 	int			outfile;
// 	struct node	*next;
// }				t_node;

void	close_unused_pipes(int process, int **pipes);

// int	ft_child(t_node *node, t_vec env)
int	ft_child(t_node *node)
{
	(void)node;
	// close_unused_pipes();
	// if (dup2(node->infile, STDIN_FILENO) < 0)
	// 	ft_pexit("dup2: ");
	// if (dup2(STDOUT_FILENO, node->outfile) < 0)
	// 	ft_pexit("dup2: ");
	// execve(ft_get_exec_path(env, node->full_cmd[0]), node->full_cmd, NULL);
	return (1);
}

// int	ft_executor(t_node *node, t_vec env)
int	ft_executor(t_node *node)
{
	while (node)
	{
		node->pid = fork();
		if (node->pid == -1)
			ft_pexit("Fork: ");
		if (node->pid == 0)
			return (ft_child(node));
			// return (ft_child(node, env));
		else
			node = node->next;
	}
	return (1);
}
