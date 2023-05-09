/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:15:26 by druina            #+#    #+#             */
/*   Updated: 2023/05/09 10:54:53 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//finds the last fd to be an infile or outfile

char	*find_infile_outfile(char **array, char *operator1, char *operator2,
		int i)
{
	char	*last;
	char	*oppsite1;
	char	*oppsite2;

	oppsite2 = "<<";
	oppsite1 = "<";
	if (operator2 == oppsite2)
		oppsite2 = ">>";
	if (operator1 == oppsite1)
		oppsite1 = ">";
	while (array[i] != '\0')
	{
		if (ft_strncmp(array[i], operator2, 2) == 0)
			last = array[i];
		else if (ft_strncmp(array[i], operator1, 1) == 0)
			last = array[i];
		else if (ft_strncmp(operator1, "<", 1) == 0 || ft_strncmp(operator2,
				"<<", 2) == 0)
			if ((ft_strncmp(array[i], oppsite2, 2) == 0) || ft_strncmp(array[i],
					oppsite1, 1) == 0)
				break ;
		i++;
	}
	return (last);
}

// finds the infile fd and opens it

int	get_infile_fd(char **array)
{
	int		fd;
	char	*infile;
	int		i;

	i = 0;
	fd = 0;
	infile = find_infile_outfile(array, "<", "<<", 0);
	while (array[i] != '\0')
	{
		if (infile == array[i])
		{
			if (ft_strncmp(infile, "<<", 2) == 0)
				fd = here_doc(array[i + 1]);
			else
				fd = open(array[i + 1], O_RDONLY);
			if (fd == -1)
				return (perror(array[i + 1]), -1);
			break ;
		}
		i++;
	}
	return (fd);
}

// finds the outfile fd and opens it

int	get_outfile_fd(char **array)
{
	int		fd;
	int		i;
	char	*outfile;

	i = 0;
	fd = 1;
	outfile = find_infile_outfile(array, ">", ">>", 0);
	while (array[i] != '\0')
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
// finds and opens the fd's, returns them in an array

int	*find_and_open_fds(char **array, int *fds, int i, int j)
{
	while (array[i] != '\0')
	{
		if (ft_strncmp(array[i], "<<", 2) == 0
			&& array[i] != find_infile_outfile(array, "<", "<<", 0))
			fds[++j] = here_doc(array[i + 1]);
		else if (ft_strncmp(array[i], "<", 1) == 0
			&& array[i] != find_infile_outfile(array, "<", "<<", 0))
			fds[++j] = open(array[i + 1], O_RDONLY);
		else if (ft_strncmp(array[i], ">>", 2) == 0
			&& array[i] != find_infile_outfile(array, ">", ">>", 0))
			fds[++j] = open(array[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0664);
		else if (ft_strncmp(array[i], ">", 1) == 0
			&& array[i] != find_infile_outfile(array, ">", ">>", 0))
			fds[++j] = open(array[i + 1], O_CREAT | O_WRONLY | O_TRUNC, 0664);
		if (fds[j] == -1 && (ft_strncmp(array[i], "<<", 2) == 0
				|| ft_strncmp(array[i], "<", 1) == 0))
			if (array[i] != find_infile_outfile(array, "<", "<<", 0))
				perror(array[i + 1]);
		i++;
	}
	fds[0] = get_infile_fd(array);
	fds[fd_amount(array) - 1] = get_outfile_fd(array);
	return (fds);
}
// finds the amount of operators for the allocation

int	fd_amount(char **array)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (array[i] != '\0')
	{
		if (ft_strncmp(array[i], "<<", 2) == 0)
			count++;
		else if (ft_strncmp(array[i], ">>", 2) == 0)
			count++;
		else if (ft_strncmp(array[i], "<", 1) == 0)
			count++;
		else if (ft_strncmp(array[i], ">", 1) == 0)
			count++;
		i++;
	}
	return (count);
}
// allocates int array and returns it with all the fd's

int	*ft_fd_handler(char **array)
{
	int	i;
	int	*fds;

	i = 0;
	fds = (int *)malloc(sizeof(int) * fd_amount(array));
	if (!fds)
		return (NULL);
	fds = find_and_open_fds(array, fds, 0, 0);
	return (fds);
}
