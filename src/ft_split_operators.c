/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:07:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/18 12:09:38 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		offset_for_combined_tokens;
	char	*temp;

	offset_for_combined_tokens = 0;
	i = 0;
	while (array[i] != 0)
	{
		if (check_operators_num_in_string(array[i]) == 0)
			answer[i + offset_for_combined_tokens] = no_operator(array[i]);
		else
		{
			temp = array[i];
			while (*array[i])
			{
				answer[i + offset_for_combined_tokens]
					= malloc_new_token_and_move_pointer_to_next(&array[i]);
				if (*array[i])
					offset_for_combined_tokens++;
			}
			array[i] = temp;
		}
		i++;
	}
	return (answer);
}

// moves the pointer to the next token if exist,
//returns the lenght of the token. example : "<Makefile|"
//first call - return 1, modified string "Makefile|".
// second call - return 8, modified string "|".
//third call - return 1, modified string "".

int	pointer_to_next_token_return_len(char **str)
{
	int	len;

	len = 0;
	if (**str != '\0' && ft_strchr("<|>", **str))
	{
		if (*(*str + 1) && ft_strchr("<>", *(*str + 1)))
		{
			(*str) += 2;
			return (2);
		}
		(*str)++;
		return (1);
	}
	while (!ft_strchr("<|>", **str))
	{
		len++;
		(*str)++;
	}
	return (len);
}

//Finds the lenght of the new array needed

int	split_operators_new_array_len(char **array, int i)
{
	int		num_of_tokens;
	char	*temp;

	num_of_tokens = 0;
	while (array[i] != 0)
	{
		temp = array[i];
		while (pointer_to_next_token_return_len(&array[i]))
			num_of_tokens++;
		array[i] = temp;
		i++;
	}
	return (num_of_tokens);
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
