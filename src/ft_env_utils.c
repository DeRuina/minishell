/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 07:07:11 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/19 14:04:30 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

// Gets the key out of env string

char	*ft_getkey(char *str)
{
	return (ft_substr(str, 0, ft_strchr(str, '=') - str));
}

// Gets the value out of env string

char	*ft_getvalue(char *str)
{
	char	*value_start;

	value_start = ft_strchr(str, '=');
	if (!value_start)
		return (NULL);
	return (ft_substr(str, value_start - str + 1, ft_strlen(value_start)));
}

// Checks if key exists in the envs list and updates it's value

int	ft_env_update(t_env *envs, t_env env, int len)
{
	int		i;
	size_t	env_key_len;

	i = 0;
	env_key_len = ft_strlen(env.key);
	while (i < len)
	{
		if (ft_strlen(envs[i].key) != env_key_len)
		{
			i++;
			continue ;
		}
		if (!ft_strncmp(envs[i].key, env.key, env_key_len))
		{
			if (envs[i].key)
				free(env.key);
			if (envs[i].value)
				free(envs[i].value);
			envs[i].value = env.value;
			return (1);
		}
		i++;
	}
	return (0);
}

// Combines key and value to a string

char	*ft_env_to_str(t_env env)
{
	char	*env_str;
	int		key_len;
	int		val_len;

	key_len = ft_strlen(env.key);
	val_len = ft_strlen(env.value);
	env_str = ft_calloc(key_len + val_len + 2, sizeof(char));
	if (!env_str)
		ft_pexit("ft_calloc: ");
	ft_strlcpy(env_str, env.key, key_len + 1);
	ft_strlcpy(&(env_str[key_len]), "=", 2);
	ft_strlcpy(&(env_str[key_len + 1]), env.value, val_len + 1);
	return (env_str);
}

// Frees the envs

void	free_envs(t_vec envs)
{
	size_t	i;

	i = 0;
	while (i < envs.len)
	{
		free(((t_env *)envs.memory)[i].key);
		free(((t_env *)envs.memory)[i].value);
		i++;
	}
}
