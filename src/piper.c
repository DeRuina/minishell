/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:06:54 by druina            #+#    #+#             */
/*   Updated: 2023/06/08 16:27:58 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Frees the allocated pipes

void	free_pipes(int **pipe_nbr, char *array)
{
	int	len;
	int	i;

	i = 0;
	len = num_of_pipes(array);
	if (len == 0)
		return ;
	while (i < len)
	{
		free(pipe_nbr[i]);
		i++;
	}
	free(pipe_nbr);
}

// Loops through the nodes and checks if a pipe is needed for the processes,
// changes the infile and outfile to the in end and out end of the pipe. 

void	change_infile_outfile_to_pipes(t_node *node, int **pipe_nbr)
{
	int	write_to_pipe;
	int	i;

	i = 0;
	write_to_pipe = 0;
	while (node->next != NULL)
	{
		if (node->infile == 0 && write_to_pipe == 1)
		{
			node->infile = pipe_nbr[i - 1][IN];
			write_to_pipe = 0;
		}
		if (node->outfile == 1)
		{
			node->outfile = pipe_nbr[i][OUT];
			write_to_pipe = 1;
			i++;
		}
		node = node->next;
	}
	if (node->infile == 0 && write_to_pipe == 1)
		node->infile = pipe_nbr[i - 1][IN];
}

// Indexes the strings and checks for number of pipes

int	num_of_pipes(char *array)
{
	int	i;
	int	len;

	len = 0;
	i = 0;
	while (array[i] != '\0')
	{
		if (array[i] == '|')
			len++;
		i++;
	}
	return (len);
}

// Allocates 2D int array for the number of pipes needed

int	**allocate_pipes(char *array)
{
	int	**pipe_nbr;
	int	i;
	int	len;

	len = num_of_pipes(array);
	if (len == 0)
		return (NULL);
	i = 0;
	pipe_nbr = ft_calloc(len, sizeof(int *));
	if (!pipe_nbr)
		return (NULL);
	while (i < len)
	{
		pipe_nbr[i] = ft_calloc(2, sizeof(int));
		if (!pipe_nbr[i])
		{
			while (--i != -1)
				free(pipe_nbr[i]);
			return (NULL);
		}
		i++;
	}
	return (pipe_nbr);
}

// Creates 2D int array of allocated pipes. Loops through the nodes and changes 
// the infile and outfile to be the IN end and OUT end of the pipe if needed.

int	**piper(char *array, t_node *node)
{
	int	**pipe_nbr;
	int	len;
	int	i;

	i = 0;
	pipe_nbr = allocate_pipes(array);
	if (pipe_nbr == NULL)
		return (NULL);
	len = num_of_pipes(array);
	while (i < len)
	{
		if (pipe(pipe_nbr[i]) == -1)
			ft_pexit("pipe :");
		i++;
	}
	change_infile_outfile_to_pipes(node, pipe_nbr);
	return (pipe_nbr);
}
