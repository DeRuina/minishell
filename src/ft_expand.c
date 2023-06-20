/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:05:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/20 14:46:14 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

// Adds the $ or ~ plus extra to result if the $ or ~ should not be expanded

static char	*ft_handle_nonexpand(char **result, char *token)
{
	char	*sub_str;
	char	*tmp;
	char	*token_start;

	token_start = token;
	while (*token != '$' && *token != '~' && *token != '\0')
		token++;
	sub_str = ft_substr(token_start, 0, token - token_start);
	if (!sub_str)
		return (NULL);
	tmp = ft_strjoin(*result, sub_str);
	free(sub_str);
	if (!tmp)
		return (NULL);
	free(*result);
	*result = tmp;
	return (token);
}

// Checks what type of expand it is or is it even expandable
// Returns the address of a next character to be checked by the ft_expand_token

char	*ft_handle_expand(t_vec env_vars, char **result, char *token,
		char *token_first_char)
{
	if (*token == '$' && (ft_isalnum(*(token + 1)) || *(token + 1) == '?'))
		token = ft_varible(env_vars, result, token);
	if (*token == '~' && ft_should_expand_tilde(token, token_first_char))
		token = ft_tilde(env_vars, result, token);
	if ((*token == '$' && !ft_isalnum(*(token + 1))) || *token == '~')
		token = ft_noexpand(result, token);
	return (token);
}
// Loops to closing single quote, stores each character in the result
// and returns tokens address after closing single quote.

static char	*to_closing_singlequote(char *token, char *result)
{
	int	i;

	result[0] = token[0];
	i = 1;
	while (token[i] && token[i] != '\'')
	{
		result[i] = token[i];
		i++;
	}
	result[i] = token[i];
	return (&token[i + 1]);
}

// Loops the characters in the token and puts those to result string.
// If there is exand tokens ($ or ~) it will try to expand those.
// Return the expanded token as a string.

char	*ft_expand_token(t_vec env_vars, char *token)
{
	char	*result;
	char	*token_first_c;

	token_first_c = token;
	result = ft_strdup("");
	if (!result)
		ft_pexit("ft_expand_token: ft_strdup");
	while (*token)
	{
		if (*token == '\'')
			token = to_closing_singlequote(token, result);
		if (*token != '$' && *token != '~')
			token = ft_handle_nonexpand(&result, token);
		if (*token == '$' || *token == '~')
			token = ft_handle_expand(env_vars, &result, token, token_first_c);
	}
	return (result);
}

// Loops all tokens and checks if it contains expandable characters

void	ft_expand(t_vec env_vars, char **token_arr)
{
	char	*tmp;

	while (*token_arr)
	{
		if (!ft_strchr(*token_arr, '$') && !ft_strchr(*token_arr, '~'))
		{
			token_arr++;
			continue ;
		}
		tmp = *token_arr;
 		*token_arr = ft_expand_token(env_vars, *token_arr);
		free(tmp);
		token_arr++;
	}
}
