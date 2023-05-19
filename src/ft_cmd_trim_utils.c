/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_trim_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 08:30:56 by druina            #+#    #+#             */
/*   Updated: 2023/05/19 08:31:42 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Allocates and copies the token from address of start until address of end

char	*allocate_token(char *token_start, char *token_end)
{
	int		len;
	char	*start;

	len = 0;
	start = token_start;
	while (&*token_start++ != &*token_end)
		len++;
	return (ft_substr(start, 0, len));
}
