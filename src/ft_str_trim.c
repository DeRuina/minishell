/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:43:56 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/04 10:43:24 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// loops and trims the unnecessary

char	*trim_loop(char *str, char *answer, int i, char *c)
{
	while (*str)
	{
		if (*str == (*c))
		{
			(*c) = 0;
			str++;
		}
		if (*str == '\0')
			break ;
		if (ft_strchr("\"'", *str) && (*c) == 0)
			(*c) = *str;
		if (*str != (*c))
			answer[i] = *str;
		i++;
		str++;
		answer[i] = '\0';
	}
	if ((*c) != 0)
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

// Check if trim is needed and returns new arr

char	*check_for_trim(char *str)
{
	char	*answer;
	char	*temp;
	char	c;
	int		i;

	i = 0;
	temp = str;
	answer = (char *)malloc(sizeof(char) * ft_strlen(str) - 1);
	while (*str != '\0')
	{
		if (ft_strchr("\"'", *str))
			break ;
		answer[i] = *str;
		i++;
		str++;
	}
	if (*str == '\0')
		return (null_term_and_free(answer, i, temp));
	c = *str;
	str++;
	answer = trim_loop(str, answer, i, &c);
	if (answer == NULL)
		return (NULL);
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
	while (*array != NULL)
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
