/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:05:30 by tspoof            #+#    #+#             */
/*   Updated: 2023/04/28 19:51:16 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// check if $ and then if it's followed by a key
// ~

// echo $ -> $
// echo $not_exist -> nothing

void	ft_expand(t_vec envs, char **line)
{
	char	*var_start;

	while (*line)
	{
		var_start = ft_strchr(*line, '$');
		if (var_start)
			ft_getenv(envs, var_start + 1);
		line++;
	}
}
