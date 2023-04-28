/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:07:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/04/28 14:57:43 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//Find proper allocation for 2D array

int	find_proper_allocation(char **array, int i)
{
	int		j;
	int		count;
	char	*temp;
	int		offset;
	int		flag;

	count = 0;
	offset = 0;
	flag = 0;
	while (array[i] != 0)
	{
		temp = array[i];
		j = -1;
		offset = check_for_operator(array[i]);
		if (offset == 0)
			count++;
		else
		{
			while (len_to_token(&array[i], &flag))
			{
				count++;
				if (!*array[i])
					break ;
			}
		}
		array[i] = temp;
		i++;
	}
	return (count);
}

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
			if (*token == array[i] && array[i + 1] == '\0' && !array[i - 1])
				count = 0;
			else if (token)
				count++;
		}
	}
	return (count);
}

// len of the next token

int	len_to_token(char **array, int *flag)
{
	int	len;

	len = 0;
	if (ft_strchr("<|>", *(*array)))
	{
		if (ft_strchr("<|>", *(*array + 1)) && *(*array + 1) != '\0' && *(*array
				+ 1) != '|')
		{
			if ((*flag) != 0)
				(*flag) = 1;
			(*array)++;
		}
		(*array)++;
		return (1);
	}
	while (!ft_strchr("<|>", *(*array)))
	{
		len++;
		(*array)++;
	}
	return (len);
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

// creates the new array and allocates

char	**divide_into_arr(char **array, char **answer)
{
	int		j;
	int		i;
	int		offset;
	char	*temp;

	j = 0;
	offset = 0;
	i = 0;
	while (array[i] != 0)
	{
		if (check_for_operator(array[i]) == 0)
		{
			answer[i + offset] = (char *)malloc(sizeof(char)
					* ft_strlen(array[i]) + 1);
			while (array[i][j] != '\0')
			{
				answer[i + offset][j] = array[i][j];
				j++;
			}
			j = 0;
			i++;
		}
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
