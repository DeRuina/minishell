/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:05:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/09 17:34:13 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_handle_expand(t_vec env_vars, char **result, char *token, char *token_init)
{
	char	*tmp;
	char	*sub_str;

	if (*token == '$' && ft_isalnum(*(token + 1)))
	{
		tmp = ft_handle_dollar(env_vars, *result, token);
		ft_tmp_to_result(result, &tmp);
		token = ft_var_end(token);
	}
	if (*token == '~' && ft_should_expand_tilde(token, token_init))
	{
		tmp = ft_strjoin(*result, ft_var_expand(env_vars, "HOME")); // protection?
		ft_tmp_to_result(result, &tmp);
		token++;
	}
	if ((*token == '$' && !ft_isalnum(*(token + 1))) || *token == '~')
	{
		sub_str = ft_substr(token, 0, 1);
		tmp = ft_strjoin(*result, sub_str); // leak
		free(sub_str);
		ft_tmp_to_result(result, &tmp);
		token++;
	}
	return (token);
}

char	*ft_expand_token(t_vec env_vars, char *token)
{
	char	*result;
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
