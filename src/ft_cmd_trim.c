/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_trim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:21:59 by druina            #+#    #+#             */
/*   Updated: 2023/05/18 08:52:28 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Finding the closing quote or reset in case of multiple quotes together

int	find_closing_quote(char *quote, int *closing_quote, char **line)
{
	if (**line == (*quote) && *(*line + 1) == ' ')
	{
		(*line)++;
		if (**line != (*quote))
			(*closing_quote) = 1;
		return (1);
	}
	else if (**line == (*quote) && *(*line + 1) == (*quote))
		(*quote) = 0;
	if (**line == (*quote))
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
		while (!ft_strchr(" \t\n\v\f\r", **line))
		{
			if (**line == '"' && !quote)
				quote = '"';
			else if (**line == '\'' && !quote)
				quote = '\'';
			else if (find_closing_quote(&quote, &closing_quote, line) == 1)
				break ;
			(*line)++;
		}
		if (**line == '\0')
			break ;
		if (!quote || (closing_quote == 1 && quote))
			break ;
		while (ft_strchr(" \t\n\v\f\r", **line) && **line != '\0')
			(*line)++;
	}
}

// Gets the next token from the line

char	*next_token_from_line(char **line)
{
	char	*token;

	if ((*line) == NULL)
		return (NULL);
	while (ft_strchr(" \t\n\v\f\r", **line) && **line)
		(*line)++;
	if (**line == '\0')
		return ((*line) = NULL);
	token = (*line);
	handle_quotes(line);
	if ((*line) == '\0')
	{
		token = allocate_token(token, (*line));
		(*line) = NULL;
		return (token);
	}
	else
		token = allocate_token(token, (*line));
	if (**line != '\0')
		(*line)++;
	return (token);
}
// Gets the number of tokens to be allocated (len)

int	cmd_trim_new_array_len(char *line)
{
	char	*temp;
	int		len;

	len = 0;
	temp = next_token_from_line(&line);
	if (temp == NULL)
		return (-1);
	while (temp != NULL)
	{
		len++;
		free(temp);
		temp = next_token_from_line(&line);
	}
	return (len);
}

// 2D array of the tokens

char	**ft_cmd_trim(char *line)
{
	char	**cmds;
	char	*temp;
	int		i;
	int		len;

	temp = line;
	len = cmd_trim_new_array_len(line);
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
