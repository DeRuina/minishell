/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:21:48 by druina            #+#    #+#             */
/*   Updated: 2023/05/30 15:09:36 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// error message in case of -1 fd and here_doc after

void	error_fd(int fd, char *array, char *error)
{
	if (fd == -1)
	{
		write(2, array, ft_strlen(array));
		write(2, ": ", 2);
		write(2, error, ft_strlen(error));
		write(2, "\n", 1);
	}
}

int	reopen_file_and_check(char *name)
{
	int infile;

	infile = open(name, O_RDWR);
	if (infile == -1)
	{
		unlink("here_doc");
		perror("here_doc");
	}
	return (infile);
}

// creates and closes here_docs in case of invalid infile

int	here_doc_invalid_infile(char **array, int i, int bad_fd, int **error_here_docs)
{
	int		fd;
	char	*error_var;
	char	*error;
	int		j;

	error = strerror(errno);
	error_var = array[i + 1];
	fd = 0;
	j = 0;
	while (array[i] != '\0')
	{
		if (ft_strncmp(array[i], "<<", 2) == 0)
		{
			fd = here_doc(array[i + 1]);
			if (array[i] == find_last_infile(&array[i]))
				(*error_here_docs)[j] = fd;
			else
				close(fd);
		}
		if (ft_strncmp(array[i], "|", 1) == 0 && ft_strlen(array[i]) == 1)
			j++;
		i++;
	}
	error_fd(bad_fd, error_var, error);
	return(-1);
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
