/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:05:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/08 14:32:12 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

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

char	*ft_handle_expand(t_vec env_vars, char **result, char *token,
		char *token_init)
{
	if (*token == '$' && (ft_isalnum(*(token + 1)) || *(token + 1) == '?'))
		token = ft_varible(env_vars, result, token);
	if (*token == '~' && ft_should_expand_tilde(token, token_init))
		token = ft_tilde(env_vars, result, token);
	if ((*token == '$' && !ft_isalnum(*(token + 1))) || *token == '~')
		token = ft_noexpand(result, token);
	return (token);
}

char	*ft_expand_token(t_vec env_vars, char *token)
{
	char	*result;
	char	*token_init_adrs;

	token_init_adrs = token;
	result = ft_strdup("");
	if (!result)
		ft_pexit("ft_expand_token: ft_strdup");
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
