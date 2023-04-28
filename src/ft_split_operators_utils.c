/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operations_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:18:22 by druina            #+#    #+#             */
/*   Updated: 2023/04/28 16:19:00 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
