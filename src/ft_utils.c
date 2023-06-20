/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:03:31 by tspoof            #+#    #+#             */
/*   Updated: 2023/06/20 14:38:39 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Checks if the command is a builtin

int	is_builtin(char *cmd)
{
	size_t	len;

	if (!cmd)
		return (-1);
	len = ft_strlen(cmd);
	if (len == ft_strlen("echo") && ft_strncmp("echo", cmd, len) == 0)
		return (FT_ECHO);
	else if (len == ft_strlen("cd") && ft_strncmp("cd", cmd, len) == 0)
		return (FT_CD);
	else if (len == ft_strlen("pwd") && ft_strncmp("pwd", cmd, len) == 0)
		return (FT_PWD);
	else if (len == ft_strlen("export") && ft_strncmp("export", cmd, len) == 0)
		return (FT_EXPORT);
	else if (len == ft_strlen("unset") && ft_strncmp("unset", cmd, len) == 0)
		return (FT_UNSET);
	else if (len == ft_strlen("env") && ft_strncmp("env", cmd, len) == 0)
		return (FT_ENV);
	else if (len == ft_strlen("exit") && ft_strncmp("exit", cmd, len) == 0)
		return (FT_EXIT);
	return (FT_NONE);
}

// Loops through the nodes and frees them

void	free_nodes(t_node *node)
{
	t_node	*temp;

	while (node->next != NULL)
	{
		temp = node;
		if (node->full_cmd)
			free_2d(node->full_cmd);
		node = node->next;
		free(temp);
	}
	if (node->full_cmd)
		free_2d(node->full_cmd);
	free(node);
}

// Uses perror with the message and exits

void	ft_pexit(char *error_msg)
{
	perror(error_msg);
	exit(EXIT_FAILURE);
}

// Welcome message to our shell

void	welcome_message(void)
{
	printf("                  __        __        __            __   __\n");
	printf("           _____ |__| ____ |__| _____|  |__   ____ |  | |  |\n");
	printf("          /     \\|  |/    \\|  |/  ___/  |  \\_/ __ \\|  | |  |\n");
	printf("         |  Y Y  \\  |   |  \\  |\\___ \\|   Y  \\  ___/|  |_|  |__\n");
	printf("         |__|_|  /__|___|  /__/____  >___|  /\\___  >____/____/\n");
	printf("               \\/        \\/        \\/     \\/     \\/ \n\n");
	printf("                               ┌┐ ┬ ┬                   \n");
	printf("                               ├┴┐└┬┘              \n");
	printf("                               └─┘ ┴               \n");
	printf("                  ╔╦╗┌─┐┌─┐┌┬┐┬ ┬  ┌─┐┌─┐┌─┐┌─┐┌─┐\n");
	printf("                   ║ ├┤ ├┤ ││││ │  └─┐├─┘│ ││ │├┤ \n");
	printf("                   ╩ └─┘└─┘┴ ┴└─┘  └─┘┴  └─┘└─┘└  \n");
	printf("                                 ┬              \n");
	printf("                                ┌┼─             \n");
	printf("                                └┘               \n");
	printf("                   ╔╦╗┌─┐┌─┐┌┐┌  ╦═╗┬ ┬┬┌┐┌┌─┐ \n");
	printf("                    ║║├┤ ├─┤│││  ╠╦╝│ │││││├─┤ \n");
	printf("                   ═╩╝└─┘┴ ┴┘└┘  ╩╚═└─┘┴┘└┘┴ ┴ \n");
}

// loops through the nodes and checks if there is redirection with no file

int	redirection_no_file_in_nodes(t_node *head)
{
	while (head->next != NULL)
	{
		if (head->infile == REDIRECTION_NO_FILE)
			return (1);
		head = head->next;
	}
	if (head->next == NULL && head->infile == REDIRECTION_NO_FILE)
		return (1);
	return (0);
}
