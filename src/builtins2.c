/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:25:33 by druina            #+#    #+#             */
/*   Updated: 2023/06/05 19:37:16 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	export_no_arg(t_vec *envs)
{
	char	**env;
	char	**temp;

	env = ft_strenv((*envs));
	temp = env;
	while (*env)
	{
		printf("declare -x %s\n", *env);
		env++;
	}
	free_2d(temp);
}

void	ft_export(char **full_cmd, t_vec *envs)
{
	if (!full_cmd[1])
		return (export_no_arg(envs));
	ft_putenv(envs, full_cmd[1]);
}

void	ft_env(t_vec envs)
{
	char	**env;
	char	**temp;

	env = ft_strenv(envs);
	temp = env;
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
	free_2d(temp);
}

void	ft_unset(t_vec *envs, char *key)
{
	t_env	*envs_array;
	int		index;

	if (!key)
		return ;
	envs_array = ft_envfind(envs, key);
	index = ((unsigned char *)envs_array - envs->memory) / envs->elem_size;
	vec_remove(envs, index);
}
