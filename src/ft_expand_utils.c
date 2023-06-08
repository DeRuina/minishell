/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 17:26:23 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/08 17:14:35 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

// gets the address of the character after the end of the variable

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

// Expands the $variable. Also handles that the $ is the only character or that
// the token is $$

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

// Checks the conditions when ~ should be expanded to HOME
// Returns true if:
// - ~ is the first char in the token and next char is an empty space or a NULL
// - The next char is ' ' or a NULL and previus char is an empty space.

int	ft_should_expand_tilde(char *token, char *token_first_char)
{
	if (token == token_first_char
		&& (*(token + 1) == ' ' || *(token + 1) == '\0'))
		return (1);
	if ((*(token + 1) == ' ' || *(token + 1) == '\0') && *(token - 1) == ' ')
		return (1);
	return (0);
}
