/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:21:59 by druina            #+#    #+#             */
/*   Updated: 2023/04/20 13:22:19 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*tokenizer(char **line)
{
	char	*start;
	char	*end;
	char	*whitespace;

	whitespace = ft_strdup(" \t\n\v\f\r");
	while (ft_strchr(whitespace, *(*line)))
		(*line)++;
	if (*(*line) == '\0')
		return ((*line) = NULL);
	start = (*line);
	end = (*line) + ft_strlen((*line));
	while (!ft_strchr(whitespace, *(*line)))
		(*line)++;
	free(whitespace);
	if ((*line) == end)
	{
		(*line = NULL);
		return (start);
	}
	*(*line) = '\0';
	(*line)++;
	return (start);
}
