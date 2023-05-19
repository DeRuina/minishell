/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:43:56 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/19 10:08:05 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// loops and trims the unnecessary

char	*trim_loop(char *str, char *answer, int i, char quote)
{
	while (*str)
	{
		if (*str == quote)
		{
			quote = 0;
			str++;
		}
		if (*str == '\0')
		{
			answer[i] = '\0';
			break ;
		}
		if (ft_strchr("\"'", *str) && !quote)
			quote = *str;
		if (*str != quote)
			answer[i] = *str;
		i++;
		str++;
		answer[i] = '\0';
	}
	if (quote)
	{
		// free(answer);
		return (NULL);
	}
	return (answer);
}

// Null terminates and frees

char	*null_term_and_free(char *answer, int i, char *temp)
{
	answer[i] = '\0';
	// free(temp);
	temp = NULL;
	return (answer);
}

// copies to malloced array in case of single quotes

char	*only_double_quotes_case(char *str)
{
	if ((ft_strncmp(str, "\"\"", 2) == 0 || ft_strncmp(str, "''", 2) == 0) && ft_strlen(str) == 2)
		return(ft_strdup(str));
	return (NULL);
}

// Check if trim is needed and returns new arr

char	*check_for_trim(char *str)
{
	char	*answer;
	char	*temp;
	char	quote;
	int		i;

	i = 0;
	temp = str;
	answer = only_double_quotes_case(str);
	if (answer)
		return(answer);
	answer = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	while (*str != '\0')
	{
		if (ft_strchr("\"'", *str))
			break ;
		answer[i++] = *str++;
	}
	if (*str == '\0')
		return (null_term_and_free(answer, i, temp));
	quote = *str;
	answer = trim_loop(++str, answer, i, quote);
	// free(temp);
	return (answer);
}

// Loops through the array and return the new one

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
			// free_2d(answer);
			return (NULL);
		}
		array++;
	}
	return (answer);
}
