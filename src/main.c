/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:16:50 by tspoof            #+#    #+#             */
/*   Updated: 2023/04/25 11:37:12 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d(char **str)
{
	char	**temp;

	temp = str;
	while (*str)
	{
		free(*str);
		str++;
	}
	free(temp);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*line = "<Makefile cat | echo \"$PWD 'hola'\" ~/src | 'tr' -d / >outfile";
	char	**str;
	(void)argv;
	argc = 0;


	while (*env)
		printf("%s\n", *env++);
	printf("(%s)\n", getenv("PWD"));
	chdir("src");
	printf("(%s)\n", getenv("PWD"));
	char buf[100];
	getcwd(buf, 100);
	printf("(%s)\n", buf);

	printf("(%s)\n", getenv("PWD"));

	str = ft_cmd_trim(line);
	free_2d(str);

	return (0);
}
