/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:05:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/09 14:54:51 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// gets the address of the end of the variable string
char	*ft_var_end(char *str)
{
	if (*str == '$')
		str++;
	while (*str)
	{
		if (!ft_isalnum(*str))
			break ;
		str++;
	}
	return (str);
}

char	*ft_var_expand(t_vec env_vars, char *str)
{
	char	*key;
	char	*value;

	if (*str == '$' && *(str + 1) && ft_isalnum(*(str + 1)))
		str++;
	key = ft_substr(str, 0, ft_var_end(str) - str);
	if (!key)
		return (NULL);
	if (*key == '$')
		value = key;
	else
		value = ft_getenv(env_vars, key);
	free(key);
	return (value);
}

char	*ft_handle_dollar(t_vec env_vars, char *line, char *token)
{
	char	*expanded_var;
	char	*result;

	result = line;
	expanded_var = ft_var_expand(env_vars, token);
	if (!expanded_var)
		return (NULL);
	return (ft_strjoin(line, expanded_var)); // leaks ft_strfjoin()?? && protection ??
}

static int	ft_should_expand_tilde(char *token, char *token_init)
{
	if (token == token_init && (*(token + 1) == ' ' || *(token + 1) == '\0'))
		return (1);
	if (*(token + 1) == ' ' && *(token - 1) == ' ')
		return (1);
	return (0);
}

char	*ft_handle_expand(t_vec env_vars, char **result, char *token, char *token_init)
{
	char	*tmp;

	if (*token == '$' && ft_isalnum(*(token + 1)))
	{
		tmp = ft_handle_dollar(env_vars, *result, token);
		if (tmp)
		{
			free(*result);
			*result = tmp;
		}
		token = ft_var_end(token);
	}
	if (*token == '~' && ft_should_expand_tilde(token, token_init))
	{
		tmp = ft_strjoin(*result, ft_var_expand(env_vars, "HOME")); // protection
		free(*result);
		*result = tmp;
		token++;
	}
	return (token);
}

static char	*ft_handle_nonexpand(char **result, char *token)
{
	char	*character;
	char	*tmp;

	character = ft_substr(token, 0, 1);
	tmp = ft_strjoin(*result, character); // protection
	free(*result);
	free(character);
	*result = tmp;
	if (*token)
		token++;
	return (token);
}

char	*ft_expand_token(t_vec env_vars, char *token)
{
	char	*result;
	// char	*tmp;
	// char	*character;
	char	*token_init_adrs;

	token_init_adrs = token;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (*token)
	{
		if (*token != '$' && *token != '~')
			token = ft_handle_nonexpand(&result, token);
		if (*token == '$' || *token == '~')
			token = ft_handle_expand(env_vars, &result, token, token_init_adrs);
		if (!*token)
			return (result);
		// if (*token == '$' || *token == '~' && *(token + 1) != '\0' && *(token + 1) != ' ')
		// if (*token == '$' && *(token + 1) != '\0' && *(token + 1) != ' ')
		// 	continue ;
	}
	return (result);
}

void	ft_expand(t_vec env_vars, char **token_arr)
{
	while (*token_arr)
	{
		if (!ft_strchr(*token_arr, '$') && !ft_strchr(*token_arr, '~'))
		{
			token_arr++;
			continue ;
		}
		*token_arr = ft_expand_token(env_vars, *token_arr);
		token_arr++;
	}
}
