/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:05:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/04 16:18:32 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//remove exit functions

// Need more research for ~. Like echo ~SHELL

// $$ ???
// echo $not_exist -> nothing ??
// $NOTEXISTING$ -> $


// gets the address of the end of the variable string
char	*ft_var_end(char *str)
{
	if (*str == '$')
		str++;
	while (*str)
	{
		if (!ft_isalnum(*str))
			break;
		str++;
	}
	return (str);
}

int ft_max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
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

// char	*ft_handle_tilde(t_vec env_vars, char *token);

char	*ft_expand_token(t_vec env_vars, char *token)
{
	// char	*expanded_var;
	char	*result;
	char	*tmp;
	char	*character;

	result = ft_strdup(""); // protection
	while (*token)
	{
		if (*token == '$' && ft_isalnum(*(token + 1)))
		{
			tmp = ft_handle_dollar(env_vars, result, token);
			if (tmp)
			{
				free(result);
				result = tmp;
			}
			token = ft_var_end(token);
		}
		if (*token == '~')
		{
			tmp = ft_strjoin(result, ft_var_expand(env_vars, "HOME")); // protection
			free(result);
			result = tmp;
			token++;
		}
		if (!*token)
			return (result);
		if (*token == '$' && *(token + 1) != '\0' && *(token + 1) != ' ')
			continue;
		character = ft_substr(token, 0, 1);
		tmp = ft_strjoin(result, character); // protection
		free(result);
		free(character);
		result = tmp;
		if (*token)
			token++;
	}
	return (result);
}

void	ft_expand(t_vec env_vars, char **token_arr)
{
	while (*token_arr)
	{
		if (!ft_strchr(*token_arr, '$'))
		{
			token_arr++;
			continue;
		}
		*token_arr = ft_expand_token(env_vars, *token_arr);
		token_arr++;
	}
}

