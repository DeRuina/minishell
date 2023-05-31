/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: druina <druina@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 19:03:56 by tspoof            #+#    #+#             */
/*   Updated: 2023/05/31 07:28:22 by druina           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

void	case_only_redirections(char ***array)
{
	while (*(*array) && **(*array) != '|' && **(*array) != '\0')
		(*array)++;
	if (*(*array))
		(*array)++;
}

int	cmd_len(char **array)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (array[i] && ft_strncmp(array[i], "|", 1) != 0)
	{
		if (ft_strncmp(array[i], "<", 1) == 0 || ft_strncmp(array[i], ">",
				1) == 0)
			i += 2;
		else
		{
			len++;
			i++;
		}
	}
	return (len);
}

char	**get_node_cmd(char ***array, char ***temp)
{
	char	**answer;
	int		i;

	i = 0;
	temp = array;
	if (cmd_len(*array) == 0)
		return (case_only_redirections(array), NULL);
	answer = (char **)malloc(sizeof(char *) * (cmd_len(*array) + 1));
	if (!answer)
		return (NULL);
	while (*(*array) && **(*array) != '|' && **(*array) != '\0')
	{
		if (ft_strncmp(*(*array), "<", 1) == 0 || ft_strncmp(*(*array), ">",
				1) == 0)
			(*array) += 2;
		else
		{
			answer[i++] = ft_strdup(*(*array));
			(*array)++;
		}
	}
	if (*(*array))
		(*array)++;
	answer[i] = 0;
	return (answer);
}

t_node	*new_node(char ***array, t_vec env, int *error_here_docs, int node_counter)
{
	t_node	*node;
	if (array == NULL)
		return (NULL);
	node = (t_node *)ft_calloc(1, sizeof(t_node));
	if (!node)
		return (NULL);
	node = ft_fd_handler((*array), node, error_here_docs, node_counter);
	node->full_cmd = get_node_cmd(array, array);
	if (node->full_cmd != NULL /*&& is_builtin(node->full_cmd[0]) != 1*/)
		node->full_cmd[0] = ft_get_exec_path(env, node->full_cmd[0]);
	if (!**array)
		node->next = NULL;
	else
		node->next = new_node(array, env, error_here_docs, ++node_counter);
	return (node);
}

t_node	*ft_parse_args(char *line, t_vec env)
{
	t_node		*head;
	char		**tokens;
	char		**temp;
	static int *error_here_docs;

	error_here_docs = ft_calloc(num_of_pipes(line) + 1, sizeof(int));
	if (!error_here_docs)
		return (NULL);
	tokens = ft_cmd_trim(line);
	if (!tokens)
		return(NULL);
	ft_expand(env, tokens);
	tokens = ft_split_operators(tokens);
	tokens = ft_str_trim(tokens);
	temp = tokens;
	head = new_node(&tokens, env, error_here_docs, 0);
	free_2d(temp);
	free (error_here_docs);
	return (head);
}
