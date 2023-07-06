/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tspoof <tspoof@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 17:13:48 by tspoof            #+#    #+#             */
/*   Updated: 2023/07/06 16:12:55 by tspoof           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

// If command is builtin, we execute

int	builtin_commands(char **cmd, t_vec envv, char *filename)
{
	if (is_builtin(cmd[0]) == FT_ECHO)
		ft_echo(cmd, STDOUT_FILENO, filename);
	if (is_builtin(cmd[0]) == FT_CD)
		ft_cd(cmd, &envv);
	if (is_builtin(cmd[0]) == FT_PWD)
		ft_pwd();
	if (is_builtin(cmd[0]) == FT_EXPORT)
		ft_export(cmd, &envv);
	if (is_builtin(cmd[0]) == FT_UNSET)
		ft_unset(&envv, cmd[1]);
	if (is_builtin(cmd[0]) == FT_ENV)
		ft_env(envv);
	if (is_builtin(cmd[0]) == FT_EXIT)
	{
		if (cmd[1] && cmd[2])
		{
			g_exit_status = 1;
			ft_putstr_fd("RuiSpo: ft_exit: too many arguments", 2);
		}
		ft_exit(cmd[1]);
	}
	exit(EXIT_SUCCESS);
}

//Changes the STDIN & STDOUT of the process to be the infile and outfile.
// executes the commands using execve.

int	ft_child(t_node *node, t_vec envv)
{
	char	**env;

	if (node->infile == -1)
		exit(EXIT_FAILURE);
	env = ft_strenv(envv);
	if (node->infile != 0)
		if (dup2(node->infile, STDIN_FILENO) < 0)
			ft_pexit("ft_child: dup2", 42);
	if (node->outfile != 1)
		if (dup2(node->outfile, STDOUT_FILENO) < 0)
			ft_pexit("ft_child: dup2", 42);
	if (node->infile != 0)
		close(node->infile);
	if (node->outfile != 1)
		close(node->outfile);
	if (is_builtin(node->full_cmd[0]) != FT_NONE)
		builtin_commands(node->full_cmd, envv, node->filename);
	if (execve(node->full_cmd[0], node->full_cmd, env) < 0)
		ft_pexit(node->full_cmd[0], 127);
	return (1);
}

// Closes the infile and outfile in the parent

static void	ft_close(t_node *node)
{
	if (node->infile != 0)
		close(node->infile);
	if (node->outfile != 1)
		close(node->outfile);
}

// Gets the exit status

static void	ft_wait(t_node *head)
{
	int	stat_loc;
	int	signal;
	int	once;

	once = 0;
	while (head)
	{
		waitpid(head->pid, &stat_loc, WUNTRACED);
		if (WIFEXITED(stat_loc))
			g_exit_status = WEXITSTATUS(stat_loc);
		else if (WIFSIGNALED(stat_loc) && once == 0)
		{
			once++;
			signal = WTERMSIG(stat_loc);
			if (signal == 3)
				printf("Quit: %d", signal);
			printf("\n");
			g_exit_status = signal + 128;
		}
		head = head->next;
	}
}

// Loops through the nodes, forks and enters child processes

int	ft_executor(t_node *node, t_vec envv)
{
	t_node	*head;

	head = node;
	signal(SIGINT, sig_ctrl_c_exec);
	while (node)
	{
		signal(SIGINT, SIG_IGN);
		node->pid = fork();
		if (node->pid == -1)
			ft_pexit("ft_executor: fork", 42);
		if (node->pid == 0)
		{
			signal(SIGQUIT, SIG_DFL);
			signal(SIGINT, SIG_DFL);
			ft_child(node, envv);
		}
		ft_close(node);
		if (node->pid > 0)
			node = node->next;
	}
	ft_wait(head);
	signal(SIGINT, sig_ctrl_c);
	return (0);
}
