/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:29:47 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/08 15:59:14 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

// Finds and returns the address of given key in the envs list
t_env	*ft_envfind(t_vec *envs_vec, char *key)
{
	size_t	i;
	t_env	*envs;
	int		key_len;

	if (!(*envs_vec).memory || *key == '\0')
		return (NULL);
	envs = (t_env *)envs_vec->memory;
	i = 0;
	key_len = ft_strlen(key);
	while (i < envs_vec->len)
	{
		if ((int)ft_strlen(envs[i].key) != key_len)
		{
			i++;
			continue ;
		}
		if (!ft_strncmp(envs[i].key, key, key_len))
			return (envs + i);
		i++;
	}
	return (NULL);
}
