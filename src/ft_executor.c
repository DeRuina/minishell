/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:13:48 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/01 12:47:49 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int builtin_commands(char **cmd, t_vec envv)
{

	if (is_builtin(cmd[0]) == 1)
		ft_echo(cmd);
	// if (is_builtin(cmd[0]) == 2)
	// 	ft_cd(cmd, envv);
	if (is_builtin(cmd[0]) == 3)
		ft_pwd();
	// if (is_builtin(cmd[0]) == 4)
	// 	ft_export(cmd);
	// if (is_builtin(cmd[0]) == 5)
	// 	ft_unset(cmd);
	// if (is_builtin(cmd[0]) == 6)
	// 	ft_env(cmd);
	if (is_builtin(cmd[0]) == 7)
		ft_exit();
	exit(EXIT_SUCCESS);
}

int	ft_child(t_node *node, t_vec envv)
{
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
	else if (execve(node->full_cmd[0], node->full_cmd, ft_strenv(envv)) < 0)
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
			perror("ft_executor: fork");
		if (node->pid == 0)
			ft_child(node, envv);
		ft_close(node);
		if (node->pid > 0)
		{
			printf("infile - %d\n", node->infile);
			printf("outfile - %d\n", node->outfile);
			printf("cmd - %s\n", node->full_cmd[0]);
			node = node->next;
		}
	}
	ft_wait(head);
	return (0);
}
