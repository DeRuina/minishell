/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:16:50 by tspoof            #+#    #+#             */
/*   Updated: 2023/04/20 15:17:47 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*line;
		char *str;

	printf("WELCOME TO SPOINA SHELL\n");
	line = readline("terminal:");
	while (1)
	{
		str = tokenizer(&line);
		printf("%s\n", str);
		// free(str);
		if (line == NULL)
			break ;
	}
	return (0);
}
