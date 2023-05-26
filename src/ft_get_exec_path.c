/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_exec_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:58:42 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/26 16:17:51 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static char	*ft_full_path(char *path, char *cmd)
{
	char	*full_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	full_path = ft_strjoin(tmp, cmd);
	free(tmp);
	if (!full_path)
		exit (1);
	return (full_path);
}
// Checks if cmd is accessible and returns the full path of the executable
char	*ft_get_exec_path(t_vec env, char *cmd)
{
	char	*path;
	char	*full_path;
	char	**path_arr;
	int		i;

	path = ft_getenv(env, "PATH");
	path_arr = ft_split(path, ':');
	if (!path_arr)
		exit (1);
	if (access(cmd, X_OK | F_OK) == 0)
			return (free_2d(path_arr), cmd);
	i = 0;
	while (path_arr[i] != '\0')
	{
		full_path = ft_full_path(path_arr[i], cmd);
		if (access(full_path, X_OK | F_OK) == 0)
			return (free_2d(path_arr),free(cmd), full_path);
		if (full_path)
			free(full_path);
		i++;
	}
	free_2d(path_arr);
	return (cmd);
}
