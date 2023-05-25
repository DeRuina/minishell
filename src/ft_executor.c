/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:13:48 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/25 17:13:47 by tspoof           ###   ########.fr       */
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

void	close_pipes(int process, int **pipes);

int	ft_child(t_node *node, t_vec envv)
{
	if (dup2(node->infile, STDIN_FILENO) < 0)
		ft_pexit("dup2: ");
	if (dup2(STDOUT_FILENO, node->outfile) < 0)
		ft_pexit("dup2: ");
	// close_pipes();
	// close(node->infile);
	// close(node->outfile);
	if (execve(node->full_cmd[0], node->full_cmd, ft_strenv(envv)) < 0)
		ft_pexit(node->full_cmd[0]);
	return (1);
}

int	ft_executor(t_node *node, t_vec envv)
{
	while (node)
	{
		node->pid = fork();
		if (node->pid == -1)
			ft_pexit("Fork: ");
		if (node->pid == 0)
			return (ft_child(node, envv));
			// return (ft_child(node, env));
		else
			node = node->next;
	}
	return (1);
}
