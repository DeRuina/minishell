/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piper.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 10:06:54 by druina            #+#    #+#             */
/*   Updated: 2023/05/23 19:24:33 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node *insert_pipes(t_node *node, int **pipe_nbr)
{

	
}

int num_of_pipes(char *array)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while (array[i] != '\0')
	{
		if (array[i] == '|')
			len++;
		i++;
	}
	return(len);
}

int	**allocate_pipes(char *array)
{
	int	**pipe_nbr;
	int	i;
	int	len;

	len = num_of_pipes(array);
	if (len == 0)
		return(NULL);
	i = 0;
	pipe_nbr = ft_calloc(len, sizeof(int *));
	if (!pipe_nbr)
		return (NULL);
	while (i < len)
	{
		pipe_nbr[i] = ft_calloc(2, sizeof(int));
		if (!pipe_nbr[i])
		{
			while (--i != -1)
				free(pipe_nbr[i]);
			return (NULL);
		}
		i++;
	}
	return (pipe_nbr);
}

int **piper(char *array)
{
	int **pipe_nbr;
	int len;
	int i;

	i = 0;
	pipe_nbr = allocate_pipes(array);
	if (pipe_nbr == NULL)
		return(NULL);
	len = num_of_pipes(array);
	while (i < len)
	{
		if(pipe(pipe_nbr[i]) == -1)
			ft_pexit("pipe :");
		i++;
	}
	return(pipe_nbr);
}
