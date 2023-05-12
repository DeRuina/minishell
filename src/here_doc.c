/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 09:21:48 by druina            #+#    #+#             */
/*   Updated: 2023/05/12 13:22:35 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creates and closes here_docs in case of invalid infile

void	here_doc_if_invalid_infile(char **array, int i)
{
	int	fd;

	fd = 0;
	while (array[i] != '\0')
	{
		if (ft_strncmp(array[i], "<<", 2) == 0)
			fd = here_doc(array[i + 1]);
		if (fd != 0)
			close(fd);
		i++;
	}
}

// reads from 0 and creates a here_doc

int	here_doc(char *delimiter)
{
	int		infile;
	char	*line;

	infile = open("here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0664);
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
		write(infile, line, ft_strlen(line));
		free(line);
	}
	free(line);
	unlink("here_doc");
	return (infile);
}
