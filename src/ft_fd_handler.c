/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:15:26 by druina            #+#    #+#             */
/*   Updated: 2023/06/20 14:17:36 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// finds and return the outfile fd

int	get_outfile_fd(char **array, char *outfile , t_node *node)
{
	int	fd;
	int	i;

	i = 0;
	fd = 1;
	while (array[i] != 0 && *array[i] != '|')
	{
		if (outfile == array[i])
		{
			if (ft_strncmp(outfile, ">>", 2) == 0)
				fd = open(array[i + 1], O_CREAT | O_RDWR | O_APPEND, 0664);
			else
			{
				fd = open(array[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0664);
				node->filename = array[i + 1];
			}
			if (fd == -1)
				return (perror(array[i + 1]), -1);
			break ;
		}
		i++;
	}
	return (fd);
}

//finds the last infile fd

char	*find_last_infile(char **array)
{
	char	*last;
	int		i;

	last = NULL;
	i = 0;
	while (array[i] != 0 && *array[i] != '|')
	{
		if (ft_strncmp(array[i], "<<", 2) == 0)
			last = array[i];
		else if (ft_strncmp(array[i], "<", 1) == 0)
			last = array[i];
		i++;
	}
	return (last);
}

// finds and return the infile fd

int	get_infile_fd(char **array, int error_here_doc, char *infile)
{
	int	fd;
	int	i;

	i = 0;
	fd = 0;
	while (array[i] != 0 && *array[i] != '|')
	{
		if (infile == array[i])
		{
			if (ft_strncmp(infile, "<", 1) == 0 && ft_strlen(infile) == 1)
				fd = open(array[i + 1], O_RDWR);
			if (ft_strncmp(infile, "<<", 2) == 0)
			{
				if (error_here_doc != 0)
					fd = error_here_doc;
				else
					fd = here_doc(array[i + 1]);
			}
			if (fd == -1)
				return (perror(array[i + 1]), -1);
		}
		i++;
	}
	return (fd);
}

// checks for invalid file before the infile, open here_docs if invalid

int	check_for_invalid_file_before_infile(char **array, int **error_here_docs,
		int node_counter)
{
	int	i;
	int	access_check;

	i = 0;
	access_check = 0;
	while (array[i] != 0 && *array[i] != '|')
	{
		if (ft_strncmp(array[i], "<", 1) == 0 && ft_strlen(array[i]) == 1)
			access_check = access(array[i + 1], R_OK);
		if (access_check == -1)
		{
			here_doc_invalid_infile(array, i, error_here_docs, node_counter);
			perror(array[i + 1]);
			return (-1);
		}
		i++;
	}
	return (0);
}

// Returns the infile and outfile, creates any neccessary fds.

t_node	*ft_fd_handler(char **array, t_node *node, int *error_here_docs,
		int node_counter)
{
	char	*infile;
	char	*outfile;

	infile = find_last_infile(array);
	outfile = find_last_outfile(array);
	if (check_for_invalid_file_before_infile(array, &error_here_docs,
			node_counter) == -1)
		node->infile = -1;
	else
		node->infile = get_infile_fd(array, error_here_docs[node_counter],
				infile);
	node->outfile = get_outfile_fd(array, outfile, node);
	find_and_open_fds(array);
	return (node);
}
