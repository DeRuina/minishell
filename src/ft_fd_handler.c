/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:15:26 by druina            #+#    #+#             */
/*   Updated: 2023/05/29 15:41:58 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				fd = open(array[i + 1], O_CREAT | O_RDWR | O_APPEND, 0664);
			else
				fd = open(array[i + 1], O_CREAT | O_RDWR | O_TRUNC, 0664);
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

int	get_infile_fd(char **array, int *error_flag)
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
				fd = open(array[i + 1], O_RDWR);
			if (fd == -1 && (*error_flag) == 0)
				return ((*error_flag) = 1, here_doc_invalid_infile(array, i,
						fd));
			if (ft_strncmp(infile, "<<", 2) == 0 && (*error_flag) == 0)
				fd = here_doc(array[i + 1]);
			if (fd == -1)
				perror(array[i + 1]);
		}
		i++;
	}
	return (fd);
}

// checks for invalid file before the infile, open here_docs if invalid

void	check_for_invalid_file_before_infile(char **array)
{
	int		i;
	char	*infile;
	int		access_check;

	i = 0;
	access_check = 0;
	infile = find_last_infile(array);
	while (array[i] != '\0' && *array[i] != '|')
	{
		if (array[i] == infile)
			return ;
		if (ft_strncmp(array[i], "<", 1) == 0 && ft_strlen(array[i]) == 1)
			access_check = access(array[i + 1], R_OK);
		if (access_check == -1)
		{
			here_doc_invalid_infile(array, i, access_check);
			return ;
		}
		i++;
	}
}

// Returns the infile and outfile, creates any neccessary fds.

t_node	*ft_fd_handler(char **array, int *error_flag, t_node *node)
{
	check_for_invalid_file_before_infile(array);
	node->infile = get_infile_fd(array, error_flag);
	node->outfile = get_outfile_fd(array);
	find_and_open_fds(array);
	return (node);
}
