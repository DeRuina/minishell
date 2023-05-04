/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:18:22 by druina            #+#    #+#             */
/*   Updated: 2023/05/03 17:48:30 by druina           ###   ########.fr       */
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
