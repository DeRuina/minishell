/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:05:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/04/29 16:33:32 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Need more research for ~. Like echo ~SHELL

// $$ ???
// echo $not_exist -> nothing ??
// $NOTEXISTING$ -> $

void	ft_check_key(char *key)
{
	(void)key;
}

void	ft_expand(t_vec envs, char **line)
{
	char	*var_start;

	while (*line)
	{
		var_start = ft_strchr(*line, '$');
		if (var_start && *(var_start + 1) != ' ' && *(var_start + 1) != '\0')
			*line = ft_getenv(envs, var_start + 1);
		line++;
	}
}
