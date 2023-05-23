/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:07:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/23 16:49:33 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if there is an operator and if its here_doc or append

int	is_token_an_operator(char **str)
{
	if (*(*str) != '\0' && ft_strchr("<|>", *(*str)))
	{
		if (*(*str + 1) && ft_strchr("<>", *(*str + 1)))
		{
			(*str) += 2;
			return (2);
		}
		(*str)++;
		return (1);
	}
	return (0);
}

// gets the next token by moving the pointer,
//returns the lenght of the token. example : "<Makefile|"
//first call - return 1, modified string "Makefile|".
//second call - return 8, modified string "|".
//third call - return 1, modified string "".

int	get_next_token(char **str)
{
	int	len;

	len = is_token_an_operator(str);
	if (len != 0)
		return (len);
	while (!ft_strchr("<|>", *(*str)))
	{
		len++;
		(*str)++;
	}
	return (len);
}

//Finds the lenght of the new array needed

int	split_operators_len(char **array)
{
	int		num_of_tokens;
	char	*temp;
	int		i;

	i = 0;
	num_of_tokens = 0;
	while (array[i] != 0)
	{
		temp = array[i];
		while (get_next_token(&array[i]))
			num_of_tokens++;
		array[i] = temp;
		i++;
	}
	return (num_of_tokens);
}

//Splits the token if there is operators attached to new tokens

char	**ft_split_operators(char **array)
{
	char	**answer;
	int		len;

	if (array == NULL)
		return (NULL);
	len = split_operators_len(array);
	answer = (char **)malloc(sizeof(char *) * (len + 1));
	if (!answer)
		return (NULL);
	answer[len] = 0;
	answer = divide_into_array(array, answer);
	free_2d(array);
	return (answer);
}
