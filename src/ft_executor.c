/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:13:48 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/06 23:06:13 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			g_exit_status = 0;

int	builtin_commands(char **cmd, t_vec envv)
{
	if (is_builtin(cmd[0]) == ECHO)
		ft_echo(cmd);
	if (is_builtin(cmd[0]) == CD)
		ft_cd(cmd, &envv);
	if (is_builtin(cmd[0]) == PWD)
		ft_pwd();
	if (is_builtin(cmd[0]) == EXPORT)
		ft_export(cmd, &envv);
	if (is_builtin(cmd[0]) == UNSET)
		ft_unset(&envv, cmd[1]);
	if (is_builtin(cmd[0]) == ENV)
		ft_env(envv);
	if (is_builtin(cmd[0]) == EXIT)
		ft_exit();
	exit(EXIT_SUCCESS);
}

int	ft_child(t_node *node, t_vec envv)
{
	char	**env;

	env = ft_strenv(envv);
	if (node->infile == -1)
		exit(EXIT_FAILURE);
	else if (node->infile != 0)
		if (dup2(node->infile, STDIN_FILENO) < 0)
			ft_pexit("ft_child: dup2");
	if (node->infile != 0)
		close(node->infile);
	if (node->outfile != 1)
		if (dup2(node->outfile, STDOUT_FILENO) < 0)
			ft_pexit("ft_child: dup2");
	if (node->outfile != 1)
		close(node->outfile);
	if (is_builtin(node->full_cmd[0]) != 0)
		builtin_commands(node->full_cmd, envv);
	else if (execve(node->full_cmd[0], node->full_cmd, env) < 0)
		ft_pexit(node->full_cmd[0]);
	return (0);
}

static void	ft_close(t_node *node)
{
	if (node->infile != 0)
		close(node->infile);
	if (node->outfile != 1)
		close(node->outfile);
}

static void	ft_wait(t_node *head)
{
	int	stat_loc;

	while (head)
	{
		wait(&stat_loc);
		if (WIFEXITED(stat_loc))
			g_exit_status = WEXITSTATUS(stat_loc);
		head = head->next;
	}
}

int	ft_executor(t_node *node, t_vec envv)
{
	t_node	*head;

	head = node;
	while (node)
	{
		node->pid = fork();
		if (node->pid == -1)
			ft_pexit("ft_executor: fork");
		if (node->pid == 0)
			ft_child(node, envv);
		ft_close(node);
		if (node->pid > 0)
			node = node->next;
	}
	ft_wait(head);
	return (0);
}
