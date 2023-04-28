/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:07:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/04/28 16:20:40 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// finds and mallocs the next operator

char	*malloc_new_token(char **array)
{
	int		i;
	char	*answer;
	char	*temp;
	int		len;
	int		flag;

	flag = 2;
	temp = (*array);
	i = 0;
	len = len_to_token(array, &flag);
	if (flag == 1)
		len++;
	answer = (char *)malloc(sizeof(char) * len + 1);
	if (!answer)
		return (NULL);
	while (i < len)
	{
		answer[i] = temp[i];
		i++;
	}
	answer[i] = '\0';
	return (answer);
}

//	part of divide_into_arr

void	*no_op(char **answer, char **array, int *offset, int *i)
{
	int	j;

	j = 0;
	answer[(*i) + (*offset)] = (char *)malloc(sizeof(char)
			* ft_strlen(array[(*i)]) + 1);
	while (array[(*i)][j] != '\0')
	{
		answer[(*i) + (*offset)][j] = array[(*i)][j];
		j++;
	}
	(*i)++;
	return (answer[(*i) + (*offset)]);
}

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
