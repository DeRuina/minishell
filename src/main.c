/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 12:16:50 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/19 14:03:44 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

// builtin without pipe is executed in the parent and not in a child

static int	call_builtin(t_node *head, t_vec *envs)
{
	if (head->full_cmd)
	{
		if (is_builtin(head->full_cmd[0]) == FT_EXIT && head->next == NULL)
		{
			free_nodes(head);
			free_envs(*envs);
			vec_free(envs);
			exit(EXIT_SUCCESS);
		}
		if (is_builtin(head->full_cmd[0]) == FT_CD && head->next == NULL)
			return (ft_cd(head->full_cmd, envs), 1);
		if (is_builtin(head->full_cmd[0]) == FT_EXPORT && head->next == NULL)
			return (ft_export(head->full_cmd, envs), 1);
		if (is_builtin(head->full_cmd[0]) == FT_UNSET && head->next == NULL)
			return (ft_unset(envs, head->full_cmd[1]), 1);
		if (is_builtin(head->full_cmd[0]) == FT_ENV && head->next == NULL)
			return (ft_env(*envs), 1);
		if (is_builtin(head->full_cmd[0]) == FT_PWD && head->next == NULL)
			return (ft_pwd(), 1);
		if (is_builtin(head->full_cmd[0]) == FT_ECHO && head->next == NULL)
			return (ft_echo(head->full_cmd, head->outfile), 1);
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
	if (call_builtin(head, envs) != 0
		|| redirection_no_file_in_nodes(head) == 1)
	{
		free_nodes(head);
		return ;
	}
	pipe_nbr = piper(line, head);
	free_pipes(pipe_nbr, line);
	ft_executor(head, *envs);
	free_nodes(head);
}



int	main(int argc, char *argv[], char *env[])
{
	char			*line;
	t_vec			envs;
	struct termios	termios;

	(void)argv;
	if (argc != 1)
		return (ft_putstr_fd("Error: Arguments invalid\n", 0), 1);
	welcome_message();
	init_signals();
	envs = ft_copyenv(env);
	increase_shlvl(&envs);
	tcgetattr(0, &termios);
	while (1)
	{
		close_echo_ctrl(&termios);
		line = readline("RuiSpo: ");
		open_echo_ctrl(&termios);
		if (!line)
			exit(0);
		if (ft_strlen(line) > 0)
			add_history(line);
		minishell(line, &envs);
		free(line);
	}
	return (0);
}
