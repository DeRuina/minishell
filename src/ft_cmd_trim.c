/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:04:42 by tspoof            #+#    #+#             */
/*   Updated: 2023/04/24 08:51:21 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handling double and single quotes
void handle_quotes(char	*whitespace, char **line)
{
	char first;
	int flag;

	flag = 0;
	first = 0;
	while (1)
	{
		if (first == '"' && **line == '"')
				flag = 1;
			if (first == '\'' && **line == '\'')
				flag = 1;
		while (!ft_strchr(whitespace, **line) && flag != 1)
		{

			if (**line == '"' && !first)
				first = '"';
			if (**line == '\'' && !first)
				first = '\'';
			(*line)++;
		}
		if (flag == 1)
			(*line)++;
		if (!first || flag == 1)
			break;
		while (ft_strchr(whitespace, **line))
			(*line)++;
	}
}

// Not working!

// Gets a token from the line, and modifies the line to a new start by the pointer
char	**ft_cmd_trim(char *line)
{
	// Current implementation will most likely cause some problems with freeing
	// and leaking.
	char	*line_start;

	if (line == NULL)
		return (NULL);
	while (*line && ft_strchr(" \t\n\v\f\r", *line))
		line++;
	if (*line == '\0')
		return (NULL);
	line_start = line;
	// handle_quotes(" \t\n\v\f\r", &line);
	if (*line == '\0')
		return (NULL);
		// return (line_start);
	// *line = '\0';
	line++;
	if (line_start)
		return (NULL);
	return (NULL);
	// return (line_start);
}
