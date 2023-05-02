/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:05:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/02 20:28:32 by tspoof           ###   ########.fr       */
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
		if (!ft_isalpha(*str))
			break;
		str++;
	}
	return (str);
}

t_vec	ft_var_expand(t_vec env_vars, char *str)
{
	t_vec	result;
	char	*key;
	char	*key_start;
	char	*value;

	if (*str == '$')
		str++;
	key_start = str;
	key = ft_substr(key_start, 0, ft_var_end(str) - key_start);
	if (!key)
		exit (1);
	value = ft_getenv(env_vars, key);
	free(key);
	if (vec_from(&result, value, ft_strlen(value), sizeof(char)) < 0)
		exit (1);
	return (result);
}

void	ft_expand(t_vec env_vars, char **arr)
{
	char	*var_start;
	t_vec	result;
	t_vec	expanded_var;

	while (*arr)
	{
		var_start = ft_strchr(*arr, '$');
		if (!var_start)
		{
			arr++;
			continue;
		}
		if(vec_new(&result, 10, sizeof(char)) < 0)
			exit (1);
		while (**arr)
		{
			if (**arr == '$')
			{
				expanded_var = ft_var_expand(env_vars, *arr);
				if (vec_append(&result, &expanded_var) < 0)
					exit (1);
				vec_free(&expanded_var);
				*arr = ft_var_end(*arr);
			}
			if (vec_push(&result, *arr) < 0)
				exit (1);
			(*arr)++;
		}
		*arr = ft_strdup((char *)result.memory);
		vec_free(&result);
		arr++;
	}
}

