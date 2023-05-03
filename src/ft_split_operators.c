/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:07:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/03 17:48:33 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creates the new array and allocates

char	**divide_into_arr(char **array, char **answer)
{
	int		i;
	int		offset;
	char	*temp;

	offset = 0;
	i = 0;
	while (array[i] != 0)
	{
		if (check_for_operator(array[i]) == 0)
			answer[i + offset] = no_op(answer, array, &offset, &i);
		else
		{
			temp = array[i];
			while (*array[i])
			{
				answer[i + offset] = malloc_new_token(&array[i]);
				if (*array[i])
					offset++;
			}
			array[i] = temp;
			i++;
		}
	}
	return (answer);
}

// part of find_proper_allocation

void	get_allocation_num(char *array, int *count)
{
	int	offset;
	int	flag;

	offset = 0;
	flag = 0;
	offset = check_for_operator(array);
	if (offset == 0)
		(*count)++;
	else
	{
		while (len_to_token(&array, &flag))
		{
			(*count)++;
			if (!*array)
				break ;
		}
	}
}

//Find proper allocation for 2D array

int	find_proper_allocation(char **array, int i)
{
	int		count;
	char	*temp;

	count = 0;
	while (array[i] != 0)
	{
		temp = array[i];
		get_allocation_num(array[i], &count);
		array[i] = temp;
		i++;
	}
	return (count);
}

//Split the tokens into operators

char	**ft_split_operators(char **array)
{
	int		i;
	char	**answer;
	char	**temp;
	int		count;

	if (array == NULL)
		return (NULL);
	i = 0;
	temp = array;
	count = find_proper_allocation(array, i);
	answer = (char **)malloc(sizeof(char *) * count + 1);
	if (!answer)
		return (answer);
	answer[i + count] = 0;
	answer = divide_into_arr(temp, answer);
	// free_2d(array);
	return (answer);
}
