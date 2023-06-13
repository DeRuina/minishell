/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:21:48 by druina            #+#    #+#             */
/*   Updated: 2023/06/13 15:34:59 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

// Reopens the here_doc to reset file "cursor"

int	reset_cursor(char *name)
{
	int	infile;

	infile = open(name, O_RDWR);
	if (infile == -1)
	{
		unlink(".here_doc.tmp");
		perror(".here_doc.tmp");
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
	int		fd;
	char	*line;

	fd = open(".here_doc.tmp", O_CREAT | O_RDWR | O_TRUNC, 0664);
	if (fd == -1)
		perror("here_doc file opening problem");
	g_exit_status = 0;
	while (g_exit_status != 1)
	{
		printf("exit status: %d\n", g_exit_status);
		line = readline("> ");
		if (!line || g_exit_status)
			break ;
		if (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
			break ;
		if (write(fd, line, ft_strlen(line)) == -1 || write(fd, "\n", 1) == -1)
			perror("here_doc writing");
		free(line);
		line = NULL;
	}
	free(line);
	close(fd);
	fd = reset_cursor(".here_doc.tmp");
	unlink(".here_doc.tmp");
	return (fd);
}
