/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:26:23 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/07 14:30:01 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	ft_tmp_to_result(char **result, char **tmp)
{
	if (*tmp)
	{
		free(*result);
		*result = *tmp;
	}
}

// gets the address of the end of the variable string
char	*ft_var_end(char *str)
{
	if (*str == '$')
		str++;
	while (*str)
	{
		if (!ft_isalnum(*str) && *str != '?')
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
		value = ft_strdup(key);
	else
		value = ft_getenv(env_vars, key);
	free(key);
	return (value);
}

int	ft_should_expand_tilde(char *token, char *token_init)
{
	if (token == token_init && (*(token + 1) == ' ' || *(token + 1) == '\0'))
		return (1);
	if ((*(token + 1) == ' ' || *(token + 1) == '\0') && *(token - 1) == ' ')
		return (1);
	return (0);
}
