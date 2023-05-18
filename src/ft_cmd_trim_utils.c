/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_trim_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 08:30:56 by druina            #+#    #+#             */
/*   Updated: 2023/05/18 08:31:20 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Allocates and copies the token from address of start until address of end

char	*allocate_token(char *token_start, char *token_end)
{
	char	*token;
	int		i;

	i = 0;
	while (&token_start[i] != &*token_end)
		i++;
	token = (char *)malloc(sizeof(char) * (i + 1));
	if (!token)
		return (NULL);
	token[i] = '\0';
	i = 0;
	while (&token_start[i] != &*token_end)
	{
		token[i] = token_start[i];
		i++;
	}
	return (token);
}
