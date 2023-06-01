/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:16:50 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/01 14:54:20 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char *line, char *env[])
{
	t_vec	envs;
	t_node	*head;
	int		**pipe_nbr;

	envs = ft_copyenv(env);
	head = ft_parse_args(line, envs);
	if (!head)
		return ;
	if (is_builtin(head->full_cmd[0]) == 7 && head->next == NULL)
		exit(EXIT_SUCCESS);
	if (is_builtin(head->full_cmd[0]) == 2 && head->next == NULL)
		ft_cd(head->full_cmd, &envs);
	pipe_nbr = piper(line, head);
	ft_executor(head, envs);
	free_nodes(head);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	int		wait_times;
	int		i;

	if (argc != 1)
		return (ft_putstr_fd("Error: Arguments invalid\n", 0), 1);
	(void)argv;
	i = -1;
	while (1)
	{
		printf("TERMINAL:");
		line = readline(NULL);
		if (strlen(line) > 0)
				add_history(line);
		minishell(line, env);
		wait_times = num_of_pipes(line);
		free(line);
		while (++i <= wait_times)
			wait(NULL);
	}
	return (0);
}
