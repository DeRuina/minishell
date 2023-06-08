/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:43:56 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/08 16:19:08 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Trims the token and returns it without the quotes

char	*trim_token(char *str, char *answer, int i, char quote)
{
	while (*str)
	{
		if (quote == *str)
		{
			quote = 0;
			str++;
		}
		if (*str == '\0')
			break ;
		if (ft_strchr("\"'", *str) && !quote)
			quote = *str;
		if (*str != quote)
			answer[i++] = *str;
		str++;
	}
	answer[i] = '\0';
	if (quote != 0)
		return (free(answer), NULL);
	return (answer);
}

// Checks the edge case for a token of only double quotes.

int	token_is_double_quotes(char *str)
{
	if ((ft_strncmp(str, "\"\"", 2) == 0 || ft_strncmp(str, "''", 2) == 0)
		&& ft_strlen(str) == 2)
		return (1);
	return (0);
}

// Checks if trim is needed, 0 if not.

int	is_trim_needed(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (ft_strchr("\"'", str[i]))
			return (1);
		i++;
	}
	return (0);
}

// Checks for edge cases, and trims the token if needed.

char	*check_for_trim(char *str)
{
	char	*answer;
	char	*temp;
	char	quote;
	int		i;

	i = 0;
	temp = str;
	if (is_trim_needed(str) == 0)
		return (str);
	if (token_is_double_quotes(str) == 1)
		return (str);
	answer = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!answer)
		return (NULL);
	while (*str != '\0')
	{
		if (ft_strchr("\"'", *str))
			break ;
		answer[i++] = *str++;
	}
	quote = *str;
	answer = trim_token(++str, answer, i, quote);
	free(temp);
	return (answer);
}

// Trims any unnecessary quotes

char	**ft_str_trim(char **array)
{
	char	**answer;

	if (array == NULL)
		return (NULL);
	answer = array;
	while (*array)
	{
		*array = check_for_trim(*array);
		if (*array == NULL)
		{
			free_2d(answer);
			return (NULL);
		}
		array++;
	}
	return (answer);
}
