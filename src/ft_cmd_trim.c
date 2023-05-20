/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:21:59 by druina            #+#    #+#             */
/*   Updated: 2023/05/20 21:40:02 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Finding the closing quote or reset in case of multiple quotes together

int	find_closing_quote(char *quote, int *closing_quote, char **line)
{
	if (*(*line) == (*quote) && *(*line + 1) == ' ')
	{
		(*line)++;
		(*closing_quote) = 1;
		return (1);
	}
	else if (*(*line) == (*quote) && *(*line + 1) == (*quote))
		(*quote) = 0;
	else if (*(*line) == (*quote))
			(*closing_quote) = 1;
	return (0);
}

// setting the pointer of line to the address of where the token ends

void	handle_quotes(char **line)
{
	char	quote;
	int		closing_quote;

	closing_quote = 0;
	quote = 0;
	while (1)
	{
		while (!ft_strchr(" \t\n\v\f\r", *(*line)))
		{
			if (*(*line) == '"' && !quote)
				quote = '"';
			else if (*(*line) == '\'' && !quote)
				quote = '\'';
			else if (find_closing_quote(&quote, &closing_quote, line) == 1)
				break ;
			(*line)++;
		}
		if (*(*line) == '\0' || !quote || closing_quote == 1)
			break ;
		while (ft_strchr(" \t\n\v\f\r", *(*line)))
			(*line)++;
	}
}

// Gets the next token from the line

char	*next_token_from_line(char **line)
{
	char	*token_start;

	if ((*line) == NULL)
		return (NULL);
	while (*(*line) && ft_strchr(" \t\n\v\f\r", *(*line)))
		(*line)++;
	if (*(*line) == '\0')
		return (NULL);
	token_start = (*line);
	handle_quotes(line);
	return (allocate_token(token_start, (*line)));
}
// Gets the number of tokens to be allocated (len)

int	cmd_trim_len(char *line)
{
	char	*token;
	int		len;

	len = 0;
	token = next_token_from_line(&line);
	if (token == NULL)
		return (-1);
	while (token != NULL)
	{
		len++;
		free(token);
		token = next_token_from_line(&line);
	}
	return (len);
}

// Gets the line and seperates it to tokens.

char	**ft_cmd_trim(char *line)
{
	char	**cmds;
	char	*temp;
	int		i;
	int		len;

	temp = line;
	len = cmd_trim_len(line);
	if (len == -1)
		return (NULL);
	cmds = (char **)malloc(sizeof(char *) * (len + 1));
	if (!cmds)
		return (NULL);
	cmds[len] = 0;
	i = 0;
	while (i != len)
		cmds[i++] = next_token_from_line(&temp);
	// free(line);
	return (cmds);
}
