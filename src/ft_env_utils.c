/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 07:07:11 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/22 07:07:59 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"


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

int	ft_env_update(t_env *envs, t_env env, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (!ft_strncmp(envs[i].key, env.key, ft_strlen(envs[i].key)))
		{
			free(envs[i].value);
			envs[i].value = env.value;
			return (1);
		}
		i++;
	}
	return (0);
}
