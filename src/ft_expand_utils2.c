/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:12:47 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/07 14:30:35 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

extern int	g_exit_status;

char	*ft_handle_dollar(t_vec env_vars, char *line, char *token)
{
	char	*expanded_var;

	if (*(token + 1) == '?')
		expanded_var = ft_itoa(g_exit_status);
	else
		expanded_var = ft_var_expand(env_vars, token);
	if (!expanded_var)
		return (ft_strdup(line));
	return (ft_strjoin(line, expanded_var));
}

// returns the address after the last char of the variable
char	*ft_varible(t_vec env_vars, char **result, char *token)
{
	char	*tmp;

	tmp = ft_handle_dollar(env_vars, *result, token);
	if (tmp)
	{
		free(*result);
		*result = tmp;
	}
	token = ft_var_end(token);
	return (token);
}

char	*ft_tilde(t_vec env_vars, char **result, char *token)
{
	char	*tmp;

	tmp = ft_strjoin(*result, ft_var_expand(env_vars, ft_strdup("HOME")));
	if (tmp)
	{
		free(*result);
		*result = tmp;
	}
	token++;
	return (token);
}

char	*ft_noexpand(char **result, char *token)
{
	char	*tmp;
	char	*sub_str;

	sub_str = ft_substr(token, 0, 1);
	tmp = ft_strjoin(*result, sub_str);
	free(sub_str);
	if (tmp)
	{
		free(*result);
		*result = tmp;
	}
	token++;
	return (token);
}
