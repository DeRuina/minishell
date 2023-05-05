/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fd_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 10:15:26 by druina            #+#    #+#             */
/*   Updated: 2023/05/05 15:03:04 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_infile(char *array, char *filename)
{
	int infile;

	infile = 0;
	if (ft_strncmp(array, "<", 1) == 0)
	{
		infile = open(filename, O_RDONLY);
		if (infile == -1)
		perror("Error: ");
	}
	return (infile);
}


int *find_and_open_fds(char **array, int *fds)
{
	int i;
	int fd;
	int j;

	i = 0;
	fd = 0;
	j = 0;
	while (array[i] != '\0')
	{
		if (ft_strncmp(array[i], "<", 1) == 0)
			{
				if (fd == 0)
					fd = find_infile(array[i],array[i + 1]);
				else
					fd = open(array[i + 1], O_RDONLY);
				if (fd == -1)
					perror("Error: ");
				fds[j] = fd;
				j++;
			}
		else if (t_strncmp(array[i], ">", 1) == 0)
		{
			if (array[i + 2] )
		}


	}
}

int fd_amount(char **array, char op)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (array[i] != '\0')
	{
		if (ft_strncmp(array[i], "<", 1) == 0 && (op == '<' || op == '*'))
			count++;
		else if ((ft_strncmp(array[i], "<<", 2) == 0) && (op == '2' || op == '*'))
			count++;
		else if ((ft_strncmp(array[i], ">", 1) == 0) && (op == '>' || op == '*'))
			count++;
		else if ((ft_strncmp(array[i], ">>", 2) == 0)&& (op == '4' || op == '*'))
			count++;
		else
			i++;
	}
	return(count);
}

int *ft_fd_handler(char **array)
{
	int i;
	int *fds;

	i = 0;
	fds = (int *)malloc(sizeof(int) * fd_amount(array, '*'));
	if (!fds)
		return(NULL);




}
