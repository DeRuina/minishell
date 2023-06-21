/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 18:46:17 by druina            #+#    #+#             */
/*   Updated: 2023/06/21 09:08:59 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;
// Changing directories with only a relative or absolute path

void	ft_cd(char **full_cmd, t_vec *envs)
{
	char	*pwd;
	char	*old_pwd;

	old_pwd = get_path();
	ft_putenv_key(envs, ft_strdup("OLDPWD"), old_pwd);
	if (!full_cmd[1])
	{
		if (chdir(ft_expand_token(*envs, "~")) == -1)
			perror(full_cmd[1]);
	}
	else if (chdir(full_cmd[1]) == -1)
		perror(full_cmd[1]);
	pwd = get_path();
	ft_putenv_key(envs, ft_strdup("PWD"), pwd);
}

// Returns the current full path

char	*get_path(void)
{
	char	path[4096];

	if (getcwd(path, sizeof(path)) == NULL)
		perror("PWD :");
	return (ft_strdup(path));
}

// Prints the current path when called

void	ft_pwd(void)
{
	char	*pwd;

	pwd = get_path();
	printf("%s\n", pwd);
	free(pwd);
}

// Exits the program when called

int	ft_exit(char *status)
{
	int		stat_int;
	char	*stat_str;
	int		compare;

	if (!status)
		exit(EXIT_SUCCESS);
	stat_int = ft_atoi(status);
	stat_str = ft_itoa(stat_int);
	compare = ft_strncmp(status, stat_str, ft_strlen(status));
	free(stat_str);
	if (compare)
	{
		g_exit_status = 255;
		ft_putstr_fd("RuiSpo: ft_exit: ", 2);
		ft_putstr_fd(status, 2);
		ft_putendl_fd(" numeric argument required", 2);
		exit(255);
	}
	g_exit_status = ft_atoi(status);
	exit(ft_atoi(status));
}
