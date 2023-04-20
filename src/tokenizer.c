/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:21:59 by druina            #+#    #+#             */
/*   Updated: 2023/04/20 15:04:49 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			if (first == '\'' && *(*line) == '\'')
				flag = 1;
		while (!ft_strchr(whitespace, *(*line)) && flag != 1)
		{

			if (*(*line) == '"' && !first)
				first = '"';
			if (*(*line) == '\'' && !first)
				first = '\'';
			(*line)++;
		}
		if (flag == 1)
			(*line)++;
		if (!first || flag == 1)
			break;
		while (ft_strchr(whitespace, *(*line)))
				(*line)++;
	}
}

char	*tokenizer(char **line)
{
	char	*start;
	char	*end;
	char	*whitespace;

	if ((*line) == NULL)
		return(NULL);
	whitespace = ft_strdup(" \t\n\v\f\r");
	while (ft_strchr(whitespace, *(*line)) && *(*line))
		(*line)++;
	if (*(*line) == '\0')
		return ((*line) = NULL);
	start = (*line);
	end = (*line) + ft_strlen((*line));
	handle_quotes(whitespace, line);
	// while (!ft_strchr(whitespace, *(*line)))
	// {
	// 	if ((*line) == '"' || (*line) == '\'')
	// 	(*line)++;
	// }
	free(whitespace);
	if ((*line) == end)
	{
		(*line) = NULL;
		return (start);
	}
	*(*line) = '\0';
	(*line)++;
	return (start);
}
