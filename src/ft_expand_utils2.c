/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 14:12:47 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/19 14:03:16 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

// Global variable for exit status

extern int	g_exit_status;

// Expands and returns the expanded token

char	*ft_handle_dollar(t_vec env_vars, char *result, char *token)
{
	char	*expanded_var;

	if (*(token + 1) == '?')
		expanded_var = ft_itoa(g_exit_status);
	else
		expanded_var = ft_var_expand(env_vars, token);
	if (!expanded_var)
		return (ft_strdup(result));
	return (ft_strjoin(result, expanded_var));
}

// Expands and adds to result.
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

// Expands ~ and adds it to result
// returns address after the ~

char	*ft_tilde(t_vec env_vars, char **result, char *token)
{
	char	*tmp;

	tmp = ft_strjoin(*result, ft_var_expand(env_vars, "HOME"));
	if (tmp)
	{
		free(*result);
		*result = tmp;
	}
	token++;
	return (token);
}

// If $ is not expanded it will be joined to result by this function.
// Returns the address of the next character in the token.

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
