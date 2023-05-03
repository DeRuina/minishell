/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:43:56 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/03 14:51:16 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *check_for_trim(char *str)
{
	char *answer;
	char *temp;
	char c;
	int i;

	i = 0;
	temp = str;
	answer = (char *)malloc(sizeof(char) * ft_strlen(str) - 1);
	if (!answer)
		return(NULL);
	while (*str != '\0')
	{
		if (ft_strchr("\"'", *str))
			break;
		answer[i] = *str;
		i++;
		str++;
	}
	if (*str == '\0')
	{
		answer[i] = '\0';
		return (answer);
	}
	c = *str;
	str++;
	while (*str)
	{
		if (*str == c)
		{
			c = 0;
			str++;
		}
		if (*str == '\0')
			break;
		if (ft_strchr("\"'", *str) && c == 0)
			c = *str;
		if (*str != c)
			answer[i] = *str;
		i++;
		str++;
	}
	if (c != 0)
	{
		free(answer);
		// free(temp);
		return(NULL);
	}
	answer[i] = '\0';
	// free(temp);
	return(answer);
}

char	**ft_str_trim(char **array)
{
	char **answer;

	if (array == NULL)
		return(NULL);
	answer = array;
	while (*array != NULL)
	{
		*array = check_for_trim(*array);
		if (*array == NULL)
		{
			// free_2d(answer);
			return(NULL);
		}
		array++;
	}
	return(answer);
}
