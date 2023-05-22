/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:45:56 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/22 07:59:23 by tspoof           ###   ########.fr       */
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
