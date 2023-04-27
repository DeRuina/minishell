/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:07:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/04/27 15:41:12 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int find_proper_allocation(char **array, int *i)
{
	int j;
	int count;
	char *arr;
	char *arr1;

	count = 0;
	j = 0;
	while (array[(*i)] != 0)
	{
		while (array[(*i)][j] != '\0')
		{
			arr = ft_strchr("<|>", array[(*i)][j]);
			arr1 = ft_strchr("<|>", array[(*i)][j + 1]);
			if (arr)
			{
				if (arr1)
					if(*arr == '<' && *arr1 == '<')
						j++;
				if (arr1)
					if(*arr == '>' && *arr1 == '>')
						j++;
				count++;
			}
			j++;
		}
			j = 0;
			(*i)++;
	}
	return(count);
}

int check_for_token(char *array)
{
	int i;
	int count;
	char *token;

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
	return(count);
}



char **divide_into_arr(char **array, char **answer)
{
	int j;
	int i;
	int offset;
	// char *arr;
	// char *arr1;

	j = 0;
	offset = 0;
	i = 0;
	while (array[i] != 0)
	{
		if (check_for_token(array[i]) == 0)
			answer[i + offset] = (char *)malloc(sizeof(char) * ft_strlen(array[i]) + 1);
		else
		{
			offset = check_for_token(array[i]);
		}

		while (array[i][j] != '\0')
		{
			answer[i + offset][j] = array[i][j];
			j++;
		}
		j = 0;
		i++;




	}
		return(answer);
}

char	**ft_split_operators(char **array)
{
	int i;
	char **answer;
	int count;

	if (array == NULL)
		return(NULL);
	i = 0;
	count = find_proper_allocation(array, &i);
	answer = (char **)malloc(sizeof(char *) * (i + count) + 1);
	if (!answer)
		return(answer);
	answer[i + count] = 0;
	answer = divide_into_arr(array, answer);

	return(answer);
}
