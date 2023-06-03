/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:46:17 by druina            #+#    #+#             */
/*   Updated: 2023/06/03 15:32:08 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void export_no_arg(t_vec *envs)
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


void ft_export(char **full_cmd, t_vec *envs)
{
	int i;
	char *key;
	char *value;

	i = 0;
	if (!full_cmd[1])
		return(export_no_arg(envs));
	while (full_cmd[1][i] != '=')
		i++;
	key = ft_substr(full_cmd[1], 0, i);
	value = ft_substr(full_cmd[1], ++i, ft_strlen(full_cmd[1]));
	ft_putenv_key(envs, key, value);
}

void	ft_cd(char **full_cmd, t_vec *envs)
{
	char	*pwd;
	char	*old_pwd;

	old_pwd = get_path();
	ft_putenv_key(envs, "OLDPWD", old_pwd);
	if (!full_cmd[1])
	{
		if (chdir(ft_expand_token(*envs, "~")) == -1)
			perror(full_cmd[1]);
	}
	else if (chdir(full_cmd[1]) == -1)
		perror(full_cmd[1]);
	pwd = get_path();
	ft_putenv_key(envs, "PWD", pwd);
}

char	*get_path(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) == NULL)
		perror("PWD :");
	return (ft_strdup(path));
}

void	ft_pwd(void)
{
	char	*pwd;

	pwd = get_path();
	printf("%s\n", pwd);
	free(pwd);
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

void	ft_exit(void)
{
	exit(EXIT_SUCCESS);
}

void	ft_echo(char **full_cmd)
{
	int	i;
	int	flag_n;

	i = 1;
	flag_n = 0;
	if (ft_strncmp(full_cmd[1], "-n", 2) == 0 && ft_strlen(full_cmd[1]) == 2)
	{
		flag_n = 1;
		i++;
	}
	while (1)
	{
		printf("%s", full_cmd[i]);
		i++;
		if (full_cmd[i] == 0)
			break ;
		printf(" ");
	}
	if (flag_n != 1)
		printf("\n");
}
