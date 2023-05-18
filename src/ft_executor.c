/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:13:48 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/17 14:38:41 by tspoof           ###   ########.fr       */
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

int	ft_executor(t_node *node)
{
	while (node)
	{
		node->pid = fork();
		if (node->pid == -1)
		{
			perror("Fork: ");
			exit (1); // check this
		}
		if (node->pid == 0)
			return (1); // child labour
		else
			node = node->next;
	}
	return (0);
}
