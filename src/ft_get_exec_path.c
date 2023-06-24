/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_exec_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:58:42 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/24 15:57:18 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Adds the path and the cmd together

char	*ft_full_path(char *path, char *cmd)
{
	char	*full_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		exit(1);
	return (full_path);
}

// Checks absolute path

static int	ft_check_abs_path(char **path_arr, char *cmd)
{
	if (access(cmd, X_OK | F_OK) == 0)
	{
		if (path_arr)
			free_2d(path_arr);
		return (1);
	}
	return (0);
}

// Checks if cmd is accessible and returns the full path of the executable

char	*ft_get_exec_path(t_vec env, char *cmd)
{
	char	*path;
	char	*full_path;
	char	**path_arr;
	int		i;

	path_arr = NULL;
	path = ft_getenv(env, "PATH");
	if (path)
		path_arr = ft_split(path, ':');
	if (ft_check_abs_path(path_arr, cmd))
		return (cmd);
	i = 0;
	while (path_arr && path_arr[i] != 0)
	{
		full_path = ft_full_path(path_arr[i], cmd);
		if (access(full_path, X_OK | F_OK) == 0)
			return (free_2d(path_arr), free(cmd), full_path);
		if (full_path)
			free(full_path);
		i++;
	}
	if (path_arr)
		free_2d(path_arr);
	return (cmd);
}
