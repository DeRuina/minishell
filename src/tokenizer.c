/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:21:59 by druina            #+#    #+#             */
/*   Updated: 2023/04/23 21:18:51 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// CONTINUE ON FT_CMD_TRIM

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

// CONTINUE ON FT_CMD_TRIM

// Gets a token from the line, and modifies the line to a new start by the pointer
char	*get_token(char **line)
{
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

// CONTINUE ON FT_CMD_TRIM

// 2D array of the tokens
// char **tokenizer(char *line)
// {

// }
