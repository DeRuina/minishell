/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:16:50 by tspoof            #+#    #+#             */
/*   Updated: 2023/04/24 12:10:04 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char *argv[])
{
	// char	*line = "<Makefile cat | echo \"$PWD 'hola'\" ~/src | 'tr' -d / >outfile";
	// char	*str;
	(void)argv;

	printf("args: %d\n", argc);
	// str = ft_cmd_trim(line);
	return (0);
}
