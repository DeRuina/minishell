/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:21:48 by druina            #+#    #+#             */
/*   Updated: 2023/06/09 13:46:00 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Reopens the here_doc to reset file "cursor"

int	reopen_file_and_check(char *name)
{
	int	infile;

	infile = open(name, O_RDWR);
	if (infile == -1)
	{
		unlink("here_doc");
		perror("here_doc");
	}
	return (infile);
}

// creates here_docs before error message in case of invalid infile

int	here_doc_invalid_infile(char **array, int i, int **error_here_docs,
		int node_counter)
{
	int	fd;

	fd = 0;
	while (array[i] != 0)
	{
		if (ft_strncmp(array[i], "<<", 2) == 0)
		{
			fd = here_doc(array[i + 1]);
			if (array[i] == find_last_infile(&array[i]))
				(*error_here_docs)[node_counter] = fd;
			else
				close(fd);
		}
		if (ft_strncmp(array[i], "|", 1) == 0 && ft_strlen(array[i]) == 1)
			node_counter++;
		i++;
	}
	return (-1);
}

// reads from 0 and creates a here_doc

int	here_doc(char *delimiter)
{
	int		infile;
	char	*line;

	infile = open(".here_doc.tmp", O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (infile == -1)
		perror("here_doc file opening problem");
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		if (write(infile, line, ft_strlen(line)) == -1
			|| write(infile, "\n", 1) == -1)
			perror("here_doc writing");
		free(line);
	}
	free(line);
	close(infile);
	infile = reopen_file_and_check(".here_doc.tmp");
	unlink(".here_doc.tmp");
	return (infile);
}
