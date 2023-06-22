/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:45:56 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/22 14:57:52 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

// Gets env string (eg. "HOME=/Users/tspoof") as a parameter and stores it in
// an array as key value pair (eg key = "HOME", value = "/Users/tspoof").

int	ft_putenv(t_vec *envs_vec, char *str)
{
	t_env	*envs;
	t_env	env;

	if (!envs_vec)
		return (0);
	envs = (t_env *)envs_vec->memory;
	env.key = ft_getkey(str);
	env.value = ft_getvalue(str);
	if (!env.key || !env.value)
		return (1);
	if (ft_env_update(envs, env, envs_vec->len))
		return (1);
	if (vec_push(envs_vec, &env) < 0)
		ft_pexit("ft_putenv: vec_push", 42);
	return (1);
}

// Gets key (eg. "HOME") and value (eg. "/Users/tspoof") and stores it in an
// array as key value pair (eg key = "HOME", value = "/Users/tspoof").

int	ft_putenv_key(t_vec *envs_vec, char *key, char *value)
{
	t_env	*envs;
	t_env	env;

	if (!envs_vec)
		return (0);
	envs = (t_env *)envs_vec->memory;
	env.key = key;
	env.value = value;
	if (ft_env_update(envs, env, envs_vec->len))
		return (1);
	if (vec_push(envs_vec, &env) < 0)
		exit (1);
	return (1);
}

// Returns the keys value
// eg. "HOME" will return "/Users/tspoof"

char	*ft_getenv(t_vec envs_vec, char *key)
{
	t_env	*envs;

	envs = ft_envfind(&envs_vec, key);
	if (!envs)
		return (NULL);
	return (envs->value);
}

// Copies the env given from main to our own env vector

t_vec	ft_copyenv(char *env[])
{
	t_vec	envs;

	if (vec_new(&envs, 10, sizeof(t_env)) < 0)
		exit (1);
	while (*env)
	{
		if (ft_putenv(&envs, *env) < 0)
			exit (0);
		env++;
	}
	return (envs);
}

// Turns env vector to array of env strings (HOME=/Users/tspoof).

char	**ft_strenv(t_vec envs_vec)
{
	t_env	*envs;
	char	**envs_str;
	size_t	i;

	envs = (t_env *)envs_vec.memory;
	envs_str = ft_calloc(envs_vec.len + 1, sizeof(char *));
	if (!envs_str)
		ft_pexit("ft_calloc: ", 42);
	i = 0;
	while (i < envs_vec.len)
	{
		envs_str[i] = ft_env_to_str(envs[i]);
		i++;
	}
	return (envs_str);
}
