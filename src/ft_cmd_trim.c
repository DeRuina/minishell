/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:21:59 by druina            #+#    #+#             */
/*   Updated: 2023/04/25 09:55:22 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// handling double and single quotes
void	handle_quotes(char *whitespace, char **line)
{
	char	first;
	int		flag;

	flag = 0;
	first = 0;
	while (1)
	{
		while (!ft_strchr(whitespace, **line))
		{
			if (**line == '"' && !first)
				first = '"';
			else if (*(*line) == '\'' && !first)
				first = '\'';
			else
			{
			if (first == '"' && *(*line) == '"' && *(*line + 1) == ' ')
			{
				(*line)++;
				if (!ft_strchr((*line), first))
					flag = 1;
				break;
			}
			else if (*(*line) == '"' && *(*line + 1) == '"')
					flag = -1;

			if (first == '"' && *(*line) == '"' && flag != -1)
				flag = 1;
			if (first == '\'' && *(*line) == '\'' && *(*line + 1) == ' ')
			{
				(*line)++;
				if (!ft_strchr((*line), first))
					flag = 1;
				break;
			}
			else if (*(*line) == '\'' && *(*line + 1) == '\'')
					flag = -1;
			if (first == '\'' && *(*line) == '\'' && flag != -1)
				flag = 1;
			}
			(*line)++;
		}
		if (*(*line) == '\0')
			break;
		if (!first || (flag == 1 && first))
			break ;
		while (ft_strchr(whitespace, *(*line)))
			(*line)++;
	}
}

// Gets a token from the line,and modifies the line to a new start by the pointer

char	*malloc_token(char *start, char *line)
{
	char	*token;
	int		i;

	i = 0;
	while (start[i] != line[0])
		i++;
	token = (char *)malloc(sizeof(char) * i + 1);
	if (!token)
		return (NULL);
	token[i] = '\0';
	i = 0;
	while (start[i] != line[0])
	{
		token[i] = start[i];
		i++;
	}
	return (token);
}

char	*get_token(char **line)
{
	char	*line_start;

	if ((*line) == NULL)
		return (NULL);
	while (ft_strchr(" \t\n\v\f\r", *(*line)) && *(*line))
		(*line)++;
	if (*(*line) == '\0')
		return ((*line) = NULL);
	line_start = (*line);
	handle_quotes(" \t\n\v\f\r", line);
	if ((*line) == '\0')
	{
		line_start = malloc_token(line_start, (*line));
		(*line) = NULL;
		return (line_start);
	}
	line_start = malloc_token(line_start, (*line));
	(*line)++;
	return (line_start);
}

// 2D array of the tokens
char	**ft_cmd_trim(char *line)
{
	char	**cmds;
	char	*temp;
	char	*temp2;
	int		i;
	int		len;

	len = 0;
	temp = line;
	temp2 = get_token(&line);
	if (temp2 == NULL)
		return(NULL);
	while (temp2 != NULL)
	{
		len++;
		free(temp2);
		temp2 = get_token(&line);
	}
	cmds = (char **)malloc(sizeof(char *) * len + 1);
	if (!cmds)
		return (NULL);
	cmds[len] = 0;
	i = 0;
	while (i != len)
		cmds[i++] = get_token(&temp);
	return (cmds);
}
