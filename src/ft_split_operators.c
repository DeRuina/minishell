/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:07:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/22 16:44:18 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if there is an operator and if its here_doc or append

int	is_token_an_operator(char **str)
{
	if (*(*str) != '\0' && ft_strchr("<|>", *(*str)))
	{
		if (*(*str) == '|' && *(*str + 1) == '|')
			return (-1);
		if (*(*str) == '|' && ft_strchr("<>", *(*str + 1))
			&& ft_strlen((*str)) == 2)
		{
			(*str)++;
			return (1);
		}
		if (*(*str + 2) && ft_strchr("<|>", *(*str + 2)))
			return (-1);
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

// iterates until the closing quote to to make it one token

void	iterate_until_closing_quote(char quote, char **str, int *len)
{
	if (*(*str) == quote && quote != '\0')
	{
		(*len)++;
		(*str)++;
		while (*(*str) && *(*str) != quote)
		{
			(*len)++;
			(*str)++;
		}
	}
}

// gets the next token by moving the pointer,
//returns the lenght of the token. example : "<Makefile|"
//first call - return 1, modified string "Makefile|".
//second call - return 8, modified string "|".
//third call - return 1, modified string "".

int	get_next_token(char **str)
{
	int		len;
	char	quote;

	len = is_token_an_operator(str);
	if (len != 0)
		return (len);
	if (*(*str) == '\"')
		quote = '\"';
	if (*(*str) == '\'')
		quote = '\'';
	iterate_until_closing_quote(quote, str, &len);
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
		while (*array[i] != '\0')
		{
			if (get_next_token(&array[i]) < 0)
				return (-1);
			else
				num_of_tokens++;
		}
		array[i] = temp;
		if (*array[i] == '\0')
			num_of_tokens++;
		i++;
	}
	return (num_of_tokens);
}

//Splits the token if there is operators attached in the token

char	**ft_split_operators(char **array)
{
	char	**answer;
	int		len;

	if (array == NULL)
		return (NULL);
	len = split_operators_len(array);
	if (len == -1)
	{
		free_2d(array);
		ft_putendl_fd("syntax error near unexpected token", 2);
		return (NULL);
	}
	answer = ft_calloc(len + 1, sizeof(char *));
	if (!answer)
		return (NULL);
	answer = divide_into_array(array, answer);
	free_2d(array);
	return (answer);
}
