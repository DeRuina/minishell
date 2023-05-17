/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:06:54 by druina            #+#    #+#             */
/*   Updated: 2023/05/17 12:19:52 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int num_of_pipes(char **array)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while (array[i] != '\0')
		if (ft_strncmp(array[i++], "|", 1))
			len++;
	return(len);
}

int	**allocate_pipes(char **array)
{
	int	**pipe_nb;
	int	i;
	int	len;

	len = num_of_pipes(array);
	i = 0;
	pipe_nb = ft_calloc(len, sizeof(int *));
	if (!pipe_nb)
		return (NULL);
	while (i < len)
	{
		pipe_nb[i] = ft_calloc(2, sizeof(int));
		if (!pipe_nb[i])
		{
			while (--i != -1)
				free(pipe_nb[i]);
			free(pipe_nb);
			return (NULL);
		}
		i++;
	}
	return (pipe_nb);
}

int **piper(char **array)
{
	int **pipe_nb;
	int len;
	int i;

	i = 0;
	pipe_nb = allocate_pipes(array);
	if (pipe_nb == NULL)
		return(NULL);
	len = num_of_pipes(array);
	while (i <= len)
	{
		if(pipe(pipe_nb[i]) == -1)
			perror("pipe i :");
		exit(EXIT_FAILURE);
	}
	return(pipe_nb);
}
