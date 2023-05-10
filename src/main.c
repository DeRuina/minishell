/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:16:50 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/10 12:40:17 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

int	main(int argc, char *argv[]/*, char *env[]*/)
{
	char	*line = "< Makefile cat > ok > this | echo << yes >>yea | cat -e | ls -l";
	char	*temp;
	char	**str;
	char	**str1;
	// int		*fds;
	// line = readline("TERMINAL:");
	temp = line;
	(void)argv;
	argc = 0;


	// while (*env)
	// 	printf("%s\n", *env++);
	// printf("(%s)\n", getenv("PWD"));
	// chdir("src");
	// printf("(%s)\n", getenv("PWD"));
	// char buf[100];
	// getcwd(buf, 100);
	// printf("(%s)\n", buf);

	// printf("(%s)\n", getenv("PWD"));

	str = ft_cmd_trim(line);
	str1 = ft_split_operators(str);
	free_2d(str);
	str1 = ft_str_trim(str1);
	// fds = ft_fd_handler(str1);
	// if (fds != NULL)
	// {
	// printf("%d\n", fds[0]);
	// printf("%d\n", fds[1]);
	// }
	new_node(&str1);
	// free(fds);
	free_2d(str1);
	free(temp);

	return (0);
}
