/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:45:56 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/02 20:28:26 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//remove exit functions
#include "minishell.h"


char	*ft_getkey(char *str)
{
	return (ft_substr(str, 0, ft_strchr(str, '=') - str));
}

char	*ft_getvalue(char *str)
{
	char	*value_start;

	value_start = ft_strchr(str, '=');
	return (ft_substr(str, value_start - str + 1, ft_strlen(value_start)));
}

// Gets env string (eg. "HOME=/Users/tspoof") and stores it in an array as
// key value pair (eg key = "HOME", value = "/Users/tspoof").
int	ft_putenv(t_vec *envs_vec, char *str)
{
	t_env	*envs;
	t_env	env;
	size_t	i;

	if (!envs_vec)
		return (0);
	envs = (t_env *)envs_vec->memory;
	env.key = ft_getkey(str);
	env.value = ft_getvalue(str);
	if (!env.key || !env.value)
		exit (1);
	i = 0;
	while (i < envs_vec->len)
	{
		if (!ft_strncmp(envs[i].key, env.key, ft_strlen(envs[i].key)))
		{
			free(envs[i].value);
			envs[i].value = env.value;
			return (1);
		}
		i++;
	}
	if (vec_push(envs_vec, &env) < 0)
		exit (1);
	return (1);
}

// Returns the keys value
char	*ft_getenv(t_vec envs_vec, char *key)
{
	size_t	i;
	t_env	*envs;

	if (!envs_vec.memory || *key == '\0')
		return ("");
	envs = (t_env *)envs_vec.memory;
	i = 0;
	while (i < envs_vec.len)
	{
		if (!ft_strncmp(envs[i].key, key, ft_strlen(key)))
			return (envs[i].value);
		i++;
	}
	return ("");
}
