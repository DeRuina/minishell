/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:21:48 by druina            #+#    #+#             */
/*   Updated: 2023/05/31 07:46:02 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// creates and closes here_docs in case of invalid infile

int	here_doc_invalid_infile(char **array, int i, int **error_here_docs,
		int node_counter)
{
	int	fd;

	fd = 0;
	while (array[i] != '\0')
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

	infile = open("here_doc", O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (infile == -1)
		perror("here_doc file opening problem");
	while (1)
	{
		write(1, "heredoc> ", 10);
		line = get_next_line(0);
		if (line == NULL)
			return (-1);
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		if (write(infile, line, ft_strlen(line)) == -1)
			perror("here_doc writing");
		free(line);
	}
	free(line);
	close(infile);
	infile = reopen_file_and_check("here_doc");
	unlink("here_doc");
	return (infile);
}
