/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 11:45:56 by tspoof            #+#    #+#             */
/*   Updated: 2023/04/26 19:57:54 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getkey(char *str)
{
	char	*str_start;

	str_start = str;
	return (ft_substr(str, 0, ft_strchr(str, '=') - str_start));
}

char	*ft_getvalue();

void	ft_putenv(t_env **envs, char *str)
{
	while (*envs)
	{
		if ((*envs)->key == "")
		envs++;
	}
}
