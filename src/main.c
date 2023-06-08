/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:16:50 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/08 17:12:46 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

// builtin without pipe is executed in the parent and not in a child

static int	call_builtin(t_node *head, t_vec *envs)
{
	if (head->full_cmd)
	{
		if (is_builtin(head->full_cmd[0]) == EXIT && head->next == NULL)
		{
			free_nodes(head);
			free_envs(*envs);
			vec_free(envs);
			exit(EXIT_SUCCESS);
		}
		if (is_builtin(head->full_cmd[0]) == CD && head->next == NULL)
			return (ft_cd(head->full_cmd, envs), 1);
		if (is_builtin(head->full_cmd[0]) == EXPORT && head->next == NULL)
			return (ft_export(head->full_cmd, envs), 1);
		if (is_builtin(head->full_cmd[0]) == UNSET && head->next == NULL)
			return (ft_unset(envs, head->full_cmd[1]), 1);
		if (is_builtin(head->full_cmd[0]) == ENV && head->next == NULL)
			return (ft_env(*envs), 1);
		if (is_builtin(head->full_cmd[0]) == PWD && head->next == NULL)
			return (ft_pwd(), 1);
		if (is_builtin(head->full_cmd[0]) == ECHO && head->next == NULL)
			return (ft_echo(head->full_cmd), 1);
	}
	return (0);
}

// Parsing and executing builtins/commands

static void	minishell(char *line, t_vec *envs)
{
	t_node	*head;
	int		**pipe_nbr;

	head = ft_parse_args(line, *envs);
	if (!head)
		return ;
	if (call_builtin(head, envs) != 0)
	{
		free_nodes(head);
		return ;
	}
	pipe_nbr = piper(line, head);
	free_pipes(pipe_nbr, line);
	ft_executor(head, *envs);
	free_nodes(head);
}

// Looping our shell

int	main(int argc, char *argv[], char *env[])
{
	char	*line;
	t_vec	envs;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("Error: Arguments invalid\n", 0), 1);
	envs = ft_copyenv(env);
	while (1)
	{
		line = readline("RuiSpo: ");
		if (strlen(line) > 0)
			add_history(line);
		minishell(line, &envs);
		free(line);
	}
	return (0);
}
