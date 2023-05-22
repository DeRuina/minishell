/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 16:18:22 by druina            #+#    #+#             */
/*   Updated: 2023/05/19 08:20:10 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// finds and mallocs the next token

char	*malloc_new_token(char **array)
{
	char	*answer;
	char	*temp;
	int		len;

	temp = (*array);
	len = get_next_token(array) + 1;
	answer = (char *)malloc(sizeof(char) * len);
	if (!answer)
		return (NULL);
	ft_strlcpy(answer, temp, len);
	return (answer);
}

//	returns malloced token that has no operator combined

char	*no_operator(char *array)
{
	return (ft_strdup(array));
}
//Checks for the number of operators in the string

int	check_operators_num_in_string(char *array)
{
	int	i;
	int	count;

	i = -1;
	count = 0;
	while (array[++i] != '\0')
	{
		if (ft_strchr("<|>", array[i]))
			count++;
	}
	return (count);
}

// creates the new array and allocates

char	**divide_into_array(char **array, char **answer)
{
	int		i;
	int		tokens_to_split;
	char	*temp;

	tokens_to_split = 0;
	i = 0;
	while (array[i] != 0)
	{
		if (check_operators_num_in_string(array[i]) == 0)
			answer[i + tokens_to_split] = no_operator(array[i]);
		else
		{
			temp = array[i];
			while (*array[i])
			{
				answer[i + tokens_to_split] = malloc_new_token(&array[i]);
				if (*array[i])
					tokens_to_split++;
			}
			array[i] = temp;
		}
		i++;
	}
	return (answer);
}
