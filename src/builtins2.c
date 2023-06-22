/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 11:25:33 by druina            #+#    #+#             */
/*   Updated: 2023/06/22 14:58:00 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

// Prints the declare list when export is called with no arguments

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

// Adds a variable to the environment

void	ft_export(char **full_cmd, t_vec *envs)
{
	if (!full_cmd[1])
		return (export_no_arg(envs));
	ft_putenv(envs, full_cmd[1]);
}

// Prints the environment

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

// Takes the variable and deletes it from the environment

void	ft_unset(t_vec *envs, char *key)
{
	t_env	*envs_array;
	int		index;

	if (!key)
		return ;
	envs_array = ft_envfind(envs, key);
	index = ((unsigned char *)envs_array - envs->memory) / envs->elem_size;
	if (envs_array && envs_array->key)
		free(envs_array->key);
	if (envs_array && envs_array->value)
		free(envs_array->value);
	if (envs_array)
		vec_remove(envs, index);
}
