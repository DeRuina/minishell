/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:05:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/03 17:53:30 by tspoof           ###   ########.fr       */
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

	if (*str == '$' && *(str + 1))
		str++;
	key = ft_substr(str, 0, ft_var_end(str) - str);
	if (!key)
		return (NULL);
	if (ft_strchr(key, '$'))
		value = key;
	else
		value = ft_getenv(env_vars, key);
	free(key);
	return (value);
}

char	*ft_handle_expand(t_vec env_vars, char *str) // better name for str
{
	char	*expanded_var;
	char	*result;

	result = ft_strdup(""); // protection
	while (*str)
	{
		if (*str == '$')
		{
			expanded_var = ft_var_expand(env_vars, str);
			if (expanded_var)
				result = ft_strjoin(result, expanded_var); // leaks ft_strfjoin()?? && protection
			str = ft_var_end(str);
		}
		result = ft_strjoin(result, &(*str)); // leaks && protection
		if (*str)
			str++;
	}
	return (result);
}

void	ft_expand(t_vec env_vars, char **arr) // better name for arr
{
	// t_vec	result;
	char	*expanded_var;

	while (*arr)
	{
		if (!ft_strchr(*arr, '$'))
		{
			arr++;
			continue;
		}
		// if(vec_new(&result, 10, sizeof(char)) < 0)
		// 	exit (1);
		while (**arr)
		{
			if (**arr == '$')
			{
				expanded_var = ft_var_expand(env_vars, *arr);
				// if (vec_append(&result, &expanded_var) < 0)
				// 	exit (1);
				// vec_free(&expanded_var);
				// *arr = ft_var_end(*arr);
			}
			// if (vec_push(&result, *arr) < 0)
			// 	exit (1);
			if (**arr)
				(*arr)++;
		}
		// *arr = ft_strdup((char *)result.memory);
		// vec_free(&result);
		arr++;
	}
}

