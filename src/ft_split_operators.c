/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:07:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/18 10:11:45 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// len of the next token

int	len_to_operator(char **array, int *flag)
{
	int	len;

	len = 0;
	if (**array != '\0' && ft_strchr("<|>", **array))
	{
		if (ft_strchr("<|>", *(*array + 1)) && *(*array + 1) != '\0' && *(*array
				+ 1) != '|')
		{
			if (flag != NULL && (*flag) != 0 )
				(*flag) = 1;
			(*array)++;
		}
		(*array)++;
		return (1);
	}
	while (!ft_strchr("<|>", **array))
	{
		len++;
		(*array)++;
	}
	return (len);
}

// part of find_proper_allocation

int	get_allocation_len(char *array)
{
	int len;

	len =	0;
	while (len_to_operator(&array, NULL))
		len++;
	return (len);
}

//Finds the lenght of the new array needed

int	split_operators_new_array_len(char **array, int i)
{
	int		len;
	int		count;
	char	*temp;

	len = 0;
	count = 0;
	while (array[i] != 0)
	{
		temp = array[i];
		while (len_to_operator(&array[i], NULL))
			count++;
		len += count;
		array[i] = temp;
		i++;
	}
	return (len);
}

//Split the tokens if they're attached to an operator

char	**ft_split_operators(char **array)
{
	char	**answer;
	int		count;

	if (array == NULL)
		return (NULL);
	count = split_operators_new_array_len(array, 0);
	answer = (char **)malloc(sizeof(char *) * (count + 1));
	if (!answer)
		return (NULL);
	answer[count] = 0;
	answer = divide_into_array(array, answer);
	// free_2d(array);
	return (answer);
}
