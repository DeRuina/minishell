/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:15:26 by druina            #+#    #+#             */
/*   Updated: 2023/05/22 13:31:55 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//finds the last outfile fd

char	*find_last_outfile(char **array)
{
	char	*last;
	int		i;

	i = 0;
	last = NULL;
	while (array[i] != '\0' && *array[i] != '|')
	{
		if (ft_strncmp(array[i], ">>", 2) == 0)
			last = array[i];
		else if (ft_strncmp(array[i], ">", 1) == 0)
			last = array[i];
		i++;
	}
	return (last);
}

// finds and return the outfile fd

int	get_outfile_fd(char **array)
{
	int		fd;
	int		i;
	char	*outfile;

	i = 0;
	fd = 1;
	outfile = find_last_outfile(array);
	while (array[i] != '\0' && *array[i] != '|')
	{
		if (outfile == array[i])
		{
			if (ft_strncmp(outfile, ">>", 1) == 0)
				fd = open(array[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0664);
			else
				fd = open(array[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
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
	while (array[i] != '\0' && *array[i] != '|')
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

int	get_infile_fd(char **array, int *here_doc_case_of_error)
{
	int		fd;
	char	*infile;
	int		i;

	i = 0;
	fd = 0;
	infile = find_last_infile(array);
	while (array[i] != '\0' && *array[i] != '|')
	{
		if (infile == array[i])
		{
			if (ft_strncmp(infile, "<", 1) == 0 && ft_strlen(infile) == 1)
				fd = open(array[i + 1], O_RDONLY);
			if (fd == -1 && (*here_doc_case_of_error) == 0)
				return ((*here_doc_case_of_error) = 1,
					here_doc_if_invalid_infile(array, i, fd));
			if (ft_strncmp(infile, "<<", 2) == 0
				&& (*here_doc_case_of_error) == 0)
				fd = here_doc(array[i + 1]);
			if (fd == -1)
				perror(array[i + 1]);
		}
		i++;
	}
	return (fd);
}

// Returns the infile and outfile, creates any neccessary fds.

t_node	*ft_fd_handler(char **array, int *here_doc_case_of_error, t_node *node)
{
	node->infile = get_infile_fd(array, here_doc_case_of_error);
	node->outfile = get_outfile_fd(array);
	find_and_open_fds(array);
	return (node);
}
