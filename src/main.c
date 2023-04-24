/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:16:50 by tspoof            #+#    #+#             */
/*   Updated: 2023/04/24 08:21:43 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line = "<Makefile cat | echo \"$PWD 'hola'\" ~/src | 'tr' -d / >outfile";
	char	*str;

	str = ft_cmd_trim(line);
	return (0);
}
