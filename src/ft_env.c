/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:45:56 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/01 16:02:48 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

// Gets env string (eg. "HOME=/Users/tspoof") and stores it in an array as
// key value pair (eg key = "HOME", value = "/Users/tspoof").
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
		exit (1);
	if (ft_env_update(envs, env, envs_vec->len))
		return (1);
	if (vec_push(envs_vec, &env) < 0)
		exit (1);
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
char	*ft_getenv(t_vec envs_vec, char *key)
{
	size_t	i;
	t_env	*envs;

	if (!envs_vec.memory || *key == '\0')
		return (NULL);
	envs = (t_env *)envs_vec.memory;
	i = 0;
	while (i < envs_vec.len)
	{
		if (!ft_strncmp(envs[i].key, key, ft_strlen(key)))
			return (envs[i].value);
		i++;
	}
	return (NULL);
}

// Copies the env from main to our own env vector
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
		ft_pexit("ft_calloc: ");
	i = 0;
	while (i < envs_vec.len)
	{
		envs_str[i] = ft_env_to_str(envs[i]);
		i++;
	}
	return (envs_str);
}
