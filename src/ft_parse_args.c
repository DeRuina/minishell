/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:03:56 by tspoof            #+#    #+#             */
/*   Updated: 2023/07/06 15:32:36 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

extern int	g_exit_status;

// Gets the node full_cmd

char	**get_node_cmd(char ***array)
{
	char	**answer;
	int		i;

	i = 0;
	if (***array == '\0')
		return (case_empty_cmd(array), NULL);
	if (cmd_len(*array) == 0)
		return (case_only_redirections(array), NULL);
	answer = ft_calloc((cmd_len(*array) + 1), sizeof(char *));
	if (!answer)
		return (NULL);
	while (**array && ***array != '|')
	{
		if (is_redir(array))
			(*array) += 2;
		else
		{
			answer[i++] = ft_strdup(*(*array));
			(*array)++;
		}
	}
	if (**array)
		(*array)++;
	return (answer);
}

// Finds the last token and checks if it's a redirection

static	int	find_last_token(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	i--;
	if (ft_strncmp(array[i], "<", 1) == 0 && ft_strlen(array[i]) == 1)
		return (1);
	if (ft_strncmp(array[i], ">", 1) == 0 && ft_strlen(array[i]) == 1)
		return (1);
	if (ft_strncmp(array[i], ">>", 2) == 0 && ft_strlen(array[i]) == 2)
		return (1);
	if (ft_strncmp(array[i], "<<", 2) == 0 && ft_strlen(array[i]) == 2)
		return (1);
	return (0);
}

// Checks if there is a redirection with no file afterwards

int	check_for_redirection_no_file_name(char **array)
{
	if (array[1] == NULL || *array[0] == '|')
	{
		if (ft_strncmp(array[0], "<", 1) == 0 && ft_strlen(array[0]) == 1)
			return (1);
		if (ft_strncmp(array[0], ">", 1) == 0 && ft_strlen(array[0]) == 1)
			return (1);
		if (ft_strncmp(array[0], ">>", 2) == 0 && ft_strlen(array[0]) == 2)
			return (1);
		if (ft_strncmp(array[0], "<<", 2) == 0 && ft_strlen(array[0]) == 2)
			return (1);
		if (ft_strncmp(array[0], "|", 1) == 0 && ft_strlen(array[0]) == 1)
			return (1);
	}
	if (find_last_token(array) == 1)
		return (1);
	return (0);
}

// Creates all the nodes recursively, adds full_cmd, infile, outfile, node.next

t_node	*new_node(char ***array, t_vec env, int *error_here_docs,
		int node_counter)
{
	t_node	*node;

	if (*array == NULL)
		return (NULL);
	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	if (check_for_redirection_no_file_name((*array)) == 1)
	{
		g_exit_status = 258;
		node->infile = REDIRECTION_NO_FILE;
		printf("RuiSpo: syntax error near unexpected token\n");
		return (node);
	}
	node = ft_fd_handler((*array), node, error_here_docs, node_counter);
	node->full_cmd = get_node_cmd(array);
	if (node->full_cmd != NULL && is_builtin(node->full_cmd[0]) == 0)
		node->full_cmd[0] = ft_get_exec_path(env, node->full_cmd[0]);
	if (!**array)
		node->next = NULL;
	else
		node->next = new_node(array, env, error_here_docs, ++node_counter);
	return (node);
}

// Parses the line and assigins the information to each node

t_node	*ft_parse_args(char *line, t_vec env)
{
	t_node		*head;
	char		**tokens;
	char		**temp;
	static int	*error_here_docs;

	error_here_docs = ft_calloc(num_of_pipes(line) + 1, sizeof(int));
	if (!error_here_docs)
		return (NULL);
	tokens = ft_cmd_trim(line);
	if (!tokens)
		return (NULL);
	ft_expand(env, tokens);
	tokens = ft_split_operators(tokens);
	tokens = ft_str_trim(tokens);
	temp = tokens;
	head = new_node(&tokens, env, error_here_docs, 0);
	if (temp)
		free_2d(temp);
	free(error_here_docs);
	return (head);
}
