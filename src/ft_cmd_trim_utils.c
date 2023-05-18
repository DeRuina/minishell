/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_trim_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 08:30:56 by druina            #+#    #+#             */
/*   Updated: 2023/05/18 08:43:28 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Allocates and copies the token from address of start until address of end

char	*allocate_token(char *token_start, char *token_end)
{
	int		i;

	i = 0;
	while (&token_start[i] != &*token_end)
		i++;
	return (ft_substr(token_start, 0, i));
}
