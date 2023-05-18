/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:18:22 by druina            #+#    #+#             */
/*   Updated: 2023/05/18 09:30:47 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Checks for the number of operators in the string

int	check_operators_num_in_string(char *array)
{
	int		i;
	int		count;
	char	*operator;

	i = -1;
	count = 0;
	operator = NULL;
	while (array[++i] != '\0')
	{
		if (ft_strchr("<|>", array[i]))
			operator = ft_strchr("<|>", array[i]);
		if (operator)
			count++;
	}
	return (count);
}

// creates the new array and allocates

char	**divide_into_array(char **array, char **answer)
{
	int		i;
	int		offset;
	char	*temp;

	offset = 0;
	i = 0;
	while (array[i] != 0)
	{
		if (check_operators_num_in_string(array[i]) == 0)
			answer[i + offset] = no_operator(answer, array, &offset, &i);
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
	len = len_to_operator(array, &flag);
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

void	*no_operator(char **answer, char **array, int *offset, int *i)
{
	int	j;

	j = 0;
	answer[(*i) + (*offset)] = (char *)malloc(sizeof(char)
			* (ft_strlen(array[(*i)]) + 1));
	while (array[(*i)][j] != '\0')
	{
		answer[(*i) + (*offset)][j] = array[(*i)][j];
		j++;
	}
	answer[(*i) + (*offset)][j] = '\0';
	(*i)++;
	return (answer[(*i) + (*offset)]);
}
