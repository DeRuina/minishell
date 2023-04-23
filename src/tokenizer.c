/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:21:59 by druina            #+#    #+#             */
/*   Updated: 2023/04/23 18:34:09 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// handling double and single quotes
void handle_quotes(char	*whitespace ,char **line)
{
	char first;
	int flag;

	flag = 0;
	first = 0;
	while (1)
	{
		if (first == '"' && *(*line) == '"')
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

// char	**get_token(char *line);

// Gets a token from the line, and modifies the line to a new start by the pointer
char	*get_token(char **line)
{
	// Current implementation will most likely cause some problems with freeing
	// and leaking.
	char	*line_start;

	if (*line == NULL)
		return (NULL);
	while (**line && ft_strchr(" \t\n\v\f\r", **line))
		(*line)++;
	if (**line == '\0')
		return (*line = NULL);
	line_start = *line;
	handle_quotes(" \t\n\v\f\r", line);
	if (**line == '\0')
	{
		*line = NULL;
		return (line_start);
	}
	**line = '\0';
	(*line)++;
	return (line_start);
}

// 2D array of the tokens

// char **tokenizer(char *line)
// {

// }
