/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:07:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/17 14:32:17 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Check if there is a operator

int	check_for_operator(char *array)
{
	int		i;
	int		count;
	char	*token;

	i = -1;
	count = 0;
	while (array[++i] != '\0')
	{
		if (ft_strchr("<|>", array[i]))
			token = ft_strchr("<|>", array[i]);
		else
			token = NULL;
		if (token != NULL)
		{
			if (array[i] == '\0' && *token == array[i] && array[i + 1] == '\0' && !array[i - 1])
				count = 0;
			else if (token)
				count++;
		}
	}
	return (count);
}

// part of find_proper_allocation

int	get_allocation_len(char *array)
{
	int	offset;
	int count;

	offset = 0;
	count =	0;
	offset = check_for_operator(array);
	if (offset == 0)
		count++;
	else
	{
		while (len_to_operator(&array, NULL))
		{
			count++;
			if (!*array)
				break ;
		}
	}
	return (count);
}

//Find proper allocation for 2D array

int	find_new_array_len(char **array, int i)
{
	int		count;

	count = 0;
	while (array[i] != 0)
	{
		count += get_allocation_len(array[i]);
		i++;
	}
	return (count);
}

//Split the tokens into operators

char	**ft_split_operators(char **array)
{
	char	**answer;
	char	**temp;
	int		count;

	if (array == NULL)
		return (NULL);
	temp = array;
	count = find_new_array_len(array, 0);
	answer = (char **)malloc(sizeof(char *) * (count + 1));
	if (!answer)
		return (NULL);
	answer[count] = 0;
	answer = divide_into_array(temp, answer);
	// free_2d(array);
	return (answer);
}
