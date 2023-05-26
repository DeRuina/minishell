/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:13:48 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/26 10:29:48 by tspoof           ###   ########.fr       */
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

// void	close_pipes(t_node *node)
// {
// 	node = node->next;
// 	while (node)
// 	{
// 		printf("infile (%d)\noutfile (%d)\n", node->infile, node->outfile);
// 		if (node->infile != 0)
// 			if (close(node->infile) < 0)
// 				ft_pexit("close_pipes: infile: close");
// 		if (node->outfile != 1)
// 			if (close(node->outfile) < 0)
// 				ft_pexit("close_pipes: outfile: close");
// 		node = node->next;
// 	}
// }

int	ft_child(t_node *node, t_vec envv)
{
	if (node->infile != 0)
		if (dup2(node->infile, STDIN_FILENO) < 0)
			ft_pexit("ft_child: dup2");
	if (node->outfile != 1)
		if (dup2(node->outfile, STDOUT_FILENO) < 0)
			ft_pexit("ft_child: dup2");
	// close_pipes(node);
	// close(node->infile);
	// close(node->outfile);
	printf("hehe\n");
	// if (close(node->infile) < 0)
	// 	ft_pexit("close_pipes: infile: close");
	// if (close(node->outfile) < 0)
	// 	ft_pexit("close_pipes: outfile: close");
	if (execve(node->full_cmd[0], node->full_cmd, ft_strenv(envv)) < 0)
		ft_pexit(node->full_cmd[0]);
	return (1);
}

int	ft_executor(t_node *node, t_vec envv)
{
	while (node)
	{
		printf("hii\n");
		node->pid = fork();
		if (node->pid == -1)
			ft_pexit("Fork");
		if (node->pid == 0)
			return (ft_child(node, envv));
			// return (ft_child(node, env));
		else
			node = node->next;
	}
	return (1);
}
